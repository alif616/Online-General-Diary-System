#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_COMPLAINTS 100

struct Complaint {
    int id;
    char firstName[50];
    char lastName[50];
    char nidNumber[11];      // 11 digits + null
    char phoneNumber[12];    // 11 digits (no +880)
    char contact[50];        // Email or alternate contact
    char complaint[500];
};

int isValidName(const char *name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i])) 
            return 0;
    }
    return 1;
}

int isValidNID(const char *nid) {
    if (strlen(nid) != 11) 
        return 0;
    for (int i = 0; i < 11; i++) {
        if (!isdigit(nid[i])) 
            return 0;
    }
    return 1;
}

int isValidPhone(const char *phone) {
    if (strlen(phone) != 11) 
        return 0;
    for (int i = 0; i < 11; i++) {
        if (!isdigit(phone[i])) 
            return 0;
    }
    return 1;
}

int main() {
    struct Complaint complaints[MAX_COMPLAINTS];
    int complaintCount = 0;
    int choice;

    // Step 2: Main menu
    while (1) {
        printf("\n====== Online General Diary (GD) ======\n");
        printf("1. File a Complaint\n");
        printf("2. View Complaints\n");
        printf("3. Exit\n");
        printf("=======================================\n");
        printf("Please Enter Your Choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        if (choice == 1) {
            if (complaintCount >= MAX_COMPLAINTS) {
                printf("Complaint limit reached. Cannot file more complaints.\n");
                continue;
            }

            struct Complaint newComplaint;
            newComplaint.id = complaintCount + 1;

            // Print the message only once before name input
            printf("⚠️ Your name should match the one on your NID card.\n");

            // First name
            while (1) {
                printf("Enter your first name (only letters): ");
                scanf(" %[^\n]s", newComplaint.firstName);

                if (isValidName(newComplaint.firstName)) 
                    break;
                else 
                    printf("❌ Invalid first name. Use only letters.\n");
            }

            // Last name
            while (1) {
                printf("Enter your last name (only letters): ");
                scanf(" %[^\n]s", newComplaint.lastName);
                if (isValidName(newComplaint.lastName)) 
                    break;
                else 
                    printf("❌ Invalid last name. Use only letters.\n");
            }

            // NID number
            while (1) {
                printf("Enter your NID number (11 digits): ");
                scanf(" %[^\n]s", newComplaint.nidNumber);
                if (isValidNID(newComplaint.nidNumber)) break;
                else printf("❌ Invalid NID. Must be 11 digits.\n");
            }

            // Phone number (now just 11 digits)
            char rawPhone[12]; // 11 digits + null
            while (1) {
                printf("Enter your 11-digit phone number: ");
                scanf(" %[^\n]s", rawPhone);

                if (isValidPhone(rawPhone)) {
                    strcpy(newComplaint.phoneNumber, rawPhone); // Directly store the 11-digit phone number
                    break;
                } else {
                    printf("❌ Invalid phone number. Must be exactly 11 digits.\n");
                }
            }

            // Contact (email or alternate contact)
            printf("Enter your contact email or alternate contact number: ");
            scanf(" %[^\n]s", newComplaint.contact);

            // Complaint
            printf("Enter your complaint: ");
            scanf(" %[^\n]s", newComplaint.complaint);

            complaints[complaintCount++] = newComplaint;
            printf("✅ Complaint filed successfully! Your Complaint ID is: %d\n", newComplaint.id);

        } else if (choice == 2) {
            if (complaintCount == 0) {
                printf("No complaints filed yet.\n");
                continue;
            }

            printf("\n------ All Complaints ------\n");
            for (int i = 0; i < complaintCount; i++) {
                printf("Complaint ID: %d\n", complaints[i].id);
                printf("Name        : %s %s\n", complaints[i].firstName, complaints[i].lastName);
                printf("NID Number  : %s\n", complaints[i].nidNumber);
                printf("Phone       : %s\n", complaints[i].phoneNumber);
                printf("Contact     : %s\n", complaints[i].contact);
                printf("Complaint   : %s\n", complaints[i].complaint);
                printf("------------------------------\n");
            }

        } else if (choice == 3) {
            printf("👋 Thank you for using Online General Diary.\n");
            break;
        } else {
            printf("❌ Invalid Choice. Please try again.\n");
        }
    }

    return 0;
}
