# get the location of this file
$scriptpath = $MyInvocation.MyCommand.Path
# get the directory path to this file
$wd = Split-Path $scriptpath
# set the working directory as this file's directory
Push-Location $wd

& "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\TestWindow\vstest.console.exe" ..\Release\sandbot-wptgen_tests.dll

Pop-Location