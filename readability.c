#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// To know what it does: https://cs50.harvard.edu/x/2023/psets/2/readability/
// It's a program that calculates the approximate grade level (U.S. system) needed to comprehend some text using the Coleman-Liau index.
// C-L index = 0.0588 * L - 0.296 * S - 15.8
// L = n.° letters per 100 words, S = n.° sentences per 100 words

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    float L = ((float) letters / words) * 100;
    float S = ((float) sentences / words) * 100;

    float index = (0.0588 * L) - (0.296 * S) - 15.8;
    int index_int = round(index);
    if (index_int < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index_int > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index_int);
    }
}

int count_letters(string text)
{
    int nletters = 0;
    int len_text = strlen(text);
    // This for loop scans through the text and if the char is a letters adds 1 to the letter counter
    for (int i = 0; i < len_text; i++)
    {
        // isalpha is a function that gives back a value > 0 if the char is a letter (be it in lower or uppercase)
        if (isalpha(text[i]) > 0)
        {
            nletters += 1;
        }
    }
    return nletters;
}

int count_words(string text)
{
    int nspaces = 0;
    int len_text = strlen(text);
    // This loops scans through the text and if it finds a blank spaces adds 1 to the nspaces counter
    for (int j = 0; j < len_text; j++)
    {
        // isblank is basically isalpha for spaces and tabs
        if (isblank(text[j]) > 0)
        {
            nspaces += 1;
        }
    }
    // You can find blanks only between words so the number of words is the number of blanks + 1
    int nwords = nspaces + 1;
    return nwords;
}

int count_sentences(string text)
{
    int n_punct = 0;
    int len_text = strlen(text);
    for (int k = 0; k < len_text; k++)
    {
        if (text[k] == '.' || text[k] == '?' || text[k] == '!')
        {
            n_punct += 1;
        }
    }
    // Sentences always ends with ".", "?" or "!" (at least for this index) so the number of sentences = number of those punctuation marks.
    // For this exercise they ask you to ignore the cases in which words end with a punctuation mark but are not the end of a sentence (e.g. suffixes like Mr. or Mrs.)
    int n_sentences = n_punct;
    return n_sentences;
}
