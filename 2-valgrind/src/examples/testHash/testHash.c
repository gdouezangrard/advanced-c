/****************************************************************************
 *
 *       testHash.c
 *
 *         This file is a testing harness for the hash module. To use this
 *         module we must include "hash.h", and link with hash.o.
 *
 ****************************************************************************/

#include <stdio.h>
#include <malloc.h>

#include "config.h"
#include "hash.h"

/* for these tests we know all our strings have a length of no more than 3 */
#define STR_LEN 3
#define TABLE_SIZE 100

/* fillTestTable
 *   Function to initial our testTable. The test table contains all of the
 *   values and keys which we will use in testing the hash module. Keys will
 *   be the strings in the table, and values will be pointers to the entry
 *   in the array. We do this to make sure keys and values are different
 *   which is more likely to be the case in real use.
 */
static void fillTestTable(testTable)
     char* testTable[];
{
  char* str;
  int index;
  for (index = 0; index < TABLE_SIZE; index++) {
    str = (char*)malloc(STR_LEN*sizeof(char));
    sprintf(str, "%d", index);
    testTable[index] = str;
  }
}

/* reportError
 *   Just prints out the error, gives us a function to break on for errors.
 */
static void reportError(msg)
     char* msg;
{
  printf("Error: %s", msg);
}

/* testMakeHashTable
 */
static hashtable* testMakeHashTable()
{
  hashtable* ht;
  printf("Testing makeHashTable.\n");
  ht = makeHashTable();
  if (!ht) {
    reportError("should be creating a hashtable, returned NULL.\n");
  }
  return(ht);
}

/* testPutHash
 *   Put entries from lower to upper from the testTable into the hashtable.
 *   Check the values that get returned, and signal error if they are
 *   incorrect. If oldValue is true then we should expect an old value to
 *   be in the table before we insert one, so we should get one back.
 */
static void testPutHash(ht, testTable, lower, upper, oldValue)
     hashtable* ht;
     char* testTable[];
     int lower;
     int upper;
     boolean oldValue;
{
  int index;
  void* value;
  printf("Testing putHash - adding from %d to %d.\n", lower, upper);
  for (index = lower; index < upper; index++) {
    value = putHash(ht, testTable[index], &testTable[index]);
    if (value) {
      if (!oldValue) {
	reportError("shouldn't be overwriting values.\n");
	printf("       Overwrote %d with %d.\n", 
	       (char**)value - testTable, index);
      }
    }
    else {
      if (oldValue) {
	reportError("should be overwriting values.\n");
	printf("       Did not find old value for %d.\n", index);
      }
    }
  }
}

/* testGetHash
 *   Get entries from lower to upper from the hashtable.
 *   Check the values that get returned, and signal error if they are
 *   incorrect. If oldValue is true then we should expect to get a
 *   value back.
 */
static void testGetHash(ht, testTable, lower, upper, oldValue)
     hashtable* ht;
     char* testTable[];
     int lower;
     int upper;
     boolean oldValue;
{
  int index;
  void* value;
  char key[STR_LEN];
  printf("Testing getHash - getting from %d to %d.\n", lower, upper);
  for (index = lower; index < upper; index++) {
    sprintf(key, "%d", index);
    value = getHash(ht, key);
    if (value) {
      if (oldValue) {
	if (index != (char**)value - testTable) {
	  reportError("found the wrong value.\n");
	  printf("       Found %d, and should have found %d.\n",
		 (char**)value - testTable, index);
	}
      }
      else {
	reportError("should not have found a value.\n");
	printf("       Found %d, when it should have been empty.\n", index);
      }
    }
    else {
      if (oldValue) {
	reportError("could not find value.\n");
	printf("       Should have found value %d.\n", index);
      }
    }
  }
}

/* testRemHash
 *   Remove entries from lower to upper from the hashtable.
 *   Check the values that get returned, and signal error if they are
 *   incorrect. If oldValue is true then we should expect an old value to
 *   be in the table when we remove it, so we should get one back.
 */
static void testRemHash(ht, testTable, lower, upper, oldValue)
     hashtable* ht;
     char* testTable[];
     int lower;
     int upper;
     boolean oldValue;
{
  int index;
  void* value;
  char key[STR_LEN];
  printf("Testing remHash - removing from %d to %d.\n", lower, upper);
  for (index = lower; index < upper; index++) {
    sprintf(key, "%d", index);
    value = remHash(ht, key);
    if (value) {
      if (oldValue) {
	if (index != (char**)value - testTable) {
	  reportError("removed the wrong value.\n");
	  printf("       removed %d, and should have removed %d.\n",
		 (char**)value - testTable, index);
	}
      }
      else {
	reportError("should not have removed a value.\n");
	printf("       removed %d, when it should have been empty.\n", index);
      }
    }
    else {
      if (oldValue) {
	reportError("did not remove value.\n");
	printf("       Should have removed value %d.\n", index);
      }
    }
  }
}

/* testDelHashTable
 *   Don't actually do any real checking here, but we will at least know
 *   where it is dying if it does.
 */
static void testDelHashTable(ht)
     hashtable* ht;
{
  printf("Testing delHashTable.\n");
  delHashTable(ht);
}

/* main
 *   Create a hashtable and do a bunch of operations on it checking that
 *   they are done correctly, and then delete the hashtable. In the operations
 *   we each possible combination of getting and putting values when the
 *   value should be there or not.
 */
int main()
{
  hashtable* ht;
  char* testTable[TABLE_SIZE];

  fillTestTable(testTable);

  ht = testMakeHashTable();
  testPutHash(ht, testTable,  0, 100, FALSE);
  testGetHash(ht, testTable,  0, 100, TRUE);
  testRemHash(ht, testTable,  0,  50, TRUE);
  testRemHash(ht, testTable,  0,  50, FALSE);
  testGetHash(ht, testTable,  0,  50, FALSE);
  testGetHash(ht, testTable, 50, 100, TRUE);
  testPutHash(ht, testTable,  0,  50, FALSE);
  testPutHash(ht, testTable, 50, 100, TRUE);
  testDelHashTable(ht);

  exit(0);
}  
