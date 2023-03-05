@echo off
set PROGRAM="%~1"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% ..\test-data\matrix1.txt ..\test-data\matrix2.txt > "%TEMP%\matrix-out.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\matrix-out.txt" ..\test-data\out-matrix1-matrix2.txt >nul
if ERRORLEVEL 1 goto err

%PROGRAM% ..\test-data\matrix3.txt ..\test-data\matrix4.txt > "%TEMP%\matrix-out.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\matrix-out.txt" ..\test-data\out-matrix3-matrix4.txt >nul
if ERRORLEVEL 1 goto err

%PROGRAM% ..\test-data\matrix5.txt ..\test-data\matrix6.txt > "%TEMP%\matrix-out.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\matrix-out.txt" ..\test-data\out-matrix5-matrix6.txt >nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1