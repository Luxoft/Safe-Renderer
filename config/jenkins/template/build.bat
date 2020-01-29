:: See `config/jenkins/template/README.txt` for more information

if "%REPO_DIR%" == "" (
    echo REPO_DIR is empty 1>&2
    exit /b 1
)

if "%BUILD_DIR%" == "" (
    echo BUILD_DIR is empty 1>&2
    exit /b 1
)

if "%COV_ARGS%" == "" (
    echo COV_ARGS is empty 1>&2
    exit /b 1
)

if "%BUILD_THREADS%" == "" (
    echo BUILD_THREADS is empty 1>&2
    exit /b 1
)

%COV_ARGS% msbuild -t:Build -p:Configuration=%BUILD_TYPE% -m:%BUILD_THREADS% ALL_BUILD.vcxproj
