@echo off
rem Build NSN documentation using Sphinx

rem Ensure virtual environment is activated
if "%VIRTUAL_ENV%"=="" (
    echo No virtual environment detected. Please activate one before building docs.
    exit /b 1
)

sphinx-build -b html Doc _build/html
if %errorlevel% neq 0 (
    echo Sphinx build failed.
    exit /b %errorlevel%
)

echo Documentation built successfully in _build/html
