:: See `config/jenkins/template/README.txt` for more information

if "%REPO_DIR%" == "" (
    echo REPO_DIR is empty 1>&2
    exit /b 1
)

if "%BUILD_DIR%" == "" (
    echo BUILD_DIR is empty 1>&2
    exit /b 1
)

if "%BUILD_TYPE%" == "" (
    echo BUILD_TYPE is empty 1>&2
    exit 1
)

msbuild -t:Build -p:Configuration=%BUILD_TYPE% PACKAGE.vcxproj
