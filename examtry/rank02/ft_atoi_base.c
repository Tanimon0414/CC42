
int	ft_strchr(const char c) {
  int i;
  char *base = "0123456789abcdef";
  i = 0;
  while (c != base[i])
    i++;
  return (i);
}
int	ft_atoi_base(const char *str, int str_base) {
  int i;
  int n;
  int res;
  int sign;

  i = 0;
  res = 0;
  n = str_base;
  sign = 1;
  while ((str[i] >= 9 && str[i] <= 12) || str[i] == 32)
    i++;
  if (str[i] == '+' || str[i] == '-') {
    if (str[i] == '-')
      sign = -1;
    i++;
  }
  while (str[i]) {
    res = res * n + (ft_strchr(str[i]));
    i++;
  }
  return (sign * res);
}
#include <stdio.h>


int	main(void) {
  char *str = "1a4";
  int b;
  b = 16;
  printf("%d\n", ft_atoi_base(str, b));
  return (0);
}

直し;
int	ft_atoi_base(const char *str, int base) {
  int i = 0;
  int sign = 1;
  int res = 0;

  // 1) 空白類をスキップ (スペース/タブ/改行など)
  while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
         str[i] == '\f' || str[i] == '\r')
    i++;

  // 2) 符号処理
  if (str[i] == '+' || str[i] == '-') {
    if (str[i] == '-')
      sign = -1;
    i++;
  }

  // 3) 文字ごとに数字に変換
  while (str[i]) {
    int digit;
    char c = str[i];

    if (c >= '0' && c <= '9')
      digit = c - '0';
    else if (c >= 'a' && c <= 'f')
      digit = c - 'a' + 10;
    else if (c >= 'A' && c <= 'F')
      digit = c - 'A' + 10;
    else
      break ; // それ以降は変換しない

    // 4) 基数外の数字ならここで終了
    if (digit >= base)
      break ;

    res = res * base + digit;
    i++;
  }

  return (res * sign);
}
