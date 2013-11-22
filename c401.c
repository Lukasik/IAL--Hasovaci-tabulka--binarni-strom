#include "c401.h"
int solved;

void BSTInit (tBSTNodePtr *RootPtr) {

	*RootPtr = NULL;
}

int BSTSearch (tBSTNodePtr RootPtr, char K, int *Content)	{

	if(RootPtr == NULL)
	{
		return 0;
	}
	else if(RootPtr->Key == K)
	{
		*Content = RootPtr->BSTNodeCont;
		return TRUE;
	}
	else if(RootPtr->Key > K && RootPtr->LPtr != NULL)
	{
		return BSTSearch(RootPtr->LPtr, K, Content);
	}
	else if(RootPtr->Key < K && RootPtr->RPtr != NULL)
	{
		return BSTSearch(RootPtr->RPtr, K, Content);
	}

	return FALSE;
}


void BSTInsert (tBSTNodePtr* RootPtr, char K, int Content)	{

	if(*RootPtr == NULL)
	{
		*RootPtr = malloc(sizeof(struct tBSTNode));

		if(*RootPtr == NULL)
		{
			//TODO
		}

		(*RootPtr)->LPtr = NULL;
		(*RootPtr)->RPtr = NULL;
		(*RootPtr)->BSTNodeCont = Content;
		(*RootPtr)->Key = K;
		return;
	}
	else if((*RootPtr)->Key == K)
	{
		(*RootPtr)->BSTNodeCont = Content;
		return;
	}
	else if((*RootPtr)->Key > K)
	{
		if((*RootPtr)->LPtr != NULL)
		{
			BSTInsert(&(*RootPtr)->LPtr, K, Content);
			return;
		}
		else
		{
			tBSTNodePtr new = malloc(sizeof(struct tBSTNode));

			if(new == NULL)
			{
				//TODO
			}

			(*RootPtr)->LPtr = new;
			new->BSTNodeCont = Content;
			new->Key = K;
			new->LPtr = NULL;
			new->RPtr = NULL;
			return;
		}
	}
	else if((*RootPtr)->Key < K)
	{
		if((*RootPtr)->RPtr != NULL)
		{
			BSTInsert(&(*RootPtr)->RPtr, K, Content);
			return;
		}
		else
		{
			tBSTNodePtr new = malloc(sizeof(struct tBSTNode));

			if(new == NULL)
			{
				//TODO
			}

			(*RootPtr)->RPtr = new;
			new->BSTNodeCont = Content;
			new->Key = K;
			new->LPtr = NULL;
			new->RPtr = NULL;
			return;
		}
	}
}

void ReplaceByRightmost (tBSTNodePtr PtrReplaced, tBSTNodePtr *RootPtr) {

	if((*RootPtr)->RPtr != NULL)
	{
		ReplaceByRightmost(PtrReplaced, &(*RootPtr)->RPtr);
	}
	else
	{
		PtrReplaced->BSTNodeCont = (*RootPtr)->BSTNodeCont;
		PtrReplaced->Key = (*RootPtr)->Key;
	}


}

void BSTDelete (tBSTNodePtr *RootPtr, char K) 		{

	if((*RootPtr) == NULL)
	{
		return;
	}
	else if((*RootPtr)->Key == K)
	{
		if((*RootPtr)->LPtr == NULL && (*RootPtr)->RPtr == NULL)
		{
			free(*RootPtr);
			*RootPtr = NULL;
		}
		else if(((*RootPtr)->RPtr == NULL && (*RootPtr)->LPtr != NULL) || ((*RootPtr)->RPtr != NULL && (*RootPtr)->LPtr == NULL))
		{
			tBSTNodePtr used = (*RootPtr)->RPtr == NULL ? (*RootPtr)->LPtr : (*RootPtr)->RPtr;

			(*RootPtr)->BSTNodeCont = used->BSTNodeCont;
			(*RootPtr)->Key = used->Key;
			(*RootPtr)->RPtr = used->RPtr;
			(*RootPtr)->LPtr = used->LPtr;

			free(used);
		}
		else
		{
			ReplaceByRightmost((*RootPtr), &((*RootPtr)->LPtr));
			BSTDelete(&(*RootPtr)->LPtr, (*RootPtr)->Key);
		}
	}
	else
	{
		if((*RootPtr)->LPtr != NULL && (*RootPtr)->Key > K)
		{
			if((*RootPtr)->LPtr->Key == K  && (*RootPtr)->LPtr->LPtr == NULL && (*RootPtr)->LPtr->RPtr == NULL)
			{
				BSTDelete(&(*RootPtr)->LPtr, K);
				(*RootPtr)->LPtr = NULL;
			}
			else
			{
				BSTDelete(&(*RootPtr)->LPtr, K);
			}
		}
		else if((*RootPtr)->RPtr != NULL && (*RootPtr)->Key < K)
		{
			if((*RootPtr)->RPtr->Key == K && (*RootPtr)->RPtr->LPtr == NULL && (*RootPtr)->RPtr->RPtr == NULL)
			{
				BSTDelete(&(*RootPtr)->RPtr, K);
				(*RootPtr)->RPtr = NULL;
			}
			else
			{
				BSTDelete(&(*RootPtr)->RPtr, K);
			}
		}

	}
}

void BSTDispose (tBSTNodePtr *RootPtr) {

	if(*RootPtr != NULL)
	{
		BSTDispose(&(*RootPtr)->LPtr);
		BSTDispose(&(*RootPtr)->RPtr);

		free(*RootPtr);
		*RootPtr = NULL;
	}
}

