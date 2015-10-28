#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>


int main(void)
{
    
    string name = GetString();
        
    printf("%c", toupper(name[0]));   
    
    for (int i = 0, n = strlen(name); i < n; i++)
    {
        if(name[i]==' ')
            printf("%c", toupper(name[i+1]));    
    }
   
    printf("\n");

}
