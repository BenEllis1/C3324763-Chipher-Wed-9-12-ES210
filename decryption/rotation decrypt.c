/*This section of code will perform task 1 where the string needs to be encrypted
by any rotation by the demonstrator however it can be broken. 
=====================================================================*/
#include<stdio.h>
void decrypt_me(char *,int);// declaring enrcyption function
int main()
{
   char ch[50]="IFMMP XPSME"; //the string to be encrypted
  
decrypt_me(ch,1);// calling the function
}
 
void decrypt_me(char *ar,int x)//function definition
{
   
   for(int i=0;i<50;i++)//for loop for the entire of the string
   {
       int task;// declareing an integer for switch case
       if (ar[i]>64&&ar[i]<91)
            task=1;             //the corresponding symbol is a capital letter
       else if(ar[i]==0)
            break;              //the corresponding symbol is a NULL character
       else 
            task=0;             //any other character
            
        switch(task) 
        {
            case 0:
                break;          //do nothing to the whitespacwe or stuff that should'nt be in the cipher
            case 1:
                ar[i]=ar[i]-x;              //do the encrypting
                    if (ar[i]<65)           //if the letter is above Z in ascii 
                    {
                        ar[i]=ar[i]+26;     //-26 to get it back into a capital letter
                        break;
                    }
                    else 
                        break;
       }  
   }
   puts(ar); 
}