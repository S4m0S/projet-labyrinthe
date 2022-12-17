#include "header.h"
int main(int argc, char *argv[])
{
    if(!init())
        return 1;
    printf("\n");
    printf("%i\n", argc);
    return 0;
}