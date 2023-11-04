#include <cs50.h>
#include <stdio.h>
#include <string.h>

// If you want to know what it does: https://cs50.harvard.edu/x/2023/psets/2/bulbs/
// It converts each character of a message in binary and shows the 1s as yellow circles (so a lighten up bulb) and the 0s as dark circles
// e.g. Message: HI!
// ⚫🟡⚫⚫🟡⚫⚫⚫
// ⚫🟡⚫⚫🟡⚫⚫🟡
// ⚫⚫🟡⚫⚫⚫⚫🟡

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    string message = get_string("Message: \n");
    int messagelen = strlen(message);
    // The for loops scans through the message letter by letter
    for (int i = 0; i < messagelen; i++)
    {
        // Initialize an array of size 8 with all 0 (the message is represented by a grid of length 8 and height = number of characters)
        int array[BITS_IN_BYTE] = {0, 0, 0, 0, 0, 0, 0, 0};
        // n_bits is a counter that I used to fill the array with 0s and 1s in the correct order
        int n_bits = 0;
        // The while loop converts decimals to binary and fills the array with 0s and 1s
        while (message[i] > 0)
        {
            int bit_value = message[i] % 2;
            message[i] = message[i] / 2;
            // With the following line and the variable n_bits you can fill the array from the right to the left with the remiander of the divisions in the previous lines
            array[BITS_IN_BYTE - 1 - n_bits] = bit_value;
            n_bits += 1;
        }
        // Prints each charcter converted in binary as a series of yellow and black circles
        int j = 0;
        while (j < 8)
        {
            print_bulb(array[j]);
            j++;
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
