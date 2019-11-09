/**
 * The following program checks the validity of a credit (or debit) card number and tells the user whether the provider is AMEX/MASTERCARD/VISA. 
 * It uses Luhn's algorithm.
 */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

unsigned long long get_card_number();
int get_no_of_digits(unsigned long long card_number);
bool luhn_algorithm(unsigned long long card_number);
int get_initial_two_digits(unsigned long long card_number, int no_of_digits);
void card_provider(int no_of_digits, int initial_two_digits);

int main(void)
{
	unsigned long long card_number = get_card_number();

	int no_of_digits = get_no_of_digits(card_number);

	bool is_valid = luhn_algorithm(card_number);

	// If the card number is valid, print the appropriate provider. Else print 'INVALID'.

	if (is_valid)
	{
		int initial_two_digits = get_initial_two_digits(card_number, no_of_digits);

		card_provider(no_of_digits, initial_two_digits);
	}
	else
	{
		printf("INVALID\n");
	}
}

unsigned long long get_card_number()
{
	// Ask for the card number

	unsigned long long card_number;

	printf("Enter Card Number: ");
	scanf("%llu", &card_number);

	return card_number;
}

int get_no_of_digits(unsigned long long card_number)
{
	// Calculate number of digits of the card

	int count = 0;

	while (card_number != 0)
	{
		card_number /= 10;
		count++;
	}

	return count;
}

bool luhn_algorithm(unsigned long long card_number)
{
	// Starting from second-to-last digit, multiply every other digit by 2 and add those products' digit together

	int total = 0;
	bool is_alternate = false; // Indicator for every alternate digit

	while (card_number != 0)
	{
		if (!is_alternate)
		{
			total += card_number % 10;
		}
		else
		{
			int temp = 2 * (card_number % 10);

			if (temp >= 10)
			{
				total += temp % 10;
				temp /= 10;
			}

			total += temp;
		}

		is_alternate = !is_alternate;

		card_number /= 10;
	}

	if (total % 10 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int get_initial_two_digits(unsigned long long card_number, int no_of_digits)
{
	// Calculate the intial two digits of card number

	return card_number / pow(10, no_of_digits - 2);
}

void card_provider(int no_of_digits, int initial_two_digits)
{
	// Checking conditions for American Express

	if (no_of_digits == 15 && (initial_two_digits == 34 || initial_two_digits == 37))
	{
		printf("AMEX\n");
	}

	// Checking conditions for MasterCard

	else if (no_of_digits == 16 && (initial_two_digits >= 51 && initial_two_digits <= 55))
	{
		printf("MASTERCARD\n");
	}

	// Checking conditions for Visa

	else if ((no_of_digits == 13 || no_of_digits == 16) && (initial_two_digits >= 40 && initial_two_digits <= 49))
	{
		printf("VISA\n");
	}

	else
	{
		printf("INVALID\n");
	}
}