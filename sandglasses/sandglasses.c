#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queues.h"

const int TRUE = 1;
const int FALSE = 0;

/* The function compare is implemented according the following specifications:
 * compare(a,b)= −1     if a precedes b
 * compare(a,b)= 0      if a is identical to b
 * compare(a,b)= +1     if b precedes a
 */
int compare(State a, State b){
	if( a.time < b.time ){
		return -1; // a precedes b
	}
	if( a.time > b.time ){
		return 1; // b precedes a
	}
	if( a.sg1 < b.sg1 ){
		return -1; // a precedes b
	}
	if( a.sg1 > b.sg1 ){
		return 1; // b precedes a
	}
	if( a.sg2 < b.sg2){
		return -1; // a precedes b
	}
	if( a.sg2 > b.sg2 ){
		return 1; // b precedes a
	}
	// else they are exactely the same.
	return 0;
}

/* The function updateTime lets time run down from the smallest sandglass.
 */
State updateTime(State s){
  if( s.sg1 == s.sg2 ){ // This also handles the case when both are zero.
    s.time += s.sg1;
    s.sg1 = 0;
    s.sg2 = 0;
    return s;
  }

  if( s.sg1 == 0 ){
    s.time += s.sg2;
    s.sg2 = 0;
  }else if( s.sg2 == 0 ){
    s.time += s.sg1;
    s.sg1 = 0;
  }else if( s.sg1 < s.sg2 ){
    s.time += s.sg1;
    s.sg2 -= s.sg1;
    s.sg1 = 0;
  }else{ //s.sg2 < s.sg1
    s.time += s.sg2;
    s.sg1 -= s.sg2;
    s.sg2 = 0;
  }
  return s;
}

/* The function action generates a new state from an existing state.
 */
State action(State s, int action, int cap1, int cap2 ) {
  switch( action ){
    case 1: /* do nothing */
    break;
    case 2: s.sg1 = cap1-s.sg1;
    break;
    case 3: s.sg2 = cap2-s.sg2;
    break;
    case 4: 
    s.sg1 = cap1-s.sg1;
    s.sg2 = cap2-s.sg2;
    break;
		default:
			printf("\nWe reached the default case. This should not be possible\n");
			abort();
		break;
  }
  s = updateTime(s);
  return s;
}

/* The function timeable checks whether a given time can be determined
 * exactly by two sandglasses with given capacities.
 */
void insertUnique(State s, Queue *qp){
  List cur, prev;
  if( isEmptyQueue(*qp) ){
    enqueue(s, qp);
    return;
  }

  cur = qp->list;
  if( compare(cur->item, s) == 1 ){
    qp->list = addItem(s, qp->list);
    return;
  }

  while( cur != NULL ){
    if( compare(cur->item, s) == 0 ){
      return; // do nothing.
    }

    if( compare(cur->item, s) == 1 ){
      prev->next = addItem(s, cur);
      return;
    }

    prev = cur;
    cur = cur->next;
  }

  prev->next = addItem(s, NULL);
}

/* The function timeable checks whether a given time can be determined
 * exactly by two sandglasses with given capacities.
 */
int timeable(int cap1, int cap2, int goalTime) {
	if( goalTime == 0|| goalTime % cap1 == 0 || goalTime % cap2  == 0){
		return TRUE;
	}
  Queue q = newEmptyQueue();
  State init, s;
  State action1, action2, action3, action4;

  init.time = 0;
  init.sg1 = 0;
  init.sg2 = 0;
  enqueue(init, &q);

  while( !isEmptyQueue(q) ){
    s = dequeue(&q);
    if( s.time < goalTime ){
      if( !(s.sg1 == 0 && s.sg2 == 0) ){ // When both sandglasses are 0, and we do nothing (operation 1), the queue runs in a loop.
        action1 = action(s, 1, cap1, cap2);
        if( action1.time > goalTime ){
        if( action1.time == goalTime ){
        	freeQueue(q);
        	return TRUE;
        }
         insertUnique(action1, &q);
      	}	

      }
      action2 = action(s, 2, cap1, cap2);
      action3 = action(s, 3, cap1, cap2);
      action4 = action(s, 4, cap1, cap2);
      if( action2.time <= goalTime )
      	insertUnique(action2, &q);
     	if( action3.time <= goalTime )
     		insertUnique(action3, &q);
     	if( action4.time <= goalTime )
     		insertUnique(action4, &q);

      if(action2.time == goalTime ||
      	action3.time == goalTime ||
      	action4.time == goalTime ){
       	freeQueue(q);
       	return TRUE;
      }
    }
  }
  freeQueue(q);
  return FALSE;
}

/* main performs a dialogue with the user. The user is asked to provide three numbers:
 * the (positive) capacities of the sandglasses and the goal time (>= 0).
 * The program indicates whether the goal time can be determined exactly. 
 * The dialogue is ended by the input '0'.
 */
int main(int argc, char *argv[]){
  int cap1, cap2, goalTime; 
  printf("give the sandglass capacities and the goal time: ");
  scanf("%d",&cap1);
  while ( cap1 > 0 ) {
    scanf("%d",&cap2);
    assert( cap2 > 0 );
    scanf("%d",&goalTime);
    assert( goalTime >= 0 );
    if ( timeable(cap1,cap2,goalTime) ) {
      printf("%d and %d can time %d\n", cap1, cap2, goalTime);
    } else {
      printf("%d and %d cannot time %d\n", cap1, cap2, goalTime);
    }
    printf("\ngive the sandglass capacities and the goal time: ");
    scanf("%d",&cap1);
  }  
  printf("good bye\n");
  return 0;
}