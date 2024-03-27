#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

string cipher_string(string word, int key);
int main(int argc, string argv[])
{

    //checks argument key
    if (argc == 2)
    {
        string key = argv[1];
        int n = strlen(key);

        for (int i = 0; i < n; i++)
        {
            if ((int)key[i] < 48 || (int)key[i] > 57)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);

    //prompt user input
    string input = get_string("plaintext:  ");

    //cipher input
    string output = cipher_string(input, key);


    //display
    printf("ciphertext: %s\n", output);


}




string cipher_string(string word, int key)
{
    char upper[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char lower[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int n = strlen(word);


    for (int i = 0; i < n; i++)
    {
        int a = 0;
        int b = 0;

        //uppercase alphabets
        for (int u = 65; u <= 90; u++)
        {
            if (u == (int)word[i])
            {
                a = (a + key) % 26;
                word[i] = upper[a];
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
            if (l == (int)word[i])
            {
                b = (b + key) % 26;
                word[i] = lower[b];
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
            if (x == (int)word[i])
            {
                word[i] = (char)word[i];
                break;
            }
        }

        //others
        for (int y = 91; y < 97; y++)
        {
            if (y == (int)word[i])
            {
                word[i] = (char)word[i];
                break;
            }
        }

        //others
        for (int z = 123; z <= 127; z++)
        {
            if (z == (int)word[i])
            {
                word[i] = (char)word[i];
                break;
            }
        }
    }

    return word;
}