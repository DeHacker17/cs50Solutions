//
// Created by Kratos on 22/06/20.
//

#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
}
        pair;

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
bool recursion(int k);
void print_winner(void);

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
    //check50 cs50/problems/2020/x/tideman
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            rank++;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (ranks[i] != ranks[j])
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    //pair_count
    //pair[]
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int p = j;
            if (preferences[i][j] > preferences[p][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = p;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[p][i])
            {
                pairs[pair_count].winner = p;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    //Variables
    int newArr[pair_count];
    int temp = 0;
    int temp2 = 0;
    int temp3 = 0;
    int n = 0;

    //Insert elements of Margin Victory into newArr
    for (int i = 0; i < candidate_count; i++)
    {
        newArr[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        if (newArr[i] < 0)
        {
            newArr[i] *= -1;
        }
    }
    //Insertion sort... I think.
    for (int i = 1; i < pair_count; i++)
    {
        n = i - 1;
        temp = pairs[i].winner;
        temp2 = pairs[i].loser;
        temp3 = newArr[i];
        while (newArr[n] < newArr[i] && n >= 0)
        {
            //NewArr
            newArr[n + 1] = newArr[n];
            newArr[n] = temp3;
            //Winner
            pairs[n + 1].winner = pairs[n].winner;
            pairs[n].winner = temp;
            //Loser
            pairs[n + 1].loser = pairs[n].loser;
            pairs[n].loser = temp2;
            n = n - 1;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%d", preferences[i][j]);
        }
        printf("\n");
    }

    //Lock pairs
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        if (&recursion)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }

    //for (int i = 0; i < pair_count; i++)
    //{
    //    bool cycleCheck = recursion(pair_count);
//
    //    if (cycleCheck == true)
    //    {
    //        locked[pairs[i].winner][pairs[i].loser] = false;
    //        locked[pairs[i].loser][pairs[i].winner] = false;
    //    }
    //}
    return;
}

bool recursion(int k)
{
    if (pair_count <= 0)
    {
        return false;
    }

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (locked[pairs[i].loser][pairs[i].winner] == true)
            {
                return recursion(k - 1), true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[pairs[i].winner][pairs[i].loser] == true)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}