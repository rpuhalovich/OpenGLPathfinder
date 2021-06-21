@echo off
cd /D "%~dp0"
call cmake -S .. -B ../build -G"Visual Studio 16 2019"
cd ..
