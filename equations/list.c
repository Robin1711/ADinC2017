#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct ListNode* List;

struct ListNode {
	char item;
	List next;
};

/* listEmptyError prints the error and aborts the program */
void listEmptyError() {
	printf("list empty\n");
	abort ();
}

/* listTooShort prints the error and aborts the program */
void listTooShort () {
	printf("List is too short\n");
	abort ();
}

/* printList prints every item in the list while recursively walking through it */
void printList(List li) {
	if (li != NULL) {
		printf("%c", li->item);
		printList(li->next);
	} else {
		printf("\n");
	}
}

/* newEmptyList returns a new empty list */
List newEmptyList() {
	return NULL;
}

/* isEmptyList returns whether the given list is empty */
int isEmptyList(List li) {
	return (li == NULL);
}

/* listLength returns the amount of items in the list */
int listLength(List li) {
	if (li == NULL) {
		return 0;
	} else {
		return 1 + listLength(li->next);
	}
}

/* addItemFront adds an item to the front of the list */
List addItemFront(char c, List li) {
	List newList = malloc(sizeof(struct ListNode));
	assert(newList != NULL);
	newList->item = c;
	newList->next = li;
	return newList;
}
/* addItemFront adds an item to the back of the list */
List addItemBack(char c, List li) {
	List newList = malloc(sizeof(struct ListNode));
	assert(newList != NULL);

	newList->item = c;
	newList->next = li;

	return newList;
}
/* removeFirstNode frees the first node of the given list and returns the tail of the list */
List removeFirstNode(List li) {
	List returnList;
	if (li == NULL) {
		listEmptyError();
	}
	returnList = li->next;
	free(li);
	return returnList;
}

/* freeList frees every node of the given list */
void freeList(List li) {
	if (li != NULL) {
		List rest = removeFirstNode(li);
		freeList(rest);
	} else {
		return;
	}
}

/* firstItem returns the first item of the list without removing the node */
char firstItem(List li) {
	if (li == NULL){
		listEmptyError ();
	}
	return li->item;
}

/* itemAtPos returns the item at the given position of the list without removing the node */
char itemAtPos(List li, int p) {
	if (li == NULL){
		listTooShort ();
	}
	if (p == 0) {
		return firstItem(li);
	} else {
		return itemAtPos(li->next ,p-1);
	}
}

/* listLength returns the amount of items in the list */
List reverseList(List li) {
	return li;
}