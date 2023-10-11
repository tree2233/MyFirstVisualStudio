#include "Linked_List.h"

/*
typedef struct node {
	struct node* next;
	int num;
}Node;

typedef struct stack {
	Node* top;
	int cur;
}Stack;
*/

int S_Empty(Stack* s) {
	return (!s->cur);
}

int S_Size(Stack* s) {
	return s->cur;
}

void S_Init(Stack* s) {

	s->cur = 0;
	s->top = NULL;
}

void S_Push(Stack* s, int num) {

	Node* temp = (Node*)malloc(sizeof(Node));

	if (S_Empty(s)) {

		temp->num = num;
		temp->next = s->top;

		s->cur++;
		s->top = temp;
	}
}

int S_Pop(Stack* s) {

	int temp = s->top->num;

	s->top = s->top->next;

	return temp;
}

int S_Top(Stack* s) {
	int temp = s->top->num;

	printf("%d\n", temp);

	s->top = s->top->next;

	return temp;
}