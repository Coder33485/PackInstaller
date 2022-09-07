@echo off
cd  /d %~dp0
set willdelpath=%cd%
cd /d C:\
timeout /t 1 /nobreak
rmdir "%willdelpath%" /s /q