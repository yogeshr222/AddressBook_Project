#include "contact.h"

int main()
{
    //all function calls should be inside main
    int choice;
    AddressBook s1;
    s1.contactCount = 0;
    
    do 
    {
        printf("\n1. Initailize the Contacts\n");
        printf("2. Create new Contact\n");
        printf("3. Search of the Contact\n");
        printf("4. Edit the contact\n");
        printf("5. Delete the existing Contact\n");
        printf("6. List all the existing Contacts\n");
        printf("7. Save and Exit\n\n");

        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            printf("You have entered Initialization of Contacts\n");
            initialize(&s1);
            break;
        case 2:
            printf("You have entered Creat Contact\n");
            createContact(&s1);
            break;
        case 3:
            printf("You have entered Search Contact\n");
            searchContact(&s1);
            break;
        case 4:
            printf("You have entered Edit Contact\n");
            editContact(&s1);
            break;
        case 5:
            printf("You have entered Delete Contact Option\n");
            deleteContact(&s1);
            break;
        case 6:
            printf("You have entered List Contact option\n");
            listContacts(&s1);
            break;
        case 7:
            printf("You have entered Save and Exit option\n");
            saveContact(&s1);
            break;
        default:
            printf("Invalid input.!!Enter choice between (1 and 7)\n");
            break;
        } 
        
    } while (choice != 7);
    
}
    

