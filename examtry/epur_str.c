
#include <unistd.h>

int main(int argc, char **argv)
{
    int i;
    int flag;
    if(argc == 2)
    {
        i = 0;
        flag = 0;
        while(argv[1][i])
        { 
            while(argv[1][i] == ' ' || argv[1][i] == '\t')  
                i++;
            if(!argv[1][i])
                break;
            if(flag == 1)
                write(1," ", 1);
            flag = 1;
            while(argv[1][i] && argv[1][i] != ' ' && argv[1][i] != '\t')
            {
                write(1, &argv[1][i], 1);
                i++;
            } 
        }
    }
    write(1,"\n", 1);
    return(0);
}
