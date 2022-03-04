#include <stdlib.h>
#include <string.h>

#include "llist.h"

//initialize a linked list
llist_t * ll_init()
{
  //TODO
  llist_t * new_ll = malloc(sizeof(llist_t));
  new_ll->head = NULL;
  new_ll->size = 0;
  return new_ll; //clearly it shouldn't return null when you finish it
}

//delete a linked list
void ll_delete(llist_t * ll)
{
  //TODO
  ll_node_t * current = ll->head;
  ll_node_t * next;
  while (current != NULL)
  {
    next = current->next;
    free(current->val); //maybe comment out
    free(current);
    current = next;
  }
  free(ll); //maybe comment out
}


//push an item onto the front of the list
void ll_push(llist_t * ll, char * s)
{
  //TODO
  ll_node_t * new_node = malloc(sizeof(ll_node_t));
  new_node->next = ll->head;
  new_node->val = strdup(s);
  ll->head = new_node;
}




