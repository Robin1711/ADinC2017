#ifndef QUEUES_H
#define QUEUES_H
/* First the type definitions.
 */

typedef struct State { /* a state contains a time and the states of the two sandglasses */
  int time;
  int sg1, sg2;
} State;

typedef struct ListNode *List;  /* List is the type of lists of states */

struct ListNode {
  State item;
  List next;
};

typedef struct Queue { /* a queue is a list and a pointer to the last node */
  List list;
  List lastNode;
} Queue;

List newEmptyList();
int isEmptyList (List li);
void listEmptyError();
List addItem(State s, List li);
State firstItem(List li);
List removeFirstNode(List li);
void freeList(List li);
Queue newEmptyQueue ();
int isEmptyQueue (Queue q);
void emptyQueueError ();
void enqueue (State s, Queue *qp);
State dequeue(Queue *qp);
void freeQueue (Queue q);

#endif