$homeDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$srcDir = "$homeDir\src"
$includeDir = "$homeDir\include"
$libDir = "$homeDir\lib"
$binDir = "$homeDir\bin"

function Help {
    Write-Output @"
Usage: makeSFML.ps1 [options]

Options:
  -h, --help        Show this help message and exit
  -c, --compile     Compile the project
  -cl, --clean      Clean the project (delete object files and shortcut)
  -a, --all         Compile the project and create a shortcut to the executable
"@
}

function Compile {
    Write-Output "Compiling..."
    if (!(Test-Path -Path $binDir)) {
        New-Item -ItemType Directory -Path $binDir | Out-Null
    }
    foreach ($file in Get-ChildItem -Path $srcDir -Filter *.cpp) {
        g++ -c "$($file.FullName)" -I"$includeDir" -o "$binDir\$($file.Name.Replace('.cpp','.o'))"
    }
    
    Write-Output "Linking..."
    $linkers = Get-Content "$homeDir\linkers.txt"
    $linkerOptions = @()
    foreach ($linker in $linkers) {
        $linkerOptions += "-l$linker"
    }
    g++ -o "$binDir\Play.exe" "$binDir\*.o" "-L$libDir" @($linkerOptions)
    Write-Output "Done!"
    
    CreateShortcut
}

function CreateShortcut {
    Write-Output "Creating shortcut..."
    $shortcutPath = "$homeDir\Play.lnk"
    $targetPath = "$binDir\Play.exe"
    $shell = New-Object -ComObject WScript.Shell
    $shortcut = $shell.CreateShortcut($shortcutPath)
    $shortcut.TargetPath = $targetPath
    $shortcut.WorkingDirectory = $binDir
    $shortcut.Save()
    Write-Output "Done!"
}


function Clean {
    Write-Output "Cleaning..."
    if (Test-Path -Path "$binDir\*.o") {
        Remove-Item -Path "$binDir\*.o" -Force -Recurse
    }
    Write-Output "Done!"
}

function CleanExe {
    Write-Output "Deleting Executable and Shortcut..."
    if (Test-Path -Path "$binDir\Play.exe") {
        Remove-Item -Path "$binDir\Play.exe" -Force
    }
    if (Test-Path -Path "$homeDir\Play.lnk") {
        Remove-Item -Path "$homeDir\Play.lnk" -Force
    }
    Write-Output "Done!"
}

if ($args.Length -eq 0) {
    Help
} else {
    switch -Regex ($args[0]) {
        "-h|--help" { Help; break }
        "-cl|--clean" { Clean; CleanExe; break }
        "-c|--compile" { Compile; break }
        "-a|--all" { Clean; CleanExe; Compile; Clean; break }
        default { Help }
    }
}