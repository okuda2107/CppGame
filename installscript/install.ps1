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

# C++コンパイラのinstall
# MSYS2のインストール
$msys64Path = "C:\msys64"
if ( -not (Test-Path $msys64Path)) {
    # wingetパッケージIDの確認（MSYS2版 mingw-w64 toolchain）
    $packageId = "MSYS2.MSYS2"

    Write-Host "=== MSYS2 (mingw-w64) をインストールします ==="
    winget install --id $packageId --exact --accept-package-agreements --accept-source-agreements

    Write-Host "=== MSYS2 の初期化と mingw-w64 インストール ==="
    $msys2Path = "C:\msys64\usr\bin\bash.exe"
    if (-not (Test-Path $msys2Path)) {
        Write-Error "MSYS2 のインストールが見つかりません。"
        exit 1
    }

    # msys2 を更新して mingw-w64 toolchain を入れる
    & $msys2Path -lc "pacman -Sy --noconfirm"
    & $msys2Path -lc "pacman -S --noconfirm mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-gdb"

    # 環境変数設定
    $mingwBin = Join-Path $mingwBin "bin"
    $currentPath = [System.Environment]::GetEnvironmentVariable("Path", "User")
    if ($currentPath -notmatch [Regex]::Escape($mingwBin)) {
        Write-Host "PATH に $mingwBin を追加します..."
        $newPath = "$currentPath;$mingwBin"
        [System.Environment]::SetEnvironmentVariable("Path", $newPath, "User")
    }
    $env:Path += ";$mingwBin"
}

if( -not (Test-Path (Join-Path $ExlibsDir "googletest-1.17.0"))) {
    $TmpDir = $(Join-Path $ExlibsDir "googletest-1.17.0")
    Download-Lib "https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip" $ExlibsDir
    cmake -S $TmpDir -B $(Join-Path $TmpDir "build") -G "MinGW Makefiles"
    cmake --build $(Join-Path $TmpDir "build") --config Release
}

if( -not (Test-Path (Join-Path $ExlibsDir "SDL2-2.32.8"))) {
    Download-Lib "https://github.com/libsdl-org/SDL/releases/download/release-2.32.8/SDL2-devel-2.32.8-mingw.zip" $ExlibsDir
}

if( -not (Test-Path (Join-Path $ExlibsDir "SDL2_image-2.8.8"))) {
    Download-Lib "https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.8/SDL2_image-devel-2.8.8-mingw.zip" $ExlibsDir
}

if( -not (Test-Path (Join-Path $ExlibsDir "SDL2_mixer-2.8.1"))) {
    Download-Lib "https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.1/SDL2_mixer-devel-2.8.1-mingw.zip" $ExlibsDir
}

if( -not (Test-Path (Join-Path $ExlibsDir "SDL2_net-2.2.0"))) {
    Download-Lib "https://github.com/libsdl-org/SDL_net/releases/download/release-2.2.0/SDL2_net-devel-2.2.0-mingw.zip" $ExlibsDir
}

if( -not (Test-Path (Join-Path $ExlibsDir "SDL2_ttf-2.24.0"))) {
    Download-Lib "https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.24.0/SDL2_ttf-devel-2.24.0-mingw.zip" $ExlibsDir
}

if( -not (Test-Path (Join-Path $ExlibsDir "rapidjson"))) {
    $TmpDir = Join-Path $ExlibsDir "rapidjson"
    git clone https://github.com/Tencent/rapidjson.git $TmpDir
}

if( -not (Test-Path (Join-Path $ExlibsDir "glew-2.2.0"))) {
    Download-Lib "https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip" $ExlibsDir
    $TmpDir = $(Join-Path $ExlibsDir "glew-2.2.0")
    cmake -S $(Join-Path $TmpDir "build/cmake")-B $(Join-Path $TmpDir "build") -G "MinGW Makefiles"
    cmake --build $(Join-Path $TmpDir "build") --config Release
}

if( -not (Test-Path (Join-Path $ExlibsDir "Simple-OpenGL-Image-Library"))) {
    $TmpDir = $(Join-Path $ExlibsDir "Simple-OpenGL-Image-Library")
    git clone https://github.com/kbranigan/Simple-OpenGL-Image-Library.git $TmpDir
    cmake -S $TmpDir -B $(Join-Path $TmpDir "build") -G "MinGW Makefiles"
    cmake --build $(Join-Path $TmpDir "build") --config Release
}

if( -not (Test-Path (Join-Path $ExlibsDir "openal-soft-1.24.3-bin"))) {
    Download-Lib "https://github.com/kcat/openal-soft/releases/download/1.24.3/openal-soft-1.24.3-bin.zip" $ExlibsDir
}

if( -not (Test-Path (Join-Path $ExlibsDir "freealut"))) {
    $TmpDir = $(Join-Path $ExlibsDir "freealut")
    $OpenALDir = $(Join-Path $ExlibsDir "openal-soft-1.24.3-bin")
    git clone https://github.com/vancegroup/freealut.git $TmpDir
    cmake -S $TmpDir -B $(Join-Path $TmpDir "build") -G "MinGW Makefiles" -DOPENAL_LIBRARY="$(Join-Path $OpenALDir "libs/Win64/OpenAL32.lib")" -DOPENAL_INCLUDE_DIR="$(Join-Path $OpenALDir "include")"
    cmake --build $(Join-Path $TmpDir "build") --config Release
}
