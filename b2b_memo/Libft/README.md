# Libft仕様書

## Part1 Libc functions

### ft_isalpha

```txt
引数cがアルファベットなら1を、そうでなければ0を返す。
```

### ft_isdigit

```txt
引数cが数字なら1を、そうでなければ0を返す。
```

### ft_isalnum

```txt
引数cがアルファベットか数字なら1を、そうでなければ0を返す。
```

### ft_isascii

```txt
引数cがascii文字なら1を、そうでなければ0を返す。
```

### ft_isprint

```txt
引数cが印字可能な文字なら1を、そうでなければ0を返す。
```

### ft_strlen

```txt
文字列sの文字数を返す。
```

### ft_memset

```txt
アドレスsの位置から文字cをn個入れる。
```

### ft_bzero

```txt
アドレスsの位置から終端文字'\0'をn個入れる。
```

### ft_memcpy

```txt
アドレスdstの位置に文字列srcをnバイトコピーする。
```

### ft_memmove

```txt
アドレスdstの位置に文字列srcをnバイトコピーする。
```

### ft_strlcpy

```txt
文字列dstに文字列srcをnバイトコピーし、dstの末尾に'\0'を追加する。
```

dstsize(コピーしたい文字数)が文字列srcの文字列よりも大きかったら、無条件でdstsizeをsrcの文字数にする。

### ft_strlcat

```txt
文字列dstに文字列srcをdstsize - ft_strlen(dst) - 1バイトコピーし、dstの末尾に'\0'を追加する。最後にdstとsrcの文字数の和を返す。
```

### ft_toupper

```txt
小文字のアルファベットを大文字に変える。引数がもし小文字のアルファベットではないならその引数をそのまま返す。
```

### ft_tolower

```txt
大文字のアルファベットを小文字に変える。引数がもし小文字のアルファベットではないならその引数をそのまま返す。
```

### ft_strchr

```txt
文字列sの先頭から文字cを探して、最初に見つかった位置をポインタで返す。見つからなかったときはNULLを返却する。
```

終端文字'\0'も文字列の一部と見なされることに注意。つまり、ft_strchr(s, 0); も可能。

### ft_strrchr

```txt
文字列sにおいて文字cが最後に見つかった位置をポインタで返却する。 見つからなかったときにはNULLを返却する。
```

終端文字'\0'も文字列の一部と見なされることに注意。つまり、ft_strrchr(s, 0); も可能。

### ft_strncmp

```txt
文字列s1とs2をn文字目まで比較。s1 = s2のときは0を返し、s1 != s2のときはs1[i] - s2[i]を返す。
```

### ft_memchr

```txt
文字列sからn文字目まで文字cを検索し、文字cが最初に出てきたアドレスを返す。文字列sの中に文字cがない場合はNULLを返す。
```

### ft_memcmp

```txt
文字列s1とs2をnバイト比較し、str1 == str2の時は0を返す。str1 != str2のときはstr1[i] - str2[i]を返す。
```

### ft_strnstr

```txt
元文字列haystackから検索文字列をneedleをそれぞれlen文字目まで比較し、文字列haystackに文字列needleが含まれていればneedleが見つかった場所のアドレスを返す。
文字列haystackに文字列needleが含まれていればNULLを返す。
```

### ft_atoi

```txt
ascii文字をint型に変換する関数。文字列strがint型に変換不可能な文字の場合、NULLを返す。
```

intの範囲に収まらない場合、C99 や C11 の仕様上は戻り値は未定義 (undefined) であることを考慮したプログラムになっている。

### ft_calloc

```txt
size * count分のメモリを確保し、メモリブロックを0にクリアする。
```

### ft_strdup

```txt
文字列s1のコピーを作成し、そのコピーした文字列のアドレスを返す。
```

## Part2 Additional functions

### ft_substr

```txt
文字列sのインデックスstartの位置から長さlenだけをコピーした新しい配列を作成して、返す。
```

startの位置が文字列sの長さを超えていた場合は空文字列を返す。

### ft_strjoin

```txt
文字列s1とs2を連結した新しい配列を作成し、返す。新しく作成した文字列の最後には当然終端文字'\0'が入る。
```

### ft_strtrim

```txt
文字列s1の両端から文字列setを取り除いた文字列を新しく作成し、返す。
```

get_size関数で文字列s1から文字列setを取り除いた後の文字列を出してて、変数sizeに代入している。
最後のft_strlcpy関数で文字列s1の最初にある文字列setを超えた場所からsize分、ft_strlcpyを使って配列を作成し、その配列を返している。

### ft_split

```txt
文字列sを文字cが入っている部分で分割する。返り値は当然2次元配列になる。
```

get_list_size関数の1つめのwhileは文字cが入ってない部分を、2つ目の部分は文字cの部分をスキップする。
countは2次元配列の個数をカウントする。

### ft_itoa

```txt
int型をascii文字に変換する関数。
```

pow_tenにはint型の10のべき乗を代入している。iには10を何乗するとpow_tenになるかの数値が入っている。
signにshort型をあえて使用しているのはバイト数の節約のため。

### ft_strmapi

```txt
文字列sの文字をコールバック関数fに渡して、その文字を変換した文字列を作成し、返す。
```

### ft_striteri

```txt
文字列sの文字をコールバック関数fに渡して、その文字を変換し、返す。
```

### ft_putchar_fd

```txt
文字cをファイルディスクリプタfdに出力する。
```

### ft_putstr_fd

```txt
文字列sをファイルディスクリプタfdに出力する。
```

### ft_putendl_fd

```txt
文字列sをファイルディスクリプタfdに出力し、改行を出力する。
```

### ft_putnbr_fd

```txt
int型nをファイルディスクリプタfdに出力する。
```

## Bonus part

### ft_lstnew

```txt
文字列sを持つリストの新しいリストを作成し、そのアドレスを返す。
```
