/* The following program checks the validity of a credit (or debit) card number and tells the user whether it belongs to AMEX/MASTERCARD/VISA. It uses Luhn's algorithm.
*/

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int digits(long long int num);
bool luhns(long long int num);
int starttwo(long long int num, int digit);

int main(void)
{

	long long int num; // We use 'long' here because 'int' cannot store 16-digit number
	int digit, start2;
	bool luhn;

    // Prompting the user to enter his/her card number without hypens and/or spaces
	do
	{
		num = get_long("Number: ");
	}
	while (false || num <= 0);


	digit = digits(num);
    luhn = luhns(num);
	start2 = starttwo(num, digit);

    // Main algorithm
	if (luhn == true)
	{
        // Checking conditions for American Express card
		if (digit == 15 && (start2 == 34 || start2 == 37))
		{
			printf("AMEX\n");
		}

        // Checking conditions for MasterCard card
		else if (digit == 16 && (start2 >= 51 && start2 <=55))
		{
			printf("MASTERCARD\n");
		}

        // Checking conditions for Visa card
        else if ((digit == 13 || digit == 16) && (start2 >= 40 && start2 < 50))
		{
			printf("VISA\n");
		}

		else
		{
			printf("INVALID\n");
		}
	}

	else
	{
		printf("INVALID\n");
	}

}

// Function to calculate the number of digits of the input
int digits(long long int num)
{
	int count = 0;
	while (num != 0)
	{
		num /= 10;
		count++;
	}
	return count;
}

// Function to validate Luhn's algorithm
bool luhns(long long int num)
{
	int ones, twos, total = 0;
	while (num != 0)
	{
		ones = num % 10;
		total += ones;
		num /= 10;

		twos = 2 * (num % 10);
		if (twos > 9)
		{
			total += twos % 10;
			twos /= 10;
			total += twos % 10;
		}
		else
		{
			total += twos;
		}
		num /= 10;
	}

	if (total % 10 == 0) {
		return true;
	}
	else
	{
		return false;
	}
}

// Function to find first two digits
int starttwo(long long int num, int digit)
{
	int start2;
	start2 = num / pow(10, digit - 2);
	return start2;
}
