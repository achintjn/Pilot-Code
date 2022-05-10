/*
Name :          ACHINT JAIN
G-Number :      G01324710
*/


#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>

struct address_t {
    int octet[4];
    char alias[11];        
    struct address_t *next; }
    ;

struct address_t *head = NULL;

//1) Add address function
struct address_t* insert(int *address, char *al, char *str_address)
{
    struct address_t *ptr1 = head;
    char address_to_string[24];
    struct address_t *curr = head;

    //below while loop will check the duplicate alias and would not add the given entry.
    while(ptr1 != NULL)
    {
        if(strcmp(ptr1->alias,al)==0){
            printf("%s already exists\n", al);
            return NULL;
        }
        ptr1 = ptr1->next; 
    }

    //similar while loop will check the duplicate address and would not add the given entry.
    ptr1 = head;
    while(ptr1 != NULL){
        sprintf(address_to_string,"%d.%d.%d.%d",ptr1->octet[0],ptr1->octet[1],ptr1->octet[2],ptr1->octet[3]);
        if(strcmp(address_to_string,str_address)==0){
            printf("%s already exists\n\n", str_address);
            return NULL;
        }
        ptr1 = ptr1->next; 
    }


    //this will create a new node of size of our structure
    struct address_t * ptr = (struct address_t*)malloc(sizeof(struct address_t));

    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");   
        return NULL; 
    }
    
    //checking addes address has any illegal entry
    for(int i=0;i<4;i++)
    {
        if(address[i]<0 || address[i]>255)
        {
            printf("Illegal Entry\n");
            return NULL;
        }
    }

    //inserting each array address with inserted address
    for(int i=0;i<4;i++)
    {
        ptr->octet[i] = address[i];
    }

    //adding the alias into the list node
    strcpy(ptr->alias,al);
    ptr->next = NULL;

    //if all entries are deleted, adding the node at the head.
    if(head == NULL) 
    {
        head = ptr;
        return ptr;
    }
    
    //adding all linked list at last positiion.
    while(curr->next!=NULL){
        curr =curr->next;    
    }
    curr->next = ptr; 
    curr = ptr;
        
    return ptr;
}


//2) Look up address
void lookup_list(char* lookup) 
{
    struct address_t *ptr = head;
    
    //looping to find the matching alias and printing its address
    while(ptr != NULL)
    {
        if(strcmp(ptr->alias,lookup)==0){
            printf("Address for %s: %d.%d.%d.%d \n",lookup,ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3]);
            return;
        }
        ptr = ptr->next; 
    }

    //message if alias in not matched
    printf("%s does not exist.\n",lookup);
    return; 
}

//3) Update address
void update_list(char* lookup)
{
    struct address_t *ptr = head;
    char address_to_string[24];

    //finding and placing the ptr to the matched string in the list
    while(ptr != NULL)
    {
        if(strcmp(ptr->alias,lookup)==0){
            printf("Update address for %s : %d.%d.%d.%d \n",lookup,ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3]);
            break;
        }
        ptr = ptr->next; 
    }
    
    //error if not matching alias found
    if(ptr==NULL){
        printf("Error: No matching alias found.\n");
        return;
    }
    
    struct address_t *ptr_chk_duplicate_address = head;
    char updated_str[24];
    int temp_oct[4]={0};
    int i=0;

    //promting for user to enter all 4 address location for an IP address with illegal entry check.
    while(i<4){
        printf("Enter location value # %d(0-255): ",i+1);
        scanf("%d",temp_oct+i);
        if(temp_oct[i]<0 || temp_oct[i]>255)
            printf("Illegal entry\n");
        else
            i++;
    }

    //checking the address entered is already present or not.
    sprintf(updated_str,"%d.%d.%d.%d",temp_oct[0],temp_oct[1],temp_oct[2],temp_oct[3]);
    while(ptr_chk_duplicate_address != NULL)
    {
        sprintf(address_to_string,"%d.%d.%d.%d",ptr_chk_duplicate_address->octet[0],ptr_chk_duplicate_address->octet[1],ptr_chk_duplicate_address->octet[2],ptr_chk_duplicate_address->octet[3]);
        if(strcmp(address_to_string,updated_str)==0){
            printf("%s already exists\n",address_to_string);
            return;
        }
        ptr_chk_duplicate_address = ptr_chk_duplicate_address->next; 
    }

    //updating the existing address with new values
    for(int i=0;i<4;i++)
    {
        ptr->octet[i] = temp_oct[i];
    }
    return;

}

//4) Delete address
void delete_list(char* lookup)
{
    struct address_t *ptr = head;
    struct address_t *prev = head;

    //looking for the matching alias and its address
    while(ptr != NULL)
    {
        if(strcmp(ptr->alias,lookup)==0){
            printf("The address is : %d.%d.%d.%d ",ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3]);
            break;
        }
        prev = ptr;         //using prev pointer to preserve the pointer at previous node
        ptr = ptr->next; 
    }

    //error when the matching alias is not found.
    if(ptr==NULL){
        printf("%s does not exist\n",lookup);
        return;
    }

    char ch[5];
    printf("delete %s %d.%d.%d.%d? (y/n) \n",lookup,ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3]);
    scanf("%s", ch);
    int loop = 1;

    //this while loop is to check if the entered character is other than y or n
    while(loop)
    {
        if(strcmp(ch,"y") == 0 || strcmp(ch,"n") == 0)
        {
            break;
        }
        else
        {
            printf("Please Enter a Valid character 'Y' or 'N' : ");
            scanf(" %s", ch);
        }
        
    }

    //using switch case to determine if the entered value is y or n and proceding accordingly
    struct address_t *del=head;

    switch (ch[0])
    {
    case 'y':
        if( head == NULL ) {
            return;
        }
        
        if(strcmp(head->alias,lookup)==0) {
            head = head->next;
            del->next=NULL;
            return;
        }
        else{
                del = ptr->next;   
                ptr->next=NULL;
                prev->next=del;
            }
        break;
    case 'n':
        return;

    default:
        printf("invalid character");
    }
}

//5) Display list
void print_list(void) 
{
    struct address_t *ptr = head;
    int count=0;

    //diplays all the node entry in the list
    while(ptr != NULL)
    {
        printf("\n %d.%d.%d.%d %s \n",ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3],ptr->alias);
        count++;
        ptr = ptr->next; 
    }
    printf("Total node count: %d\n", count);
    return; 
}

//6) Display alias for location
void print_alias_for_location(void) 
{
    struct address_t *ptr = head;
    int temp_oct[2]={0};
    int no_match=1;
    int i=0;

    //prompting user to enter the values and checking the range for them
    while(i<2){
        printf("Enter location value # %d(0-255): ",i+1);
        scanf("%d",temp_oct+i);
        if(temp_oct[i]<0 || temp_oct[i]>255)
            printf("Illegal entry\n");
        else
            i++;
    }

    //searching the list for all possible matching of that entered address
    int oct[4]={0};
    while(ptr != NULL)
    {
        if(ptr->octet[0]==temp_oct[0] && ptr->octet[1]==temp_oct[1] ){
            printf("\n %d.%d.%d.%d %s \n",ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3],ptr->alias);
            no_match=0;
        }
        ptr = ptr->next; 
    }

    if(no_match)
        printf("doesn not exist\n");
    
    return; 
}


//7) Save to file 
void save_to_file(){
    struct address_t *ptr = head;
    FILE * ptr_file;
    char save_file_name[100];

    printf("Enter file name: ");
    scanf("%s",save_file_name);
    ptr_file = fopen(save_file_name,"w");

    if(ptr_file == NULL) {
        printf("Error opening destination file"); 
        return;
    }

    while(ptr!=NULL){
        fprintf(ptr_file,"%d.%d.%d.%d %s\n",ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3],ptr->alias);
        ptr = ptr->next;
    }

    fclose(ptr_file);
    printf("File saved.\n");
}

//8)Quit
void quit(){
    printf("Good Bye!\n");
}

//checking if the alias is present or not
int check_duplicate_alias(char* lookup) 
{
    struct address_t *ptr = head;
    
    //looping to find the matching alias and printing error
    while(ptr != NULL)
    {
        if(strcmp(ptr->alias,lookup)==0){
            printf("%s already exist\n",lookup);
            return 1;
        }
        ptr = ptr->next;
    }
    return 0; 
}

int main(void){


    FILE *ll_ptr;
    char buf[50];

    char alias1[11];
    int oct[4] ={0};
    char str[24];

    ll_ptr = fopen("CS531_Inet.txt","r");
    if(ll_ptr == NULL)
    {
        perror("Error opening CS531_Inet.txt");
        return(-1); 
    }

    int no_end_of_file=1;

    //below while loop will go over the file and insert each line into the linked list
    while(no_end_of_file){
        no_end_of_file=0;
        if(fgets(buf, sizeof(buf), ll_ptr) !=NULL)
        {
            no_end_of_file=1;
            sscanf(buf,"%s %s",str,alias1);
            sscanf(str,"%d.%d.%d.%d",oct,oct+1,oct+2,oct+3) ;
            insert(oct,alias1, str);
        }
        
    }

    fclose(ll_ptr);
    
    
    //below switch case is used to display the menu lis
    //and it will repromt after every option chosen
    //each switch case calls its aprropriate function.
    int a;
    int flag=1;
    while(flag){
        printf("1) Add address\n2) Look up address\n3) Update address \n4) Delete address\n5) Display list\n6) Display aliases for location\n7) Save to file \n8) Quit\n");
        printf("Enter option: ");
        scanf("%d",&a);
        switch (a)
        {
        case 1:
            printf("enter the Alias:");
            scanf("%s", alias1);
            if(check_duplicate_alias(alias1))
                break;
            printf("enter IPv4 address:");
            scanf("%s", str);
            sscanf(str,"%d.%d.%d.%d",oct,oct+1,oct+2,oct+3) ;
            insert(oct,alias1, str);
            break;
        case 2:
            printf("Enter alias: ");
            scanf("%s", str);
            lookup_list(str);
            break;
        case 3:
            printf("Enter alias to update the address:");
            scanf("%s", str);
            update_list(str);
            break;
        case 4:
            printf("Enter alias: ");
            scanf("%s", str);
            delete_list(str);
            break;
        case 5:
            print_list();
            break;
        case 6:
            print_alias_for_location();
            break;
        case 7:
            save_to_file();
            break;
        case 8:
            quit();
            flag=0;
            break;
        default:
            printf("Options from 1-8\n");
        }
    }

    
    return 0;
}

