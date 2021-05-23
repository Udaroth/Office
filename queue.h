#ifndef OFFICE_QUEUE
#define OFFICE_QUEUE

#include <stdlib.h>
#include "office.h"
#include <stdio.h>

struct Queue {
  int front;
  int rear;
  size_t size;
  size_t capacity;
  struct employee** array;
};

struct Queue* createQueue(int capacity){
  struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
  queue->capacity = capacity;
  queue->front = 0;
  queue->size = 0;
  queue->rear = capacity - 1;
  queue->array = (struct employee**)malloc(queue->capacity * sizeof(struct employee*));

  return queue;
}

void freeQueue(struct Queue* queue){

  free(queue->array);
  free(queue);


}

int isFull(struct Queue* queue){

  return (queue->size == queue->capacity);

}


int isEmpty(struct Queue* queue) {

  return (queue->size == 0);

}

void enqueue(struct Queue* queue, struct employee* emp){

  if(isFull(queue)){
    return;
    // queue->array = (struct employee*)realloc(queue->array, queue->capacity * 2);
  }

  queue->rear = (queue->rear + 1) % queue->capacity;
  queue->array[queue->rear] = emp;
  queue->size = queue->size + 1;

}

struct employee* dequeue(struct Queue* queue){

  if(isEmpty(queue)){
    return NULL;
  }

  struct employee* emp = queue->array[queue->front];
  queue->front = (queue->front + 1) % queue->capacity;
  queue->size = queue->size - 1;
  return emp;


}


#endif