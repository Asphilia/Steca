ECHO Storing current directory in VSCMD_START_DIR
SET "VSCMD_START_DIR=%CD%"
CALL "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
cd .build
SET QTDIR=C:\Qt\5.11.2\msvc2017_64
SET PATH=C:\Qt\5.11.2\msvc2017_64\bin;C:\opt\local_x64\lib;%PATH%
cmake --build . --config Release
