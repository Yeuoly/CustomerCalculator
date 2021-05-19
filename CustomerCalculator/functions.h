#pragma once

#define OPT_ADD 0x1
#define OPT_SUB 0x2
#define OPT_MUL 0x3
#define OPT_DIV 0x4

#define OPT_ADD 0x1
#define OPT_SUB 0x2

struct OptItem {
	char opt = 0x5;
	double num;
};

int parseInt(char *src_start, char *src_end);

double __cdecl calc(char *str, int head, int tail);