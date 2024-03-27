#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string convert_cipher(string text, string keyarray);
int main(int argc, string argv[])
{
    string key = argv[1];

    //checks argument key
    if (argc == 2)
    {
        int n = strlen(key);

        //check for number of characters
        if (n != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }

        //check for allowing only upper/lowercase alphabets
        for (int i = 0; i < n; i++)
        {
            int x = (int)key[i];
            if ((x >= 65 && x <= 90) || (x >= 97 && x <= 122))
            {
                continue;
            }
            else
            {
                printf("Key must only contain alphabetical characters.\n");
                return 1;
            }
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // key to uppercase
    for (int i = 0; i < 26; i++)
    {
        key[i] = toupper(key[i]);
    }

    //check for repeated characters
    for (int i = 0; i < 26; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if ((int)key[i] == (int)key[i - j])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
            else
            {
                continue;
            }
        }
    }

    string input = get_string("plaintext:  ");

    string output = convert_cipher(input, key);

    printf("ciphertext: %s\n", output);
}

string convert_cipher(string text, string keyarray)
{
    int n = strlen(text);

    //making lower case array
    char keyarraylower[26];
    for (int i = 0; i < 26; i++)
    {
        keyarraylower[i] = tolower(keyarray[i]);
    }

    for (int i = 0; i < n; i++)
    {
        int a = 0;
        int b = 0;

        //uppercase alphabets
        for (int u = 65; u <= 90; u++)
        {
            if ((int)text[i] == u)
            {
                text[i] = keyarray[a];
                break;
            }
            else
            {
                a++;
            }
        }

        //lowercase alphabets
        for (int l = 97; l <= 122; l++)
        {
            if ((int)text[i] == l)
            {
                text[i] = keyarraylower[b];
                break;
            }
            else
            {
                b++;
            }
        }

        //others
        for (int x = 0; x < 65; x++)
        {
            if ((int)text[i] == x)
            {
                text[i] = (char)text[i];
                break;
            }
        }

        //others
        for (int y = 91; y < 97; y++)
        {
            if ((int)text[i] == y)
            {
                text[i] = (char)text[i];
                break;
            }
        }

        //others
        for (int z = 123; z <= 127; z++)
        {
            if ((int)text[i] == z)
            {
                text[i] = (char)text[i];
                break;
            }
        }
    }


    return text;
}