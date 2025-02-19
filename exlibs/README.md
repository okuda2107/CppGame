# For Developper
## set up (vcpkg)
1. vcpkgを準備
```
git clone https://github.com/microsoft/vcpkg
cd vcpkg
./bootstrap-vcpkg.sh
```
1. 依存ライブラリを`vcpkg-export-XXXXXXXX-XXXXXX.zip`を解凍して取得．
ファイルを置き換える．

## export vcpkg
```
./vcpkg export --zip {まとめたいライブラリを列挙}
```
