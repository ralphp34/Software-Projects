#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <math.h>
#include <string.h>

#include "llist.h"
#include "hashmap.h"

//local function for hashing an input value (do not edit)
unsigned int _hash(hashmap_t * hm, char * val){
  //based on Java's String.hashcode()
  double k = 0;
  double len = (double) strlen(val);
  int i=1;
  for(char * c = val; *c ; c++,i++){
    k += (*c) * pow(31,len-i);
  }

  return (unsigned int) (((unsigned long) k) % hm->num_buckets);
}


//local function: resize the hashmap by doubling the number of buckets and rehashing
void _resize(hashmap_t * hm)
{
  //TODO: resize the hashmap if the load gets too high
  int new_len = hm->num_buckets * 2;
  llist_t ** new_buck = calloc(sizeof(llist_t*), new_len);

  for (int i = 0; i < new_len; i++)
  {
    new_buck[i] = ll_init();
  }

  int temp = hm->num_buckets;
  hm->num_buckets *= 2;

  for (int i = 0; i < temp; i++)
  {
    if ((hm->buckets[i])->head == NULL)
    {
      continue;
    }
    ll_node_t * current = (hm->buckets[i])->head;
    while (current != NULL)
    {
      unsigned int hash = _hash(hm, current->val);
      ll_push(new_buck[hash], current->val);
      current = current->next;
    }
  }
  for (int i = 0; i < temp; i++)
  {
    ll_delete(hm->buckets[i]);
  }

  free(hm->buckets);
  hm->buckets = new_buck;  
}


//initliaze a hashmap with initial number of buckets
hashmap_t * hm_init(){

  //create the hashmap
  hashmap_t * hm = calloc(sizeof(hashmap_t),1);


  //TODO the rest of the setup!
  hm->buckets = calloc(sizeof(llist_t*), HM_INIT_NUM_BUCKETS);
  hm->num_buckets = HM_INIT_NUM_BUCKETS; 
  for (int i = 0; i < HM_INIT_NUM_BUCKETS; i++)
  {
    hm->buckets[i] = ll_init();
  }
  hm->size = 0;
  return hm;
}


//delete/deallocate the hashmap
void hm_delete(hashmap_t * hm){

  //TODO: properly deallocate
  for (int i = 0; i < hm->num_buckets; i++)
  {
    ll_delete(hm->buckets[i]);
  }
  free(hm->buckets);
  //delete the hashmap
  free(hm);
}

//add a string value to the hashmap
void hm_add(hashmap_t * hm, char * val){
  // You get this function for free :)
  
  //check the load on the hashtable, if > max load, resize!
  if(((hm->size+1)/(double) hm->num_buckets) > HM_MAX_LOAD){
    _resize(hm); 
  }

  unsigned int h = _hash(hm,val); //get hash
  ll_push(hm->buckets[h],val); //note that list does string dup
  hm->size++; //increase size
}

//see if a string value is in the hashmap
bool hm_check(hashmap_t * hm, char * val){

  //TODO check if a value is in the hashmap
  unsigned int num = _hash(hm, val);
  ll_node_t * compar = (hm->buckets[num])->head;
  while (compar != NULL)
  {
    if (strcmp(compar->val, val) == 0)
    {
      return true;
    }
    compar = compar->next;
  }
  return false; //otherwise false
}


