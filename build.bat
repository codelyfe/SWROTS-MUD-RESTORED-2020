@echo off
setlocal
cd /d "%~dp0"
echo Building SWRotS...
wsl -e bash -lc "cd /mnt/j/0/SWROTS-MUD-RESTORED-2020-master/src && make swr"
if errorlevel 1 (
  echo Build failed.
  exit /b 1
)
echo Build finished. Binary is src\swr
endlocal
