#include"functions.h"

double parseNumber(char *src_start, char *src_end) {
	double result = 0;
	while (src_start != (src_end + 1) && *src_start != '.') {
		result = result * 10 + (*(src_start++) - '0');
	}
	if (*src_start == '.') {
		double _float = 0;
		while (src_start != (src_end)) {
			_float = (_float + *(src_end--) - '0') / 10;
		}
		result += _float;
	}
	return result;
}

double calc(char *str, int head, int tail) {
	OptItem opts[20];
	int lp = head, optlp = 0;
	opts[0].opt = OPT_ADD;
	while (lp <= tail) {
		int quot_count = 1;
		int src_start = lp;
		switch (str[lp]) {
		case '(':
			//获取右括号，然后把里面的内容传进去
			while (++lp != tail) {
				if (str[lp] == '(') {
					quot_count++;
				}
				else if (str[lp] == ')') {
					if (--quot_count == 0) {
						break;
					}
				}
			}
			opts[optlp].num = calc(str, src_start + 1, lp - 1);
			optlp++;
			break;
		case '+':
			opts[optlp].opt = OPT_ADD;
			lp++;
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			//找出下一个不是数字的，然后闭合并设置num
			while ((str[lp] >= '0' && str[lp] <= '9') || str[lp] == '.') {
				lp++;
			}
			lp--;
			opts[optlp].num = parseNumber(str + src_start, str + lp);
			optlp++;
			lp++;
			break;
		case '-':
			opts[optlp].opt = OPT_SUB;
			lp++;
			break;
		case '*':
			opts[optlp].opt = OPT_MUL;
			lp++;
			break;
		case '/':
			opts[optlp].opt = OPT_DIV;
			lp++;
			break;
		default:
			lp++;
		}
	}
	//然后计算结果，先处理乘除部分
	int rlp;
	for (rlp = 0; rlp <= optlp; rlp++) {
		switch (opts[rlp].opt)
		{
		case OPT_MUL:
			opts[rlp].num = opts[rlp - 1].num * opts[rlp].num;
			opts[rlp - 1].num = 0;
			opts[rlp].opt = opts[rlp - 1].opt;
			break;
		case OPT_DIV:
			opts[rlp].num = opts[rlp - 1].num / opts[rlp].num;
			opts[rlp - 1].num = 0;
			opts[rlp].opt = opts[rlp - 1].opt;
			break;
		default:
			break;
		}
	}
	double result = 0;
	for (rlp = 0; rlp <= optlp; rlp++) {
		switch (opts[rlp].opt) {
		case OPT_ADD:
			result += opts[rlp].num;
			break;
		case OPT_SUB:
			result -= opts[rlp].num;
			break;
		}
	}
	return result;
}