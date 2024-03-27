#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentence(string text);
float calculate_index(int letter, int word, int sentence);
int main(void)
{
    string input = get_string("Text: ");

    int letter = count_letters(input);
    int word = count_words(input);
    int sentence = count_sentence(input);

    float index = calculate_index(letter, word, sentence);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }
}

//count letter function
int count_letters(string text)
{
    int count = 0;
    int n = strlen(text);

    for (int i = 0; i < n; i++)
    {
        int x = (int)text[i];

        if ((x >= 48 && x <= 57) || (x >= 65 && x <= 90) || (x >= 97 && x <= 122))
        {
            count++;
        }
    }

    return count;
}

//count word function
int count_words(string text)
{
    int count = 1;
    int n = strlen(text);

    for (int i = 0; i < n; i++)
    {
        int x = (int)text[i];

        if (x == 32)
        {
            count++;
        }
    }

    return count;
}

//count sentence function
int count_sentence(string text)
{
    int count = 0;
    int n = strlen(text);

    for (int i = 0; i < n; i++)
    {
        int x = (int)text[i];

        if ((x == 33) || (x == 46) || (x == 63))
        {
            count++;
        }
    }

    return count;
}

//calculate index
float calculate_index(int letter, int word, int sentence)
{
    float preL = ((float)letter / (float)word) * 10000.00;
    float preS = ((float)sentence / (float)word) * 10000.00;

    float L = round(preL) / 100.00;
    float S = round(preS) / 100.00;

    float index = (0.0588 * L) - (0.296 * S) - 15.8;

    index = round(index);

    return index;
}