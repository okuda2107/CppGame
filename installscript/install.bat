@echo off
setlocal

REM カレントディレクトリに PCL_1.14.1 がなければダウンロードと実行
if not exist "PCL_1.14.1" (
    curl -L -o installer.exe "https://github.com/PointCloudLibrary/pcl/releases/download/pcl-1.14.1/PCL-1.14.1-AllInOne-msvc2022-win64.exe"

    start /wait "" installer.exe
)
