#ifndef EQUATIONS_LIST_H
#define EQUATIONS_LIST_H

typedef struct ListNode* List;

struct ListNode {
  char item;
  List next;
};

/* listEmptyError prints the error and aborts the program */
void listEmptyError();

/* listTooShort prints the error and aborts the program */
void listTooShort ();

/* printList prints every item in the list while recursively walking through it */
void printList(List li);

/* newEmptyList returns a new empty list */
List newEmptyList();

/* isEmptyList returns whether the given list is empty */
int isEmptyList(List li);

/* listLength returns the amount of items in the list */
int listLength(List li);

/* addItemFront adds an item to the front of the list */
List addItemFront(char c, List li);

/* addItemBack adds an item to the back of the list */
List addItemBack(char c, List li);

/* removeFirstNode frees the first node of the given list and returns the tail of the list */
List removeFirstNode(List li);

/* freeList frees every node of the given list */
void freeList(List li);

/* firstItem returns the first item of the list without removing the node */
char firstItem(List li);

/* itemAtPos returns the item at the given position of the list without removing the node */
char itemAtPos(List li, int p);

/* listLength returns the amount of items in the list */
List reverseList(List li);

#endif //EQUATIONS_LIST_H
