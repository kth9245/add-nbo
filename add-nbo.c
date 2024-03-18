#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

uint32_t fton(char *file)
{
	FILE *fp = fopen(file, "rb");
	if (fp == NULL) {
		printf("Can't open file: %s\n", file);
		return 0;
	}
	
	fseek(fp, 0, SEEK_END);
	long int size = ftell(fp);
	if (size < sizeof(uint32_t)) {
		printf("%s has too small size\n", file);
		return 0;
	}
	fseek(fp, 0, SEEK_SET);
	
	uint32_t n;
	fread(&n, sizeof(uint32_t), 1, fp);
	fclose(fp);
	
	uint32_t a = 0;
	while (n > 0)
	{
		a *= 0x100;
		a += (n%0x100);
		n /= 0x100;
	}
	return a;
}

int main(int argc, char *argv[]){
	char *f1 = argv[1];
	char *f2 = argv[2];
	
	uint32_t n1 = fton(f1);
	uint32_t n2 = fton(f2);
	
	if (n1*n2 == 0){
		printf("Something Error\n");
		return 1;
	}
	printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", n1, n1, n2, n2, n1+n2, n1+n2);
	return 0;
}

