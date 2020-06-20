
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

function generate_file
{
	& "$($executable_path)\sandbot-wptgen.exe" -w128 $args[0]
}

# $args[0] file to check
# $args[1] expected hash
function check_hash
{
	$hash = (Get-FileHash $args[0]).Hash

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
	($output = generate_file $args[0] $args[1]) > $null

	Write-Host "Generating waypoint for $($args[0])"

	check_hash $args[1] $args[2]

	# delete the .wpt file
	Remove-Item $args[1]

	Write-Host "================"
}

test_waypointing bsp/bounce.bsp bounce.wpt "114A7C91EF50A618CBF62EBCEA21B77921DA1CBEEAB7ACD5CBA9A7345C5B7748"
test_waypointing bsp/frenzy.bsp frenzy.wpt "790139C453A27727819801FDB545F3D0A455DF98EC5830277EE634888EFCF5D4"

if ($global:has_failed)
{
	Write-Host "There was at least one failure" -foregroundcolor "red"
}
else
{
	Write-Host "All the tests passed" -foregroundcolor "green"
}

Pop-Location
