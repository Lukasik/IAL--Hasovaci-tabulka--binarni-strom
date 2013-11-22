#include "c016.h"

int HTSIZE = MAX_HTSIZE;
int solved;

int hashCode ( tKey key ) {
	int retval = 1;
	int keylen = strlen(key);
	for ( int i=0; i<keylen; i++ )
		retval += key[i];
	return ( retval % HTSIZE );
}


void htInit ( tHTable* ptrht ) {

	for(int i = 0; i < HTSIZE; ++i)
	{
		(*ptrht)[i] = NULL;
	}
}


tHTItem* htSearch ( tHTable* ptrht, tKey key ) {

	int index = hashCode(key);
	tHTItem* item = (*ptrht)[index];

	while(item != NULL)
	{
		if(strcmp(item->key, key) == 0) return item;
		item = item->ptrnext;
	}


	return NULL;
}


void htInsert ( tHTable* ptrht, tKey key, tData data ) {

	tHTItem *new, *item = htSearch(ptrht, key);

	if(item == NULL)
	{
		int index = hashCode(key);
		item = (*ptrht)[index];
		new = malloc(sizeof(tHTItem));

		if(new == NULL)
		{
			//TODO
		}

		new->ptrnext = item;
		new->data = data;
		new->key = malloc(strlen(key)+1);

		if(new->key == NULL)
		{
			//TODO
		}

		memcpy(new->key, key, strlen(key)+1);

		(*ptrht)[index] = new;
	}
	else
	{
		item->data = data;
	}
}

tData* htRead ( tHTable* ptrht, tKey key ) {

	tHTItem* item = htSearch(ptrht, key);

	return item == NULL ? NULL : &(item->data);
}


void htDelete ( tHTable* ptrht, tKey key ) {

	tHTItem *item, *prev;
	int index = hashCode(key);
	prev = item = (*ptrht)[index];

	if(item == NULL)
	{
		return;
	}

	while(strcmp(item->key, key) != 0 && item->ptrnext != NULL)
	{
		prev = item;
		item = item->ptrnext;
	}

	if(strcmp(item->key, key) == 0)
	{
		if(prev == item)
		{
			if(item->ptrnext != NULL)
			{
				(*ptrht)[index] = item->ptrnext;
			}
			else
			{
				(*ptrht)[index] = NULL;
			}
		}
		else if(prev != item && item->ptrnext != NULL)
		{
			prev->ptrnext = item->ptrnext;
		}
		else if(item->ptrnext == NULL)
		{
			prev->ptrnext = NULL;
		}

		free(item->key);
		free(item);
	}


}

void htClearAll ( tHTable* ptrht ) {

	tHTItem *item, *next;

	for(int i = 0; i < HTSIZE; ++i)
	{

		next = (*ptrht)[i];

		while(next != NULL)
		{
			item = next;
			next = next->ptrnext;

			free(item->key);
			free(item);
		}

		(*ptrht)[i] = NULL;
	}
}
