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

#define ERR_FUNC_UNDEF 0x001
#define ERR_QOUT_OVFLW 0x002
#define ERR_FUNC_EMPTY 0x003
#define ERR_FUNC_OVFLW 0x004
#define ERR_NUM_BLANK 0x005
#define ERR_NUM_BUSY 0x006
#define ERR_OPT_BUSY 0x007
#define ERR_EXPR_EXTRA 0x008

#define PI 3.1415926535
#define E  2.7182818284
#define DEFAULT_OPT_NUM 127

struct OptItem {
	char opt = DEFAULT_OPT_NUM;
	double num;
	bool filled = 0;
};

int parseInt(char *src_start, char *src_end);

double parseNumber(char *src_start, char *src_end);

double calc(char *str, int head, int tail, int *err);