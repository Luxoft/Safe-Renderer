@echo off
set SCRIPT_DIR=%~dp0

:: Show usage if no parameters
if "%~1" == "" (
    echo Script converts DocBook file to PDF
    echo usage: %0 DocBookFile.xml [OutputFile.pdf]
    exit /b 0
)

:: Parameter 1
set INPUT_FILE="%~1"

:: Parameter 2
if not "%~2" == "" (set OUTPUT_FILE="%~2") else (set OUTPUT_FILE="%~dpn1.pdf")

:: Make paths absolute
for /f "delims=" %%I in (%INPUT_FILE%) do set INPUT_FILE=%%~fI
for /f "delims=" %%I in (%OUTPUT_FILE%) do set OUTPUT_FILE=%%~fI

:: Just for user information
echo Output file is "%OUTPUT_FILE%"

:: Check can write into file (i.e. file is open already)
:: * copy doesn't change ERRORLEVEL if copy failed
:: * xcopy can't use NUL as source
>"%OUTPUT_FILE%" 2>NUL echo 1
for %%I in ("%OUTPUT_FILE%") do set OUTPUT_SIZE=%%~zI
if not "%OUTPUT_SIZE%" == "3" (
    echo Output file is opened
    exit /b 1
)

set INPUT_DIR=%~dp1

:: Setup intermediate files
set XINCLUDE_FILE=%TMP%\xinclude-%~n1%RANDOM%.xml
set TMP_FILE=%TMP%\docbook-%~n1%RANDOM%.fo

:: Convert
pushd "%SCRIPT_DIR%"

:: Make intermediate file with xincludes processed
call "%DK_WIN%\tools\xmllint\2-2.7.8.win32\bin\xmllint.exe" --output "%XINCLUDE_FILE%" --xinclude "%INPUT_FILE%"
set EXIT_CODE=%ERRORLEVEL%
if not "%EXIT_CODE%" == "0" goto :SKIP_CMDS

:: Process intermediate file with stylesheets into another intermediate file
call java -cp %DK_WIN%\tools\saxon\HE9-7-0-20J\saxon9he.jar net.sf.saxon.Transform -xmlversion:1.0 -s:"%XINCLUDE_FILE%" -xsl:stylesheets\ChangeLogAdaptations.xsl -o:"%TMP_FILE%" img.src.path="file:///%INPUT_DIR:\=/%" --suppressXsltNamespaceCheck:on
set EXIT_CODE=%ERRORLEVEL%
if not "%EXIT_CODE%" == "0" goto :SKIP_CMDS

:: Make the output PDF file from the second intermediate file
set FOP_HYPHENATION_PATH=%DK_WIN%\tools\offo\2.2\fop-hyph.jar
call "%DK_WIN%\tools\fop\1.1\fop.bat" -c "%SCRIPT_DIR%\LuxoftFopAdaptations.xconf" "%TMP_FILE%" "%OUTPUT_FILE%"
set EXIT_CODE=%ERRORLEVEL%
:SKIP_CMDS
popd

:: Cleanup
del /q "%TMP_FILE%"
if not "%EXIT_CODE%" == "0" del /q "%OUTPUT_FILE%" 2>NUL 1>NUL
set XINCLUDE_FILE=
set FOP_HYPHENATION_PATH=
set SCRIPT_DIR=
set TMP_FILE=
set OUTPUT_FILE=
set INPUT_DIR=
exit /b %EXIT_CODE%
