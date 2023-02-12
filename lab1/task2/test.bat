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

%PROGRAM% 10 10 2147483647 > nul
if ERRORLEVEL 1 goto err    

echo OK
exit 0

:err
echo Program testing failed
exit 1