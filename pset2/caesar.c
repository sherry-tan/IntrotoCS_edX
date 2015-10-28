#include<stdio.h>
#include<string.h>
#include<cs50.h>
#include<stdlib.h>
#include<ctype.h>

int main(int argc, string argv[])
{
    
    if (argc != 2)
        {
            printf("don't forget to specify the command-line argument!\n");
            return 1;
        }    
    else
        {
            int k = atoi(argv[1]);
            string text = GetString();
        
            for (int i = 0, n = strlen(text); i < n; i++)
                {
                    int j = (int) text[i];
               
                    if (isupper(text[i]))
                        text[i] = (char)(((j - 65 + k)%26) + 65);
                    else if (islower(text[i]))
                        text[i] = (char)(((j - 97 +k)%26) + 97);               
                }         
                         
             printf("%s\n", text);  
             return 0;       
     
        }
}    


