#pragma once

#define OPT_ADD 0x1
#define OPT_SUB 0x2
#define OPT_MUL 0x3
#define OPT_DIV 0x4
#define OPT_MOD 0x5
#define OPT_SFL 0x6
#define OPT_SFR 0x7
#define OPT_POW 0x8
#define OPT_FAC 0x9

#define PI 3.1415926535
#define E  2.7182818284

struct OptItem {
	char opt = 0x8f;
	double num;
};

int parseInt(char *src_start, char *src_end);

double parseNumber(char *src_start, char *src_end);

double calc(char *str, int head, int tail);