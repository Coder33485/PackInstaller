@echo off
cd  /d %~dp0
set willdelpath=%cd%
cd /d C:\
timeout /t 2 /nobreak
rmdir %willdelpath% /s /q
if %errorlevel% == 0 (
　　echo successfully
)else(
　　echo failed
)
pause