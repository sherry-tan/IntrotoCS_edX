#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;
    
    //gets change owed
    do
    {
        printf("Change owed:");
        change = GetFloat();
    }
    while (change < 0);
    
    //converts change owed to cents
    int m = round(100*change);
    
    //computes number of quarters, dimes, nickels and pennies
    int q = m / 25;
    int d = m%25 / 10;
    int n = ((m%25)%10)/5;
    int p = ((m%25)%10)%5;
   
    printf("%i\n", q + d + n +p);
}
