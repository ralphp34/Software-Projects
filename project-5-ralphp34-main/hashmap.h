#ifndef HASHMAP_H
#define HASHMAP_H

struct llnode {
        char* word;
        char* document_id;
        int num_occurrences;
        struct llnode* next;
};

struct hashmap {
        struct llnode** map;
        int num_buckets;
        int num_elements;
};

struct hashmap* hm_create(int num_buckets);
int hm_get(struct hashmap* hm, char* word, char* document_id);
void hm_put(struct hashmap* hm, char* word, char* document_id);
void hm_remove(struct hashmap* hm, char* word, char* document_id);
void hm_destroy(struct hashmap* hm);
int hash(struct hashmap* hm, char* word);
int searchFile(char * word, char * doc_id);
void populate(struct hashmap *hm, char *doc_id);
struct hashmap * training(struct hashmap *hm);
int read_query(struct hashmap * hm);
void rank(struct hashmap *hm, char *query);

#endif
