@echo off
if "%DK_WIN%" == "" (
    1>&2 echo ERROR: Variable DK_WIN is not set!
    exit /b 1
)
pushd "%~dp0"
call mklink /J DK_Win %DK_WIN%
popd
