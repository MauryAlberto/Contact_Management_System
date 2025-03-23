#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact{//structure contatining contact information
    char name[100];
    char phone[15];
    char email[50];
    struct Contact* next;
};
//function prototypes
struct Contact* addContact(struct Contact* head);
struct Contact* searchContact();
struct Contact* deleteContact(struct Contact* head);
void displayContacts();


int main(){
    int choice;
    struct Contact* head;
    head = NULL;
    while(1){//wait for user input
        printf("---------------------------\n");
        printf("Contact Management System\n");
        printf("1. Add Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        printf("---------------------------\n");

        switch (choice) {//perform specific function according to user input
            case 1:
                head = addContact(head);//update the linked list
                break;
            case 2: 
                displayContacts(head);//traverse the linked list and display all values in each node
                break;
            case 3:
                searchContact(head);//travese the linked list search for contact information
                break;
            case 4:
                head = deleteContact(head);//update the linked list
                break;
            case 5:
                printf("Exiting Program\n");//exiting the program
                printf("---------------------------\n");
                return 0;
            default: printf("Invalid choice. Try again.\n");//invalid choice
        }
    }
    return 0;
}

struct Contact* addContact(struct Contact* head){
    struct Contact* new_Contact = (struct Contact*) malloc(sizeof(struct Contact));//allocate memory for new node
    struct Contact* temp = head;

    new_Contact->next = NULL;
    printf("Enter Contact Name (Firt_Last): ");//get user input
    scanf("%s", new_Contact->name);
    printf("Enter Email: ");
    scanf("%s", new_Contact->email);
    printf("Enter Phone Number (###-###-####): ");
    scanf("%s", new_Contact->phone);

    if(head == NULL){//check if there is no head
        head = new_Contact;
    }else{
        while(temp->next != NULL){//traverse to the last node in the linked list
            temp = temp->next;
        }
        temp->next = new_Contact;
    }
    return head;//return the original head pointer
}

void displayContacts(struct Contact* head){
    struct Contact* temp = head;//temp used for traversing the linked list
    int counter = 1;//counter used for displaying the contact number


    if(temp == NULL){//check if the linked list is empty
        printf("No Contacts To Display\n");
        return;
    }

    while(temp != NULL){//display all contacts and their info
        printf("Contact %i\n", counter);
        printf("%s\n", temp->name);
        printf("%s\n", temp->email);
        printf("%s\n", temp->phone);
        temp = temp->next;
        counter++;
    }
    
}

struct Contact* searchContact(struct Contact* head){
    char input_name[100];
    struct Contact* temp = head;
    printf("Enter a name to search: ");//wait for user input
    scanf("%s", input_name);
    while(temp != NULL){//traverse linked list contact name
        if(strcmp(temp->name, input_name) == 0){//compare if the two names are the same
            printf("Contact Found\n");
            printf("%s\n", temp->name);
            printf("%s\n", temp->email);
            printf("%s\n", temp->phone);
            return temp;
        }
        temp = temp->next;
    }
    printf("Contact Not Found\n");//display no contact found
    return NULL;
}

struct Contact* deleteContact(struct Contact* head){
    struct Contact* temp = head;
    struct Contact* contact_location;
    char input_name[100];

    printf("Enter a name to delete: ");//ask user for name to delete from the linked list
    scanf("%s", input_name);

    while(temp != NULL){
        if(strcmp(temp->name, input_name) == 0){//search for the name
            contact_location = temp;
            break;
        }
        temp = temp->next;
    }
    if(temp == NULL){
        printf("Contact Not Found\n");//display contact not found
        return head;
    }

    temp = head;

    printf("Deleting %s\n", contact_location->name);
    if(head == contact_location){//if head is deleted
        head = head->next;//move head to point to next
        free(contact_location);//free memory
        contact_location = NULL;//create null pointer
        return head;
    }else{
        while(temp->next != contact_location){//traverse the linked list to the contact location
            temp = temp->next;//go to the enxt contact
        }
        temp->next = contact_location->next;//point the next pointer to the contact after contact location
        free(contact_location);//free memory
        return head;
    }
}