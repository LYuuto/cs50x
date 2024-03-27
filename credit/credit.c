#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    char check_type(long cardnumber);
    bool checksum(long cardnumber);

    long cardnumber = get_long("Card number: ");
    char type = check_type(cardnumber);

//AMEX_FINAL
    if (type == 'a')
    {
        bool validity = checksum(cardnumber);

        if (validity == true)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

//MASTERCARD_FINAL
    else if (type == 'm')
    {
        bool validity = checksum(cardnumber);

        if (validity == true)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

//VISA_FINAL
    else if (type == 'v')
    {
        bool validity = checksum(cardnumber);

        if (validity == true)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    else
    {
        printf("INVALID\n");
    }
}

char check_type(long cardnumber)
{
    //AMEX
    if (cardnumber >= 34 * pow(10, 13) && cardnumber < 35 * pow(10, 13))
    {
        return 'a';
    }

    else if (cardnumber >= 37 * pow(10, 13) && cardnumber < 38 * pow(10, 13))
    {
        return 'a';
    }

    //MASTERCARD
    else if (cardnumber >= 51 * pow(10, 14) && cardnumber < 56 * pow(10, 14))
    {
        return 'm';
    }

    //VISA
    else if (cardnumber >= 4 * pow(10, 12) && cardnumber < 5 * pow(10, 12))
    {
        return 'v';
    }

    else if (cardnumber >= 4 * pow(10, 15) && cardnumber < 5 * pow(10, 15))
    {
        return 'v';
    }

    //INVALID
    else
    {
        return 'i';
    }
}

bool checksum(long cardnumber)
{
    int one = cardnumber % 10;
    int two_ = (((cardnumber % 100) - (cardnumber % 10)) / 10) * 2;
    int three = ((cardnumber % 1000) - (cardnumber % 100)) / 100;
    int four_ = (((cardnumber % 10000) - (cardnumber % 1000)) / 1000) * 2;
    int five = ((cardnumber % 100000) - (cardnumber % 10000)) / 10000;
    int six_ = (((cardnumber % 1000000) - (cardnumber % 100000)) / 100000) * 2;
    int seven = ((cardnumber % 10000000) - (cardnumber % 1000000)) / 1000000;
    int eight_ = (((cardnumber % 100000000) - (cardnumber % 10000000)) / 10000000) * 2;
    int nine = ((cardnumber % 1000000000) - (cardnumber % 100000000)) / 100000000;
    int ten_ = (((cardnumber % 10000000000) - (cardnumber % 1000000000)) / 1000000000) * 2;
    int eleven = ((cardnumber % 100000000000) - (cardnumber % 10000000000)) / 10000000000;
    int twelve_ = (((cardnumber % 1000000000000) - (cardnumber % 100000000000)) / 100000000000) * 2;
    int thirteen = ((cardnumber % 10000000000000) - (cardnumber % 1000000000000)) / 1000000000000;
    int fourteen_ = (((cardnumber % 100000000000000) - (cardnumber % 10000000000000)) / 10000000000000) * 2;
    int fifteen = ((cardnumber % 1000000000000000) - (cardnumber % 100000000000000)) / 100000000000000;
    int sixteen_ = (((cardnumber % 10000000000000000) - (cardnumber % 1000000000000000)) / 1000000000000000) * 2;



    int two = (two_ / 10) + (two_ % 10);
    int four = (four_ / 10) + (four_ % 10);
    int six = (six_ / 10) + (six_ % 10);
    int eight = (eight_ / 10) + (eight_ % 10);
    int ten = (ten_ / 10) + (ten_ % 10);
    int twelve = (twelve_ / 10) + (twelve_ % 10);
    int fourteen = (fourteen_ / 10) + (fourteen_ % 10);
    int sixteen = (sixteen_ / 10) + (sixteen_ % 10);


    // adding 2nds
    int x = two + four + six + eight + ten + twelve + fourteen + sixteen;
    int y = x + one + three + five + seven + nine + eleven + thirteen + fifteen;

    int z = y % 10;

    if (z == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}