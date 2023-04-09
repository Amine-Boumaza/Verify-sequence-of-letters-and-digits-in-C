#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    FILE *fp;
    char str[100];
    int num_of_letters = 0, num_of_digits = 0, num_of_first_letters = 0, has_first_letter = 0, has_digits = 0;

    fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        printf("Cannot open file.\n");
        return 1;
    }

    while (fgets(str, sizeof(str), fp))
    {
        // Reset the counters for each line
        num_of_letters = 0;
        num_of_digits = 0;
        num_of_first_letters = 0;
        has_first_letter = 0;
        has_digits = 0;

        for (int i = 0; i < strlen(str); i++)
        {
            // Verify the first condition
            if (i == 0 && (str[i] < 'a' || str[i] > 'z'))
            {
                printf("Error: The first element of the sequence must be a letter.\n");
                fclose(fp);
                return 1;
            }

            // Count the number of letters and digits
            if (isalpha(str[i]))
            {
                num_of_letters++;
                if (i < 4)
                {
                    num_of_first_letters++;
                }
                else
                {
                    has_digits = 1;
                }
            }
            else if (isdigit(str[i]))
            {
                num_of_digits++;
                if (i < 4)
                {
                    has_first_letter = 1;
                }
            }
            else
            {
                printf("Error: The sequence contains invalid characters.\n");
                fclose(fp);
                return 1;
            }
        }

        // Check the first condition
        if (num_of_letters % 2 == 0)
        {
            printf("Error: The total number of letters in the sequence must be an odd number.\n");
            fclose(fp);
            return 1;
        }

        // Check the second condition
        if (num_of_first_letters == 4 && num_of_digits == strlen(str) - 5 && !has_first_letter)
        {
            printf("The sequence follows condition 2.\n");
            fclose(fp);
            return 1;
        }

        // Check for remaining letters
        if (num_of_letters > num_of_first_letters && !has_digits && num_of_letters % 2 == 1)
        {
            printf("The sequence follows condition 1.\n");
            fclose(fp);
            return 1;
        }
    }

    // If neither condition is satisfied, print an error message and exit
    printf("Error: The sequence does not follow any of the conditions.\n");
    fclose(fp);
    return 1;
}
