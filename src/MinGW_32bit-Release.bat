@echo off
::读取配置路径信息

for /f "eol=# tokens=1,2* delims==" %%i in (pubConfig.ini) do (if /i "%%i"=="sourceCodePath" set sourceCodePath=%%j
if /i "%%i"=="qtMinGWPath32" set qtMinGWPath32=%%j
)

set logFileName=%DATE:~0,4%%DATE:~5,2%%DATE:~8,2%%TIME:~0,2%MinGW_32bit.log


@echo sourceCodePath：%sourceCodePath%
@echo qtMinGWPath32: %qtMinGWPath32%
@echo logFileName: %logFileName%

echo ---------------------------Doraemon.exe---------------------- >> %logFileName%
xcopy "%sourceCodePath%\build-DoraemonSolution-Desktop_Qt_5_5_1_MinGW_32bit-Release\Doraemon\release\Doraemon.exe" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y   >> %logFileName%
xcopy "%sourceCodePath%\build-DoraemonSolution-Desktop_Qt_5_5_1_MinGW_32bit-Release\Doraemon\release\data\comm_record.dor" "%sourceCodePath%\MinGW_32bit-Release\data\" /d /c /f /y   >> %logFileName%
xcopy "%sourceCodePath%\build-DoraemonSolution-Desktop_Qt_5_5_1_MinGW_32bit-Release\QControlSo\release\QControlSo.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y   >> %logFileName%
xcopy "%sourceCodePath%\build-DoraemonSolution-Desktop_Qt_5_5_1_MinGW_32bit-Release\QDatabaseSo\release\QDatabaseSo.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y   >> %logFileName%
xcopy "%sourceCodePath%\build-DoraemonSolution-Desktop_Qt_5_5_1_MinGW_32bit-Release\QNetSo\release\QNetSo.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y   >> %logFileName%
echo ---------------------------windeployqt.exe---------------------- >> %logFileName%
::%qtMinGWPath32%\5.5\msvc2013_64\bin\windeployqt.exe %sourceCodePath%\MinGW_32bit-Release\Doraemon.exe

xcopy "%sourceCodePath%\DoraemonSolution\plugins\flash\NPSWF32_9.0.28.0.dll" "%sourceCodePath%\MinGW_32bit-Release\plugins\" /d /c /f /y  
xcopy "%sourceCodePath%\DoraemonSolution\configs\config_windows_32.ini" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y   
ren "%sourceCodePath%\MinGW_32bit-Release\config_windows_32.ini" "config.ini"
xcopy "%sourceCodePath%\DoraemonSolution\configs\log4qt.conf" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y   

echo ---------------------------plugins---------------------- >> %logFileName%
xcopy "%qtMinGWPath32%\5.5\mingw492_32\plugins\platforms\qwindows.dll" "%sourceCodePath%\MinGW_32bit-Release\platforms\" /d /c /f /y   >> %logFileName%
xcopy "%qtMinGWPath32%\5.5\mingw492_32\plugins\sqldrivers\qsqlite.dll" "%sourceCodePath%\MinGW_32bit-Release\sqldrivers\" /d /c /f /y   >> %logFileName%

echo ---------------------------dependent---------------------- >> %logFileName%
xcopy "%sourceCodePath%\DoraemonSolution\dependent\libeay32.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y   
xcopy "%sourceCodePath%\DoraemonSolution\dependent\ssleay32.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y   

echo ---------------------------Qt---------------------- >> %logFileName%
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\Qt5Core.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y   >> %logFileName%
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\Qt5Gui.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y   >> %logFileName%
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\Qt5Network.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y   >> %logFileName%
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\Qt5Sql.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y   >> %logFileName%
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\Qt5Widgets.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y   >> %logFileName%
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\Qt5WebKitWidgets.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y  
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\Qt5WebKit.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y  
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\Qt5Sensors.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y  
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\Qt5MultimediaWidgets.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y  
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\Qt5Multimedia.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y  
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\Qt5PrintSupport.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y  
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\Qt5OpenGL.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y  
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\icuin54.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y 
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\icuuc54.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y 
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\Qt5Positioning.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y 
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\Qt5Quick.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y 
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\Qt5Qml.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y 
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\Qt5WebChannel.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y 
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\icudt54.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y 
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\libgcc_s_dw2-1.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y 
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\libstdc++-6.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y 
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\libgcc_s_dw2-1.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y 
xcopy "%qtMinGWPath32%\5.5\mingw492_32\bin\libwinpthread-1.dll" "%sourceCodePath%\MinGW_32bit-Release\" /d /c /f /y 
