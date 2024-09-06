#include "my_stdio.h"

void my_printf(char* str, ...) {

	va_list ap; //char* type pointer for reading variable arguments
	va_start(ap, str); //ap is setted variable argument pointer and last address position after str address position
						//ap�� �������� �����ͷ� ���� �غ� �Ѵٴ� ǥ��ȭ ���ÿ�, �������ڸ� ���� ��ġ�� str�ּ� �ٷ� ������ �����ؼ� �Ű����� str ���Ŀ� �� �پ ���� ...�� ����� ���� �����ּҷ� ap�� �����Ѵ�.
	while (*str) {

		if (*str == '%') {

			char temp = *(++str);
			int val;
			char* string;

			switch (temp) {
			case 'c':

				val = va_arg(ap, int); //for using putchar, character is saved in integer validation
									   //putchar�� ���ڷ� int�� �ޱ� ������ �̸� ����ϱ� ���ؼ� int������ ����
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
			
			char val; //%c ������ ��� '\n'�� ���� ó���� ���� �ʴ� ���� ����غ��� case�ȿ� �־�� ������..?
					  //�ƴ���, ���� ���尪�� �״�� ������ �ִٰ� �ٷ� Ż���ع����°� �Ǵ� �Ŵϱ�
					  //���������� �����ؼ� �ʱ�ȭ ���� �ʰ��ϰ�, val�� ���� �����ִ��� Ȯ���ϰ� ������ �д�
					  //���ǹ��� �߰��ؾ� �ҵ�?
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
