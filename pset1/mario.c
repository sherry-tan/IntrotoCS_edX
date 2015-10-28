#include <stdio.h>
#include <cs50.h>
/**
 * Prints (x - n) spaces in the nth row of a pyramid with height x
 *
 */
void printspace(int n, int x)
{
    for (int i = 1; i <= x - n; i++)
        {
            printf(" ");            
        }
}

/**
 * Prints ( n + 1) #'s in the nth row of a pyramid
 *
 */
void printhash(int n)
{
    for (int j = 1; j <= n + 1; j++)
        {
            printf("#"); 
        }
}

int main(void)
{   
    int x;

    // Get height of pyramid, x
    do
    {
        printf("height:");
        x = GetInt();
    }
    while (x < 0 || x> 23);

    // Print spaces and hashes for each row in pyramid of height x
    for (int n = 1; n <= x; n++)
    {
        printspace(n,x);
        printhash(n); 
        printf("\n");        
      }    
}

