# get the location of this file
$scriptpath = $MyInvocation.MyCommand.Path
# get the directory path to this file
$wd = Split-Path $scriptpath
# set the working directory as this file's directory
Push-Location $wd

& "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.com" "..\sandbot-wptgen.sln" /Clean "Debug|x86" | Out-Host
& "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.com" "..\sandbot-wptgen.sln" /Build "Debug|x86" | Out-Host

& "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.com" "..\sandbot-wptgen.sln" /Clean "Debug|x64" | Out-Host
& "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.com" "..\sandbot-wptgen.sln" /Build "Debug|x64" | Out-Host


& "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.com" "..\sandbot-wptgen.sln" /Clean "Release|x86" | Out-Host
& "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.com" "..\sandbot-wptgen.sln" /Build "Release|x86" | Out-Host

& "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.com" "..\sandbot-wptgen.sln" /Clean "Release|x64" | Out-Host
& "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.com" "..\sandbot-wptgen.sln" /Build "Release|x64" | Out-Host

Pop-Location