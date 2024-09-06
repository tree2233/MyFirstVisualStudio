#include "my_stdio.h"

void my_printf(char* str, ...) {

	va_list ap; //char* type pointer for reading variable arguments
	va_start(ap, str); //ap is setted variable argument pointer and last address position after str address position
						//ap를 가변인자 포인터로 읽을 준비를 한다는 표시화 동시에, 가변인자를 읽을 위치를 str주소 바로 앞으로 설정해서 매개변수 str 이후에 딱 붙어서 들어온 ...에 저장된 값의 시작주소로 ap를 설정한다.
	while (*str) {

		if (*str == '%') {

			char temp = *(++str);
			int val;
			char* string;

			switch (temp) {
			case 'c':

				val = va_arg(ap, int); //for using putchar, character is saved in integer validation
									   //putchar이 인자로 int를 받기 때문에 이를 사용하기 위해서 int형으로 받음
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
					  //아니지, 이전 저장값을 그대로 가지고 있다가 바로 탈출해버리는게 되는 거니깐
					  //전역변수로 설정해서 초기화 되지 않게하고, val에 값이 남아있는지 확인하고 없으면 읽는
					  //조건문을 추가해야 할듯?
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
