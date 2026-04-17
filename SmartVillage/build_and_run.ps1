
# Define paths
$GLUT_ROOT = "e:\8th semester\CGL\Files\freeglut-MSVC-3.0.0-2.mp\freeglut"
$INCLUDE_PATH = "$GLUT_ROOT\include"
$LIB_PATH = "$GLUT_ROOT\lib"
$DLL_PATH = "$GLUT_ROOT\bin\freeglut.dll"

# Copy DLL to current directory if not present
if (-not (Test-Path "freeglut.dll")) {
    Copy-Item $DLL_PATH .
    Write-Host "Copied freeglut.dll to current directory."
}

# Collect all .cpp files
$cppFiles = Get-ChildItem -Recurse -Filter *.cpp | Where-Object { $_.Name -ne "test_glut.cpp" } | Resolve-Path -Relative

Write-Host "Compiling project..."

# Run g++
g++ $cppFiles -o SmartVillage.exe `
    -I"$INCLUDE_PATH" `
    -L"$LIB_PATH" `
    -lfreeglut -lopengl32 -lglu32 -lwinmm

if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilation successful! Running SmartVillage.exe..."
    .\SmartVillage.exe
} else {
    Write-Host "Compilation failed."
}
