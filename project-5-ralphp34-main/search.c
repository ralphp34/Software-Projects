#include <stdlib.h>
#include "hashmap.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

int main (void)
{
    int buckets = 0;
    printf("How many buckets?:\n");
    scanf("%d", &buckets);

    const int num_buckets = buckets;
    struct hashmap * hm = hm_create(num_buckets);    
    training(hm);
    int comm = 0;

    printf("Enter the search string or X to exit:\n");
    scanf("%d", &comm);

    while (comm == 0)
    {
        comm = read_query(hm);
    }
    printf("%s", "Exiting Program!");
    hm_destroy(hm);
    return 0;

}
