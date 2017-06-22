#ifndef PLUGINFILELOADER_H
#define PLUGINFILELOADER_H

#define PLUGIN_FOLDER "pythonPlugins"

#include <fstream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

//Qt
#include <QDirIterator>

//boost
#include <boost/algorithm/string.hpp>

//local
#include <utils/Utils.h>

#include <pythonPlugins/pythonplugins_global.h>

class PLUGINFILELOADER_EXPORT PluginFileLoader
{
public:
	static PluginFileLoader* GetInstance() {
		if (!m_pInstance)
			m_pInstance = new PluginFileLoader();
		return m_pInstance;
	}

	static void freeCommandInterface() {
		if (m_pInstance) {
			delete m_pInstance;
		}
	}

    static void setPluginDir(const std::string & pluginDir);

	virtual ~PluginFileLoader();

	std::string getPath(std::string name) throw (std::invalid_argument);
    std::string getSuperClass(std::string name) throw (std::invalid_argument);
    std::vector<std::string> getAllNames();

    std::string toText();

protected:
    static std::string pluginDir;

	std::unordered_map<std::string, std::string> namePathMap;
    std::unordered_map<std::string, std::string> nameSuperclassMap;

	bool checkDirectory(string path, string mask);
    void checkFile(std::string path);

private:
	PluginFileLoader();
    PluginFileLoader(const PluginFileLoader&) {}
    PluginFileLoader& operator=(const PluginFileLoader& com) {return PluginFileLoader(com);}

	static PluginFileLoader *m_pInstance;
};

#endif // PLUGINFILELOADER_H

