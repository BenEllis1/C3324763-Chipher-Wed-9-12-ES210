/*This section of code will perform task 1 where the string needs to be encrypted
by any rotation by the demonstrator however it can be broken. 
=====================================================================*/
#include<stdio.h>
int * unknown_rotation(char*);// working out three possible values of the letter E
void decrypt_me(char *,int);// declaring enrcyption function
int any_one_letter_word(char *);//work out what A or I could be
int determine_rotation(int *,int);//determine the most likely number to rotate by
int * determine_rotation_using_last_letter(char *);//determine most likely key using most common final letter (E)
int compare_E(int *,int *);//this function will compare the positions of the most frequent last letter and 
                           // and most frequent letter to determine E if there is no 1 letter words
int main()
{
char ch[100000]="DWLLWJ OGGVWV VAJWUL LOG EWF AFVWWV AFUGEW KAKLWJ. AEHJWKKAGF MH SVEAJSLAGF ZW TQ HSJLASDALQ AK. AFKLSFLDQ AEEWVASLW ZAK KSO GFW VSQ HWJUWANWV. GDV TDMKZWK JWKHWUL TML GXXAUWK ZWSJLWV EAFMLWK WXXWULK. OJALLWF HSJLAWK OAFVAFY GZ SK AF OALZGML GF KLSJLWV. JWKAVWFUW YWFLDWESF QWL HJWKWJNWV XWO UGFNAFUWV. UGEAFY JWYJWL KAEHDW DGFYWJ DALLDW SE KAKLWJ GF. VG VSFYWJ AF LG SVAWMK DSVAWK ZGMKWK GZ WDVWKL. YGFW HMJW DSLW YSQ ZSE. LZWQ KAYZ OWJW FGL XAFV SJW JWFL. ";
int t;
t=any_one_letter_word(ch);
int *Epossibles;
Epossibles=unknown_rotation(ch);
int the_key;
int *E_last_letter;
if(t==0)
{   E_last_letter=determine_rotation_using_last_letter(ch);
    the_key=compare_E(Epossibles,E_last_letter);
}
else
    the_key=determine_rotation(Epossibles,t);
if(the_key<5)
    the_key+=26;
int rot_by_unknown;
rot_by_unknown=the_key-5;
decrypt_me(ch,rot_by_unknown);// calling the function

unknown_rotation(ch);

}
int * unknown_rotation(char *fg)
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
   static int num[3];               //static array is required for syntax
   int othernum=0;                  // just another variable
   for (int i=0;i<3;i++)            //make a loop to repeat 3 times
   {
       int j=0;
       while(j<26)
       {
            if(counter[j]>=counter[othernum]) //works out the greatest number in the counter array
            {    
                othernum=j;
                num[i]=j+1;                     // creates an array of the three most likely positions of the letter E
            }    
            j++;  
       }
       
       counter[othernum]=0;                   //set the value of thed highest number to zero so it isn't found again 
       othernum=0;                            //set number to zero so loop can begin again
       
   }
   return num;
}
/*====================================================================================================
The decrypt_me function uses a key and the encrypted text to decrypt the messsage and print it to the 
compiler. 
=================================================================================================== */

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
                    ar[i]=ar[i]-x;  //do the encrypting
                    if (ar[i]<65)
                        ar[i]+=26;
                    break;
                default:
                    break;
            }
        }
        puts(ar);
}
/*========================================================================================================================
 
========================================================================================================================*/
int any_one_letter_word(char *str)
{
    for(int i=0;i<1000000;i++)
        {
            if(str[i]==32&&str[i+2]==32&&str[i+1]<92&&str[i+1]>64) //ie there is a 1 letter word with a space either side
                return str[i+1]-64;
            else if (str[i+1]==0)      //ie a null character is reached andhence there is no 1 letter words in the text
                break;
        }
    return 0;
}
/*=========================================================================================================================
 
 ========================================================================================================================*/
int determine_rotation(int *Epossibles,int the_letter)
{
    
    for(int i=0;i<3;i++)    // the Epossibles array is only three numbers long so the loop should go max 3 times
    {
        int check_for_A=0;
        int check_for_I=0;
        check_for_A=Epossibles[i]-4; //A is E minus 4 in ASCII
        check_for_I=Epossibles[i]+4; //I is E plus 4 in ASCII
        if (check_for_A<0)
            check_for_A+=26;           //if outside the (0,25) range add 26 
        else if(check_for_I>26)
            check_for_I-=26;           //if outside the (0,25) range subtract 26
        if(check_for_A==the_letter || check_for_I==the_letter)
            return Epossibles[i];   // if one of the 2 variables match then return the value for the position of the letter E                                 
    }
return 0;  
}
/*=========================================================================================================================
 check to see if it is committing
=========================================================================================================================*/
int * determine_rotation_using_last_letter(char *str)
{
    char counter[26]; // creating a counter that will work out the letter that occurs the most
    for(int i=0;i<27;i++)
        counter [i]=0;          /*setting each of the numbers in the counter array to zero to 
                           avoid any mishaps from memory addresses not being set to zero*/
    int x;
    for(int i=0;i<1000000;i++)
    {
        if(str[i]>65 && str[i]<91 && str[i+1]==32) // ie the last letter in the word
        {
            x=str[i]-65;
            counter[x]++;   // add 1 to the counter in the range (0,25)
        }
        else if(str[i+1]==0) // when a null character reached, the loop is terminated
            break;
    }
 static int num[3];               //static array is required for syntax
   int othernum=0;                  // just another variable
   for (int i=0;i<3;i++)            //make a loop to repeat 3 times
   {
       int j=0;
       while(j<26)
       {
            if(counter[j]>=counter[othernum]) //works out the greatest number in the counter array
            {    
                othernum=j;
                num[i]=j+1;                     // creates an array of the three most likely positions of the letter E
            }    
            j++;  
       }
       
       counter[othernum]=0;                   //set the value of thed highest number to zero so it isn't found again 
       othernum=0;                            //set number to zero so loop can begin again
       
   }
   return num;
}   
 /*=============================================================================================================================
  
==============================================================================================================================*/
int compare_E(int * all_let,int *last_let)
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(all_let[i]==last_let[j])     // the letter positions match
                return all_let[i];          //return the calculated value of E
        }
    }
return 50;      //ie something went wrong, since there were no matching numbers
}






