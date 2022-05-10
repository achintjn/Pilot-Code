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
    struct address_t *leftChild , *rightChild; }
    ;

struct address_t *head = NULL;

//This will create a new node for BST
struct address_t *newNode(int *address, char *al)
{
    
    struct address_t *temp = (struct address_t *)malloc(sizeof(struct address_t)); 
    
    //Checking if the input address is valid or not
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
        temp->octet[i] = address[i];
    }

    //adding the alias into the list node
    strcpy(temp->alias,al);

    temp->leftChild = temp->leftChild = NULL;
    
    return temp;
}

//functiom to check that whole BST consist of any duplicate address or not.
void duplicate_address(struct address_t * ptr, char *str_address, int *flag){
    char address_to_string[24];
    if (ptr != NULL)
    {
        duplicate_address(ptr->leftChild,str_address,flag);
        sprintf(address_to_string,"%d.%d.%d.%d",ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3]);
        if(strcmp(address_to_string,str_address)==0){
            printf("%s already exists\n\n", str_address);
            *flag=1;
        }
        duplicate_address(ptr->rightChild,str_address,flag);
    }

    return;
}

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
        if(strcmp(ptr1->alias,al) >0) {
            ptr1 = ptr1->leftChild;
        }else{
            ptr1 = ptr1->rightChild;
        }
    }

    //calling duplicate address function to check any duplicate address.
    ptr1 = head;
    int flag=0;
    duplicate_address(ptr1, str_address, &flag);
    if(flag)
        return NULL;


    //this will create a new node of size of our structure
    struct address_t * ptr = newNode(address, al);

    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");   
        return NULL; 
    }
    

    //if all entries are deleted, adding the node at the head.
    if(head == NULL) 
    {
        head = ptr;
        return ptr;
    }
    
    struct address_t * temp = head;

    while( 1 ) {
        
        //if alias is same
        //below if will check the duplicate alias and would not add the given entry.
        if(temp->alias != NULL){
                if(strcmp(temp->alias,al)==0){
                    printf("%s already exists\n", al);
                    return NULL;
                }
        }

        if(strcmp(temp->alias,al) >0) {
            //insert to left
            //check if temp already has a left child
            if( temp->leftChild == NULL ) {
                temp->leftChild=ptr;
                return ptr;
            }
            temp = temp->leftChild;
        }
        else {
            //insert to right
            //check if temp is already having a right child
            if( temp->rightChild == NULL ) {
                temp->rightChild=ptr;
                return ptr;
            }
            temp = temp->rightChild;
        }
    }
        
    return ptr;
}

//2)Lookup Address
void lookup_list(char* lookup) {

    ////looping to find the matching alias in left or right tree and printing its address
    struct address_t *ptr1 = head;
    while(ptr1 != NULL)
    {
        if(strcmp(ptr1->alias,lookup)==0){
            printf("Address for %s: %d.%d.%d.%d \n",lookup,ptr1->octet[0],ptr1->octet[1],ptr1->octet[2],ptr1->octet[3]);
            return;
        }
        if(strcmp(ptr1->alias,lookup) >0) {
            ptr1 = ptr1->leftChild;
        }else{
            ptr1 = ptr1->rightChild;
        }
    }

    printf("%s does not exist.\n",lookup);
    return;
}

//3)Update address
void update_address(char * lookup){
    struct address_t *ptr1 = head;
    
    //finding and placing the ptr to the matched string in the list
    while(ptr1 != NULL)
    {
        if(strcmp(ptr1->alias,lookup)==0){
            printf("Update Address for %s: %d.%d.%d.%d \n",lookup,ptr1->octet[0],ptr1->octet[1],ptr1->octet[2],ptr1->octet[3]);
            break;
        }
        if(strcmp(ptr1->alias,lookup) >0) {
            ptr1 = ptr1->leftChild;
        }else{
            ptr1 = ptr1->rightChild;
        }
    }

     //error if not matching alias found
    if(ptr1==NULL){
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

    //checking for duplicate address before updating
    sprintf(updated_str,"%d.%d.%d.%d",temp_oct[0],temp_oct[1],temp_oct[2],temp_oct[3]);
    int flag=0;
    duplicate_address(ptr_chk_duplicate_address, updated_str, &flag);
    if(flag)
        return;

    for(int i=0;i<4;i++)
    {
        ptr1->octet[i] = temp_oct[i];
    }

    return;
}

/* Given a non-empty binary search tree, return the node with the minimum key value found in that tree. */
struct address_t * minValueNode(struct address_t* node)
{
    struct address_t* current = node;
    /* loop down to find the leftmost leaf */ 
    while (current && current->leftChild != NULL)
        current = current->leftChild;
    
    return current; 
}

//4)Delete address
struct address_t* delete(struct address_t * root, char* lookup){

    // base case
    if (root == NULL) 
        return root;

    if(strcmp(root->alias,lookup) >0)
        root->leftChild = delete(root->leftChild, lookup);
    else if (strcmp(root->alias,lookup) <0)
    {
        root->rightChild = delete(root->rightChild, lookup);
    }
    else{
        // node with only one child or no child 
        if (root->leftChild == NULL)
        {
            struct address_t *temp = root->rightChild; 
            free(root);
            return temp;
        }
        else if (root->rightChild == NULL)
        {
            struct address_t *temp = root->leftChild; 
            free(root);
            return temp;
        }

        // node with two children: Get the inorder successor (smallest // in the right subtree)
        struct address_t* temp = minValueNode(root->rightChild);
        // Copy the inorder successor's content to this node 
        strcpy(root->alias,temp->alias);
        root->octet[0] = temp->octet[0];
        root->octet[1] = temp->octet[1];
        root->octet[2] = temp->octet[2];
        root->octet[3] = temp->octet[3];
        // Delete the inorder successor
        root->rightChild = delete(root->rightChild, temp->alias); 

    }
    return root;
    
}

//5)print BST using inorder traversal
void print_bst(struct address_t * ptr)
{
    //struct address_t * ptr = head;
    
    if (ptr != NULL)
    {
        print_bst(ptr->leftChild);
        printf("\n %d.%d.%d.%d %s \n",ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3],ptr->alias);
        print_bst(ptr->rightChild);
    }
}

//6)Display alias for location
void print_alias_for_location(struct address_t * ptr, int *temp_oct){

    if (ptr != NULL)
    {
        print_alias_for_location(ptr->leftChild, temp_oct);
        if(ptr->octet[0]==temp_oct[0] && ptr->octet[1]==temp_oct[1] )
            printf("\n %d.%d.%d.%d %s \n",ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3],ptr->alias);
        print_alias_for_location(ptr->rightChild, temp_oct);
    }

    return;
}

//tracing though each node to print in a file
void files(struct address_t *root, FILE *fptr){     //function to traverse through the tree to print in the file.
    if (root != NULL){
        files(root->leftChild,fptr);
        fprintf(fptr,"%d.%d.%d.%d %s\n",root->octet[0],root->octet[1],root->octet[2],root->octet[3],root->alias);
        files(root->rightChild,fptr); 
        }
}

//7) Save to file 
void save_to_file(struct address_t* ptr){
    FILE * ptr_file;
    char save_file_name[100];

    printf("Enter file name: ");
    scanf("%s",save_file_name);
    ptr_file = fopen(save_file_name,"w");

    if(ptr_file == NULL) {
        printf("Error opening destination file"); 
        return;
    }

    files(ptr, ptr_file);

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
    struct address_t *ptr1 = head;
    while(ptr1 != NULL)
        {
            if(strcmp(ptr1->alias,lookup)==0){
                printf("%s already exists\n", lookup);
                return 1;
            }
            if(strcmp(ptr1->alias,lookup) >0) {
                ptr1 = ptr1->leftChild;
            }else{
                ptr1 = ptr1->rightChild;
            }
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

    struct address_t *ptr1 = head; 
    
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
            update_address(str);
            break;
        case 4:
            printf("Enter alias: ");
            scanf("%s", str);
            // ptr1 = head;
            head = delete(head,str);
            break;
        case 5:
            ptr1 = head;
            print_bst(ptr1);
            break;
        case 6:
            ptr1 = head;
            int temp_oct[2]={0};
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
            print_alias_for_location(ptr1, temp_oct);
            break;
        case 7:
            ptr1 = head;
            save_to_file(ptr1);
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

