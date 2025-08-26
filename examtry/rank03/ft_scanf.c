
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

int	match_space(FILE *f)
{
	// You may insert code here
	return (0);
}

int	match_char(FILE *f, char c)
{
	int	next_c;

	next_c = fgetc(f);
	if (next_c == c)
		return (1);
	if (next_c != EOF)
		ungetc(next_c, f);
	return (0);
}

int	scan_char(FILE *f, va_list ap)
{
	char	*p;
	int		c;

	p = va_arg(ap, char *);
	c = fgetc(f);
	if (c == EOF)
		return (0);
	*p = (char)c;
	return (1);
}

int	scan_int(FILE *f, va_list ap)
{
	// You may insert code here
	return (0);
}

int	scan_string(FILE *f, va_list ap)
{
	// You may insert code here
	return (0);
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
