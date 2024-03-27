#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
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
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    int n = strlen(word);
    // TODO: Compute and return score for string
    //make all uppercase
    for (int i = 0; i < n; i++)
    {
        word[i] = toupper(word[i]);
    }

    //assign point to each word
    int pt[n];
    for (int i = 0; i < n; i++)
    {
        int a = 0;
        for (int j = 65; j <= 90; j++)
        {
            if (j == (int) word[i])
            {
                pt[i] = POINTS[a];
                break;
            }
            else
            {
                a++;
            }
        }

        for (int j = 64; j >= 0; j--)
        {
            if (j == (int) word[i])
            {
                pt[i] = 0;
                break;
            }
        }

        for (int j = 123; j <= 127; j++)
        {
            if (j == (int) word[i])
            {
                pt[i] = 0;
                break;
            }
        }
    }

    //adding all points
    int p = 0;

    for (int i = 0; i < n; i++)
    {
        p = p + pt[i];
    }

    return p;

}
