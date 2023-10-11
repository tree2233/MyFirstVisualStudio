#pragma once
#ifndef MY_STRING_H
#define MY_STRING_H

#include <string.h>

int my_strcmp(char* string1, const char* string2);
char* my_strcpy(char* string1, const char* string2);
char* my_strcat(char* string1, const char* string2);
int my_strlen(char* string);

void* my_memset(void* ptr, int value, size_t size);
void* my_memcpy(void* dest, const void* source, size_t size);

#endif 