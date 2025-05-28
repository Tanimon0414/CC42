本来のstrjoin関数ではs1とs2どちらか一方にでもNULLがきたらその時点でNULLを返すことになっている。
しかし、今回の場合はそれが違ってs1のみが入っていた場合はs1を返さないといけない。
しかし、
```C
if (s1 && !s2)
	return (s1);
```
という処理はすることができない。なぜなら、s1が`char const *s1`という形で宣言されており、返り値の型は`char *`でならないといけないからだ。
また、`char const *`はポインタ位置の変更ができないため`free`をすることができない。
https://qiita.com/mizcii/items/35df2bceac67a75f75dd
その結果、メモリリークを起こしてしまう。
↓
今回ように新しいstrjoin関数を作るべきだと考えた。
↓
```C
if (s1 && !s2)
	return (s1);
```
という書き方を可能にするためにも、新しいstrjoin関数の引数は`char const *`ではなく、`char *`で宣言していくことにする。

ボーナスについて
openできるファイル数を256までにした理由は
```bash
 ulimit -n
```
上記のコマンドをGuacamoleで実行した場合、256が出力されるから。

char const *str のfree方法について
https://stackoverflow.com/questions/2819535/unable-to-free-const-pointers-in-c
