$RootDir = Split-Path $PSScriptRoot -Parent

if (-not (Get-Command winget -ErrorAction SilentlyContinue)) {
    Write-Error "winget is not installed. Please install 'App Installer' from Microsoft Store."
    exit 1
}

$ExlibsDir = Join-Path $RootDir exlibs -Resolve

function Install-Command {
    param(
        [Parameter(Mandatory)]
        [hashtable]$MapCommandsPackages
    )

    foreach ($Command in $MapCommandsPackages.keys) {
        if (-not (Get-Command $Command)) {
            winget install --id $MapCommandsPackages[$Command] --exact --silent --accept-package-agreements --accept-source-agreements
        }
    }
}

function Download-Lib ($Uri, $OutputPath) {
    $TmpZip = [System.IO.Path]::GetTempFileName()
    Invoke-WebRequest -Uri $Uri -OutFile $TmpZip
    Expand-Archive -Path $TmpZip -DestinationPath $OutputPath
    Remove-Item $TmpZip
}

Install-Command -MapCommandsPackages @{
    git = "Git.Git"
    cmake = "cmake"
}

if (-not (winget list --id Microsoft.VisualStudio.2022.Community | Select-String "Microsoft.VisualStudio.2022.Community")) {
    winget install --id Microsoft.VisualStudio.2022.Community -e --override "--quiet --add Microsoft.VisualStudio.Workload.NativeDesktop"
}

if( -not (Test-Path (Join-Path $ExlibsDir "SDL2-2.32.8"))) {
    Download-Lib "https://github.com/libsdl-org/SDL/releases/download/release-2.32.8/SDL2-devel-2.32.8-VC.zip" $ExlibsDir
}

if( -not (Test-Path (Join-Path $ExlibsDir "SDL2_image-2.8.8"))) {
    Download-Lib "https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.8/SDL2_image-devel-2.8.8-VC.zip" $ExlibsDir
}

if( -not (Test-Path (Join-Path $ExlibsDir "SDL2_mixer-2.8.1"))) {
    Download-Lib "https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.1/SDL2_mixer-devel-2.8.1-VC.zip" $ExlibsDir
}

if( -not (Test-Path (Join-Path $ExlibsDir "SDL2_net-2.2.0"))) {
    Download-Lib "https://github.com/libsdl-org/SDL_net/releases/download/release-2.2.0/SDL2_net-devel-2.2.0-VC.zip" $ExlibsDir
}

if( -not (Test-Path (Join-Path $ExlibsDir "SDL2_ttf-2.24.0"))) {
    Download-Lib "https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.24.0/SDL2_ttf-devel-2.24.0-VC.zip" $ExlibsDir
}

if( -not (Test-Path (Join-Path $ExlibsDir "rapidjson-1.1.0"))) {
    Download-Lib "https://github.com/Tencent/rapidjson/archive/refs/tags/v1.1.0.zip" $ExlibsDir
}

if( -not (Test-Path (Join-Path $ExlibsDir "glew-2.2.0"))) {
    Download-Lib "https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip" $ExlibsDir
    $TmpDir = $(Join-Path $ExlibsDir "glew-2.2.0")
    cmake -S $(Join-Path $TmpDir "build/cmake")-B $(Join-Path $TmpDir "build")
    cmake --build $(Join-Path $TmpDir "build")
}

if( -not (Test-Path (Join-Path $ExlibsDir "Simple-OpenGL-Image-Library"))) {
    $TmpDir = $(Join-Path $ExlibsDir "Simple-OpenGL-Image-Library")
    git clone https://github.com/kbranigan/Simple-OpenGL-Image-Library.git $TmpDir
    cmake -S $TmpDir -B $(Join-Path $TmpDir "build")
    cmake --build $(Join-Path $TmpDir "build")
}
