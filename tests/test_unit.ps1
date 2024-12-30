Set-StrictMode -Version 3.0

$ErrorActionPreference = "Stop"
$PSNativeCommandUserErrorActionPerference = $true

# get the location of this file
$scriptpath = $MyInvocation.MyCommand.Path
# get the directory path to this file
$wd = Split-Path $scriptpath
# set the working directory as this file's directory
Push-Location $wd

# build the solution for all targets
& "MSBuild.exe" /t:Build /p:Platform=x86 /p:Configuration=Debug "../sandbot-wptgen.sln"
& "MSBuild.exe" /t:Build /p:Platform=x64 /p:Configuration=Debug "../sandbot-wptgen.sln"
& "MSBuild.exe" /t:Build /p:Platform=x86 /p:Configuration=Release "../sandbot-wptgen.sln"
& "MSBuild.exe" /t:Build /p:Platform=x64 /p:Configuration=Release "../sandbot-wptgen.sln"

# run the tests - add --diag:out.txt to get extra information if required
& "vstest.console.exe" ..\Debug\sandbot-wptgen_tests.dll --logger:"console;verbosity=Normal"
& "vstest.console.exe" ..\x64\Debug\sandbot-wptgen_tests.dll --logger:"console;verbosity=Normal"

Pop-Location