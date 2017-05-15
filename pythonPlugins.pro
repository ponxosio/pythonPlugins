#-------------------------------------------------
#
# Project created by QtCreator 2017-05-15T18:29:36
#
#-------------------------------------------------

# ensure one "debug_and_release" in CONFIG, for clarity...
debug_and_release {
    CONFIG -= debug_and_release
    CONFIG += debug_and_release
}
    # ensure one "debug" or "release" in CONFIG so they can be used as
    #   conditionals instead of writing "CONFIG(debug, debug|release)"...
CONFIG(debug, debug|release) {
    CONFIG -= debug release
    CONFIG += debug
}
CONFIG(release, debug|release) {
    CONFIG -= debug release
    CONFIG += release
}

QT       -= gui

TARGET = pythonPlugins
TEMPLATE = lib

DEFINES += PYTHONPLUGINS_LIBRARY

SOURCES += pythonPlugins/pythonplugins.cpp \
    pythonPlugins/environment/PluginFileLoader.cpp \
    pythonPlugins/environment/PythonEnvironment.cpp \
    pythonPlugins/actuators/centrifugationpythonproduct.cpp \
    pythonPlugins/actuators/electrophoresispythonproduct.cpp \
    pythonPlugins/actuators/fluorescencesensorpythonproduct.cpp \
    pythonPlugins/actuators/heaterpythonproduct.cpp \
    pythonPlugins/actuators/ligthpythonproduct.cpp \
    pythonPlugins/actuators/luminiscencesensorpythonproduct.cpp \
    pythonPlugins/actuators/odsensorpythonproduct.cpp \
    pythonPlugins/actuators/pumppythonproduct.cpp \
    pythonPlugins/actuators/shakepythonproduct.cpp \
    pythonPlugins/actuators/stirerpythonproduct.cpp \
    pythonPlugins/actuators/temperaturesensorpythonproduct.cpp \
    pythonPlugins/actuators/valvepythonproduct.cpp \
    pythonPlugins/actuators/volumensensorpythonproduct.cpp \
    pythonPlugins/actuators/pythonpluginabstractfactory.cpp

HEADERS += pythonPlugins/pythonplugins.h\
        pythonPlugins/pythonplugins_global.h \
    pythonPlugins/environment/PluginFileLoader.h \
    pythonPlugins/environment/PythonEnvironment.h \
    pythonPlugins/actuators/centrifugationpythonproduct.h \
    pythonPlugins/actuators/electrophoresispythonproduct.h \
    pythonPlugins/actuators/fluorescencesensorpythonproduct.h \
    pythonPlugins/actuators/heaterpythonproduct.h \
    pythonPlugins/actuators/ligthpythonproduct.h \
    pythonPlugins/actuators/luminiscencesensorpythonproduct.h \
    pythonPlugins/actuators/odsensorpythonproduct.h \
    pythonPlugins/actuators/pumppythonproduct.h \
    pythonPlugins/actuators/shakepythonproduct.h \
    pythonPlugins/actuators/stirerpythonproduct.h \
    pythonPlugins/actuators/temperaturesensorpythonproduct.h \
    pythonPlugins/actuators/valvepythonproduct.h \
    pythonPlugins/actuators/volumensensorpythonproduct.h \
    pythonPlugins/actuators/pythonpluginabstractfactory.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

debug {
    QMAKE_POST_LINK=X:\pythonPlugins\pythonPlugins\setDLL.bat $$shell_path($$OUT_PWD/debug) debug

    INCLUDEPATH += X:\utils\dll_debug\include
    LIBS += -L$$quote(X:\utils\dll_debug\bin) -lutils

    INCLUDEPATH += X:\commomModel\dll_debug\include
    LIBS += -L$$quote(X:\commomModel\dll_debug\bin) -lcommonModel

    LIBS += -L$$quote(X:\libraries\boost_1_63_0\stage\lib) -lboost_python-vc140-mt-gd-1_63
}

!debug {
    QMAKE_POST_LINK=X:\pythonPlugins\pythonPlugins\setDLL.bat $$shell_path($$OUT_PWD/release) release

    INCLUDEPATH += X:\utils\dll_release\include
    LIBS += -L$$quote(X:\utils\dll_release\bin) -lutils

    INCLUDEPATH += X:\commomModel\dll_release\include
    LIBS += -L$$quote(X:\commomModel\dll_release\bin) -lcommonModel

    LIBS += -L$$quote(X:\libraries\boost_1_63_0\stage\lib) -lboost_python-vc140-mt-1_61
}

INCLUDEPATH += X:\libraries\boost_1_63_0
INCLUDEPATH += X:\libraries\cereal-1.2.2\include

#python environment
INCLUDEPATH += C:\Python27\include
LIBS += -L$$quote(C:\Python27\libs)
