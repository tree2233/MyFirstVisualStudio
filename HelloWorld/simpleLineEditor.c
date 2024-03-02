#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define cursorForward(X) printf("\033[%dC", X)
#define cursorBackward(X) printf("\033[%dD", X)
#define lineDel() printf("\r\033[K")

#define KEY_ESCAPE  0x001b
#define KEY_ENTER   0x000a
#define KEY_UP      0x0105
#define KEY_DOWN    0x0106
#define KEY_LEFT    0x0107
#define KEY_RIGHT   0x0108
#define BACK_SPACE 127
#define SPACE 32

char str[100] = "hello my name is";

static struct termios newSet, oldSet;

static void setKb(void);
static void resetKb(void);
static int getCh(void);
static int kbHit(void);
static int kbEsc(void);
static int kbGet(void);
static void addChar(char* str, int lineNum, char ch);
static void delChar(char* str, int lineNum);
static void printStr(char* str, int lineNum);
char* kbControl(char* str);

static void setKb(void) {
	//tcgetattr : get termios setting return 0 on success -1 on fail
	if(tcgetattr(0, &oldSet))
		printf("get oldkbSet fail!\n");
		
	if(memcpy(&newSet, &oldSet, sizeof(oldSet)) != &newSet)
		printf("copy Set old to new fail!\n");


	//ICANON : standard input setting / ECHO : print keyboard input to console display
	newSet.c_lflag &= ~(ICANON | ECHO);
	//VMIN : minimun size to wait
    newSet.c_cc[VMIN] = 1;
	//VTIME : minimun time to wait
    newSet.c_cc[VTIME] = 0;

	//tcsetattr : set termios setting return 0 on success -1 on fail
    if(tcsetattr(0, TCSANOW, &newSet))
		printf("set newkbSet fail!\n");
}

static void resetKb(void) {
	if(tcsetattr(0, TCSANOW, &oldSet))
		printf("resetkb() fail!\n");
}

static int getCh(void)
{
    int c = 0;

	setKb();

    c = getchar();

	resetKb();
    return c;
}

static int kbHit(void)
{
    int c = 0;

	setKb();
	
	//kbhit need to breakout even user do not keyboard hit
	/*
	newSet.c_cc[VMIN] = 0;
	newSet.c_cc[VTIME] = 1;
	tcsetattr(0, TCSANOW, &newSet);
	*/

	c = getchar();

	resetKb();

	//ungetc: return ch to buffer
    if (c != -1) ungetc(c, stdin);
    return ((c != -1) ? 1 : 0);
}

static int kbEsc(void) 
{
    int c;

    if (!kbHit()) return KEY_ESCAPE;
    c = getCh();
    if (c == '[') {
        switch (getCh()) {
            case 'A':
                c = KEY_UP;
                break;
            case 'B':
                c = KEY_DOWN;
                break;
            case 'C':
                c = KEY_RIGHT;
                break;
            case 'D':
				c = KEY_LEFT;
                break;
            default:
                c = 0;
                break;
        }
	}
    else {
        c = 0;
    }
    if (c == 0) while (kbHit()) getCh();
    return c;
}

static int kbGet(void)
{
    int c;

    c = getCh();
    return (c == KEY_ESCAPE) ? kbEsc() : c;
}

static void addChar(char* str, int lineNum, char ch) {

	int i;

	for(i = strlen(str)-1; i >= lineNum; i--)
		str[i+1] = str[i];
	
	str[lineNum] = ch;

}	
	
static void delChar(char* str, int lineNum) {
	
	int i, size = strlen(str)-1;

	for(i = lineNum; i <= size; i++)
		str[i] = str[i+1];

	str[size] = ' ';
}

static void printStr(char* str, int lineNum) {
	int i;

	//line clear
	lineDel();

	//new str input
	printf("\r%s\r", str);
	
	//cursor position
	if(lineNum)
		cursorForward(lineNum);
}

char* kbControl(char* str) {
	int c, lineNum = 0;

	printf("\n%s\r", str); 
	while(1) {
		if(kbHit())
			c = kbGet();

        if (c == KEY_ENTER || c == KEY_ESCAPE || c == KEY_UP || c == KEY_DOWN) {
            break;
        } 
		else if (c == KEY_RIGHT) {
            cursorForward(1);
			lineNum++;
        }
		else if (c == KEY_LEFT) {
            cursorBackward(1);
			if(lineNum) lineNum--;
        }
		else if (c == SPACE) {
			addChar(str, lineNum, ' ');
			lineNum++;
			printStr(str, lineNum);
		}
		else if (c == BACK_SPACE) {
			if(lineNum > 0) {
				delChar(str, lineNum-1);
				lineNum--;
				printStr(str, lineNum);
			}

        }
		else {
			addChar(str, lineNum, c);
			lineNum++;
			printStr(str, lineNum);
		}
	}
	
	return str;
}

int main(void)
{
		
	kbControl(str);

    return 0;
}
