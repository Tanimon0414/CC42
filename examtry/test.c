
#include <stdio.h>
#include <unistd.h>


int count_words(char *str)
{
    int i;
    int words;
    i = 0;
    words = 0;
    while(str[i])
    {
        while(str[i] == ' ' || str[i] == '\t')
            i++;
        if(!str[i])
            break;
        words++;
        while(str[i] && str[i] != ' ' && str[i] != '\t')
            i++;
    }
    return(words);
}

int	main(void)
{
	char *str = "You hate people! But I love gatherings. Isn't it ironic?";
	printf("%d\n", count_words(str));
	return(0);
}