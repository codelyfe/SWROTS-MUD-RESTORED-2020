@echo off
setlocal EnableExtensions EnableDelayedExpansion
cd /d "%~dp0"

where git >nul 2>&1
if errorlevel 1 (
    echo Git is not installed or not on PATH.
    pause
    exit /b 1
)

if not exist ".git" (
    echo Initializing git repository...
    git init
    if errorlevel 1 goto :fail
    git branch -M main
)

set "REMOTE_URL=https://github.com/codelyfe/SWROTS-MUD-RESTORED-2020.git"
git remote get-url origin >nul 2>&1
if errorlevel 1 (
    git remote add origin "%REMOTE_URL%"
    if errorlevel 1 goto :fail
) else (
    git remote set-url origin "%REMOTE_URL%"
)

git add -A
git diff --cached --quiet
if errorlevel 1 (
    git commit -m "Update project"
    if errorlevel 1 goto :fail
) else (
    echo Nothing new to commit.
)

echo Pushing to origin...
git push -u origin HEAD
if errorlevel 1 goto :fail

echo Done.
pause
exit /b 0

:fail
echo Push failed.
pause
exit /b 1
