@echo off
if not exist ..\DK_Win call ..\MakeDkWinJunction.bat
if not exist ..\DK_Win (
    1>&2 echo ERROR: ..\DK_Win is missing!
    exit /b 1
)
perl ..\support\update_changelogs\GenerateChangeLogPDFs.pl
pause
