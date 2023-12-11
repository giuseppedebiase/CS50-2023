#include <cs50.h>
#include <stdio.h>
#include <string.h>

/* If you want to know what it does: https://cs50.harvard.edu/x/2023/psets/3/tideman/ 
This programs runs a made up election choosing the winner via the tideman algorithm
NOTE: The lines between "Max number of candidates" and the last line of main were already written, the job of the student was to complete the rest
NOTE 2: After struggling a few days witht he lock_pairs function I read this article that gives a hint on how to do it: https://gist.github.com/nicknapoli82/6c5a1706489e70342e9a0a635ae738c9 
              ._      _.
             /  `""""`  \
        .-""`'-..____..-'`""-.
      /`\                    /`\
    /`   |                  |   `\
   /`    |                  |    `\
  /      |                  |      \
 /       /                  \       \
/        |    :) Tideman    |        \
'-._____.|                  |._____.-'
         |                  |
         |                  |
         |                  |
         \                  |
         /                  |
         |                  \
         |                  |
         '._              _.'
            `""--------""`    Tshirt Art by Joan Stark 
*/

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void cycle(int W, int w, int l, pair lpairs[], int lock_pair_count, int c_count[]);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    /* For every voter the program creates an array called ranks
    each rank takes the index of the candidate name in the argv array
    E.g. list of candidate: Bob Alice, if the voter chooses Alice as first preference and Bob ranks[0]=1 and ranks[1]=0*/
    
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    /* goes through the ranks array and makes a comparison between each possible pair of candidates,
    if in this array candidate number i is in a higher position than candidate number j then 
    the preferences array gets updatd in the [i][j] position
    */
    for (int a = 0; a < candidate_count; a++)
    {
        for (int b = 0; b < candidate_count; b++)
        {
            if (a < b)
            {
                int i = ranks[a];
                int j = ranks[b];
                preferences[i][j] += 1;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                int a = pair_count;
                pairs[a].winner = i;
                pairs[a].loser = j;
                pair_count += 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    /* Bubble sort
    "Strength of vistory" is the difference between the n.° of people who preferred candidate i over j - the n.° of people who preferred j over i
    */
    for (int c = 0; c < pair_count; c++)
    {
        for (int a = 0; a < pair_count - 1; a++)
        {
            int b = a + 1;
            if (b < pair_count)
            {
                int i = pairs[a].winner;
                int j = pairs[a].loser;
                int margin_vic1 = preferences[i][j] - preferences[j][i];

                i = pairs[b].winner;
                j = pairs[b].loser;
                int margin_vic2 = preferences[i][j] - preferences[j][i];

                if (margin_vic1 < margin_vic2)
                {
                    pair placeholder = pairs[b];
                    pairs[b] = pairs[a];
                    pairs[a] = placeholder;
                }
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // lpairs contains only the already locked pairs
    int lock_pair_count = 1;
    pair lpairs[pair_count];

    // This for fills the lpairs array with non existant candidates
    for (int i = 0; i < pair_count; i++)
    {
        lpairs[i].winner = 999;
        lpairs[i].loser = 999;
    }

    for (int i = 0; i < pair_count; i++)
    {
        int w = pairs[i].winner;
        int l = pairs[i].loser;
        /* The difference between W and w is the W is "constant", during the traversal of the graph to find cycles w and l changes (I used recursion in the cycle function) but W stays the same 
        so W is the winner of the pair with which we begin the search of the (possible) cycles
        */
        int W = pairs[i].winner;
        // c_count counts of pair that, if locked, would lead to a cycle
        int c_count[1] = {0};
        cycle(W, w, l, lpairs, lock_pair_count, c_count);
        if (c_count[0] == 0)
        {
            locked[w][l] = true;
            lpairs[lock_pair_count - 1] = pairs[i];
            lock_pair_count += 1;
        }
    }
    return;
}

void cycle(int W, int w, int l, pair lpairs[], int lock_pair_count, int c_count[])
{
    for (int i = 0; i < lock_pair_count; i++)
    {
        if (lpairs[i].winner == l && lpairs[i].loser == W)
        {
            c_count[0] += 1;
        }
        else if (lpairs[i].winner == l)
        {
            cycle(W, l, lpairs[i].loser, lpairs, lock_pair_count, c_count);
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int j = 0; j < candidate_count; j++)
    {
        int c = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            c += locked[i][j];
        }
        if (c == 0)
        {
            // If the jth candidates has 0 other candidates locked over it then j is the origin of the graph and thus the winner
            printf("%s\n", candidates[j]);
            // Only one winner
            return;
        }
    }
    return;
}
