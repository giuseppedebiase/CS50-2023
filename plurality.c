#include <cs50.h>
#include <stdio.h>
#include <string.h>

// If you want to know what this program does: https://cs50.harvard.edu/x/2023/psets/3/plurality/#specification
// This program simulates an election based on the plurality system (The candidate with the most votes wins)
// In this exercise most of the program was already written, the only parts to fill werr the functions vote and print_winner

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    // This loop scans the list of candidates and if the argument of vote is = to one of the candidates name
    // the counter for that candidates' votes increases b 1
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    // Code for finding the biggest number
    int max = 0;
    // This loops scans the number of votes that each candidate has,
    // each time it founds a new high among the number of votes max gets updated to that value
    // and the loop keeps iterating until it founds a new max (or the number of candidates ends)
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max)
        {
            max = candidates[i].votes;
        }
    }

    // The loops scans the same thing as the last one
    // if one (or more candidates if there is a tie) has a number of votes = max his/her name gets printed
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}
