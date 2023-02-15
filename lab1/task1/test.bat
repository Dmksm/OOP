@echo off
set PROGRAM="%~1"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% test-data\fox.txt "%TEMP%\fox.txt" bird cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox.txt >nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\fox.txt "%TEMP%\fox.txt" dog cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" test-data\fox-replace-dog-with-cat.txt >nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\multiple-approaches.txt "%TEMP%\replace-out.txt" 1231234 orange
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\replace-out.txt" test-data\multiple-approaches-replace-1231234-with-orange.txt >nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\door.txt "%TEMP%\replace-out.txt" "" crow
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\replace-out.txt" test-data\door-replace-nothing-with-crow.txt >nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\window.txt "%TEMP%\replace-out.txt" window ""
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\replace-out.txt" test-data\window-replace-window-with-nothing.txt >nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\lorem.txt "%TEMP%\replace-out.txt" o a
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\replace-out.txt" test-data\lorem-replace-o-with-a.txt >nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1