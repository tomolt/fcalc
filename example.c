#include <stdio.h>

double fcalc(char **str, int *err, int _);

int main()
{
	char line[2048];
	char *ptr = line;
	int err;
	while (1)
	{
		printf("> ");
		fgets(line, 2048, stdin);
		if (line[0] == 'q') break;
		double ret = fcalc(&ptr, &err, 0);
		if (err) printf("<err>\n");
		else     printf("= %f\n", ret);
	}
	return 0;
}
