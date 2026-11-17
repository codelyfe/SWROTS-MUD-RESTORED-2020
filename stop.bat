@echo off
setlocal
echo Stopping SWRotS...
wsl -e bash -lc "if pgrep -x swr >/dev/null; then pkill -x swr; sleep 1; echo Stopped.; else echo Not running.; fi"
endlocal
