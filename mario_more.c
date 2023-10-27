//Takes a number as input and draws two adjacent pyramids of # dvided by two spaces
//e.g. Pyramid height: 3
//  #  #
// ##  ##
//###  ###
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        do
        {
            n = get_int("Pyramid height: ");
        }
        while (n > 8);
    }
    while (n < 1);

    for (int i = n; i > 0; i--)
    {
        for (int j = i - 1; j > 0; j--)
        {
            printf(" ");
        }
        for (int k = 0; k < n - i + 1; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int k = 0; k < n - i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
