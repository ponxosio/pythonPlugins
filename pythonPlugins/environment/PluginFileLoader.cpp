#include "PluginFileLoader.h"

using namespace std;

PluginFileLoader *PluginFileLoader::m_pInstance = NULL;
std::string PluginFileLoader::pluginDir = Utils::getCurrentDir() + "\\" + PLUGIN_FOLDER;


PluginFileLoader::PluginFileLoader()
{
    checkDirectory(this->pluginDir, "*");
}


PluginFileLoader::~PluginFileLoader()
{

}

void PluginFileLoader::setPluginDir(const std::string & pluginDir)
{
    PluginFileLoader::pluginDir = pluginDir;
}


bool PluginFileLoader::checkDirectory(string path, string mask)
{   
    QDirIterator it(QString::fromUtf8(path.c_str()), QStringList() << QString::fromUtf8(mask.c_str()), QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        std::string file = it.next().toUtf8().constData();
        checkFile(file);
    }
    return true;
}

void PluginFileLoader::checkFile(std::string path) {
	if (Utils::ends_with(path, ".py")) {
        ifstream inFile(path);
		while (!inFile.eof()) {
			string line;
			getline(inFile, line);
			if (Utils::starts_with(line, "class")) {
				size_t posOpen = line.find("(");
                size_t posClose = line.find(")");

                string className = line.substr(5, posOpen - 5);
				boost::algorithm::trim(className);

                string superClass = line.substr(posOpen + 1, (posClose - 1) - posOpen);
                boost::algorithm::trim(superClass);
				
				this->namePathMap.insert(make_pair(className, path));
                this->nameSuperclassMap.insert(make_pair(className, superClass));
			}
		}
	}
}

std::string PluginFileLoader::getPath(std::string name) throw (std::invalid_argument) {
	auto it = namePathMap.find(name);
	if (it != namePathMap.end()) {
		return it->second;
	}
	else {
		throw(std::invalid_argument("key " + name + " does not exists"));
	}
}

std::string PluginFileLoader::getSuperClass(std::string name) throw (std::invalid_argument) {
    auto it = nameSuperclassMap.find(name);
    if (it != nameSuperclassMap.end()) {
        return it->second;
    }
    else {
        throw(std::invalid_argument("key " + name + " does not exists"));
    }
}

std::vector<std::string> PluginFileLoader::getAllNames() {
    vector<string> keys;
    keys.reserve(namePathMap.size());

    for (auto kv: namePathMap) {
        keys.push_back(kv.first);
    }
    return keys;
}

std::string PluginFileLoader::toText() {
    std::stringstream stream;
    for (auto it = namePathMap.begin(); it != namePathMap.end(); ++it) {
        stream << "name: " << it->first << ", second: " << it->second << ";";
	}

    for (auto it = nameSuperclassMap.begin(); it != nameSuperclassMap.end(); ++it) {
        stream << "name: " << it->first << ", superClass: " << it->second << ";";
    }
    return stream.str();
}
