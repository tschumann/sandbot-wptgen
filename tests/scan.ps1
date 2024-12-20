# get the location of this file
$scriptpath = $MyInvocation.MyCommand.Path
# get the directory path to this file
$wd = Split-Path $scriptpath
# set the working directory as this file's directory
Push-Location $wd

& "MSBuild.exe" /p:RunCodeAnalysis=true "../sandbot-wptgen.sln"

Pop-Location