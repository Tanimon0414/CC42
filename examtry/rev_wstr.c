
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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

int words_len(char *str, int j)
{
    int len;
    while(str[j] && str[j++] != ' ' && str[j++] != '\t')
        len++;
    return(len);
}

char *set_words(char *str, int *i)
{
    int len;
    char *busu;
    int j;
    j = 0;
    len = words_len(str, *i);
    busu = malloc((sizeof(char)*len + 1));
    while(j < len)
    {
        busu[j] = str[*i];
        (*i)++;
        j++;
    }
    busu[j] = '\0';
    return(busu);
}

void put_words(char *str)
{
    int i;
    i = 0;
    while(str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
}

int main(int argc, char **argv)
{
    int i;
    int words;
    char **res;
    int num;
    i = 0;
    num = 0;
    if(argc == 2)
    {
        words = count_words(argv[1]);
        res = malloc((sizeof(char *)) * words);
        while(num < words)
        {
            while(argv[1][i] == ' ' || argv[1][i] == '\t')
                i++;                 
            res[num] = set_words(argv[1], &i);
            num++;
        }
        while(num--)
        {
            put_words(res[num]);
            if(num > 0)
                write(1, " ", 1);
        }
    }
    write(1, "\n", 1);
    return(0);
}
