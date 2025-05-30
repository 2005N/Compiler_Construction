%{
#include<stdio.h>
int vowels=0;
int cons=0;
%}
vowels [aeiouAEIOU]
alphabets [a-zA-Z]
newline \n
%%
{vowels} {vowels++; }
{alphabets} {cons++;}
{newline} {return 0;}
%%

int main(){
printf("Enter the string:");
yylex();
printf("Output:\n");
printf("No of vowels=%d \nNo of consonants=%d\n",vowels,cons);
return 0;
}

int yywrap(){
    return 1;
}