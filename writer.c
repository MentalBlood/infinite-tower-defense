#include "stdio.h"

int main(void)
{
	FILE *file = fopen("towersSpecifications/0.txt", "wb");
	fprintf(file, "%f\n%f\n%f\n%f\n%d\n%f", 0.2, 120.0, 0.07, 256.0, 0, 30.0);
	return 0;
}
