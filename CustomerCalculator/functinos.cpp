#include"functions.h"
#include"ids.h"
#include<math.h>
#include<string>

#define OPT_BUSY_EXPR(pos) if(opts[optlp].opt != DEFAULT_OPT_NUM){ err->err_code = ERR_OPT_BUSY; err->err_position = pos; return 0; }

using namespace std;

double runFunc(char *funcname, double value, CalcError *err) {
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
	err->err_code = ERR_FUNC_UNDEF;
	return 0;
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

double calc(char *str, unsigned int head, unsigned int tail, CalcError *err) {
	if (tail == -1) {
		return 0;
	}
	OptItem opts[20];
	unsigned int lp = head, optlp = 0;
	opts[0].opt = OPT_ADD;
	while (lp <= tail) {
		int quot_count = 1;
		unsigned int src_start = lp;
		if (str[lp] == '(') {
			//获取右括号，然后把里面的内容传进去
			while (++lp <= tail) {
				if (str[lp] == '(') {
					quot_count++;
				}
				else if (str[lp] == ')') {
					if (--quot_count == 0) {
						break;
					}
				}
			}
			if (lp > tail) {
				err->err_code = ERR_QOUT_OVFLW;
				err->err_position = src_start;
				return 0;
			}
			opts[optlp].num = calc(str, src_start + 1, lp - 1, err);
			opts[optlp].pos_num = src_start;
			opts[optlp].filled = true;
			optlp++;
		}
		else if (str[lp] == '+') {
			OPT_BUSY_EXPR(lp)
			opts[optlp].opt = OPT_ADD;
			opts[optlp].pos_opt = lp;
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
			opts[optlp].pos_num = src_start;
			opts[optlp].filled = true;
			optlp++;
			lp++;
		}
		else if (str[lp] == '-') {
			OPT_BUSY_EXPR(lp)
			opts[optlp].opt = OPT_SUB;
			opts[optlp].pos_opt = lp;
			lp++;
		}
		else if (str[lp] == '*') {
			OPT_BUSY_EXPR(lp)
			opts[optlp].opt = OPT_MUL;
			opts[optlp].pos_opt = lp;
			lp++;
		}
		else if (str[lp] == '/') {
			OPT_BUSY_EXPR(lp)
			opts[optlp].opt = OPT_DIV;
			opts[optlp].pos_opt = lp;
			lp++;
		}
		else if (str[lp] == '%') {
			OPT_BUSY_EXPR(lp)
			opts[optlp].opt = OPT_MOD;
			opts[optlp].pos_opt = lp;
			lp++;
		}
		else if (str[lp] == '^') {
			OPT_BUSY_EXPR(lp)
			opts[optlp].opt = OPT_POW;
			opts[optlp].pos_opt = lp;
			lp++;
		}
		else if (str[lp] == '!') {
			//获取后面的数字然后整阶乘，这里要求是一个整数，但不能太大，超过double的限制，当然了其实可以整高级一点的操作用字符串做运算或者用int作为进制
			//但是太麻烦了=，=
			src_start = optlp - 1;
			opts[src_start].num = fact((int)opts[src_start].num);
			opts[optlp].pos_num = src_start;
			lp++;
		}
		else if ((str[lp] >= 'a' && str[lp] <= 'z') || (str[lp] >= 'A' && str[lp] <= 'Z')) {
			//这里解析函数，函数里的内容统一看做表达式迭代一遍calc
			//找出下一个不是英文字母的
			unsigned int func_start = src_start;
			lp++;
			while ((str[lp] >= 'a' && str[lp] <= 'z') || (str[lp] >= 'A' && str[lp] <= 'Z') || (str[lp] >= '0' && str[lp] <= '9')) {
				lp++;
			}
			char funcname[16] = { 0 };
			//越界检测
			if (lp - src_start <= 15) {
				strncpy_s(funcname, str + src_start, lp - src_start);
			}
			else {
				//函数名越界
				err->err_code = ERR_FUNC_OVFLW;
				err->err_position = src_start;
				strncpy_s(funcname, str + src_start, 15);
			}
			if (strcmp(funcname, "PI") == 0) {
				opts[optlp].num = PI;
				opts[optlp].filled = true;
				opts[optlp].pos_num = src_start;
			}
			else if (strcmp(funcname, "e") == 0) {
				opts[optlp].num = E;
				opts[optlp].filled = true;
				opts[optlp].pos_num = src_start;
			}
			else {
				src_start = lp;
				//检测括号对，如果连个左括号都没有就离谱了啊
				unsigned int left_quot_count = 0;
				//这里由于quot_count被在前面定义了，且默认值为1，但是这两种括号对的判断逻辑不太一样，这里我们需要把它改成0
				quot_count = 0;
				while (lp <= tail) {
					if (!quot_count && str[lp] != '(' && str[lp] != ' ') {
						err->err_code = ERR_QOUT_OVFLW;
						err->err_position = src_start;
						return 0;
					}
					if (str[lp] == '(') {
						left_quot_count++;
						quot_count++;
					}
					else if (str[lp] == ')') {
						if (--quot_count == 0) {
							break;
						}
					}
					lp++;
				}
				//没有左括号
				if (!left_quot_count) {
					err->err_code = ERR_QOUT_OVFLW;
					err->err_position = func_start;
					return 0;
				}
				if (lp > tail && quot_count != 0) {
					err->err_code = ERR_QOUT_OVFLW;
					err->err_position = src_start;
					return 0;
				}
				//如果函数内无值
				if (src_start + 1 >= lp) {
					err->err_code = ERR_FUNC_EMPTY;
					err->err_position = func_start;
					return 0;
				}
				else {
					//计算函数结果
					double num = calc(str, src_start + 1, lp - 1, err);
					opts[optlp].num = runFunc(funcname, num, err);
					if (err->err_code) {
						err->err_position = func_start;
						return 0;
					}
					opts[optlp].pos_num = func_start;
					opts[optlp].filled = true;
				}
				lp++;
			}
			optlp++;
		}
		else if(str[lp] == ' ' || str[lp] == ')' || str[lp] == '\n' || str[lp] == '\r') {
			lp++;
		}
		else {
			err->err_code = ERR_EXPR_EXTRA;
			err->err_position = lp;
			return 0;
		}
	}
	unsigned int rlp;
	//然后计算结果，先处理乘方部分
	for (rlp = 0; rlp <= optlp; rlp++) {
		if (opts[rlp].opt == DEFAULT_OPT_NUM && opts[rlp].filled) {
			//无计算符号
			err->err_code = ERR_NUM_BUSY;
			err->err_position = opts[rlp].pos_num;
			return 0;
		}
		if (!opts[rlp].filled && opts[rlp].opt != DEFAULT_OPT_NUM) {
			//计算符号后面为空，即有计算符号，但是无数据
			err->err_code = ERR_NUM_BLANK;
			err->err_position = opts[rlp].pos_opt;
			return 0;
		}
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