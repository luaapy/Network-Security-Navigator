@echo off
rem NSN MSVC Build Script

setlocal

if "%1" == "" set CONFIG=Release
if not "%1" == "" set CONFIG=%1

echo Building NSN (%CONFIG%)...

msbuild nsn.sln /p:Configuration=%CONFIG% /p:Platform=x64

if %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    exit /b %ERRORLEVEL%
)

echo Build successful.
