:: See `config/jenkins/template/README.txt` for more information

if "%REPO_DIR%" == "" (
    echo REPO_DIR is empty 1>&2
    exit /b 1
)

if "%BUILD_TYPE%" == "" (
    echo BUILD_TYPE is empty 1>&2
    exit /b 1
)

cmake -G "Visual Studio 12" -T v120_xp ^
    -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
    -DUNIT_TESTS=OFF ^
    -DCOVERAGE=OFF ^
    -DHMI_PROJECT_PATH=%REPO_DIR%/test/database/Telltales ^
    -DCMAKE_TOOLCHAIN_FILE=%REPO_DIR%/toolchains/toolchain-vs-windows-x86.cmake ^
    %REPO_DIR%
