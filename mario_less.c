// This program takes in input a number between 1 and 8 (included) and gives in output a stair made of # the size of the number in input
// e.g Pyramid height: 3 would give as output the following:
//  #
// ##
//###
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
        printf("\n");
    }
}
