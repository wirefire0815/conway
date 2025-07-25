@echo off
gcc -Wall -Wextra conway.c -o conway.exe

if errorlevel 1 (
    echo Fehler
    pause
    exit /b
)

conway.exe

echo.