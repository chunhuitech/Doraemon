@echo off
::��ȡ����·����Ϣ

for /f "eol=# tokens=1,2* delims==" %%i in (pubConfig.ini) do (if /i "%%i"=="sourceCodePath" set sourceCodePath=%%j
if /i "%%i"=="qtMSVC2013Path32" set qtMSVC2013Path32=%%j
)

set logFileName=%DATE:~0,4%%DATE:~5,2%%DATE:~8,2%%TIME:~0,2%MSVC2013_32bit.log


@echo sourceCodePath��%sourceCodePath%
@echo qtMSVC2013Path32: %qtMSVC2013Path32%
@echo logFileName: %logFileName%

echo ---------------------------Doraemon.exe---------------------- >> %logFileName%
xcopy "%sourceCodePath%\build-DoraemonSolution-Desktop_Qt_5_5_1_MSVC2013_32bit-Release\Doraemon\release\Doraemon.exe" "%sourceCodePath%\MSVC2013_32bit-Release\" /d /c /f /y   >> %logFileName%
xcopy "%sourceCodePath%\build-DoraemonSolution-Desktop_Qt_5_5_1_MSVC2013_32bit-Release\Doraemon\release\log4qt.conf" "%sourceCodePath%\MSVC2013_32bit-Release\" /d /c /f /y   >> %logFileName%
xcopy "%sourceCodePath%\build-DoraemonSolution-Desktop_Qt_5_5_1_MSVC2013_32bit-Release\Doraemon\release\data\comm_record.dor" "%sourceCodePath%\MSVC2013_32bit-Release\data\" /d /c /f /y   >> %logFileName%
xcopy "%sourceCodePath%\build-DoraemonSolution-Desktop_Qt_5_5_1_MSVC2013_32bit-Release\QControlSo\release\QControlSo.dll" "%sourceCodePath%\MSVC2013_32bit-Release\" /d /c /f /y   >> %logFileName%
xcopy "%sourceCodePath%\build-DoraemonSolution-Desktop_Qt_5_5_1_MSVC2013_32bit-Release\QDatabaseSo\release\QDatabaseSo.dll" "%sourceCodePath%\MSVC2013_32bit-Release\" /d /c /f /y   >> %logFileName%
xcopy "%sourceCodePath%\build-DoraemonSolution-Desktop_Qt_5_5_1_MSVC2013_32bit-Release\QNetSo\release\QNetSo.dll" "%sourceCodePath%\MSVC2013_32bit-Release\" /d /c /f /y   >> %logFileName%
echo ---------------------------windeployqt.exe---------------------- >> %logFileName%
::%qtMSVC2013Path32%\5.5\msvc2013_64\bin\windeployqt.exe %sourceCodePath%\MSVC2013_32bit-Release\Doraemon.exe


echo ---------------------------plugins---------------------- >> %logFileName%
xcopy "%qtMSVC2013Path32%\5.5\msvc2013\plugins\platforms\qwindows.dll" "%sourceCodePath%\MSVC2013_32bit-Release\platforms\" /d /c /f /y   >> %logFileName%

echo ---------------------------Qt---------------------- >> %logFileName%
xcopy "%qtMSVC2013Path32%\5.5\msvc2013\bin\Qt5Core.dll" "%sourceCodePath%\MSVC2013_32bit-Release\" /d /c /f /y   >> %logFileName%
xcopy "%qtMSVC2013Path32%\5.5\msvc2013\bin\Qt5Gui.dll" "%sourceCodePath%\MSVC2013_32bit-Release\" /d /c /f /y   >> %logFileName%
xcopy "%qtMSVC2013Path32%\5.5\msvc2013\bin\Qt5Network.dll" "%sourceCodePath%\MSVC2013_32bit-Release\" /d /c /f /y   >> %logFileName%
xcopy "%qtMSVC2013Path32%\5.5\msvc2013\bin\Qt5Sql.dll" "%sourceCodePath%\MSVC2013_32bit-Release\" /d /c /f /y   >> %logFileName%
xcopy "%qtMSVC2013Path32%\5.5\msvc2013\bin\Qt5Widgets.dll" "%sourceCodePath%\MSVC2013_32bit-Release\" /d /c /f /y   >> %logFileName%
