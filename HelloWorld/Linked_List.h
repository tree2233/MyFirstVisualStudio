#pragma once
#ifndef Linked_List_H
#define Linked_List_H

#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	struct node* next;
	int num;
}Node;

typedef struct stack {
	Node* top;
	int cur;
}Stack;

int S_Empty(Stack* s);

int S_Size(Stack* s);

void S_Init(Stack* s);

void S_Push(Stack* s, int num);

int S_Pop(Stack* s);

int S_Top(Stack* s);

#endif