
$executable_path = $args[0]

# get the location of this file
$scriptpath = $MyInvocation.MyCommand.Path
# get the directory path to this file
$wd = Split-Path $scriptpath
# set the working directory as this file's directory
Push-Location $wd

if($executable_path -eq $null)
{
	$executable_path = 'Debug'
}

$global:has_failed = 0

Write-Host "Using executable in $($executable_path)"

function convert_file
{
	& "$($executable_path)\sandbot-wptgen.exe" -w128 $args[0]
}

function get_file_hash
{
	# TODO: eventually replace this with Get-FileHash which only newer versions of PowerShell support
	$fullPath = Resolve-Path $args[0]
    $md5 = new-object -TypeName System.Security.Cryptography.MD5CryptoServiceProvider
    $file = [System.IO.File]::Open($fullPath,[System.IO.Filemode]::Open, [System.IO.FileAccess]::Read)
    [System.BitConverter]::ToString($md5.ComputeHash($file))
    $file.Dispose()
}

# $args[0] file to check
# $args[1] expected hash
function check_hash
{
	$hash = get_file_hash $args[0]

	if ($hash -eq $args[1])
	{
		Write-Host "Passed" -foregroundcolor "green"
	}
	else
	{
		Write-Host "Failed - got hash $hash" -foregroundcolor "red"
		# uncomment below when there are too many failures to manually copy
		# Write-Host "(""$($args[0])"", ""$hash""),"
		$global:has_failed = 1
	}
}

# $args[0] file to waypoint
# $args[1] .wpt file
# $args[2] expected hash of .wpt file
function test_waypointing
{
	($output = convert_file $args[0] $args[1]) > $null

	Write-Host "Generating waypoint for $($args[0])"

	check_hash $args[1] $args[2]

	# delete the .wpt file
	Remove-Item $args[1]

	Write-Host "================"
}

test_waypointing bsp/bounce.bsp bounce.wpt "92-5A-B0-26-7D-50-DB-C2-AA-7E-04-C2-81-99-99-F6"
test_waypointing bsp/frenzy.bsp frenzy.wpt "62-4E-F5-63-71-C5-0B-57-40-E5-67-88-2D-86-5C-37"

if ($global:has_failed)
{
	Write-Host "There was at least one failure" -foregroundcolor "red"
}
else
{
	Write-Host "All the tests passed" -foregroundcolor "green"
}

Pop-Location
