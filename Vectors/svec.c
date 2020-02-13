#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "svec.h"

svec*
make_svec()
{
    svec* sv = malloc(sizeof(svec));
    sv->data = malloc(2 * sizeof(char*));
    sv->size = 0;
    sv->capacity = 2;
    // TODO: --DONE--  correctly allocate and initialize data structure
    return sv;
}

void
free_svec(svec* sv)
{
    // TODO: --DONE-- free all allocated data
    for(int ii = 0; ii < sv->size; ++ii) {
	    free(sv->data[ii]);
    }
    free(sv->data);
    free(sv);
}

char*
svec_get(svec* sv, int ii)
{
    assert(ii >= 0 && ii < sv->size);
    return sv->data[ii];
}

void
svec_put(svec* sv, int ii, char* item)
{
	assert(ii >= 0 && ii < sv->size);
	sv->data[ii] = strdup(item);

    // TODO: --DONE BUT ???-- insert item into slot ii
    // Consider ownership of string in collection. 
}

void
svec_push_back(svec* sv, char* item)
{
    int ii = sv->size;
    int jj = sv->capacity;
    if(ii >= jj) {
    	    sv->capacity = 2 * jj; //doubles capacity
    	    sv->data = realloc(sv->data, jj*2*sizeof(char*));
    }
    //these two steps need to happen either way
    sv->size = ii + 1;
    svec_put(sv, ii, item); // places the item one past the size because order doesn't matter yet
    //sv->size = ii + 1; // increases the size in case we need to add more
  

    // TODO: --DONE-- expand vector if backing erray
    // is not big enough
}

void
svec_swap(svec* sv, int ii, int jj)
{
    // TODO: --DONE-- Swap the items in slots ii and jj
    char* temp = sv->data[ii];
    sv->data[ii] = sv->data[jj];
    sv->data[jj] = temp;

}
