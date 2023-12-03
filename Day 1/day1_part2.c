#include <stdio.h>
#include <string.h>

typedef unsigned char bool;
typedef unsigned char uchar;
typedef unsigned long long ulong2;

const int IN_LENGTH = 256;

const unsigned int FIRST_THREE = 16777215;
const ulong2 FIRST_FIVE = 1099511627775;

const uchar* ONE = "one";
const uchar* TWO = "two";
const uchar* THREE = "three";
const uchar* FOUR = "four";
const uchar* FIVE = "five";
const uchar* SIX = "six";
const uchar* SEVEN = "seven";
const uchar* EIGHT = "eight";
const uchar* NINE = "nine";

bool is_digit(uchar c)
{
	return (uchar)(c - '0') < 10;
}

bool single_digit_word_to_num(uchar* starting_char, uchar* last_char_of_string)
{
	switch (*starting_char)
	{
	case 'o':
		return (last_char_of_string - starting_char >= 2 && (*(int*)starting_char & FIRST_THREE) == (*(int*)ONE & FIRST_THREE) ) * 1;
	case 't':
	{
		uchar is_two = last_char_of_string - starting_char >= 2 && (*(int*)starting_char & FIRST_THREE) == (*(int*)TWO & FIRST_THREE);
		uchar is_three = last_char_of_string - starting_char >= 4 && (*(ulong2*)starting_char & FIRST_FIVE) == (*(ulong2*)THREE & FIRST_FIVE);
		return (is_two * 2) | (is_three * 3);
	}
	case 'f':
	{
		uchar correct_length = last_char_of_string - starting_char >= 3;
		// Exactly four bytes, no mask needed
		uchar is_four = correct_length && *(int*)starting_char == *(int*)FOUR;
		uchar is_five = correct_length && *(int*)starting_char == *(int*)FIVE;
		return (is_four * 4) | (is_five * 5);
	}
	case 's':
	{
		uchar is_six = last_char_of_string - starting_char >= 2 && (*(int*)starting_char & FIRST_THREE) == (*(int*)SIX & FIRST_THREE);
		uchar is_seven = last_char_of_string - starting_char >= 4 && (*(ulong2*)starting_char & FIRST_FIVE) == (*(ulong2*)SEVEN & FIRST_FIVE);
		return (is_six * 6) | (is_seven * 7);
	}
	case 'e':
		return (last_char_of_string - starting_char >= 4 && (*(ulong2*)starting_char & FIRST_FIVE) == (*(ulong2*)EIGHT & FIRST_FIVE)) * 8;
	case 'n':
		return (last_char_of_string - starting_char >= 3 && *(int*)starting_char == *(int*)NINE) * 9;
	}
	return 0;
}

int main()
{
	FILE* file; 
	file = fopen("input.txt", "r");

	char str[IN_LENGTH];
	int sum = 0;
	while (fgets(str, sizeof(str), file) != NULL)
	{
		uchar line_value = 0;
		uchar* cur_char  = NULL;

		cur_char = str;
		uchar* last_char = cur_char + (strlen(str) - 1);
		uchar digit_status = is_digit(*cur_char);
		uchar num_word_status = single_digit_word_to_num(cur_char, last_char);
		while (!digit_status && !num_word_status)
		{
			cur_char++;

			digit_status = is_digit(*cur_char);
			num_word_status = single_digit_word_to_num(cur_char, last_char);
		}
		line_value += ((*cur_char - '0')*digit_status + num_word_status) * 10;
		
		cur_char = last_char;
		digit_status = is_digit(*cur_char);
		num_word_status = single_digit_word_to_num(cur_char, last_char);
		while (!digit_status && !num_word_status)
		{
			cur_char--;

			digit_status = is_digit(*cur_char);
			num_word_status = single_digit_word_to_num(cur_char, last_char);
		}
		line_value += (*cur_char - '0')*digit_status + num_word_status;
		
		printf("\tLine value: %hu\n", line_value);
		sum += line_value;
	}
	printf("\n--- Calibration Value: %hu ---\n", sum);
	fclose(file);
	return 0;
}