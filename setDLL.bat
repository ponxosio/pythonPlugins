COPY %1\pythonPlugins.dll X:\pythonPlugins\dll_%2\bin\pythonPlugins.dll
COPY %1\pythonPlugins.lib X:\pythonPlugins\dll_%2\bin\pythonPlugins.lib

DEL /S X:\pythonPlugins\dll_%2\include\*.h
XCOPY /S /Y X:\pythonPlugins\pythonPlugins\*.h X:\pythonPlugins\dll_%2\include