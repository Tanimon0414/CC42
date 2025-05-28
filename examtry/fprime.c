
#include <stdio.h>
#include <stdlib.h>

int find_next_prime(int n)
{
    int waru;
    while(1)
    {
        waru = 2;
        while(n % waru != 0 && n >= waru * waru)
            waru++;
        if(n % waru == 0)
            n++;
        else
            break;
    }
    return(n);

}

int main(int argc, char **argv)
{
    int origin;
    int prime;
    prime = 2;
    if(argc == 2)
    {
        origin = atoi(argv[1]);
        if(origin == 1)
        {
            printf("1\n");
            return(0);
        }
        while(origin > 1)
        {
            while(origin % prime == 0)
            {
                origin = origin / prime;
                if(origin == 1)
                {
                    printf("%d", prime);
                    break;
                }
                printf("%d*", prime);
            }
            prime = find_next_prime(prime + 1);
        }
    }
    printf("\n");
    return(0);
}
