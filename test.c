#include <stdio.h>

double fcalc(const char **str, int *err, int _);

const double EPSILON = 0.00001;

unsigned int fails, total;

void test(const char *name, const char *str, double er, int ee)
{
	total++;
	int e;
	double r = fcalc(&str, &e, 0);
	double dr = r - er;
	if ((dr > 0.0 ? dr : -dr) > EPSILON || e != ee)
	{
		printf("Test '%s' failed; Expected %f/%d, got %f/%d\n", name, er, ee, r, e);
		fails++;
	}
}

int main()
{
	test("Integer", "11", 11, 0);
	test("Real number", "11.32", 11.32, 0);
	test("Sub-0-Real", ".32", 0.32, 0);
	test("Negation", "-42", -42, 0);
	test("Addition", "1.2 + 5", 6.2, 0);
	test("Subtraction", "3 - 1.4", 1.6, 0);
	test("Multiplication", "10 * 5", 50, 0);
	test("Division", "50 / 10", 5, 0);
	test("Precedence", "3 - 2 * 5", -7, 0);
	test("Pi", "pi", 3.14159265358979, 0);
	test("Parentheses", "3 * (1 + 2)", 9, 0);
	test("Unmatched (", "(1 + 2", 0.0, -1);
	printf("Performed %d tests, %d failures, %d%% success rate.\n", total, fails, 100 - fails * 100 / total);
	return fails == 0 ? 0 : -1;
}
