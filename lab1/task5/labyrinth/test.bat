set PROGRAM="%~1"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% test-data\empty-labyrinth.txt "%TEMP%\labyrinth-out.txt"
if NOT ERRORLEVEL 1 goto err

%PROGRAM% test-data\labyrinth-standard.txt "%TEMP%\labyrinth-out.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\labyrinth-out.txt" test-data\labyrinth-standard-with-way.txt >nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\labyrinth-with-big-distance.txt "%TEMP%\labyrinth-out.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\labyrinth-out.txt" test-data\labyrinth-with-long-way.txt >nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\labyrinth-105x105-and-no-way.txt "%TEMP%\labyrinth-out.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\labyrinth-out.txt" test-data\labyrinth-100x100-without-way.txt >nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1