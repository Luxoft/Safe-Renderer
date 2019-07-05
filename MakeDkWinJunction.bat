@echo off
pushd "%~dp0"
call mklink /J DK_Win %DK_WIN%
popd