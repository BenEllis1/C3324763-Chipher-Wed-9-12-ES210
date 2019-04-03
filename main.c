#include <stdio.h>

 int main()
 {
//     char the[60]; // this array will store the char values for the name that will eventually get changed
     char name[60];// this will be the string that stores the original name
     short number; // just a number to rotate in the cipher
     scanf("%s",name);// input a word
     
     for(int i=0; i<60;i++)// go through each letter and store them in the "the" array as a value between 0 and 25
     {    if(name[i]!=0) 
         {
//         the[i]=name[i];
         printf("%i\n",(char)name[i]);
         }

         else 
         break;
     }
     scanf("%d\n", &number);// input a rotate by
     printf("%d\n",number);
     

     
     
     return 0;
   
 }