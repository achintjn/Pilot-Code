/*
Name :          ACHINT JAIN
G-Number :      G01324710
*/


#include <stdio.h>
#include <string.h>

int check_duplicate(char *, int );

int illegalChar(char *);

void sortAsc();

void sortDesc();

void printarray();

char array_string[10][30];

int reEnter;

int main()
{
char dynamic_string[100];
int i=0;

//this while loop will run untill all 10 strings are entered
while(i<10)
{
reEnter=1;  //boolean check variable
printf("Enter a String: ");
fgets(dynamic_string,sizeof(dynamic_string),stdin);

    //this while loop will run until a valid string is entered on the screen
    //individual valid checks are done inside this loop
    while(reEnter)
    {
        reEnter = 0; 

        //re-prmpting if the string is more than 25 character
        while (strlen(dynamic_string)>26)
        {
            reEnter = 1;
            printf("Error: Entered String is greater than 25, Enter again: ");
            fgets(dynamic_string,sizeof(dynamic_string),stdin);
        }

        //re-prompting if the string is duplicate
        while(check_duplicate(dynamic_string, i))
        {
            reEnter = 1;
            printf("Error: Entered String is already been entered, type a different string: ");
            fgets(dynamic_string,sizeof(dynamic_string),stdin);
        }

        //re-prompting if the string is a null string
        while(dynamic_string[0] == '\n')
        {
            reEnter = 1;
            printf("Error: Cannot be a null character: ");
            fgets(dynamic_string,sizeof(dynamic_string),stdin);
        }

        //re-prompting if the string has following illegal characters - ’!’, ’@’, ’#’, ’$’, ‘%’, ‘^’, ’(’, or ’)’
        while(illegalChar(dynamic_string))
        {
            reEnter = 1;
            printf("Error: Entered String is an Illegal Character type a different string: ");
            fgets(dynamic_string,sizeof(dynamic_string),stdin);
        }

    }

strcpy(array_string[i],dynamic_string);  //once a valid string is entered we will copy it in our 2-D array of characters.
i++;

}

char ch[25];
printf("Print character strings in 'A'scending or 'D'escending order: ");
scanf(" %s", ch);
int loop = 1;

//this while loop is to check if the entered character is other than A or D
while(loop)
{
    if(strcmp(ch,"A") == 0 || strcmp(ch,"D") == 0)
    {
        break;
    }
    else
    {
        printf("Please Enter a Valid character 'A' or 'D' : ");
        scanf(" %s", ch);
    }
    
}

//switch statement to print the desired sorting as entered on screen
switch (ch[0])
{
case 'A':
    sortAsc();
    printf("Asceding Order: \n\n");
    break;
case 'D':
    sortDesc();
    printf("Desceding Order: \n\n");
    break;

default:
    printf("invalid character");
}

printarray();  //printing out the 2-D array


//prints and labels the character string with the lowest ascii value and that with the highest ascii value
//as determined by strcmp()
if(ch[0] == 'A')
    printf("String with lowest ascii value: %s\n\nString with highest ascii value: %s\n",array_string[0],array_string[9]);

if(ch[0] == 'D')
    printf("String with lowest ascii value: %s\n\nString with highest ascii value: %s\n",array_string[9],array_string[0]);

}

//function to identify if the string is duplicate
int check_duplicate(char *dynamic_string2, int i2)
{
    int flag = 0;
    for(int j=0; j<i2;j++)
    {
        if(strcmp(array_string[j], dynamic_string2)==0)
        {
            flag = 1;
            break;
        }
    }

    return flag;

}

//function to identify if the string has any illegal character from following - ’!’, ’@’, ’#’, ’$’, ‘%’, ‘^’, ’(’, or ’)’
int illegalChar(char *dynamic_string3 )
{
    int flag = 0;
    for(int i=0; i<strlen(dynamic_string3);i++)
    {
        if((dynamic_string3[i]=='!') || (dynamic_string3[i]=='@') || (dynamic_string3[i]=='#') || (dynamic_string3[i]=='$') || (dynamic_string3[i]=='%') || (dynamic_string3[i]=='^') || (dynamic_string3[i]=='(') || (dynamic_string3[i]==')'))
        {
            flag=1;
            break;
        }
    }

    return flag;
}

//simple function to print all string in 2-D array of characters
void printarray()
{
    for(int i=0; i<10; i++)
    {
        printf("%s\n", array_string[i]);
    }
        
}

//below function sorts the array in decending order using strcmp
void sortDesc()
{
    for(int i=0;i<10; i++)
    {
        for(int j=0;j<10-i;j++)
        {
            int ret = strcmp(array_string[j],array_string[j+1]);
            if(ret<0)
            {
                char temp[27];

                strcpy(temp,array_string[j]);
                strcpy(array_string[j],array_string[j+1]);
                strcpy(array_string[j+1], temp);
                
            }
        }
    }    
}

//function to sort the array in ascending order using strcmp()
void sortAsc()
{
    for(int i=0;i<10; i++)
    {
        for(int j=0;j<10-i-1;j++)
        {
            int ret = strcmp(array_string[j],array_string[j+1]);
            if(ret>0)
            {
                char temp[27];

                strcpy(temp,array_string[j]);
                strcpy(array_string[j],array_string[j+1]);
                strcpy(array_string[j+1], temp);
                
            }
        }
    }    
}

