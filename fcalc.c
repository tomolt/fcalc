
/* fcalc - a basic, fully self-contained one-function calculator, *\
\* released into the public domain. written by Thomas Oltmann.    */
double fcalc(char **str, int *err, int _)
{
	switch (_)
	{
		case 0: ; /* Parse full expression */
			char *str1 = *str;
			int err1 = 0;
			double ret = fcalc(&str1, &err1, 1);
			while (*str1 != 0)
			{
				if (*str1 != ' ' && *str1 != '\n')
					err1 = 1;
				str1++;
			}
			if (err != 0) *err = err1;
			return ret;
		case -1: /* Parse primitive */
			while (**str == ' ') (*str)++; /* Skip whitespace */
			switch (**str)
			{
				case '-': /* Parse unary minus (negation) */
					(*str)++;
					return -fcalc(str, err, -1);
				case '(': /* Parse subexpression in parentheses */
					(*str)++;
					double ret = fcalc(str, err, 1);
					if (**str != ')')
					{
						*err = -1;
						return 0.0;
					}
					(*str)++;
					return ret;
				case '0': case '1': case '2': case '3': case '4': /* Parse number */
				case '5': case '6': case '7': case '8': case '9': case '.':
					_ = 0;
					double dig = 0.0, bak = 1.0;
					for (;;)
					{
						if (**str == '.')
						{
							_ = 1;
							(*str)++;
						}
						if (!(**str >= '0' && **str <= '9'))
							break;
						if (_ == 1) bak /= 10.0;
						dig = dig * 10.0 + (**str - '0');
						(*str)++;
					}
					return dig * bak;
				case 'p': case 'P': /* Parse 'pi' */
					(*str)++;
					if (**str != 'i' && **str != 'I')
					{
						*err = -1;
						return 0.0;
					}
					(*str)++;
					return 3.14159265358979;
				default:
					*err = -1;
					return 0.0;
			}
		default: ; /* Parse binary operation */
			double lhs = fcalc(str, err, -1);
			if (*err) return 0.0;
			for (;;)
			{
				while (**str == ' ') (*str)++;  /* Skip whitespace */
#define fcalc_BINOP(sym, prec, op) \
	if (prec >= _ && **str == sym) \
	{ \
		(*str)++; \
		double rhs = fcalc(str, err, (prec + 1)); \
		if (*err) return 0.0; \
		op; \
	}
				     fcalc_BINOP('+', 1, lhs = lhs + rhs)
				else fcalc_BINOP('-', 1, lhs = lhs - rhs)
				else fcalc_BINOP('*', 2, lhs = lhs * rhs)
				else fcalc_BINOP('/', 2, lhs = lhs / rhs)
				else return lhs;
#undef fcalc_BINOP
			}
	}
}
