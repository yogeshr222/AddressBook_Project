#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;


void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContact(AddressBook *addressBook);
void populate_contact(AddressBook *addressBook);
int my_searchContact(AddressBook *addressBook);
void loadContacts(AddressBook *addressBook);

#endif
