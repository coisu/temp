#include <unistd.h>

int main(int argc, char **argv)
{
    int i;
    int p;
    char *tmp;

    i = 0;
    p = 0;
    tmp = argv[1];
    while (tmp[i])
    {
        p = (p + (tmp[i] == '\"'));
        if (p == 1 && tmp[i] == '\"')
            tmp[i] *= -1;
        write (1, &tmp[i], 1);
        i++;
    }
    write (1, "\n", 1);
    return (0);
}