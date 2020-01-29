This folder contains templates to run building of project.
There are three type of files:
* cmake.sh/cmake.bat to invoke cmake
* build.sh/build.bat to invoke build command (e.g. make, msbuild)
* package.sh/package.bat to create package and process it (e.g. add additional files, extract google breakpad's symbols)

Jenkins calls them in the following order:
1) cmake
2) build
3) package

There are input parameters:
* cmake:
  - BUILD_DIR is absolute path to build folder
  - BUILD_TYPE is Debug, Release, RelWithDebInfo, MinSizeRel
  - REPO_DIR is absolute path to repo
* build:
  - BUILD_DIR is absolute path to build folder
  - BUILD_THREADS is number of desired build threads
  - BUILD_TYPE is Debug, Release, RelWithDebInfo, MinSizeRel
  - COV_ARGS is an invokation of cov-build command with arguments
  - REPO_DIR is absolute path to repo
* package:
  - BUILD_DIR is absolute path to build folder
  - BUILD_TYPE is Debug, Release, RelWithDebInfo, MinSizeRel
  - REPO_DIR is absolute path to repo

They are omitted if don't used in scripts.
Every script is running from a build folder (BUILD_DIR).
