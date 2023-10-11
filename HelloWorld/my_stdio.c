#include "my_stdio.h"

void my_printf(char* str, ...) {

	va_list ap;
	va_start(ap, str);

	while (*str) {

		if (*str == '%') {

			char temp = *(++str);
			int val;
			char* string;

			switch (temp) {
			case 'c':

				val = va_arg(ap, int);

				putchar(val);

				break;

			case 'd':

				val = va_arg(ap, int);
				char num[100] = { 0, }, count = 0;

				while (val > 0) {
					num[count++] = (val % 10)+48;
					val = val / 10;
				}

				while(count--)
					putchar(num[count]);

				break;

			case 's':

				string = va_arg(ap, char*);

				while (*(string) != '\0')
					putchar(*(string++));

				break;
			}
		}
		else {

			putchar(*str);
		}

		str++;
	}

	va_end(ap);

	return;
}

void my_scanf(char* str, ...) {

	va_list ap;
	va_start(ap, str);

	while (*str) {

		int* num;
		char* charactor;
		char* string;

		if (*str == '%') {

			char temp = *(++str);
			
			char val; //%c 서식일 경우 '\n'에 대한 처리를 하지 않는 점도 고려해보면 case안에 넣어야 할지도..?
			while ((val = getchar()) == ' ');

			switch (temp) {
			case 'c':

				charactor = va_arg(ap, char*);

				if(val != ' ')
					*charactor = val;

				break;

			case 'd':

				num = va_arg(ap, int*);
				int sum = 0, number[100] = { 0, }, count = 0, sign = 1;

				while (val != ' ' && val != '\n') {

					number[count++] = val - 48;

					val = getchar();
				}

				while (count--) {
					sum += number[count] * sign;
					sign *= 10;
				}

				*num = sum;

				break;

			case 's': 

				string = va_arg(ap, char*);

				while (val != ' ' && val != '\n') {

					*(string++) = val;

					val = getchar();
				}

				*(string) = '\0';

				break;
			}
		}
		else {

			str++;
		}
		
	}

	va_end(ap);

	return;
}