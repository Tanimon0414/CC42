
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

int	match_space(FILE *f)
{
	int	c;

	// isspace()が真を返す限り、文字を読み進める
	while ((c = fgetc(f)) != EOF && isspace(c))
	{
		// ループ内で何もしない
	}
	// 空白でない文字が見つかった場合、ストリームに1文字戻す
	if (c != EOF)
		ungetc(c, f);
	// ストリームエラーをチェック
	if (ferror(f))
		return (-1);
	return (0);
}

int	match_char(FILE *f, char c)
{
	int	next_c;

	next_c = fgetc(f);
	// 読み込んだ文字が期待する文字と一致すれば成功
	if (next_c == c)
		return (1);
	// 一致しない場合、読み込んだ文字をストリームに戻す
	if (next_c != EOF)
		ungetc(next_c, f);
	return (0);
}

int	scan_char(FILE *f, va_list ap)
{
	char	*p;
	int		c;

	// %cは空白を読み飛ばさない
	p = va_arg(ap, char *);
	c = fgetc(f);
	if (c == EOF)
		return (0);
	*p = (char)c;
	return (1);
}

int	scan_int(FILE *f, va_list ap)
{
	int		*p;
	long	n;
	int		sign;
	int		c;
	int		count;

	n = 0;
	sign = 1;
	count = 0;
	p = va_arg(ap, int *);
	c = fgetc(f);
	// 符号の処理
	if (c == '+' || c == '-')
	{
		if (c == '-')
			sign = -1;
		c = fgetc(f);
	}
	// 数字が続く限り読み込み、整数に変換
	while (isdigit(c))
	{
		n = n * 10 + (c - '0');
		count++;
		c = fgetc(f);
	}
	// 数字でない文字はストリームに戻す
	if (c != EOF)
		ungetc(c, f);
	// 1文字も数字を読んでいない場合は失敗
	if (count == 0)
		return (0);
	*p = (int)(n * sign);
	return (1);
}

int	scan_string(FILE *f, va_list ap)
{
	char	*p;
	int		c;
	int		count;

	count = 0;
	p = va_arg(ap, char *);
	// 空白文字に遭遇するまで読み込む
	while ((c = fgetc(f)) != EOF && !isspace(c))
	{
		*p++ = (char)c;
		count++;
	}
	// 最後に読み込んだ空白文字はストリームに戻す
	if (c != EOF)
		ungetc(c, f);
	// 1文字も読み込んでいない場合は失敗
	if (count == 0)
		return (0);
	// 文字列の終端にヌル文字を追加
	*p = '\0';
	return (1);
}

int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
	case 'c':
		return (scan_char(f, ap));
	case 'd':
		match_space(f);
		return (scan_int(f, ap));
	case 's':
		match_space(f);
		return (scan_string(f, ap));
	case EOF:
		return (-1);
	default:
		return (-1);
	}
}

int	ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int	nconv;
	int	c;

	nconv = 0;
	c = fgetc(f);
	if (c == EOF)
		return (EOF);
	ungetc(c, f);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break ;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break ;
		}
		else if (match_char(f, *format) != 1)
			break ;
		format++;
	}
	if (ferror(f))
		return (EOF);
	return (nconv);
}

int	ft_scanf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return (ret);
}
