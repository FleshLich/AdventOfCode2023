#include <stdio.h>
#include <string.h>

const int IN_LENGTH = 256;

unsigned char is_digit(unsigned char c)
{
	return (unsigned char)(c - '0') < 10;
}

int main()
{
	FILE* file; 
	file = fopen("input.txt", "r");

	char str[IN_LENGTH];
	int sum = 0;
	while (fgets(str, sizeof(str), file) != NULL)
	{
		unsigned char line_value = 0;
		unsigned char* cur_char  = NULL;

		cur_char = str;
		while (!is_digit(*cur_char))
		{
			cur_char++;
		}
		printf("First: %c, %hu\n", *cur_char, (*cur_char));
		line_value += (*cur_char - '0') * 10;
		
		cur_char = str + (strlen(str) - 1);
		while (!is_digit(*cur_char))
		{
			cur_char--;
		}
		printf("Last: %c, %hu\n", *cur_char, *cur_char);
		line_value += (*cur_char - '0');
		
		printf("\tLine value: %hu\n", line_value);
		sum += line_value;
	}

	printf("\n\n--- Calibration Value: %hu ---\n", sum);
	fclose(file);
	return 0;
}