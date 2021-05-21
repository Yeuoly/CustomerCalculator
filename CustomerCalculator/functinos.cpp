#include"functions.h"
#include<math.h>
#include<string>
#include<vector>

using namespace std;

double runFunc(char *funcname, double value) {
	if (strcmp(funcname, "sin") == 0) {
		return sin(value);
	}
	else if (strcmp(funcname, "cos") == 0) {
		return cos(value);
	}
	else if (strcmp(funcname, "ln") == 0) {
		return log(value);
	}
	else if (strcmp(funcname, "tan") == 0) {
		return tan(value);
	}
	else if (strcmp(funcname, "sec") == 0) {
		return (double)1 / cos(value);
	}
	else if (strcmp(funcname, "csc") == 0) {
		return (double)1 / sin(value);
	}
	else if (strcmp(funcname, "exp") == 0) {
		return exp(value);
	}
	else if (strcmp(funcname, "lg") == 0) {
		return log10(value);
	}
	else if (strcmp(funcname, "arcsin") == 0) {
		return asin(value);
	}
	else if (strcmp(funcname, "arccos") == 0) {
		return acos(value);
	}
	else if (strcmp(funcname, "arctan") == 0) {
		return atan(value);
	}
	else if (strcmp(funcname, "cot") == 0) {
		return (double)1 / tan(value);
	}
	return value;
}

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

double fact(int base) {
	if (base == 0) {
		return 1;
	}
	double result = 1;
	for (int i = 2; i <= base; i++) {
		result *= i;
	}
	return result;
}

int parseInt(char *src_start, char *src_end) {
	int result = 0;
	while (src_start != (src_end + 1) && *src_start != '.') {
		result = result * 10 + (*(src_start++) - '0');
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
		if (str[lp] == '(') {
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
		}
		else if (str[lp] == '+') {
			opts[optlp].opt = OPT_ADD;
			lp++;
		}
		else if (str[lp] >= '0' && str[lp] <= '9') {
			//找出下一个不是数字的，然后闭合并设置num
			lp++;
			while ((str[lp] >= '0' && str[lp] <= '9') || str[lp] == '.' && lp <= tail) {
				lp++;
			}
			lp--;
			opts[optlp].num = parseNumber(str + src_start, str + lp);
			optlp++;
			lp++;
		}
		else if (str[lp] == '-') {
			opts[optlp].opt = OPT_SUB;
			lp++;
		}
		else if (str[lp] == '*') {
			opts[optlp].opt = OPT_MUL;
			lp++;
		}
		else if (str[lp] == '/') {
			opts[optlp].opt = OPT_DIV;
			lp++;
		}
		else if (str[lp] == '%') {
			opts[optlp].opt = OPT_MOD;
			lp++;
		}
		else if (str[lp] == '^') {
			opts[optlp].opt = OPT_POW;
			lp++;
		}
		else if (str[lp] == '!') {
			//获取后面的数字然后整阶乘，这里要求是一个整数，但不能太大，超过double的限制，当然了其实可以整高级一点的操作用字符串做运算或者用int作为进制
			//但是太麻烦了=，=
			src_start = optlp - 1;
			opts[src_start].num = fact((int)opts[src_start].num);
			lp++;
		}
		else if ((str[lp] >= 'a' && str[lp] <= 'z') || (str[lp] >= 'A' && str[lp] <= 'Z')) {
			//这里解析函数，函数里的内容统一看做表达式迭代一遍calc
			//找出下一个不是英文字母的
			lp++;
			while ((str[lp] >= 'a' && str[lp] <= 'z') || (str[lp] >= 'A' && str[lp] <= 'Z') || (str[lp] >= '0' && str[lp] <= '9')) {
				lp++;
			}
			char funcname[256] = { 0 };
			//越界检测
			if (lp - src_start <= 255) {
				strncpy_s(funcname, str + src_start, lp - src_start);
			}
			else {
				strncpy_s(funcname, str + src_start, 255);
			}
			if (strcmp(funcname, "PI") == 0) {
				opts[optlp].num = PI;
			}
			else if (strcmp(funcname, "e") == 0) {
				opts[optlp].num = E;
			}
			else {
				src_start = ++lp;
				//检测括号对
				while (lp <= tail) {
					if (str[lp] == '(') {
						quot_count++;
					}
					else if (str[lp] == ')') {
						if (--quot_count == 0) {
							break;
						}
					}
					lp++;
				}
				//计算函数结果
				double num = calc(str, src_start, lp - 1);
				opts[optlp].num = runFunc(funcname, num);
				lp++;
			}
			optlp++;
			
		}
		else {
			lp++;
		}
	}
	int rlp;
	//然后计算结果，先处理乘方部分
	for (rlp = 0; rlp <= optlp; rlp++) {
		switch (opts[rlp].opt)
		{
		case OPT_POW:
			opts[rlp].num = pow(opts[rlp - 1].num, opts[rlp].num);
			opts[rlp - 1].num = 0;
			opts[rlp].opt = opts[rlp - 1].opt;
			break;
		default:
			break;
		}
	}
	//然后计算结果，先处理乘除模部分
	for (rlp = 1; rlp <= optlp; rlp++) {
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
		case OPT_MOD:
			opts[rlp].num = fmod(opts[rlp - 1].num, opts[rlp].num);
			opts[rlp - 1].num = 0;
			opts[rlp].opt = opts[rlp - 1].opt;
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