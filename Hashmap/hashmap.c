#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// TODO: --DONE-- sudo apt install libbsd-dev 
// This provides strlcpy
// See "man strlcpy"
#include <bsd/string.h>
#include <string.h>

#include "hashmap.h"


int
hash(char* key, int nn) //ADD CAPACITY TO HASH
{
    // TODO: --DONE-- Produce an appropriate hash value. 
    int hh = 0;
    for (int ii = 0; key[ii]; ++ii) {
	    hh = hh * 67 + key[ii];
    }
    return hh & (nn - 1);
}


hashmap*
make_hashmap_presize(int nn)
{
    hashmap* hh = calloc(1, sizeof(hashmap));
    hh->size = 0;
    hh->capacity = nn;
    hh->data = calloc(hh->capacity, sizeof(hashmap_pair));
    // TODO: --DONE--  Allocate and initialize a hashmap with capacity 'nn'.
    // Double check "man calloc" to see what that function does.
    return hh;
}

hashmap*
make_hashmap()
{
    return make_hashmap_presize(4);
}

void
free_hashmap(hashmap* hh)
{
    // TODO: --DONE-- Free all allocated data.
   /* for (long ii = 0; ii < hh->capacity; ++ii) {
	    //free_pair(mm->data[ii]);
	    hashmap_pair  this_pair = hh->data[ii];
	    free(this_pair->key)  DONT NEED THIS??
	    free(this_pair->val);
	    free(this_pair->used);
	    free(this_pair->tomb);
	    free(this_pair); // freed all fields of this pair so we can free the pair and move to next
    }*/
    free(hh->data); //cleared al the data above
    free(hh);
}

int
hashmap_has(hashmap* hh, char* kk)
{
    return hashmap_get(hh, kk) != -1;
}

int
hashmap_get(hashmap* hh, char* kk)
{
    // TODO: --DONE ???-- Return the value associated with the
    // key kk.
    // Note: return -1 for key not found.
    int ii = hash(kk, hh->capacity);
    if(hh->data[ii].used == 1)
    {
	    return hh->data[ii].val;
    }
    else {
	    return -1;
    }
}

void
hashmap_grow(hashmap* hh)
{
	int old_cap = hh->capacity;
	hh->capacity = hh->capacity*2;
	hashmap_pair* old_data = hh->data;
	hh->data = calloc(hh->capacity, sizeof(hashmap_pair));
	hh->size = 0;
	for(int ii = 0; ii < old_cap; ii++) 
	{
		hashmap_pair curr = old_data[ii];
		if(curr.tomb == 0 && curr.used == 1)
		{
			hashmap_put(hh, curr.key, curr.val);
		}
	}
	free(old_data);
}
		    

void
hashmap_put(hashmap* hh, char* kk, int vv)
{
    // TODO: --DONE-- Insert the value 'vv' into the hashmap
    // for the key 'kk', replacing any existing value
    // for that key.
    hashmap_pair* hd = hh->data;
    if(hh->size >= hh->capacity * 0.5) {
	hashmap_grow(hh);
    }
    int ii = hash(kk, hh->capacity);
    int is_set = 0;
    for(; ii<hh->capacity; ii++) 
    {
	    if(hh->data[ii].key == kk)
	    {
		    hh->data[ii].val = vv;
		    hh->data[ii].used = 1;
		    hh->data[ii].tomb = 0;
		    is_set = 1;
		    break;		    
	    }

	    else if(hh->data[ii].used == 0 || hh->data[ii].tomb == 1) 
	    {
		    strcpy(hh->data[ii].key, kk);
		    hh->data[ii].val = vv;
		    hh->data[ii].used = 1;
		    hh->data[ii].tomb = 0;
		    is_set = 1;
		    break;
	    }
    }
    if ( is_set == 0) 
    {
	    hashmap_grow(hh);
	    //update everything at hhsize
	    hh->data[hh->size].val = vv;
	    hh->data[hh->size].used = 1;
	    hh->data[hh->size].tomb = 0;
	    is_set = 1;
    }
    hh->size++;

}

void
hashmap_del(hashmap* hh, char* kk)
{
    // TODO: --DONE-- Remove any value associated with
    // this key in the map.
    int ii = hash(kk, hh->capacity);
    for(int ii = 0; ii < hh->capacity; ii++) 
    {
	    if(hh->data[ii].key == kk)
	    {
		    hh->data[ii].tomb = 1; 
		    hh->size--;
		    break;
	    }
    }
}

hashmap_pair
hashmap_get_pair(hashmap* hh, int ii)
{
    // TODO: --DONE-- Get the {k,v} pair stored in index 'ii'.
    hashmap_pair wanted_pair = hh->data[ii];
    return wanted_pair;
}

void
hashmap_dump(hashmap* hh)
{
    for(int ii = 0; ii < hh->capacity; ii++) {
	    hashmap_pair curr = hh->data[ii];
	    if(curr.used && !curr.tomb) { //can i do this?
		   printf("%s	%d\n", curr.key, curr.val);
	    }
    }
    // TODO --DONE--: Print out all the keys and values currently
    // in the map, in storage order. Useful for debugging.
}
