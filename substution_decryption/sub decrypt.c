#include <stdio.h>
void do_encryption(char*,char*);
int main()
{
    
    char encryption_key[26]="QWERTYUIOPASDFGHJKLZXCVBNM";
    char str[50]="QW)ER TYU I&OP";
    do_encryption(str,encryption_key);
    return 0;
}
void do_encryption(char *ab,char *cd)
{

   for(int i=0;i<50;i++)//for loop for the entire of the string
   {
       int task;// declareing an integer for switch case
       if (ab[i]>64&&ab[i]<91)
            task=1;             //the corresponding symbol is a capital letter
       else if(ab[i]==0)
            break;              //the corresponding symbol is a NULL character
       else 
            task=0;             //any other character
        int j=0;    
        switch(task) 
        {
            case 0:
                break;          //do nothing to the whitespacwe or stuff that should'nt be in the cipher
            case 1:
                
                while(ab[i]!=cd[j]) //work out which letter corresponds to which place in the decryption key
                {
                    j++;            //just incremen a variable until it is found
                }
                ab[i]=j+65;         // j will be between 0 and 25 so just add 65 to convert to ascii letter
                break;
            default:
            break;
                    
       }  
   }
   puts(ab); 
}