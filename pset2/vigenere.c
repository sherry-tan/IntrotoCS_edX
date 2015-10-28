#include<stdio.h>
#include<string.h>
#include<cs50.h>
#include<stdlib.h>
#include<ctype.h>


bool has_non_alpha(string k);


int main(int argc, string argv[])
{
    //checks for a single command line argument that has only alphabets
    if (argc != 2 || has_non_alpha(argv[1]))
        {
            printf("Specify single command-line argument, alphabets only!\n");
            return 1;
        }          
            
    else
        {   
            string k = argv[1];     
            string text = GetString();
           
            for (int i = 0, j = 0, n = strlen(text), m = strlen(k); i < n; i++)
                {
                    int t = (int) text[i];
                                     
                    //finds index number of jth character of k, relative to A/a, where A/a = 0. j%m enables cycling of k when m < n
                    int c = (int) (toupper(k[j%m]))-65; 
                    
                    //encrypts ith character of text if alphabetical and increments j by one
                    if (isupper(text[i]))
                        {
                            text[i] = (char)(((t - 65 + c)%26) + 65);
                            j++;  
                        }
                    else if (islower(text[i]))
                        {
                            text[i] = (char)(((t - 97 + c)%26) + 97);               
                            j++ ; 
                        }
                }         
                         
             printf("%s\n", text);  
             return 0;       
     
        }
}    

/**
 * checks if there are any non-alphabetical characters in keyword k
 *
 */
bool has_non_alpha(string k)
{
    for(int i = 0, n = strlen(k); i < n; i++)
        {
            // returns true once a non-alphabet is detected
            if (!isalpha(k[i]))
                return true;
        }
    // else returns false if not terminated in for loop i.e. no non-alphas detected   
    return false;            
}


