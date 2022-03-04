#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <glob.h>
#include "hashmap.h"

int read_query(struct hashmap * hm)
{

    printf("Enter the search string or X to exit:\n");
    char query[100];
    char * comm = "X";
    scanf("%s", query);
    if(strcmp(query, comm) == 0)
    {
        return -1;
    }
    fgets(query, 100, stdin);
    ///printf("QUERY %s\n", query);
    rank(hm, query);
    return 0;
}


void rank(struct hashmap *hm, char *query)
{
    glob_t result;
    char * dir = "p5docs/*.txt";
    glob(dir, 0, NULL, &result);
    int numFiles = (int)result.gl_pathc;
    printf("Searching %d files...\n", numFiles);
    printf("\n");
    char space[] = " ";
    int length = 0;


    for (int i = 0; i < 100; i++)
    {
        if (query[i] == '\n')
        {
            query[i + 0] = '\0';
            query[i + 1] = '\n';
        }
    }

    int searchCount[numFiles][100];
    int notFound = 0;
    printf("Hello");
    for (int i = 0; i < numFiles; i++)
    {
        char * temp = strdup(query);
        char * onlyWords = strtok(temp, space);
        int count = 0;
        while (onlyWords != NULL)
        {
            char * word = strdup(onlyWords);
            if (onlyWords != NULL)
            {
                strcpy(word, onlyWords);
                searchCount[i][count] = hm_get(hm, word, result.gl_pathv[i]);
                if (searchCount[i][count] != 0)
                {

                    notFound = 1;
                }
                count++;
            }
            onlyWords = strtok(NULL, space);
        }
        searchCount[i][count] = -1;
        length = count;

    }

    if (notFound == 0)
    {
        printf("No words in query.\n");
        return;
    }

    int docNumFound = 0;
    double idf[length];
    
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < numFiles; j++)
        {
            if (searchCount[j][i] != 0)
            {
                docNumFound++;
            }
        }

        if (docNumFound != 0)
        {
            double temp = 3.0 / docNumFound;
            idf[i] = log10(temp);
        }
        else 
        {
            idf[i] = 0;
        }
        docNumFound = 0;
    }

    double tfidf[numFiles][length];
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < numFiles; j++)
        {
            tfidf[j][i] = searchCount[j][i] * idf[i];
        }
    }

        double bubbleSort[numFiles];
    for (int i = 0; i < numFiles; i++)
    {
        bubbleSort[i] = 0;
    }
    for (int i = 0; i < numFiles; i++)
    {
        for (int j = 0; j < length; j++)
        {
            //printf("%.2f ", tfidf[i][j]);
            if (j == length - 1)
            {
                printf("\n");
            }
        }
    }

    int counter = 0;
    for (int i = 0; i < numFiles; i++)
    {
        while (counter != length)
        {
            bubbleSort[i] = tfidf[i][counter] + bubbleSort[i];
            counter++;
        }
        counter = 0;
    }

    char * docs[numFiles];
    for (int i = 0; i < numFiles; i++)
    {
        docs[i] = result.gl_pathv[i];
    }

    for (int i = 0; i < numFiles - 1; i++)
    {
        for (int j = 0; j < numFiles - i - 1; j++)
        {
            if (bubbleSort[j] > bubbleSort[j + 1])
            {
                double temp = bubbleSort[j];
                bubbleSort[j] = bubbleSort[j + 1];
                bubbleSort[j + 1] = temp;
                char * temp2 = docs[j];
                docs[j] = docs[j + 1];
                docs[j + 1] = temp2;
            }
        }
    }

    for (int i = numFiles - 1; i > -1; i--)
    {
        // DOCUMENTS WITH TFIDF SCORE 0 ARE NOT PRINTED TO CONSOLE
        if (bubbleSort[i] != 0)
        {
            printf("%s\n", docs[i]);
        }
    }

    FILE *file_ptr;
    file_ptr = fopen("p5docs/search_scores.txt", "a");
    if (file_ptr == NULL)
    {
        printf("ERROR!\n");
        return;
    }
    for (int i = numFiles - 1; i > -1; i--)
    {
        fprintf(file_ptr, "%s:%.3f\n", docs[i], bubbleSort[i]);
    }
    fprintf(file_ptr, "-------------------\n");
    fclose(file_ptr);

}
