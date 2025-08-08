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

### windows
**powershellでスクリプトを実行するための準備**

管理者権限でPowerShellを起動し，以下のコマンドを実行する．
ポリシーを変更する．

```PowerShell
> Set-ExecutionPolicy RemoteSigned
実行ポリシーは、信頼されていないスクリプトからの保護に役立ちます。実行ポリシーを変更すると、about_Execution_Policies
のヘルプ トピックで説明されているセキュリティ上の危険にさらされる可能性があります。実行ポリシーを変更しますか?
[Y] はい(Y)  [N] いいえ(N)  [S] 中断(S)  [?] ヘルプ (既定値は "Y"): y
```

**補足**

windows環境ではC++コンパイラの自動インストールをサポートできていない．

`installscript/install`を実行する前に，C++コンパイラのインストールと，`cmake`コマンドでビルドできる環境にしておく必要がある．

### docker
`.devcontainer/`ディレクトリ下で以下のコマンドを叩く
```
$ docker-compose run --rm dev ./game
```
