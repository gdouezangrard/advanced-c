/****************************************************************************
 *
 *       hash.h
 *
 *         This file contains all the function declarations necessary to
 *         use the hash module.
 *
 ****************************************************************************/

#ifndef HASH_H
#define HASH_H

/* hashtable
 *   Type for using hashtables
 */
typedef void* hashtable;

/* makeHashTable
 *   Create a hashtable. This hashtable is then passed to the other functions
 */
extern hashtable* makeHashTable P(());

/* delHashTable
 *   When finished with a hashtable this function will remove it, after this
 *   function is called the pointer to the hashtable has been freed and should
 *   not be used.
 */
extern void delHashTable P((hashtable* ht));

/* getHash
 *   To get a value out of the hashtable that was put in under key. If NULL
 *   is returned then no match was found.
 */
extern void* getHash P((hashtable* ht, char* key));

/* putHash
 *   To put a value into the hashtable under key. If a value was previously
 *   in the table under this key, then it is returned.
 */
extern void* putHash P((hashtable* ht, char* key, void* value));

/* remHash
 *   To remove a value from the hashtable which was previously put in under
 *   key. If there was a value under key then it is returned.
 */
extern void* remHash P((hashtable* ht, char* key));

#endif /* HASH_H */
