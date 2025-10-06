#include "contact.h"

int my_searchContact(AddressBook *addressBook)
{
    int choice;
    char input[30];
    printf("Search contact by: \n");
    printf("1.Name\n");
    printf("2.Phone Number\n");
    printf("3.Email Address\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:
           printf("Enter the name: ");
           scanf(" %[^\n]",input);
           break;
        case 2:
           printf("Enter the Phone number: ");
           scanf("%s",input);
           break;
        case 3:
           printf("Enter the email: ");
           scanf("%s",input);
           break;
        default:
           printf("Invalid choice.!!\n\n");
           return -1;        
    }

    //collect all matching indexes
    int matches[20], count = 0;
    for(int i=0; i < addressBook->contactCount; i++){

        if((choice == 1 && strcasecmp(input, addressBook->contacts[i].name) == 0 ) || 
           (choice == 2 && strcmp(input, addressBook->contacts[i].phone) == 0 ) ||
           (choice == 3 && strcasecmp(input, addressBook->contacts[i].email) == 0 ) )
           {
                matches[count++] = i;
           } 
    }
    if (count == 0) {
        return -1;  //no match found
    } else if (count == 1){
        return matches[0];   //only one contact found
    } else {
        printf("\nMultiple contacts found:\n");
        for(int i = 0; i < count; i++) {
            int ind = matches[i];
            printf("%d. %s | %s | %s\n", i+1,
                    addressBook->contacts[ind].name,
                    addressBook->contacts[ind].phone,
                    addressBook->contacts[ind].email);
        }

        int sel;
        printf("Enter the number to select: ");
        scanf("%d",&sel);

        if(sel >=1 && sel <= count) {
            return matches[sel-1];
        } else {
            printf("Invalid selection.\n");
            return -1;
        }
    }
}

void loadContacts(AddressBook *addressBook) {

    FILE *fp = fopen("contacts.txt", "r");  // open in read mode
    if (fp == NULL) {
        // file doesn’t exist yet, so no contacts to load
        addressBook->contactCount = 0;
        return;
    }

    while (fscanf(fp, "%[^,],%[^,],%[^\n]\n",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3) {
        addressBook->contactCount++;
    }

    fclose(fp);
}


