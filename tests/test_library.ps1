# Tests library functions and types.

$LibraryTests = "error notify support system_string winapi"
$LibraryTestsWithInput = "file"
$OptionSets = "" -split " "

. .\test_functions.ps1

Function RunTestBinaryWithDevice
{
	param( [string]$TestExecutablesDirectory, [string]$TestName, [string]$TestFile )

	$TestExecutable = "${TestExecutablesDirectory}\${TestName}.exe"

	If (-Not (Test-Path -Path ${TestExecutable} -PathType Leaf))
	{
		$TestDescription = "Missing binary: ${TestName}"
		WriteTestResult ${TestDescription} ${ExitCommandNotFound}

		Return ${ExitCommandNotFound}
	}
	$Output = Invoke-Expression "${TestExecutable} ${TestFile}"
	$Result = $global:LastExitCode

	If (${Result} -ne ${ExitSuccess})
	{
		Write-Host ${Output} -foreground Red
	}
	$TestDescription = "${TestName} with input: '${TestFile}"
	WriteTestResult ${TestDescription} ${Result}

	Return ${Result}
}
$TestExecutablesDirectory = GetTestExecutablesDirectory

If (-Not (Test-Path ${TestExecutablesDirectory}))
{
	Write-Error "Missing test executables directory"

	Exit ${ExitFailure}
}

$Result = ${ExitSuccess}

Foreach (${TestName} in ${LibraryTests} -split " ")
{
	# Split will return an array of a single empty string when LibraryTests is empty.
	If (-Not (${TestName}))
	{
		Continue
	}
	$ResultRun = RunTestBinary ${TestExecutablesDirectory} "cfile_test_${TestName}"

	If ((${ResultRun} -ne ${ExitSuccess}) -And (${ResultRun} -ne ${ExitIgnore}))
	{
		$Result = ${ResultRun}
	}
}

$TestInputs = GenerateTestInputs "libcfile" ${OptionSets}

Foreach (${TestName} in ${LibraryTestsWithInput} -split " ")
{
	# Split will return an array of a single empty string when LibraryTestsWithInput is empty.
	If (-Not (${TestName}))
	{
		Continue
	}
	ForEach ($TestInput in ${TestInputs})
	{
		$ResultRun = RunTestBinaryWithInput ${TestExecutablesDirectory} "cfile_test_${TestName}" ${TestInput}

		If ((${ResultRun} -ne ${ExitSuccess}) -And (${ResultRun} -ne ${ExitIgnore}))
		{
			$Result = ${ResultRun}
		}
	}
}

$ResultRun = RunTestBinaryWithDevice ${TestExecutablesDirectory} "cfile_test_file" '\\.\PhysicalDrive0'

If ((${ResultRun} -ne ${ExitSuccess}) -And (${ResultRun} -ne ${ExitIgnore}))
{
	$Result = ${ResultRun}
}
$ResultRun = RunTestBinaryWithDevice ${TestExecutablesDirectory} "cfile_test_file" '\\.\C:'

If ((${ResultRun} -ne ${ExitSuccess}) -And (${ResultRun} -ne ${ExitIgnore}))
{
	$Result = ${ResultRun}
}
Exit ${Result}
