#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// If you want to know what it does: https://cs50.harvard.edu/x/2023/psets/2/substitution/
// It's a substitution cipher that takes a key (in the CLI) and a message (called plain text) and gives back an ecrypted message

int main(int argc, string argv[])
{
    // the program takes only one argument (the key) besides the name of the program
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // The program gives an error if the key contain a number of character less than the numbers of the letters of the alphabet
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // The program gives an error if the key contain anything besides the letter of the alphabet
    for (int k = 0; k < 26; k++)
    {
        if (isalpha(argv[1][k]) < 1)
        {
            printf("You key must contain only letters.\n");
            return 1;
        }
    }

    //Checks that each letter is present only one time, be it in lowercase or uppercase
    bool isOne = true;
    int a = 0;
    while (isOne == true && a < 26)
    {
        int countletter = 0;
        for (int j = 0; j < 26; j++)
        {
            if (argv[1][a] == toupper(argv[1][j]) || argv[1][a] == tolower(argv[1][j]))
            {
                countletter += 1;
            }
        }
        if (countletter != 1)
        {
            printf("Each letter must be present in the key one and one time only!\n");
            isOne = false;
            return 1;
        }
        a++;
    }

    //plaintext is the message to encrypt
    string plaintext = get_string("plain text: \n");
    int lenplaintext = strlen(plaintext);
    //cyphertext is the array that will contain each of the encrypted letters
    int ciphertext[lenplaintext];
    //This loop takes the letter in the plain text, calculates the position that that letters has in the alphabet (A = 1, B = 2, C = 3 ...)
    //Then checks to what letter in the key that numbers correspondes to 
    //e.g. the first letter in the plaintext is A, A (in ASCII) is 65, 
    //to get the position in which A is present in the alphabet you can subtract 64 to the ASCII value
    //checks what letters in present in the key in the position obtained through the ASCII - 65
    //adds it to the ciphertext array
    //In ASCII A is 65 and a is 97
    for (int i = 0; i < lenplaintext; i++)
    {
        if (islower(plaintext[i]) > 0)
        {
            int positionkey = plaintext[i] - 96 - 1;
            ciphertext[i] = tolower(argv[1][positionkey]);
        }
        else if (isupper(plaintext[i]) > 0)
        {
            int positionkey = plaintext[i] - 64 - 1;
            ciphertext[i] = toupper(argv[1][positionkey]);
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    printf("ciphertext: ");
    for (int j = 0; j < lenplaintext; j++)
    {
        printf("%c", ciphertext[j]);
    }
    printf("\n");
}
