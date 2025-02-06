/**
 * https://www.codewars.com/kata/525f50e3b73515a6db000b83
 * 
 * Write a function that accepts an array of 10 integers (between 0 and 9), that
 * returns a string of those numbers in the form of a phone number.
 * 
 * Example:
 *     create_phone_number(phnum, (const unsigned char[]){1,2,3,4,5,6,7,8,9,0});
 *         phnum <- "(123) 456-7890"
 * 
 * Returned format must be correct in order to complete this challenge.
 */

/* LOL */

#include <stdint.h>

#define ENCLOSURE_OPEN		0
#define ENCLOSURE_CLOSE		4
#define SPACE_PLACE			5
#define MINUS				9
#define PHNUM_END			14

char *create_phone_number(char phnum[15], const uint8_t digits[10]) {
	uint32_t iter = 0;
	char fill = 0;

	while (iter < PHNUM_END && digits) {
		switch (iter) {
			case ENCLOSURE_OPEN:	fill = '(';
				break;
			case ENCLOSURE_CLOSE:	fill = ')';
				break;
			case SPACE_PLACE:		fill = ' ';
				break;
			case MINUS:				fill = '-';
				break;
			default:				fill = *digits + '0';
				++digits;
				break;
		}
		phnum[iter++] = fill;
	}
	phnum[iter] = '\x00';
	return phnum;
}
