#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Card 4003 6000 0000 0014

// This is how we can get each number 
// 4003600000000014 % 10 = 4 
// 4003600000000014 / 100 = 40036000000000

// 1st case: 
// Iteratate through the CC number 
// Use modulo to get the last digit
// Add last digit to sum
// Divide the CC number by 100 
// Repeat 

// 2nd case: 
// Divide the CC number by 10 to get second to last number
// Iterate through the CC number 
// Use modulo to get the last digit 
// Add last digit multiplied by 2 to the sum 
    // If that digit is more than 9 we must do something
    // By seperating if its 10 it will become 1 + 0 according to luhn's algorithm we must do it
    // We will it by taking that number using modulo 10 and geeting the remainder 
    // While also dividing that number by ten 
    // That will lead up to us getting those two numbers and adding them up. 
// Divide the CC number by 100 
// Repeat 



// These are our global variables 
int normsum, multiplesum; 

// This will sum up the numbers normally starting at the last digit and doing modulo 10 (Modulo 10 gets the last digit which is want we want)
void normCCcal(long long x);

// This will sum up the numbers multiplied starting at the second to last digit and doing modulo 10 (Modulo 10 gets the last digit which is want we want)
void multipleCCcal(long long x);

// Verifies the Card Brand
void CardBrand(long long x);

int main() 
{
    // Here is our main variables
    long long CCnumber, WorkingCC, CountingCC; 
    int finalizer, intlength;
    // This variables is important to start our main while loop 
    // But also to eventually verify if the length is right 
    bool verify = 0;


    while(verify == 0)
    {
        do
        {
            printf("Enter your Credit Card number: ");
            scanf("%lld", &CCnumber);
        }while (CCnumber < 0);

        CountingCC = CCnumber;

        // This function will count the length of the credit card number 
        intlength = 0; 
        do{
            CountingCC = CountingCC / 10;
            intlength += 1;  
        }while(CountingCC != 0);

        if (intlength == 13 || intlength == 14 || intlength == 15 || intlength == 16)
        {
            verify = 1;
        }
        else
        {
            printf("Credit Card is not valid.\n");
        }
    }

    printf("You've entered %lld\n", CCnumber);

    WorkingCC = CCnumber; 

    normCCcal(WorkingCC);
    multipleCCcal(WorkingCC);

    // For debugging purposes
    //printf("normsum: %d, multiplesum: %d\n", normsum, multiplesum);

    finalizer = normsum + multiplesum; 

    if (finalizer % 10 == 0)
    {
        printf("This Credit Card is Valid!\n");
    }
    else
    {
        printf("Error!\n");
    }

    CardBrand(CCnumber);
    return 0;
}

void normCCcal(long long x)
{
    int lastnumb;
    while (x > 0)
    {
        // This modulo ten here will give us the last number especially in a long long number
        lastnumb = x % 10;
        // This will loop our sum for us 
        normsum += lastnumb; 
        // This will be the order (a) (b a b a) since we are starting from the last number 
        // Also this will take us to the next number after a -2 move
        x = x/100;
    }
}

void multipleCCcal(long long x)
{
    int lastnumb, lastnumbby2, a, b;
    // This changes the order to (a) (a b a b) order since we start at the second last number 
    x = x / 10; 
    while (x > 0)
    {
        // This equation will always take away the last number
        lastnumb = (x % 10);
        // Multiplies by 2 and then prepares our number if its more than two digits 
        lastnumbby2 = lastnumb * 2;
        if (lastnumbby2 > 9)
        {
            // Takes out the remainder of the two digit number (for example 15 % 10 = 5)
            a = lastnumbby2 % 10;
            multiplesum += a;
            // Takes the multiple and ignores all decimals so if 1.5 it will be 1 since its a int
            b = lastnumbby2 / 10; 
            multiplesum +=  b;
        }
        else 
        {
            multiplesum += lastnumbby2;
        }
        // This equal will take us to the next number after a -2 move
        x = x/100;
    }
}

void CardBrand(long long x)
{
    // This while loop looks for the first two integers of a credit card
    // As it loops and deletes every last number since it's divided by 10 
    while (x > 100)
    {
        x = x / 10; 
    }

    switch (x)
    {
    case 40 ... 50:
        printf("VISA\n");
        break;
    case 34:
        printf("AMERICAN EXPRESS\n");
        break;
    case 37:
        printf("AMERICAN EXPRESS\n");
        break;
    case 22 ... 27: 
        printf("MASTERCARD\n"); 
        break;
    case 51 ... 55: 
        printf("MASTERCARD\n"); 
        break;
    case 30: 
        printf("DINERS CLUB\n");
        break;
    case 60 ... 65: 
        printf("DISCOVER\n"); 
        break;
    case 35: 
        printf("JCB\n");
        break;
    default:
        printf("Unknown Company\n");
        break;
    }
}