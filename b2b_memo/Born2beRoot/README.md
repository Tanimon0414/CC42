# Born2beRoot

## ハッシュ値の算出方法

`shasum`コマンドを使う。
この課題で使用したvdiファイル名が`debian.vdi`だった場合。

```bash
shasum debian.vdi
```

基本情報を確認する
```bash
uname -a
```

このコマンドを打つことで、`debian.vdi`のハッシュ値を算出でき、今回の課題ではこのハッシュ値を`signature.txt`書いて提出する。

課題提出後に`signature.txt`に記入する用のハッシュ値の算出に利用したVMを少しでも触ってしまと、ハッシュ値の値が変わってしまうことには注意が必要。

## レビュー項目

### Project overview

- 仮想マシンはどのように機能するのか。

  仮想マシンとは、仮想化技術を利用して、コンピューター内にもうひとつのコンピューターを再現する技術のこと。ホストマシンとゲストマシン（仮想マシン）とを仮想的に切り分けることが可能になる。OS自体を破壊しかねないスクリプトやウイルスに感染する危険性の高いテストを行うときに、仮想マシンを使うことでホストマシンに影響を及ぼすことなく、安全にテストを行うことができる。

- CentOSとDebianの基本的な違い。

  Linuxの系統がそもそも違う。CentOSはFedoraという系統のOSであり、 Fedora系とDebian系という時点でOSの系統が違う。
  [参照](https://gigazine.net/news/20060827_linux_distributions)</br>
  Fedora系とDebian系の大きな違いはパッケージマネージャーである。Fedoraはrpmを、Debianはaptをパッケージ管理に使用している。</br>
  その他にも、CentOSは有償のRHEL(Red Hat Enterprise Linux)から商標を除去しており、無償を実現しているなどの特徴もある。

- 仮想マシンの使用目的。

  **「仮想マシンはどのように機能するのか。」** 参照。

- aptitudeとaptの違いは何か。また、APPArmorとは何か。

  aptはaptitudeの派生、進化版。aptitudeはインストールや削除したいパッケージを対話的に選ぶことができ、aptよりもよりユーザーフレンドリー（人によると思いますが）でグラフィカルな方法でパッケージをマネジメントすることができる。</br>
  ユーザがプロセス、ファイル、システムデバイスといったリソースへアクセスする権限を全て自由に制御できず、管理者から一定の強制を受ける、強制アクセス制御(MAC)を実行するためのプログラムがAPPArmorである。</br>
  APPArmorと似たものとして、SELinuxがある。APPArmorはUbuntuやSUSE Linux、SELinuxはRHELやCentOSなどで主に使われている。

### Simple setup

- UFWサービスがスタートしているかを確認する。

  UFWサービスのインストールが必要な場合。

  ```bash
  $ su -
  $ apt install ufw
  $ ufw enable
  $ reboot # 再起動が必要
  ```

  UFWサービスがスタート（アクティブ）になっているかの確認。

  ```bash
  $ systemctl status ufw
  ```

- SSHサービスがスタートしているかを確認する。

  SSHサービスのインストールが必要な場合。

  ```bash
  $ su -
  $ apt install openssh-server
  ```

  SSHサービスがスタート（アクティブ）になっているかの確認。

  ```bash
  $ systemctl status sshd
  ```

### User

- レビューイーのユーザが`sudo`、`user42`グループに属しているかを確認する。

  ユーザを`sudo`グループに所属させる。

  ```bash
  $ su -
  $ adduser ユーザ名 sudo
  $ reboot # 再起動が必要
  ```

  ユーザが`sudo`グループに属しているかを確認する。

  ```bash
  $ getent group sudo
  ```

  `keisuke`が所属しているグループ一覧を表示

  ```bash
  groups keisuke
  ```

  `user42`グループを作成し、ユーザをそのグループに所属させる。

  ```bash
  $ su -
  $ addgroup user42
  $ adduser ユーザ名 user42
  ```

  ユーザが`user42`グループに属しているかを確認する。

  ```bash
  $ getent group user42
  ```

userの削除コマンド
```bash
userdel -r ユーザ名
```

```
passwd: Authentication token manipulation error
```
これが出て`passwd`コマンドを実行してもパスワードを変更できなかった場合は以下のコマンドを使用する。
（/etc/passwdと/etc/shadowの整合性をとる）

```bash
sudo pwunconv
sudo pwconv
```

この2つのファイルを変更することでホストネームを変えられる。そして再起動する
/etc/hostname
/etc/hosts


hostnamectl set-hostname 新しいホストネーム

以下の必要条件を満たす強固なパスワードポリシーをセットアップする。

セットアップファイルを開く
```bash
sudo vim /etc/login.defs
```

1. パスワードが30日毎に失効する設定にする。

```bash
PASS_MAX_DAYS   99999
```
↓
```bash
PASS_MAX_DAYS   30
```

2. パスワードの変更までに許容される最短日数を2日に設定する。

```bash
PASS_MIN_DAYS   0
```
↓
```bash
PASS_MIN_DAYS   2
```

3. パスワードの有効期限が切れる7日前に警告メッセージを表示する。

デフォルトでこうなってるで心配いらない
```bash
PASS_WARN_AGE   7
```

ここまでやったら一度再起動する
```bash
sudo systemctl reboot
```

4、５、６、について

まず、以下のコマンドを実行して`libpam-pwquality`をインストールする。
（それをしないでこれからする`common-password`を変えようとすると`passwd: Authentication token manipulation error`というエラーが発生する。）

```bash
sudo apt install libpam-pwquality
```

`libpam-pwquality`をインストールしたら以下コマンドで`common-passwordファイルを編集する。

```bash
sudo vim /etc/pam.d/common-password
```

そしたら、このスクリプトが書いてある場所をみつけ、下のように編集して再起動すれば４、５、６、７は完了。
```
password requisite pam_pwquality.so retry=3
```
↓
```
password requisite pam_pwquality.so retry=3 minlen=10 ucredit=-1 dcredit=-1 maxrepeat=3 reject_username difok=7 enforce_for_root
```
↓
```bash
sudo systemctl reboot
```

`difok=7`については勝手にrootユーザに適応されないようになっている

4. パスワードは10文字以上でなければならず、大文字と数字が含まれている必要があります。また、同じ文字が3つ以上連続して含まれていてはいけない。

5. パスワードにユーザ名を含んではいけない。

6. rootパスワードには、このルールは適用されません。「パスワードには、以前のパスワードに含まれていない文字が少なくとも7文字含まれていなければいけない。」

7. もちろん、rootパスワードは上記のポリシーに従わなければならない。


### SUDU

sudoのインストール

```bash
su -
apt install sudo
adduser ユーザ名 sudo
reboot
```

sudoコマンドのlogを残すlogファイルを作成する
```bash
cd /var/log
mkdir sudo
cd sudo
touch sudo.log
```

```bash
cd /etc
vi sudoers
```

badpass_message=""
の形でパスワードが間違えた時のメッセージを変更できる

/etc/sudoersのdefaults以下に下のスクリプトを追記
```bash
Defaults        passwd_tries=3
Defaults        logfile="/var/log/sudo/sudo.log"
Defaults        log_input, log_output
Defaults        iolog_dir="/var/log/sudo"
Defaults        requiretty 
```

`chage -l ユーザ名`コマンドでパスワードポリシーの適応内容について調べられてしまう
パスワードポリシーについて



### UFW
4242ポートを許可
```bash
sudo ufw allow 4242
```

ufwのステータス確認
```bash
sudo ufw status
```

4242ポートの許可を削除
```bash
sudo ufw delete allow 4242
```

### SSH
SSHが4242ポートを使用して接続されるようにする

まずsshd_configのページを開く
```bash
sudo vim /etc/ssh/sshd_config
```

そしたら`#Port 22`のところを探して`Port 4242`に変える。

rootログインを禁止するために`#PermitRootLogin prohibit-password`を`PermitRootLogin no`にする。


## crontabの実行コマンド

crontabを止めてと言われたら
`sudo systemctl disable cron`でできる。
`reboot`

その確認
`sudo systemctl status cron`

`sudo systemctl enable cron`でできる。

でも1つのこの定期実行を止めるためにわざわざcron全体を止めるのはどうなの？という形でdefenseする。

正規表現の`^`について。直後の文字が行の 先頭 にある場合にマッチする。
https://userweb.mnet.ne.jp/nakama/

`grep`コマンドについて
任意のファイルの内容を調べるコマンド。

grepコマンドの`c`オプションについて。
`grep | wc -l`と同じ役割をする。

`monitoring.sh`について
https://qiita.com/yoshi389111/items/a9026769a6c6a8786c90

`free -m | awk '$1 == "Mem:" {print $3}'`について
1フィールド目が`Mem:`という文字列の時、3フィールド目を出力する。

`fdisk`と`udisk`について
`grep -v '/boot$`コマンドの意味は、`/boot`の文字列で終わる行を削除した検索結果を表示する。


`fd`コマンドの`awk`コマンドについては下のページを参照
https://qiita.com/kitsuyui/items/3647bd5b8a5b3e858d3c

`top`コマンドについて（参照: https://atmarkit.itmedia.co.jp/ait/articles/1706/30/news018.html）
`-b`オプションをつけるとキー操作を受け付けなくする。
`-n`オプションで表示を繰り返す回数を指定。

`cut`コマンドについて
`cut -c 9-`で9文字目以降の1列を取得

0.0 us, 0.0 sy, 0.0 ni,100.0 id, 0.0 wa, 0.0 hi, 0.0 si, 0.0 st

cpu使用率の説明については下のページを参照
https://milestone-of-se.nesuke.com/sv-basic/linux-basic/top-command/
https://office54.net/iot/linux/top-command-system

`wall`コマンドで現在ログインしているすべてのユーザーの端末にメッセージを送る

## 用語解説

### viとvimの違い

vi = vimではない。
viの由来はvisual editor、vimの由来はvisual editor improvedである。すなわち、vimはviの改良版という認識で問題ない。
今回は、viの初期設定のままでは使いづらいため、vimをインストールして使うことにする。

### sudoとsuの違い

sudoはそのユーザの権限でプログラムを実行するコマンドである。特定のユーザにとあるコマンドのみ root 権限で実行させたい場合に便利。sudoコマンドを使用する際はrootのパスワードを知っている必要はなく、そのユーザのパスワードを知っていればよい。

suは他のユーザにスイッチする管理系のコマンドである。`$ su`でrootユーザに切り替えることができる。この際に、rootのパスワードを知っていることと、そのユーザがrootユーザに切り替えることが許可されている必要がある。

参照: [sudoとsuの違い](http://tooljp.com/windows/chigai/html/Linux/sudo-su-chigai.html)

## 初期セットアップ

VMを作成し、ホストOSのターミナルから操作できるようにするにはこちらの動画を見てください。

[Born2beRoot初期セットアップ](B2B_setup.mp4)

### vim、sudoのインストール

まず初めに、`apt install`コマンドを実行するためにrootユーザに切り替える。

```terminal
$ su

# apt install vim sudo
```

### /sbin にパスを通す

adduser等の管理システムコマンドがあるディレクトリsbinには最初は環境パスが通っていないため、パスを通す。

```terminal
# echo 'export PATH="$PATH:/sbin:/usr/sbin:usr/local/sbin"' >> ~/.bashrc

# source ~/.bashrc
```

### sudoグループにユーザを追加

sudoグループにユーザを追加する。

```terminal
# adduser <username> sudo
```

sudoグループにユーザが正常に追加されたかを確認する。

```terminal
# getent group sudo
```

変更を反映するために再起動する。

```terminal
# systemctl reboot
```

### 日本語の文字化けを修正する

この項目はdebianのインストール時に言語に日本語を選んだ人のみが行う必要がある。

```terminal
# echo 'case $TERM in
    linux) LANG=C ;;
    *) LANG=ja_JP.UTF-8 ;;
esac' >> /etc/bash.bashrc

# source /etc/bash.bashrc
```

ここで、`TERM`とは端末種別のことである。例えばMacの場合は

```terminal
# echo $TERM
xterm-256color
```

であり、ターミナルの種類はxterm-256colorである。しかし、今回のdebianの場合は以下のようになる。

```terminal
# echo $TERM
linux
```

ターミナルの種類がlinuxのときは`LANG=C`、つまり英語表記に、それ以外の時は`LANG=ja_JP.UTF-8`、つまり日本語表記にしてね、ということである。
実際、VirtualBoxからdebianにログインすると英語表記になるが、Macのターミナルからログインすると日本語表記になる。
