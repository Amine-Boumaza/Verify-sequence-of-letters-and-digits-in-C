#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct path *Tpath;
struct path
{
    int val;
    char c;
    struct path *next;
};

typedef struct graph *Tlist;
struct graph
{
    int val;
    struct graph *next;
    Tpath d;
};

Tlist addtoendlist(Tlist l, int v)
{
    Tlist p = malloc(sizeof(struct graph));
    p->next = NULL;
    p->d = NULL;
    p->val = v;

    if (l == NULL)
        l = p;
    else
    {
        Tlist q = l;
        while (q->next != NULL)
            q = q->next;
        q->next = p;
    }
    return l;
}

void addtoendpath(Tpath *l, int val, char c)
{
    Tpath p = malloc(sizeof(struct path));
    p->next = NULL;
    p->val = val;
    p->c = c;

    if (*l == NULL)
        *l = p;
    else
    {
        Tpath q = *l;
        while (q->next != NULL)
            q = q->next;
        q->next = p;
    }
}

int main()
{
    FILE *fp;
    char str[100];
    int num_of_letters = 0;
    Tlist graph = NULL;

    // Open the input file
    fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        printf("Cannot open file.\n");
        return 1;
    }

    // Read the input file line by line
    while (fgets(str, sizeof(str), fp))
    {
        Tlist p = NULL;
        for (int i = 0; i < strlen(str); i++)
        {
            // Verify the first condition
            if (i == 0 && (str[i] < 'a' || str[i] > 'z'))
            {
                printf("Error: The first element of the sequence must be a letter.\n");
                return 1;
            }

            // Create a new graph node for each character
            p = addtoendlist(p, i);
            if (str[i] >= 'a' && str[i] <= 'z')
            {
                num_of_letters++;
            }
            // Create a new path for each letter
            if (str[i] >= 'a' && str[i] <= 'z' && (i < 4 || num_of_letters % 2 != 0))
            {
                addtoendpath(&p->d, i + 1, str[i]);
            }

            // Verify the second condition
            if (i == strlen(str) - 1 && (num_of_letters % 2 == 0 || (num_of_letters >= 4 && !isdigit(str[i]))))
            {
                printf("Error: The sum of all letters in the sequence is not an odd number or the first 4 elements of the sequence are letters including the 1st element and the rest of the elements are digits.\n");
                return 1;
            }
        }
        // Add the graph node to the main graph list
        graph = addtoendlist(graph, p->val);
        graph->d = p->d;
    }

    if (num_of_letters % 2 == 1 && (num_of_letters >= 4 && isdigit(str[strlen(str) - 1])))
    {
        printf("The sequence follows the conditions.\n");
    }

    // Close the input file
    fclose(fp);

    return 0;
}