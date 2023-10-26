//Lab 1: Population Growth
// Determine how long it takes for a population of n individuals to reach a particular size. Each year yhere are n/3 births and n/4 deaths.
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int sp;
    do
    {
        sp = get_int("Start size: ");
    }
    while (sp < 9);
    // TODO: Prompt for end size
    int ep;
    do
    {
        ep = get_int("End size: ");
    }
    while (ep < sp);
    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    while (sp < ep)
    {
        sp = sp + sp / 3 - sp / 4;
        years++;
    }
    // TODO: Print number of years
    printf("Years: %i\n", years);
}
