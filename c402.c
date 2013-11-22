#include "c402.h"
int solved;

void BTWorkOut (tBTNodePtr Ptr)		{

	if (Ptr==NULL)
    printf("Chyba: Funkce BTWorkOut byla volána s NULL argumentem!\n");
  else
    printf("Výpis hodnoty daného uzlu> %d\n",Ptr->Cont);
}

void SInitP (tStackP *S)
{
	S->top = 0;
}

void SPushP (tStackP *S, tBTNodePtr ptr)
{
  if (S->top==MAXSTACK)
    printf("Chyba: Do¹lo k pøeteèení zásobníku s ukazateli!\n");
  else {
		S->top++;
		S->a[S->top]=ptr;
	}
}

tBTNodePtr STopPopP (tStackP *S)
{
	if (S->top==0)  {
		printf("Chyba: Do¹lo k podteèení zásobníku s ukazateli!\n");
		return(NULL);
	}
	else {
		return (S->a[S->top--]);
	}
}

bool SEmptyP (tStackP *S)

{
  return(S->top==0);
}

void SInitB (tStackB *S) {

	S->top = 0;
}

void SPushB (tStackB *S,bool val) {

	if (S->top==MAXSTACK)
		printf("Chyba: Do¹lo k poeteèení zásobníku pro boolean!\n");
	else {
		S->top++;
		S->a[S->top]=val;
	}
}

bool STopPopB (tStackB *S) {
	if (S->top==0) {
		printf("Chyba: Do¹lo k podteèení zásobníku pro boolean!\n");
		return(NULL);
	}
	else {
		return(S->a[S->top--]);
	}
}

bool SEmptyB (tStackB *S) {

  return(S->top==0);
}

void BTInit (tBTNodePtr *RootPtr)	{

	 *RootPtr = NULL;
}

void BTInsert (tBTNodePtr *RootPtr, int Content) {

	if(*RootPtr == NULL)
	{
		tBTNodePtr new = malloc(sizeof(struct tBTNode));

		if(new == NULL)
		{
			//TODO
		}

		new->LPtr = NULL;
		new->RPtr = NULL;
		new->Cont = Content;
		*RootPtr = new;
	}
	else
	{
		tBTNodePtr node, prev;
		node = prev = *RootPtr;

		while(node != NULL)
		{
			prev = node;

			if(Content > node->Cont)
			{
				node = node->RPtr;
			}
			else if(Content < node->Cont)
			{
				node = node->LPtr;
			}
			else
			{
				node = NULL;
				prev = NULL;
			}
		}

		if(prev != NULL)
		{
			tBTNodePtr new = malloc(sizeof(struct tBTNode));

			if(new == NULL)
			{
				//TODO
			}

			new->LPtr = NULL;
			new->RPtr = NULL;
			new->Cont = Content;

			if(Content > prev->Cont)
			{
				prev->RPtr = new;
			}
			else if(Content < prev->Cont)
			{
				prev->LPtr = new;
			}
		}
	}


}

/*                                  PREORDER                                  */

void Leftmost_Preorder (tBTNodePtr ptr, tStackP *Stack)	{

	while(ptr != NULL)
	{
		SPushP(Stack, ptr);
		BTWorkOut(ptr);
		ptr = ptr->LPtr;
	}
}

void BTPreorder (tBTNodePtr RootPtr)	{

	if(RootPtr == NULL)
	{
		return;
	}

	tStackP *stack = malloc(sizeof(tStackP));
	if(stack == NULL)
	{
		//TODO
	}

	SInitP(stack);
	Leftmost_Preorder(RootPtr, stack);

	while(!SEmptyP(stack))
	{
		RootPtr = STopPopP(stack);
		Leftmost_Preorder(RootPtr->RPtr, stack);
	}

	free(stack);
}


/*                                  INORDER                                   */

void Leftmost_Inorder(tBTNodePtr ptr, tStackP *Stack)		{

	while(ptr != NULL)
	{
		SPushP(Stack, ptr);
		ptr = ptr->LPtr;
	}
}

void BTInorder (tBTNodePtr RootPtr)	{

	if(RootPtr == NULL)
	{
		return;
	}

	tStackP *stack = malloc(sizeof(tStackP));
	if(stack == NULL)
	{
		//TODO
	}

	SInitP(stack);
	Leftmost_Inorder(RootPtr, stack);

	while(!SEmptyP(stack) || RootPtr->RPtr != NULL)
	{
		RootPtr = STopPopP(stack);
		BTWorkOut(RootPtr);

		if(RootPtr->RPtr != NULL)
		{
			Leftmost_Inorder(RootPtr->RPtr, stack);
		}
	}

	free(stack);
}

/*                                 POSTORDER                                  */

void Leftmost_Postorder (tBTNodePtr ptr, tStackP *StackP, tStackB *StackB) {

	while(ptr != NULL)
	{
		SPushP(StackP, ptr);
		SPushB(StackB, true);
		ptr = ptr->LPtr;
	}

}

void BTPostorder (tBTNodePtr RootPtr)	{

	if(RootPtr == NULL)
	{
		return;
	}

	tStackP *stack = malloc(sizeof(tStackP));

	if(stack == NULL)
	{
		//TODO
		exit(1);
	}
	SInitP(stack);

	tStackB *stackVisited = malloc(sizeof(tStackB));
	if(stackVisited == NULL)
	{
		//TODO
		exit(1);
	}
	SInitB(stackVisited);

	Leftmost_Postorder(RootPtr, stack, stackVisited);

	while(!SEmptyP(stack))
	{
		RootPtr = STopPopP(stack);

		if(STopPopB(stackVisited))
		{
			SPushP(stack, RootPtr);
			SPushB(stackVisited, false);
			Leftmost_Postorder(RootPtr->RPtr, stack, stackVisited);
		}
		else
		{
			BTWorkOut(RootPtr);
		}

	}

	free(stackVisited);
	free(stack);
}


void BTDisposeTree (tBTNodePtr *RootPtr)	{

	if(*RootPtr == NULL)
	{
		return;
	}

	tStackP *stack = malloc(sizeof(tStackP));
	if(stack == NULL)
	{
		//TODO
	}

	SInitP(stack);
	Leftmost_Inorder(*RootPtr, stack);

	while(!SEmptyP(stack))
	{
		*RootPtr = STopPopP(stack);

		if((*RootPtr)->RPtr != NULL)
		{
			Leftmost_Inorder((*RootPtr)->RPtr, stack);
		}

		free(*RootPtr);
	}

	*RootPtr = NULL;
	free(stack);

}

