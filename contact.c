#include "contact.h"
//all function definitions are here

void listContacts(AddressBook *addressBook) 
{
    int choice;
    if (addressBook->contactCount == 0) {
        printf("No contacts to display.\n");
        return;
    }

    printf("List options:\n");
    printf("1. All contacts (Dummy + New)\n");
    printf("2. Only Dummy contacts\n");
    printf("3. Only New contacts\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("------------------------------------------------------------------------------------------\n");
    printf("Sl. Name:               Phone:          Email:\n");
    printf("------------------------------------------------------------------------------------------\n");

    int start = 0, end = addressBook->contactCount;

    if (choice == 2) { 
        // Only Dummy contacts (first 10)
        end = (addressBook->contactCount >= 10) ? 10 : addressBook->contactCount;
    } else if (choice == 3) {
        // Only new contacts (after first 10)
        start = 10;
    }
    
    int sl = 1;
    for (int i = start; i < end; i++) {
        printf("%d. %-20s %-15s %-30s\n", 
               sl++, 
               addressBook->contacts[i].name, 
               addressBook->contacts[i].phone, 
               addressBook->contacts[i].email);
    }

    printf("------------------------------------------------------------------------------------------\n");
}


void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;

    FILE *fptr = fopen("contacts.txt", "r");
    if (fptr == NULL) {
        // if the File not exist → load dummy contacts only
        populate_contact(addressBook);
        printf("Dummy contacts initialized (first time).\n");

    } else {
        
        populate_contact(addressBook);
        loadContacts(addressBook);

        fclose(fptr);
        printf("Contacts loaded from file.\n");
    }

    printf("Contacts are initialized Successfully.!\n");
    listContacts(addressBook);

}


void saveContact(AddressBook *addressBook)
{
    FILE *fptr = fopen("contacts.txt", "w");
    if (fptr == NULL) {
        printf("Error: Unable to save contacts!\n\n");
        return;
    }
    
    //save only new created contacts 
    for (int i = 10; i < addressBook->contactCount; i++) {
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fptr);
    printf("Contacts saved successfully to contacts.txt\n");

    printf("-------------------------------------------------------------------------\n");
}

void createContact(AddressBook *addressBook) 
{
    if(addressBook->contactCount == MAX_CONTACTS){
        printf("AddressBook is full!\n\n");
        return;
    }

    Contact newContact;
    printf("Enter the name: ");
    scanf(" %[^\n]",newContact.name);

    //Phone number validation and duplicate check
    int valid  = 0;
    do {
        printf("Enter the Phone number: ");
        scanf("%s",newContact.phone);
        
        valid = 1;
        //check if the length is 10 and only digits
        if(strlen(newContact.phone)!=10){
            printf("Invalid Phone number. Must be exactly 10 digits\n\n");
            valid = 0;
        } else {
            for(int i=0; i<10; i++){
                if(!isdigit(newContact.phone[i])){
                    printf("Invalid Phone number. ONly digits are allowed.\n");
                    valid = 0;
                    break;
                }
            }
        } 
        //check for duplicate
        if(valid){
            for(int i = 0; i < addressBook->contactCount; i++) {
                if(strcmp(newContact.phone, addressBook->contacts[i].phone)==0){
                    printf("This phone number is already present. Please enter a new one.\n");
                    valid = 0;
                    break;
                }
            }
        }
    } while(!valid);

    // Email validation and duplicate check
    int valid_mail = 0;
    do { 
        printf("Enter the Email address: ");
        scanf("%s", newContact.email);

        valid_mail = 1;
        int atPos = -1, dotPos = -1;
        int len = strlen(newContact.email);

        for(int i=0; i<len; i++) {
            if(newContact.email[i] == '@') {
                if(atPos != -1) {    //check if multiple '@
                    valid_mail = 0;   
                    break;
                }   
                atPos = i;
            } 
            else if(newContact.email[i] == '.') {
                dotPos = i;
            }
        }

        if (atPos < 1 || dotPos < atPos + 2 || dotPos >= len-1){
            valid_mail = 0;
            printf("Invalid Email.!!! Enter a valid email address\n");
        }

        //check for duplicate mail
        if(valid_mail) {
            for(int i = 0; i < addressBook->contactCount; i++) {
                if(strcasecmp(newContact.email, addressBook->contacts[i].email)==0){
                    printf("This mail is already exists. Please enter a new one.\n");
                    valid_mail = 0;
                    break;
                }
            }
        }
    } while(!valid_mail);
    
    //save contact
    addressBook->contacts[addressBook->contactCount++] = newContact;
    printf("New Contact added successfully\n");
    printf("------------------------------------------------------------------------------------------\n");
}

void searchContact(AddressBook *addressBook)
{
    int res = my_searchContact(addressBook);
    if(res >= 0 ){
        printf("Contact found at the index %d\n",res+1);
        printf("Name: %s\n",addressBook->contacts[res].name);
        printf("Phone No: %s\n",addressBook->contacts[res].phone);
        printf("Email: %s\n",addressBook->contacts[res].email);
    }
    else
        printf("Sorry, Contact is not found.!!\n");
    printf("------------------------------------------------------------------------------------------\n");
}

void editContact(AddressBook *addressBook) 
{
    char option;
    printf("Do you really want to edit the contact (y/n)? ");
    scanf(" %c",&option);

    if(option == 'y' || option == 'Y') {
        int index = my_searchContact(addressBook);
        if (index == -1) {
            printf("Contact not found!\n");
            return;
        }

        printf("Editing contact: %s\n", addressBook->contacts[index].name);

        char buffer[50];

        // Name
        printf("Enter new name (or press enter to skip): ");
        getchar(); 
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (buffer[0] != '\0') {
            strcpy(addressBook->contacts[index].name, buffer);
        }

        // Phone
        int valid;
        do {
            printf("Enter new phone (or press enter to skip): ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            if (buffer[0] == '\0') break; // skip

            valid = 1;
            if(strlen(buffer)!=10) {
                printf("Phone must be 10 digits.\n");
                valid = 0;
            } else {
                for(int i=0;i<10;i++){
                    if(!isdigit(buffer[i])) { valid=0; break; }
                }
            }

            for(int i=0;i<addressBook->contactCount;i++){
                if(i!=index && strcmp(buffer,addressBook->contacts[i].phone)==0){
                    printf("Phone already exists!\n");
                    valid=0; break;
                }
            }
            if(valid) strcpy(addressBook->contacts[index].phone, buffer);
        } while(!valid);

        // Email
        int valid_mail;
        do {
            printf("Enter new email (or press enter to skip): ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            if (buffer[0] == '\0') break; // skip

            valid_mail = 1;
            int atPos=-1,dotPos=-1,len=strlen(buffer);
            for(int i=0;i<len;i++){
                if(buffer[i]=='@'){ if(atPos!=-1){valid_mail=0;break;} atPos=i;}
                else if(buffer[i]=='.'){dotPos=i;}
            }
            if(atPos<1 || dotPos<atPos+2 || dotPos>=len-1) valid_mail=0;

            for(int i=0;i<addressBook->contactCount;i++){
                if(i!=index && strcasecmp(buffer,addressBook->contacts[i].email)==0){
                    printf("Email already exists!\n");
                    valid_mail=0; break;
                }
            }
            if(valid_mail) strcpy(addressBook->contacts[index].email, buffer);
        } while(!valid_mail);

        printf("Contact updated successfully!\n");

    } else {
        printf("Edit cancelled.\n");
    }
    printf("-------------------------------------------------------------------------\n");
}

void deleteContact(AddressBook *addressBook) 
{
    char option;
    printf("Do you really want to delete a contact (y/n)? ");
    scanf(" %c",&option);

    if(option == 'y' || option == 'Y') {
        int index = my_searchContact(addressBook);
        if (index == -1) {
            printf("Contact not found!\n");
            return;
        }

        printf("Deleting contact: %s | %s | %s\n",
               addressBook->contacts[index].name,
               addressBook->contacts[index].phone,
               addressBook->contacts[index].email);

        for(int i=index; i<addressBook->contactCount-1; i++){
            addressBook->contacts[i] = addressBook->contacts[i+1];
        }
        addressBook->contactCount--;

        printf("Contact deleted successfully!\n");

    } else {
        printf("Delete cancelled.\n");
    }
    printf("-------------------------------------------------------------------------\n");
}



