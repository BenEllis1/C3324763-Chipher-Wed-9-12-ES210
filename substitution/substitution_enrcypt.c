#include <stdio.h>
void do_encryption(char*,char*);
int main()
{
    
    char encryption_key[26]="QWERTYUIOPASDFGHJKLZXCVBNM";
    char str[50]="ABCDEFGH";
    do_encryption(str,encryption_key);
    return 0;
}
void do_encryption(char *ab,char *cd)
{
    for(int i=0;i<50;i++)
    {
        int x;
        x=ab[i]-65;
        ab[i]=cd[x];
    
    }
    puts(ab);
}