/****************************************************************************
 *
 *       hash.c
 *
 *         This file implements the hash module. To use this module you must
 *         include "hash.h" and link with hash.o. The functions implemented
 *         by this module are described in hash.h.
 *
 *         The hashtable uses an open hash creating lists of key, value pairs
 *         chained off the backbone of the hashtable. Hashing on the keys
 *         determines which bucket to put the key, value pair into.
 *
 ****************************************************************************/

#include <strings.h>
#include <malloc.h>

#include "config.h"
#include "hash.h"

/* some prime, this one is small for the sake of these examples */
#define HASHTABLE_SIZE 13

/* hashEntry
 *   A hashEntry keeps the key, value pair together in a list hashEntries.
 */
typedef struct struct_hashEntry {
  char* key;
  void* value;
  struct struct_hashEntry* next;
} hashEntry;

/* makeHashTable
 *   Builds the backbone of the hashtable to a fixed size, and returns it.
 */
hashtable* makeHashTable()
{
  hashtable* ht;
  ht = (hashtable*)malloc(HASHTABLE_SIZE*sizeof(hashEntry*));

  return(ht);
}

/* delHashTable
 *   Walks through the hashtable freeing all the entries in it, and then
 *   frees the backbone.
 */
void delHashTable(ht)
     hashtable* ht;
{
  int index;
  hashEntry* last_entry;
  hashEntry* entry;
  for (index = 0; index < HASHTABLE_SIZE; index++) {
    for (last_entry = NULL, entry = ht[index]; 
	 entry; 
	 last_entry = entry, entry = entry->next) {
      if (last_entry) {
	free(last_entry->key);
	free(last_entry->value);
	free(last_entry);
      }
    }



  }
  free(ht);
}

/* hashIndex
 *   Determines what bucket (index) to place a key in. Given a key it
 *   returns the index of the appropriate bucket.
 */
static int hashIndex(key)
     char* key;
{
  int index;
  for (index = 0; *key != '\0'; key++) {
    index = (index<<1) + *key;
  }
  if (index < 0) {
    index = index * -1;
  }
  index = index%HASHTABLE_SIZE;
  return(index);
}

/* getHash
 *   Hashes into the appropriate bucket, and then walks the chain of
 *   hash entries. It compares the keys with strcmp because the keys
 *   do not have to have the same pointer, just the same string. When
 *   a match is found the associated value is returned. NULL is returned
 *   if no match is found.
 */
void* getHash(ht, key)
     hashtable* ht;
     char* key;
{
  hashEntry* entry;
  int index = hashIndex(key);
  for (entry = ht[index];
       entry && strcmp(entry->key, key);
       entry = entry->next) {
  }
  if (entry) {
    return (entry->value);
  }
  else {
    return (NULL);
  }
}

/* putHash
 *   Hashes into the appropriate bucket, and then walks the chain of hash
 *   entries to see if the key is already in this bucket. If it is it 
 *   puts the new value in that entry, and returns the old value so the
 *   it can be freed. If it is not in the table a new entry is created
 *   and added to the end of the list. Note that when a new entry is created
 *   we copy the key into it, we don't just include the key pointer or it
 *   might get changed out from underneath us. The value we just store 
 *   because thats what this facility is all about.
 */  
void* putHash(ht, key, value)
     hashtable* ht;
     char* key;
     void* value;
{
  hashEntry* last_entry;
  hashEntry* entry;
  char* new_key;
  void* old_value;
  int index = hashIndex(key);
  for (last_entry = NULL, entry = ht[index];
       entry && strcmp(entry->key, key);
       last_entry = entry, entry = entry->next) {
  }
  if (entry) {
    old_value = entry->value;
    entry->value = value;
  }
  else {
    old_value = NULL;
    entry = (hashEntry*)malloc(sizeof(hashEntry));
    new_key = malloc(strlen(key)*sizeof(char));
    strcpy(new_key, key);
    entry->key = new_key;
    entry->value = value;
    entry->next = NULL;
    if (last_entry) {
      last_entry->next = entry;
    }
    else {
      ht[index] = entry;
    }
  }
  return(old_value);
}

/* remHash
 *   Hashes to the appropriate bucket, and then walks the chain of hash
 *   entries to see if the key is already in this bucket. If it is then
 *   it can be removed. When we remove an entry we free the key and the
 *   entry and then fix up the list to not include it. We return the 
 *   value which was in the entry so that it can also be freed.
 */
void* remHash(ht, key)
     hashtable* ht;
     char* key;
{
  hashEntry* last_entry;
  hashEntry* entry;
  void* value;
  int index = hashIndex(key);
  for (last_entry = NULL, entry = ht[index];
       entry && strcmp(entry->key, key);
       last_entry = entry, entry = entry->next) {
  }
  if (entry) {
    value = entry->value;
    free(entry->key);
    free(entry);
    if (last_entry) {
      last_entry->next = entry->next;
    }
    else {
      ht[index] = entry->next;
    }
  }
  else {
    value = NULL;
  }
  return(value);
}
