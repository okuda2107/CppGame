# Cpp Game
## 動作確認環境
* Windows 11
* vscode
    - extensions
        - WSL
        - Dev Conainers
* WSL
* Docker
* docker compose
* VcXsrv (X Window System)

## Usage
それぞれのアーキテクチャに対応している`installscript/install`スクリプトを実行する

### docker
`.devcontainer/`ディレクトリ下で以下のコマンドを叩く
```
$ docker-compose run --rm dev ./game
```
