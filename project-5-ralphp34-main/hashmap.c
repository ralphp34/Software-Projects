#include "hashmap.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>


struct hashmap * hm_create(int num_buckets)
{
    struct hashmap * hm = calloc(sizeof(struct hashmap), 1);
    hm->map = calloc(sizeof(struct llnode*), num_buckets);
    hm->num_buckets = num_buckets;
    for (int i = 0; i < num_buckets; i++)
    {
        hm->map[i] = NULL;
    }
    hm->num_elements = 0;
    return hm;
}

int hm_get(struct hashmap* hm, char* word, char* document_id)
{
    struct llnode * node = (calloc(sizeof(struct llnode), 1));
    node->word = word;
    node->document_id = document_id;

    for (int i = 0; hm->num_buckets; i++)
    {
        struct llnode * current = hm->map[i]; 
        while (current != NULL)
        {
            if ((strcmp(node->word, current->word) == 0) && ((strcmp(node->document_id, current->document_id) == 0)))

            {
                return current->num_occurrences;
            }
            current = current->next;
        }
    }
    return -1;
}

void hm_put(struct hashmap* hm, char* word, char* document_id)
{
    int b_number; 
	b_number = hash(hm, word);
    int num_occurrences = 1;

    struct llnode * node = (calloc(sizeof(struct llnode), 1));
    node->word = word;
    node->document_id = document_id;

    for (int i = 0; i < hm->num_buckets; i++)
	{
		struct llnode * current = hm->map[i]; 


        while (current != NULL)
		{
			if ((strcmp(current->word, current->word) == 0) && ((strcmp(current->document_id, current->document_id) == 0)))
			{
                current->num_occurrences = current->num_occurrences + 1;
                return;
            }
        }
    }

    if (hm->map[b_number] == NULL)
	{
		hm->map[b_number] = (struct llnode *)malloc(sizeof(struct llnode));
		hm->map[b_number]->word = word;
		hm->map[b_number]->document_id = document_id;
		hm->map[b_number]->num_occurrences = num_occurrences;
		hm->map[b_number]->next = NULL;
		return;
	}

    struct llnode * counter = hm->map[b_number];
	//Case 2: Bucket already has nodes
	while (counter != NULL)
	{
		if (counter->next == NULL)
		{
			counter->next = (struct llnode *)malloc(sizeof(struct llnode));
			counter->next->word = word;
			counter->next->document_id = document_id;
			counter->next->num_occurrences = num_occurrences;
			counter->next->next = NULL;
			return;
		}
		counter = counter->next;
	}
}

void hm_remove(struct hashmap * hm, char* word, char* document_id)
{

    struct llnode * node = (calloc(sizeof(struct llnode), 1));
    node->word = word;
    node->document_id = document_id;

    for (int i = 0; hm->num_buckets; i++)
    {
        if (hm->map[i] != NULL)
		{
			//Case 1: Only one element in linked list
			if ((strcmp(node->word, hm->map[i]->word) == 0) && (strcmp(node->document_id, hm->map[i]->document_id) == 0) && (hm->map[i]->next == NULL))
			{
                hm->map[i] = NULL;
				return;
            } 
        }

        if (hm->map[i] != NULL)
		{
			//Case 2: Head is to be removed
			if ((strcmp(node->word, hm->map[i]->word) == 0) && (strcmp(node->document_id, hm->map[i]->document_id) == 0) && (hm->map[i]->next == NULL))
			{
                struct llnode *temp = hm->map[i]->next;
				free(hm->map[i]->next);
				hm->map[i] = temp;
				free(temp);
                return;
            }
        }

        struct llnode * current = hm->map[i];
        while (current != NULL)
		{
			//Case 3: Head is to be removed
			if ((strcmp(node->word, hm->map[i]->word) == 0) && (strcmp(node->document_id, hm->map[i]->document_id) == 0) && (hm->map[i]->next == NULL))
			{
                    struct llnode *temp = current;
					free(current->next);
					temp->next = current->next->next;
                    return;
            }
            current = current->next;
        }
    }


}
void hm_destroy(struct hashmap* hm)
{
    //hm->map->
    for (int i = 0; i < hm->num_buckets; i++)
    {
        struct llnode * current = hm->map[i]; //equal head
        struct llnode * next;
        while(current != NULL)
        {
            next = current->next;
            free(current->word); //maybe comment out
            free(current->document_id);
            free(current);
            current = next;
        }
    }
    free(hm->map);
    free(hm);
}

int hash(struct hashmap* hm, char* word)
{
	int k = 0;
	int modulo;
	int i = 1;
    //int w_len = strlen(word);

	while (*(word + i) != '\0')
	{
		k = k + (int)*(word + i);
		i++;
	}
	modulo = k % hm->num_buckets;

	return modulo;
}
