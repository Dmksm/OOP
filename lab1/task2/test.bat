set PROGRAM="%~1"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err      

%PROGRAM% 2 36 01 > nul
if ERRORLEVEL 1 goto err  

%PROGRAM% 36 2 AZ09 > nul
if ERRORLEVEL 1 goto err 

%PROGRAM% 37 2 AZ09 > nul
if NOT ERRORLEVEL 1 goto err  

%PROGRAM% 36 1 AZ09 > nul
if NOT ERRORLEVEL 1 goto err  

%PROGRAM% 1 2 AZ09 > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 2 37 AZ09 > nul
if NOT ERRORLEVEL 1 goto err 

%PROGRAM% 2 36 2 > nul
if NOT ERRORLEVEL 1 goto err  

%PROGRAM% 36 10 + > nul
if NOT ERRORLEVEL 1 goto err  

%PROGRAM% + 10 2 > nul
if NOT ERRORLEVEL 1 goto err  

%PROGRAM% 10 10 A > nul
if NOT ERRORLEVEL 1 goto err  
                          
%PROGRAM% 10 10 10 10 > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 10 10 2147483647 > "%TEMP%\out-radix"
if ERRORLEVEL 1 goto err    
fc.exe "%TEMP%\out-radix" test-data\max-int.txt >nul
if ERRORLEVEL 1 goto err

%PROGRAM% 16 10 -80000000 > "%TEMP%\out-radix"
if ERRORLEVEL 1 goto err    
fc.exe "%TEMP%\out-radix" test-data\min-int.txt >nul
if ERRORLEVEL 1 goto err

%PROGRAM% 10 10 2147483648 >  nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 10 10 -2147483649 > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 16 10 FF > "%TEMP%\out-radix"
if ERRORLEVEL 1 goto err    
fc.exe "%TEMP%\out-radix" test-data\FF-from-16-to-10-base.txt >nul
if ERRORLEVEL 1 goto err

%PROGRAM% 10 16 255 > "%TEMP%\out-radix"
if ERRORLEVEL 1 goto err    
fc.exe "%TEMP%\out-radix" test-data\255-from-10-to-16-base.txt >nul
if ERRORLEVEL 1 goto err

%PROGRAM% 10 36 36 > "%TEMP%\out-radix"
if ERRORLEVEL 1 goto err    
fc.exe "%TEMP%\out-radix" test-data\36-from-10-to-36-base.txt >nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1