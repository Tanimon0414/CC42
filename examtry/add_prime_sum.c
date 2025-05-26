
#include <unistd.h>

int fuckin_atoi(char *str)
{
    int i;
    int n;
    i = 0;
    n = 0;
    while(*str >= 0 && *str <= 9)
    {
        n = n * 10 + (*str - '0');
        *str++;
    }
    return(n);
}

int main(int argc, char **argv)
{
    if(argc != 2 || argv[1][0] == '-' || argv[1][0] == '0' || argv[1][0] == '1' )
        return(write(1, "0\n", 2),0);
    int n;
    n = fuckin_atoi(argv[1]);
    int res;
    res = 0;
    res = add_prime_sum(n);
    return(res);
    
}
