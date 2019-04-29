/*  Title: Programming Assignment 1 English Ciphers
    Author: 30420861
    This program can sucessfully encrypt and decrypt a rotational cipher and a substitutional cipher given the appropriate 
    key. It can also decrypt a rotational cipher without a key. In ordee fo the program to work properly the user is required
    to enter an input into 3 different files. the first file (input.txt) is where the text that needs to be encrypted or 
    decrypted is entered. In the file (task_selection) the usre is required to enter a number form 1 to 5 in order to select the 
    appropriate process to tae place. The third file is the (task_key) this is where they task key must be entered. A number for 
    the rotational cipher(task 1 and 2) and a 26 character string with no spaces for the substitutional cipher (task 3 and 4). 
    Task 5, the rotational cipher without a key does not use the task_key file.
 */

#include<stdio.h>
#include<stdlib.h>

int get_rotation_key_from_string(char *);//this will go through the task_key file and find a key to use
int * unknown_rotation(char*);// working out three possible values of the letter E
char * decrypt_me(char *,int);// declaring rotation dercyption function
char * encrypt_me(char *,int );// declaring rotation encryption function
char * do_substitution_encrypt(char*,char*);// declaring substitution function
char * do_substitution_decrypt(char*,char*);// declaring substitution function
int any_one_letter_word(char *);//work out what A or I could be
int determine_rotation(int *,int);//determine the most likely number to rotate by
int * determine_rotation_using_last_letter(char *);//determine most likely key using most common final letter (E)
int compare_E(int *,int *);//this function will compare the positions of the most frequent last letter and 
                           // and most frequent letter to determine E if there is no 1 letter words
int main()
{
    /*the following printf statments decsribe the requirements for the files in order to get the assessment task to work
    failure to write the relevant text and integers in the correct position will cause a crash of the program */
    printf("Welcome to the Enigma Machine\n\n");
    printf("Enter number in file (task_selection)\n");
    printf("For encryption with a rotation cipher given plain text and key enter: 1\n");
    printf("For decryption with a rotation cipher given plain text and key enter: 2\n");
    printf("For encryption with a substitution cipher given plain text and key enter: 3\n");
    printf("For decryption with a substitution cipher given cipher text and key enter: 4\n");
    printf("For decryption of a previously unseen cipher text encrypted with a rotation cipher enter: 5\n");
    printf("Please write text in file (input.txt)\nNote: only capital letters will be encrypted/decrypted\n");
    printf("If there is a key, enter key in file (task_key)\n");
    
    FILE *input;
    FILE *output;
    FILE *ts;
    FILE *tk;
    
    /*Open all the required files for the task and set their modes to what is required*/
    input = fopen("input.txt", "r"); // read mode
    ts = fopen("task_selection", "r");//read mode 
    tk = fopen("task_key","r");//read mode
    output = fopen("output","w");// write mode
    
    // the code that ensures that the program is killed if the files aren't opened correctly or something goes wrong.
    if (input == NULL || output == NULL || ts==NULL|| tk==NULL)
    {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
    }
    
    char ch, the_string[100000], task_selection[50],task_key[50]; //set the strings so the text can be read from the files into these strings
    int t,task,i=0; //integers that are required throughtout the code 
    while((ch = fgetc(input)) != EOF) // read the text in input and store as a string of text under the_string
    {
      the_string[i]=ch;
      i++;
    }
    i=0;
    ch=0;
    while((ch = fgetc(ts)) != EOF) // read the number from task selection store as a string of text under task_selection
    {
      task_selection[i]=ch;
      i++;
    }
    i=0;
    /*this for statement goes through and works out what the task number is if the task number is 5 the task key isn't read because it is not needed
    it also allocates task 6 if the there isn't a number between 1 and 5 in the task selection file. Task 6 prints something went wrong to the output*/
    for(int j=0;j<50;j++)
    {
        if(task_selection[j]<53&&task_selection[j]>48)  // ie a number between 1 and 4
        {                                               // the task will need a key 
            task=task_selection[j]-48;
            while((ch = fgetc(tk)) != EOF) // read the number from task key store as a string of text under task_key
            {
                task_key[i]=ch;
                i++;
            }
            break;
        }
        else if(task_selection[j]==53)                     // ie number 5
        {                                               // no key required
            task=5;
            break;
        }
        else if(task_selection[j]==0)                   //no relevent task number supplied
        {                                               // will cause a something went wrong statement
            task=6;
            break;
        }
        else                                            //add one to j to try and find a relevant number
            j++;
    }
    char * the_output; //this is a pointer to the string that is printed to the output file
    int number; //number is the integer that will be used as the key for the rotation cipher
    switch(task)// using a switch statement because there are 5 tasks that can be perform and they can each be numbered and put under a case
    {
        case 1:
            number=get_rotation_key_from_string(task_key);// need to obtain a number between 0 and 26 from the task key file
            the_output = encrypt_me(the_string,number);// encrypts the text from the input file and stores is as the output string
            break;
        case 2:
            number=get_rotation_key_from_string(task_key);// need to obtain a number between 0 and 26 from the task key file
            the_output=decrypt_me(the_string,number);// encrypts the text from the input file and stores is as the output string
            break;        
        case 3:
            the_output=do_substitution_encrypt(the_string,task_key);//do the substitution and store it as the output
            break;
        case 4:
            the_output=do_substitution_decrypt(the_string,task_key);//do the substitution and store it as the output
            break;
        case 5:
            t=any_one_letter_word(the_string);// find if there are any one letter words and the value of that letter is returned and stored as t
                                              // where t is a number between 1 and 26 ie is there is a single letter Z on its own t will be 26
            int *Epossibles;// creates a pointer to a three number array that will be the three most likely options for the letter E
            Epossibles=unknown_rotation(the_string);//work out the three most likely options for E using the frequency that each letter occured
            int the_key;// an integer between 0 and 26 that the text will be rotated by
            int *E_last_letter;// this will be similar to Epossibles but it uses the three most common last letters
            if(t==0) // if there isn't any 1 letter words the most common last letter is used 
            {
                E_last_letter=determine_rotation_using_last_letter(the_string);// function that uses the input string to determine three most frequent 
                the_key=compare_E(Epossibles,E_last_letter);//compares the Epossibles to the Elastletter to determin what E is
                if(the_key==50)                                          //last letters
                    the_output="The string could not be decrypted";//the function returned 50 since there was no match between the Epossibles and the last letter E
            }

            else
                the_key=determine_rotation(Epossibles,t);// this uses the one letter word to determine the letter E
            if(the_key<5) //if the key(E) is less than 5 than 26 is added becasue 5 is taken away later on and the number needs to be positive
                the_key+=26; 
            the_key=the_key-5;//minus 5 to get the how much a has been rotated from a instead of how much e has been rotated from a
            the_output=decrypt_me(the_string,the_key);// decrypt the text and make it the output string
            break;        
        default://something went wrong with task selction or not using the files properly so the program doesn't try to execute 
                // it just stops so that the code can't be broken
            the_output="Something went wrong.";
    }
    int z=0;// initialise an integer which will be the placeholder for the string
    while(the_output[z]!=0) //while its not the end of the string print letter by letter to the output file
    {
        fprintf(output,"%c",the_output[z]);
        z++;
    }
    //close all the files that have been opened
    fclose(input);
    fclose(output);
    fclose(ts);
    fclose(tk);
    return 0;
}
/*=========================================================================================================================
 The get_rotation_key_from_string function gets the number required for the key if task 1 or 2 is selected. Because when a
 string of text is read in it only registers as single digit numbers ie a 17 would read as a 1 and a 7 instead of the 17.
 Since there should inj theory only be a number between 0 and 26, this function works out what that number is and sets it 
 as an integer all other numbers are considered invalid and hence 0 is return so the cipher isn't rotated.
 ========================================================================================================================*/
int get_rotation_key_from_string(char *str)
{
    for(int i=0;i<50;i++)
    {
        if(str[i]>50 &&str[i]<58) //if its a number between 3 and 9
        {
            return str[i]-48; //return that number as an integer
        }
        else if(str[i]==48) // if the first number is a 0
        {
            if(str[i+1]>47 &&str[i+1]<58)//test if the 2nd number is between 0 and 9
                return str[i+1]-48;// if true return that number
            else 
                return 0;//otherwise return 0
        }
        else if(str[i]==49)//if first number a 1
        {
            if(str[i+1]>47 &&str[i+1]<58)//test 2nd number if it between 0 and 9
                return 10+str[i+1]-48;//if so return that number
            else
                return 1;//else just return 1
        }
        else if(str[i]==50)//if first number a 2
        {
            if(str[i+1]>47&&str[i+1]<55)//test if second number is between 0 and 6
                return 20+str[i+1]-48;//if so return that number
            else
                return 2;//else just return 2
        }//if there was no number in this list found, then just go to the next number is found
        //if there is no relevant numbers found, then a 0 will be returned from the function
    }
return 0;
}
/*=========================================================================================================================
The unknown_rotation funtion takes the string from the input file and individually counts each letter then stores the
frequency of each letter in 26 number array. This array is then evaluated and the three most frequent positions are then 
returned by another array. These three poistions are the three most likely positions of the letter E since on average E is 
the most common letter in the English language hence the majority of the time it will be one of the most frequent letters 
in any paragraph or sentence.
=========================================================================================================================*/
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
The decrypt_me function uses a key and the encrypted text to decrypt the messsage using the rotational 
which is also supplied to the function as an integer between 0 and 26. Because of the rotational key, 
some of the letters will "fall off the end" so if that happens 26 is added to its ASCII number to put
 it back on the right position.  
=================================================================================================== */

char * decrypt_me(char *ar,int x)//function definition
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
   return ar; 
}
/*====================================================================================================
The encrypt_me function uses a key and the encrypted text to decrypt the messsage using the rotational 
which is also supplied to the function as an integer between 0 and 26. Because of the rotational key, 
some of the letters will "fall off the end" so if that happens 26 is subtracted to its ASCII number to put
 it back on the right position.  
=================================================================================================== */

char * encrypt_me(char *ar,int x)//function definition
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
                ar[i]=ar[i]+x;              //do the encrypting
                    if (ar[i]>90)           //if the letter is above Z in ascii 
                    {
                        ar[i]=ar[i]-26;     //-26 to get it back into a capital letter
                        break;
                    }
                    else 
                        break;
       }  
   }
   int j=0;
   while(ar[j]!=0)
   {
       printf("%c",ar[j]);
       j++;
   }
   return ar; 
}
/*========================================================================================================================
The do_sustitution_encrypt function takes a text of english language and then encrypts it using the desired key that was
entered in the the_key file it does this by finding out the place value of the letter between 0 and 25 by going the ASCII
value minus 65 and then making the new letter the encryption key letter stored under the 0 to 25 number
 =======================================================================================================================*/
char* do_substitution_encrypt(char *ab,char *cd)
{
    int j=0; 
   for(int i=0;i<1000000;i++)//for loop for the entire of the string
   {
       int task;// declareing an integer for switch case
       if (ab[i]>64&&ab[i]<91)
            task=1;             //the corresponding symbol is a capital letter
       else if(ab[i]==0)
            break;              //the corresponding symbol is a NULL character
       else 
            task=0;             //any other character
   
        switch(task) 
        {
            case 0:
                break;          //do nothing to the whitespacwe or stuff that should'nt be in the cipher
            case 1:
                
                j=ab[i]-65; //work out which letter corresponds to which place in the decryption key
             
                ab[i]=cd[j]; // change the letter of the string to the corresponding letter of the key
                break;  // break out of the switch statement 
            default:                // this should never occur but its there in case
            break;
                    
       } 
       
   } 
   return ab; 
}
/*========================================================================================================================
The do_sustitution_decrypt function works by decrypting the string using the code provided. How the function works is by 
looking at a single letter in the string that needs to be encrypted or decrypted. It then matches that letter to the same 
letter in the encryption key. Using the place value of that letter being between 1 and 26. The function then adds 65 to it
so that it is a capitalcorresponding its position and replaces it with the new letter. The string pointer is the returned 
form the function.
 =======================================================================================================================*/
char* do_substitution_decrypt(char *ab,char *cd)
{

   for(int i=0;i<1000000;i++)//for loop for the entire of the string
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
                ab[i]=j+65;       // j will be between 0 and 25 so just add 65 to convert to ascii letter
                break;
            default:                // this should never occur but its there in case
            break;
                    
       } 
       
   } 
   return ab; 
}

/*========================================================================================================================
 This function goes through the rotational cipher text that doesnt have a key and determines if there are any one letter 
 words within the cipher that needs to be decrypted. Since there are theoretically only two one letter words in the english
 lanuguage, in theory the key has been narrowed down to 1 of 2 possible combinations. The Epossibles, array can then be used
 to determine what is the most likely key.
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
 This function takes the one letter word value (between 1 and 26), and the 3 Epossibles and uses that information to determine
 what the key should be. Since A and I in ASCII are + and - 4 from E respectively it can be used to determine which E letter 
 is 4 places from the A or I. It can't reallhy go wrong because the only other letters that can be found using this method is 
 W and M which are in the bottom 13 most common letters in the English language, therefore it would be a rarity for something 
 to go wrong.
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
If in the case that the string to be decrypted does not have any one letter words in it, the plan B is to use the most common 
last letter. This function works exactly the same as the Epossibles function, except it only counts the last letter of each 
word since there is a little bit of difference between the most common last letter and the most common letter in general 
except for the letter E, in theory the next function should be able to work out what E by finding the
matching letters between the Epossibles and the last letter arrays.
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
  The compare_E function goes through the E_possibles array and the E_last letter array and tries to find a match between the 2
  arrays
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
