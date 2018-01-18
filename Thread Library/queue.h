#ifndef QUEUE_H
#define QUEUE_H

typedef void *any_ptr;

/* Define Boolean type, and associated constants. */
typedef int Boolean;
#define TRUE ((Boolean)1)
#define FALSE ((Boolean)0)


typedef struct queueObj_t
{
  any_ptr obj;
  struct queueObj_t *next;
}queueObj, *queueObj_ptr;

typedef struct Queue_t
{
 char name[20];      // every queue has some name now
 int numObj; // number of elements in the queue
 queueObj_ptr head;
 queueObj_ptr tail;
}Queue_t,*Queue;


/* External functions */
extern Queue q_create();
extern void q_destroy(Queue q);
extern void q_insert(Queue q, any_ptr obj);
extern any_ptr q_remove(Queue q);
extern Boolean q_is_empty(Queue q);
typedef void (*ThreadFunc)(any_ptr);
#endif
