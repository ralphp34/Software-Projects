# Project5 Report

# search.c

```java
- Programs asks for number of buckets for hashmap.
- $USER inputs integer value from console.
- creates hashmap by calling hm_create
- calls training() function from training.c to populate hashmap with words
- loops through retrieval phase
- loop stopped when `X` is input
- loop continues when <enter_key> is pressed
- read() function from retrieval calls rank() to output rank of relevant files on screen
```

# hashmap.c
`struct hashmap* hm_create(int num_buckets)`

```java
/** This function allocates space in the heap for hashmap to be created
 * @param num_buckets size of hashmap buckets
 * @return empty hashmap of given size
*/
```

`void hm_remove(struct hashmap * hm, char *word, char *document_id)`
```java
/** This function removes a node from hashmap
 * @param hm hashmap from which word is to be removed from
 * @param word word to remove
 * @param document_id document ID to remove
 * @return void
*/
```

`void hm_destroy(struct hashmap * hm)`

```java
/** This function frees memory of the hashmap to avoid all memory leaks
 * @param hm hashmap to free from heap
 * @return void
*/
```

`int hash(struct hashmap *hm, char *w)`

```java
/** This function provides the bucket number after hashing it.
 * @param hm hashmap to use number of buckets from
 * @param w word to use hashing function for
 * @return bucket number after hashing
*/
```

`void hm_put(struct hashmap *hm, char *word, char *document_id)`

```java
/** This function inserts word and documentID into the hashmap. If a word and document
 * that is already inserted before then it increments the frequency count of the node.
 * @param hm hashmap to insert node into
 * @param word word to be added
 * @param document_id document ID to be added
 * @return void
*/
```

`int hm_get(struct hashmap *hm, char *word, char * document_id)`

```java
/** This function searches through the hashmap for a word and then return the 
 * number of occurances of that word in hashmap
 * @param hm hashmap to search from
 * @param w word to search for
 * @param docID document ID with the word
 * @return number of occurance of the word
*/
```


# training.c

Option 1 is implemented with arbitrary number of files in directory using glob.

`int searchFile(char * word, char * doc_id)`

```java
/** This function searches through the File for a word
 * @param doc_id document you are searching through
 * @param word word we are searching for
 * @return numOccurances number of times the word has occured in document
*/
```
`void populate(struct hashmap *hm, char *doc_id)`


```java
/** This function populates hashmap with a certain document
 * @param hm hashmap to populate
 * @param doc_id document to populate with
 * @return void
*/
```
`struct hashmap *training(struct hashmap *hm)`

```java
/** This function uses populate function and iterates through directory to
 *  populate hashmap with all files
 * @param hm hashmap to populate
 * @return hm populate hashmap
*/
```


# retrieval.c

`int read_query(struct hashmap *hm)`


```java
/** This function reads the user input query and then calls rank 
 * @param hm hashmap to search query from
 * @return void
*/
```

`void rank(struct hashmap *hm, char *query)`

```java
/** This function ranks each word in the query. It calls hash_deep_search function
 * in hashmap.c to search for number of occurances of word in all documents. Then 
 * it calculates idf and tf-idf and writes the rank to file search_scores.txt
 * @param hm hashmap to search query from
 * @param query multiple words we are searching for
 * @return numOccurances number of times the word has occured in document
*/
```


# Assumptions

- No words are longer that 20 chars
- Stopwords function is implemented using if statement such that if the word is not found in all documents in directory it wont show on console for the relevant file.
- All words are lowercase
- They enter on one line

