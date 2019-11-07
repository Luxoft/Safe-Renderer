@echo off
setlocal enableextensions enabledelayedexpansion

pushd "%~dp0"
set EXIT_CODE=0

call :PROCESS_DIR sug_lsr_build_configuration
call :PROCESS_DIR sug_lsr_editor_user_manual
call :PROCESS_DIR sug_lsr_hardware_requirements
call :PROCESS_DIR sug_lsr_safety_notes
call :PROCESS_DIR changelog
call :PROCESS_DIR gi_common_files
popd

if "%EXIT_CODE%" == "0" (
  echo.
  echo All XML files are valid.
  echo.
) else (
  echo.
  echo There are errors in XML files! See output above.
  echo.
)
pause
exit /b %EXIT_CODE%

:PROCESS_DIR
for /f "delims=" %%i in ('dir /b /s %1\*.xml') do call :VALIDATE_XML "%%~i"
exit /b 0

:VALIDATE_XML
echo XML: %~1
java -jar %DK_WIN%\tools\Jing\20091111\bin\jing.jar %DK_WIN%\data\relax-ng\1.0\docbookxi.rng "%~1" || set EXIT_CODE=1
exit /b 0
