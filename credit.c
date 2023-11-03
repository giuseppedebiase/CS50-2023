#include <cs50.h>
#include <stdio.h>

//if you want to know what this program does: https://cs50.harvard.edu/x/2023/psets/1/credit/ 
//it basically uses the Luhn's Algorithm on a credit card number and gives back what kind ocredit card it is (Mastercard, Visa or American Express)

//this program "extracts" certain digits from a number (called credit) and does some mathematical operations with them
//to get a certain digit from the credit I divided the credit by a power of 10 that is a order of magnitude greater than the position of the the digit that i wanted and got the remainder with the % operator
//then to have the single digit without the number that followed the digit that i wanted i divided the remainder of the previous operation by a power of 10 equal to the order of magnitude of the digit that i wanted

// e.g. credit = 12345 and i want the number 3, to do this you can:
// 12345 % 1000 = 345
// 345 / 100 = 3.45, but the value in an int so 3.45 = 3
long power_10(int k);
void cardtype(long credit);
int main(void)
{
    long credit = get_long("Credit: ");
    int checksum1 = 0;
    for (int i = 1; power_10(i) <= credit * 10; i = i + 2)
    {
        long a = power_10(i);
        long c = credit % a;
        int b = c / (power_10(i - 1));
        checksum1 = checksum1 + b;
    }

    int checksum2 = 0;
    for (int i = 2; power_10(i) <= credit * 10; i = i + 2)
    {
        long a = power_10(i);
        long c = credit % a;
        int b = c / (power_10(i - 1));
        b = b * 2;
        if (b > 9)
        {
            int b_unit = b % 10;
            int b_dec = b % 100;
            b_dec = b_dec / 10;
            checksum2 = checksum2 + b_unit + b_dec;
        }
        else
        {
            checksum2 = checksum2 + b;
        }
    }
    int checksumtot = checksum1 + checksum2;

    if (checksumtot % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        cardtype(credit);
    }
}

long power_10(int k)
{
    //function used to calculate 10 to the power of something
    long a = 1;
    for (int i = 0; i < k; i++)
    {
        a = a * 10;
    }
    return a;
}

void cardtype(long credit)
{
    //MASTERCARD OR VISA (16 DIGITS)
    if (credit >= power_10(15) && credit < power_10(17))
    {
        int first_two = credit / power_10(14);
        if (first_two > 39 && first_two < 50)
        {
            printf("VISA\n");
        }
        else if (first_two > 50 && first_two < 56)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    //AMERICAN EXPRESS (15 DIGITS)
    else if (credit >= power_10(14) && credit < power_10(16))
    {
        int first_two = credit / power_10(13);
        if (first_two == 34 || first_two == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    //VISA (13 DIGITS)
    else if (credit >= power_10(12) && credit < power_10(14))
    {
        int first_two = credit / power_10(12);
        if (first_two == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    else
    {
        printf("INVALID\n");
    }
}
