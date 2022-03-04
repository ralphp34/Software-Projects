#include <stdlib.h>
#include "hashmap.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <glob.h>

int searchFile (char * word, char * doc_id)
{
        FILE * file_ptr;
        int num_occurances = 0;
        file_ptr = fopen(doc_id, "r");

        if (file_ptr == NULL)
        {
            printf("Error! No File Found\n");
            return -1;
        }
        char buf[1023];
        int found = 0;
        int l_num = 1;

        while (fgets(buf, 1023, file_ptr) != NULL)
        {
            for (int i = 0; i < 1023; i++)
            {
                if (buf[i] == '\n')
                {
                    buf[i + 0] = '\0';
                }
            }

            char space[] = " ";
            char * onlyWords = strtok(buf, space);

            while(onlyWords != NULL)
            {
                if (onlyWords != NULL)
                {
                    if (strcmp(word, onlyWords) == 0)
                    {
                        found = 1;
                        num_occurances++;
                    }
                }
                onlyWords = strtok(NULL, space);
            }
            l_num++;
            memset(buf, 0, sizeof buf);
        }

        if (found == 0)
        {
            printf("No matches found\n");
        }
        if (file_ptr)
        {
            fclose(file_ptr);
        }
        return num_occurances;
}

void populate(struct hashmap * hm, char * doc_id)
{
    FILE * file_ptr;
    file_ptr = fopen(doc_id, "r");

    if (file_ptr == NULL)
    {
        printf("Error! No File Found\n");
        return;
    }
    char buf[1023];
    int l_num = 1;
    while (fgets(buf, 1023, file_ptr) != NULL)
    {
        for (int i = 0; i < 1023; i++)
        {
            if (buf[i] == '\n')
            {
                buf[i + 0] = '\0';
            }
        }

        char space[] = " ";
        char * onlyWords = strtok(buf, space);

        while(onlyWords != NULL)
        {
            char * word = strdup(onlyWords);
            if (onlyWords != NULL)
            {
                strcpy(word, onlyWords);
                hm_put(hm, word, doc_id);
            }
            onlyWords = strtok(NULL, space);
        }
        l_num++;
        memset(buf, 0, sizeof buf);
    }
    if (file_ptr)
    {
        fclose(file_ptr);
    }    
}

// void stop_words (struct hashmap * hm, char * word, char * doc_id)
// {
//     FILE * file_ptr;
//     int num_occurances = 0;
//     file_ptr = fopen(doc_id, "r");

//     if (file_ptr == NULL)
//     {
//         printf("Error! No File Found\n");
//         return -1;
//     }
//     char buf[1023];
//     int found = 0;
//     int l_num = 1;

//     while (fgets(buf, 1023, file_ptr) != NULL)
//     {
//         for (int i = 0; i < 1023; i++)
//         {
//             if (buf[i] == '\n')
//             {
//                 buf[i + 0] = '\0';
//             }
//         }
//         char space[] = " ";
//         char * onlyWords = strtok(buf, space);

//         while(onlyWords != NULL)
//         {
//             if (onlyWords != NULL)
//             {

//                 //m_put(hm, word, doc_id);
//             }
//             onlyWords = strtok(NULL, space);
//         }
//         l_num++;
//         memset(buf, 0, sizeof buf);
//     }
    
//     if (file_ptr)
//     {
//         fclose(file_ptr);
//     } 

// }

struct hashmap * training (struct hashmap * hm)
{
    glob_t result;
    char * dir = "p5docs/*.txt";
    glob(dir, 0, NULL, &result);
    int numFiles = (int)result.gl_pathc;
    for (int i = 0; i < numFiles; i++)
    {
        populate(hm, result.gl_pathv[i]);
    }
    return hm;
}
