#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

//To know what it does: https://cs50.harvard.edu/x/2023/labs/2/

// Points assigned to each letter of the alphabet
// A = 1 pt, B = 3 pt, C = 3pt ...
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else
    {
        (score1 > score2) ? printf("Player 1 wins!\n") : printf("Player 2 wins!\n");
    }
}

int compute_score(string word)
{
    int k = strlen(word);
    int score = 0;
    // TODO: Compute and return score for string
    // The first for loop scans each letter of the word
    for (int i = 0; i < k; i++)
    {
        //The following line converts lowercase to uppercase
        word[i] = toupper(word[i]);
        //The following line gives 0 point everything that isn't a capital letter
        if (word[i] < 65 || word[i] > 90)
        {
            score += 0;
        }
        else
        {
            //The second loop "scans" the POINTS array
            for (int j = 1; j < 27; j++)
            {
                //a "converts" the letter word[i] into the position that word[i] has in the alphabet (A=1, B=2, C=3 ...)
                int a = word[i] - 64;
                //The following if check if a is equal to j (which similarly to a represents the word of the alphabet in the same way that a does for the word entered by the user), 
                //if the "letter" in the word == the "letter" in the POINTS array the score is updated
                if (a == j)
                {
                    score += POINTS[j - 1];
                }
            }
        }
    }
    return score;
}
