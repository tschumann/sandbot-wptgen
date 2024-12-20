# get the location of this file
$scriptpath = $MyInvocation.MyCommand.Path
# get the directory path to this file
$wd = Split-Path $scriptpath
# set the working directory as this file's directory
Push-Location $wd

# run the tests - add --diag:out.txt to get extra information if required
& "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\TestWindow\vstest.console.exe" ..\Debug\sandbot-wptgen_tests.dll --logger:"console;verbosity=Normal"
& "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\TestWindow\vstest.console.exe" ..\x64\Debug\sandbot-wptgen_tests.dll --logger:"console;verbosity=Normal"

Pop-Location