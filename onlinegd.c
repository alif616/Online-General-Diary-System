#include<stdio.h>
#include<string.h>
#include<time.h>

#define MAX_COMPLAINTS 100

struct Complaint {
    int id;
    char firstName[100];
    char lastName[100];
    char idNumber[19];
    char bcNumber[19];
    char phoneNumber[12];
    char contact[50];
    char complaint[500];
    char policeStation[100];
    char dateTime[100];
};

void getCurrentDateTime(char *dateTime) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dateTime, "%02d-%02d-%d %02d:%02d:%02d",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
            tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void fileComplaint(struct Complaint complaints[], int *complaintCount) {
    if (*complaintCount >= MAX_COMPLAINTS) {
        printf("Complaint limit reached. Cannot file more complaints.\n");
        return;
    }

    struct Complaint newComplaint;
    newComplaint.id = *complaintCount + 1;

    int ageOption;
    printf("Are you less than 18 years old or greater than 18?\n");
    printf("1. Less than 18\n");
    printf("2. Greater than 18\n");
    printf("Enter your choice: ");
    scanf("%d", &ageOption);

    printf("Enter your first name: ");
    scanf(" %99[^\n]", newComplaint.firstName);

    printf("Enter your last name: ");
    scanf(" %99[^\n]", newComplaint.lastName);

    if (ageOption == 1) {
        printf("Enter your 18-digit birth certificate number: ");
        scanf(" %18s", newComplaint.bcNumber);
    } else if (ageOption == 2) {
        printf("Enter your NID number (11 digits): ");
        scanf(" %11s", newComplaint.idNumber);
    } else {
        printf("Invalid choice. Please try again.\n");
        return;
    }

    printf("Enter your 11-digit phone number: ");
    scanf(" %11s", newComplaint.phoneNumber);

    printf("Enter your contact email or alternate contact number: ");
    scanf(" %49[^\n]", newComplaint.contact);

    printf("Enter your complaint: ");
    scanf(" %499[^\n]", newComplaint.complaint);

    printf("Enter the name of your nearby police station: ");
    scanf(" %99[^\n]", newComplaint.policeStation);

    getCurrentDateTime(newComplaint.dateTime);

    complaints[(*complaintCount)++] = newComplaint;
    printf("\u2705 Complaint filed successfully! Your Complaint ID is: %d\n", newComplaint.id);
}

void viewComplaints(struct Complaint complaints[], int complaintCount) {
    if (complaintCount == 0) {
        printf("No complaints filed yet.\n");
        return;
    }

    printf("\n------ All Complaints ------\n");
    for (int i = 0; i < complaintCount; i++) {
        printf("Complaint ID  : %d\n", complaints[i].id);
        printf("Name          : %s %s\n", complaints[i].firstName, complaints[i].lastName);
        printf("ID Number     : %s\n", complaints[i].idNumber);
        printf("Phone         : %s\n", complaints[i].phoneNumber);
        printf("Contact       : %s\n", complaints[i].contact);
        printf("Complaint     : %s\n", complaints[i].complaint);
        printf("Police Station: %s\n", complaints[i].policeStation);
        printf("Date and Time : %s\n", complaints[i].dateTime);
        printf("------------------------------\n");
    }
}

void editComplaint(struct Complaint complaints[], int complaintCount) {
    if (complaintCount == 0) {
        printf("No complaints filed yet.\n");
        return;
    }

    int complaintID;
    printf("Enter the Complaint ID you want to edit: ");
    scanf("%d", &complaintID);

    for (int i = 0; i < complaintCount; i++) {
        if (complaints[i].id == complaintID) {
            struct Complaint *complaintEdit = &complaints[i];

            printf("Enter new first name: ");
            scanf(" %99[^\n]", complaintEdit->firstName);

            printf("Enter new last name: ");
            scanf(" %99[^\n]", complaintEdit->lastName);

            printf("Enter new phone number: ");
            scanf(" %11s", complaintEdit->phoneNumber);

            printf("Enter new contact email or alternate contact number: ");
            scanf(" %49[^\n]", complaintEdit->contact);

            printf("Enter new complaint: ");
            scanf(" %499[^\n]", complaintEdit->complaint);

            printf("Enter new police station: ");
            scanf(" %99[^\n]", complaintEdit->policeStation);

            getCurrentDateTime(complaintEdit->dateTime);

            printf("\u2705 Complaint ID %d updated successfully!\n", complaintID);
            return;
        }
    }
    printf("Complaint ID %d not found.\n", complaintID);
}

int main() {
    struct Complaint complaints[MAX_COMPLAINTS];
    int complaintCount = 0;
    int choice;

    while (1) {
        printf("\n====== Online General Diary (GD) System ======\n");
        printf("1. File a Complaint\n");
        printf("2. View Complaints\n");
        printf("3. Edit Complaint\n");
        printf("4. Exit\n");
        printf("=======================================\n");
        printf("Please Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fileComplaint(complaints, &complaintCount);
                break;
            case 2:
                viewComplaints(complaints, complaintCount);
                break;
            case 3:
                editComplaint(complaints, complaintCount);
                break;
            case 4:
                printf("Thank you for using Online General Diary.\n");
                return 0;
            default:
                printf("Invalid Choice. Please try again.\n");
        }
    }
}
