
unsigned char	reverse_bits(unsigned char octet)
{
	int i;
	i = 8;
	unsigned char res;
	res = 0;
	while (i--)
	{
		res = res * 2 + (octet % 2);
		octet = octet / 2;
	}
	return (res);
}
