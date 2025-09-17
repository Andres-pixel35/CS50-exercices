#include <cs50.h>
#include <stdio.h>

int calculate_coins(int cents, int coin_value);

int main(void)
{
    int cents;
    do
    {
        cents = get_int("Changed owed: ");
    }
    while (cents < 0);

    int quarters = calculate_coins(cents, 25);
    cents = cents - (quarters * 25);
    int dimes = calculate_coins(cents, 10);
    cents = cents - (dimes * 10);
    int nickels = calculate_coins(cents, 5);
    cents = cents - (nickels * 5);
    int pennies = calculate_coins(cents, 1);

    printf("%i\n", quarters + dimes + nickels + pennies);
}

int calculate_coins(int cents, int coin_value)
{
    int num_coins = 0;
    while (cents >= coin_value)
    {
        num_coins++;
        cents = cents - coin_value;
    }
    return num_coins;
}
