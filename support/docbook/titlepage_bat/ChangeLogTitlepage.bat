@echo off
pushd "%~dp0"
call java -cp %DK_WIN%\tools\saxon\HE9-7-0-20J\saxon9he.jar net.sf.saxon.Transform -xmlversion:1.0 -s:..\stylesheets\ChangeLogTitlepage.xml -xsl:%DK_WIN%\tools\docbook-xsl\1.79.1\template\titlepage.xsl -o:..\stylesheets\ChangeLogTitlepage.xsl
popd
