int test(int n)
{
	return n;
}

double test(double x)
{
	return x;
}

char test(char c)
{
	return c;
}


#include <stdio.h>
int main(void)
{
	printf("int: %d, float: %f, char: %c\n", test(42), test(3.14159), test('Z'));
}
