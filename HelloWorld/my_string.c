#include "my_string.h"

int my_strlen(char *string) {

	int count = 0;

	while (*(string + count) != '\0')
		count++;

	return count;
}

char* my_strcpy(char *string1, const char *string2) {

	char count = 0;

	while (*(string2 + count) != '\0') {
		*(string1 + count) = *(string2 + count);
		count++;
	}

	*(string1 + count) = '\0';

	return string1;
}

char* my_strcat(char *string1, const char *string2) {

	int string1_size = my_strlen(string1);
	char count = 0;

	while (*(string2 + count) != '\0') {
		*(string1 + string1_size+count) = *(string2 + count);
		count++;
	}

	*(string1 + string1_size + count) = '\0';

	return string1;
}

int my_strcmp(char *string1, const char *string2) {

	int result = 0;
	int count = 0;

	while (result == 0 || *(string1+count) != '\0') {
		result = *(string1 + count) - *(string2 + count);
		count++;
	}

	return result;
}

void* my_memset(void *ptr, int value, size_t size) {

	size_t i = 0;
	unsigned char *temp = ptr;

	if (ptr == NULL || size == 0)
		return NULL;

	while (i < size) 
		temp[i++] = (unsigned char)value;

	return temp;
}

void* my_memcpy(void *dest, const void *source, size_t size) {

	size_t i = 0;
	unsigned char *temp_d = dest;
	const unsigned char *temp_s = source;

	if (temp_d == NULL || size == 0)
		return NULL;

	if (temp_s == NULL || size == 0)
		return NULL;

	while (size-- > 0)
		temp_d[i] = temp_s[i++];

	return temp_d;
}