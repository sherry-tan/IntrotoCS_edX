/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
 
bool binarysearch(int value, int values[], int i, int j);

bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if (n <= 0)
        return false;
    
  
    if (binarysearch(value, values, 0, n-1))
        return true;
    else
        return false;
    
}


bool binarysearch(int value, int values[], int i, int j)
{
    int m = (i + j)/2;
    
    if (value == values[m])
        return true;
    else if (value < values[m] && i < j)
        return binarysearch(value, values, i, m); 
    else if (value > values[m] && i < j)
        return binarysearch(value, values, m + 1, j);
    else
        return false;
}     
/**
 * Sorts array of n values.
 */
 
void swap(int *x, int *y); 

void sort(int values[], int n)
{
    // insertion sort
                    
    for (int i = 0; i < n; i++)
        {
            for (int j = i; j > 0; j--)
            {
                if (values[j-1] > values[j])
                    swap(&values[j-1], &values[j]);
            }
         } 
         
    
                                    
    return;
}

void swap (int *x, int *y)
{
    int tmp;
    
    tmp = *x;
    *x = *y; 
    *y = tmp;
}
