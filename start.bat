@echo off
setlocal
cd /d "%~dp0"
echo Starting SWRotS on port 1111...
wsl -e bash -lc "cd /mnt/j/0/SWROTS-MUD-RESTORED-2020-master/area && if pgrep -x swr >/dev/null; then echo Already running.; exit 0; fi; setsid ../src/swr 1111 >>../log/server.log 2>&1 </dev/null & sleep 4; if pgrep -x swr >/dev/null; then echo Started. Log is log/server.log; else echo Server exited. See log/server.log; exit 1; fi"
endlocal
