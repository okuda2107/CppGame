
$RootDir = Split-Path $PSScriptRoot -Parent

$ExlibsDir = Join-Path $RootDir exlibs -Resolve

function Download-Lib ($URI) {
    $uri = New-Object System.Uri($URI)
    $file = Split-Path $uri.AbsolutePath -Leaf
    $WebClient.DownloadFile($uri, (Join-Path $ExlibsDir $file)) | Expand-Archive
}

if((Test-Path $(Join-Path $ExlibsDir "SDL2-2.32.0")) -eq $false) {
    Download-Lib "https://github.com/libsdl-org/SDL/releases/download/release-2.32.8/SDL2-devel-2.32.8-VC.zip"
    Write-Host $pwd
}

# ダウンロードURLと出力先のディレクトリ
$zipUrl = "https://example.com/archive.zip"
$extractPath = "C:\Path\To\Extract"

# 一時ディレクトリにZIPを保存
$tmpZip = [System.IO.Path]::GetTempFileName()
$tmpRealZip = "$tmpZip.zip"
Rename-Item -Path $tmpZip -NewName $tmpRealZip

# ダウンロード
Invoke-WebRequest -Uri $zipUrl -OutFile $tmpRealZip

# 展開先のディレクトリが存在しなければ作成
if (-not (Test-Path $extractPath)) {
    New-Item -ItemType Directory -Path $extractPath | Out-Null
}

# ZIPを展開
Expand-Archive -Path $tmpRealZip -DestinationPath $extractPath -Force

# ZIPを削除
Remove-Item -Path $tmpRealZip -Force
