#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
    int size;

};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List*list=(List*)malloc(sizeof(List));
  list->head=NULL;
  list->tail=NULL;
  list->current=NULL;
  return list;
}

void * firstList(List * list) {
  if (list==NULL){
    return NULL;
  }
  if(list->head==NULL){
    return NULL;
  }
  list->current=list->head;
  return list->current->data;
}

void * nextList(List * list) {
  if (list==NULL){
    return NULL;
  }
  if (list->current == NULL){
    return NULL;
  }
  if (list->current->next == NULL){
    return NULL;
  }
  list->current=list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  if (list==NULL){
    return NULL;
  }
  if (list->tail == NULL){
    return NULL;
  }
    list->current=list->tail;
  return list->current->data;
}

void * prevList(List * list) {
  if (list==NULL){
    return NULL;
  }
  if (list->current == NULL){
    return NULL;
  }
  if (list->current->prev == NULL){
    return NULL;
  }
  list->current=list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) {
  Node*new=createNode(data);
  new->next=list->head;
  if(list->head != NULL){
    list->head->prev=new;
    new->prev=NULL;
    list->head=new;
    list->size++;
  }
  else{
    list->head=list->tail=new;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node*new=createNode(data);
  new->next=list->current->next;
  if(list->current->next != NULL){ 
  list->current->next=new;
  new->prev=list->current;
  list->size++;
  }
  else{
    list->head=list->tail=new;
  }
  if(list->current->next==NULL){
    list->current->next=new;
    new->prev=list->current;
    new->next=NULL;
    list->size++;
  }
  
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if (list==NULL){
    return NULL;
  }

  Node*actual= list->current;
  Node*previo=actual->prev;
  Node*siguiente=actual->next;
  void*data=actual->data;

  if(list->current==list->head){
    list->current=siguiente;
    list->head=siguiente;
    list->current->prev=NULL;
  }
  else{
    list->current=siguiente;
    if(siguiente==NULL){
      siguiente->prev=previo;
      
    }
  }
  free(actual);
  return data;

  }

 

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}