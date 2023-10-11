#pragma once
#ifndef MY_STDIO_H
#define MY_STDIO_H

#include <stdio.h>
#include <stdarg.h>
#include "my_string.h"

void my_printf(char *str, ...);
void my_scanf(char *str, ...);

#endif