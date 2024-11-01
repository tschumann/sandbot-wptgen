# get the location of this file
$scriptpath = $MyInvocation.MyCommand.Path
# get the directory path to this file
$wd = Split-Path $scriptpath
# set the working directory as this file's directory
Push-Location $wd

$configuration = $args[0]
$platform = $args[1]

& "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.com" "..\sandbot-wptgen.sln" /Clean "$($configuration)|$($platform)" | Out-Host
# build the solution (use devenv.com so that we get output)
& "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.com" "..\sandbot-wptgen.sln" /Build "$($configuration)|$($platform)" | Out-Host

Pop-Location