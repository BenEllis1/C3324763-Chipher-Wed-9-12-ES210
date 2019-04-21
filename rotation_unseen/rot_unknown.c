/*This section of code will perform task 1 where the string needs to be encrypted
by any rotation by the demonstrator however it can be broken. 
=====================================================================*/
#include<stdio.h>
int * unknown_rotation(char*);
void decrypt_me(char *,int);// declaring enrcyption function
int main()
{
char ch[100000]="SJSFMPCRM WG O USBWIG. PIH WT MCI XIRUS O TWGV PM WHG OPWZWHM HC QZWAP O HFSS, WH KWZZ ZWJS WHG KVCZS ZWTS PSZWSJWBU HVOH WH WG GHIDWR. - OZPSFH SWBGHSWB"; //the string to be encrypted
int rot_by_unknown=14;
int *something;
something=unknown_rotation(ch);
for(int i=0;i<3;i++)
{
    printf("\n%d",something[i]);
}
printf("\n");
decrypt_me(ch,rot_by_unknown);// calling the function

unknown_rotation(ch);

}
int *unknown_rotation(char *fg)
{
   char counter[26]; // creating a counter that will work out the letter that occurs the most
   for(int i=0;i<27;i++)
        counter [i]=0;          /*setting each of the numbers in the counter array to zero to 
                            avoid any mishaps from memory addresses not being set to zero*/
   int t=0;
   for(int i=0;i<100000;i++)       // creating a loop that will go through every character in the string
   {
        if(fg[i]==0)
            break;                  // break out of the for loop if there is a null character
        else if(fg[i]>64&&fg[i]<91) 
        {
            t=fg[i]-65;              // if it is a letter add on to the corrsponding letter on the counter array 
            counter[t]++;
        } 
    }
       for (int i = 0; i < 26; ++i) // this will get deleted it is for programmer 
    {
        printf(" %d", counter[i]);
    }
   static int num[3];               //static array is required for syntax
   int othernum=0;                  // just another variable
   printf("\n");
   for (int i=0;i<3;i++)            //make a loop to repeat 3 times
   {
       int j=0;
       while(j<26)
       {
            if(counter[j]>=counter[othernum])
                othernum=j;
                num[i]=j;
            j++;  
       }
       
       counter[othernum]=0;
       othernum=0;
       
   }
   return num;
}
 
void decrypt_me(char *ar,int x)//function definition
{
     for(int i=0;i<1000000;i++)//for loop for the entire of the string
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