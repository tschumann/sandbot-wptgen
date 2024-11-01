# get the location of this file
$scriptpath = $MyInvocation.MyCommand.Path
# get the directory path to this file
$wd = Split-Path $scriptpath
# set the working directory as this file's directory
Push-Location $wd

$configuration = $args[0]
$platform = $args[1]

if ($platform -eq "x86")
{
	& "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\TestWindow\vstest.console.exe" ..\$($configuration)\sandbot-wptgen_tests.dll
}
elseif ($platform -eq "x64")
{
	& "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\TestWindow\vstest.console.exe" ..\$($platform)\$($configuration)\sandbot-wptgen_tests.dll --logger:"console;verbosity=Normal"
}

Pop-Location