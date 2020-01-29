:: See `config/jenkins/template/README.txt` for more information

if "%BUILD_TYPE%" == "" (
    echo BUILD_TYPE is empty 1>&2
    exit 1
)

if "%BUILD_THREADS%" == "" (
    echo BUILD_THREADS is empty 1>&2
    exit /b 1
)

msbuild -t:Build -p:Configuration=%BUILD_TYPE% -m:%BUILD_THREADS% ALL_BUILD.vcxproj
