$iconPath = "$PSScriptRoot\data\img\RR.png"
$exePath = "$PSScriptRoot\bin\Play.exe"

# Load the System.Drawing assembly to access the Icon class
Add-Type -AssemblyName System.Drawing

# Load the icon from the file
$icon = [System.Drawing.Icon]::ExtractAssociatedIcon($iconPath)

# Set the icon of the executable file
$exe = [System.Reflection.Assembly]::LoadFile($exePath)
$exe.EntryPoint.Module.SetPEKind([System.Reflection.PortableExecutableKinds]::PE32Plus)
$exe.EntryPoint.Module.Attributes = [System.Reflection.ModuleAttributes]::Preferred32Bit
$exe.EntryPoint.Module.Resources.Add((New-Object System.Resources.ResourceWriter("temp.resx")).Write("1", $icon.ToBitmap()))
$exe.EntryPoint.Module.DefineUnmanagedResource("temp.resx")

# Clean up temporary resources
Remove-Item "temp.resx"
