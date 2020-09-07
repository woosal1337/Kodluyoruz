#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, string argv[])
{

    int l; // individual key position
    int v; // new converted key


// check no. of arguments given make sure there is only 1
    if (argc != 2)
    {
        printf("Usage: ./caesar k\n");

        return 1;
    }

    else
    {
        //Check that key is in the alphabet
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isalpha(argv[1][i])) // check through individual chars in the key is in the alphabet
            {
            }
            else
            {
                printf("Usage: ./caesar k\n");
                return 1;
            }
        }
    }

    string k = argv[1]; // get the ceasar KEY value convert into integar k[i] is each letter



    string s = get_string("plaintext: "); // get text
    printf("ciphertext: "); // print out cipher

// iterate through plain text letter by letter




    for (int i = 0, n = strlen(s), count = 0 ; i < n; i++) // iterate through each char of string
    {


        l =  count % strlen(k); // l is the position in the key

        if (islower(k[l]))
        {
            v = k[l] - 'a'; // v is the new converted key
            // printf("%i", v);
        }

        else if (isupper(k[l]))
        {
            v = k[l] - 'A'; // 75 - 65 = 10
            // printf("%i", v);
        }



        if (islower(s[i]))
        {
            printf("%c", (((s[i] - 'a') + v) % 26) + 'a'); // print out lowercase with key;
            count++;

        }
        else if (isupper(s[i]))
        {
            printf("%c", (((s[i] - 'A') + v) % 26) + 'A');  // print out uppercase with key;
            count++;
        }

        else

        {
            printf("%c", s[i]);

// printf("%i", v);
        }

    }


    printf("\n");
    return 0;



}