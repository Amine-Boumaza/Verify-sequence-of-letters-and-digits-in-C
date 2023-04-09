#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    FILE *fp;
    char str[100];
    int num_of_letters = 0;
    int num_of_digits = 0;
    int num_of_first_letters = 0;

    fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        printf("Cannot open file.\n");
        return 1;
    }

    while (fgets(str, sizeof(str), fp))
    {

        for (int i = 0; i < strlen(str); i++)
        {

            if (i == 0 && (str[i] < 'a' || str[i] > 'z'))
            {
                printf("Error: The first element of the sequence must be a letter.\n");
                fclose(fp);
                return 1;
            }

            if (isalpha(str[i]))
            {
                num_of_letters++;
                if (i < 4)
                    num_of_first_letters++;
            }
            else if (isdigit(str[i]))
            {
                num_of_digits++;
            }
        }
    }

    if (num_of_letters % 2 == 1)
    {
        printf("The sequence follows condition 1.\n");
        return 1;
    }

    if (num_of_first_letters == 4 && num_of_digits == strlen(str) - 4)
    {
        printf("The sequence follows condition 2.\n");
        return 1;
    }

    printf("Error: The sequence does not follow any condition.\n");
    fclose(fp);
    return 1;

    fclose(fp);

    return 0;
}
