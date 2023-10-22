#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

struct node2
{
    struct node2* link;
    char date[11];
    float weight;
    char disease[100];
    char medicine[50];
};

struct node1
{
    struct node1* link;
    struct node2* ptr; // Use struct node2* for ptr
    int age, patient_no;
    char patient_name[50], gender[10], appointment_date[11], appointment_time[6];
};

struct node1* root = NULL;

void searchByName(const char* name);
void calculateFee(const char date[]);
void scheduleAppointment();
void add_new_patient();
void add_patient_info();
void display(int number);
void delete_patient(int number);

int main()
{
    int ch;
    while (1)
    {
        printf("\nPress 1 to add a new patient\n");
        printf("Press 2 to add old patient's information\n");
        printf("Press 3 to delete information of a patient\n");
        printf("Press 4 to search by name\n");
        printf("Press 5 to exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            add_new_patient();
            break;

        case 2:
        {
            int number;
            printf("Enter patient number: ");
            scanf("%d", &number);
            display(number);
            add_patient_info();
            break;
        }

        case 3:
        {
            int number;
            printf("Enter number of patient to delete: ");
            scanf("%d", &number);
            delete_patient(number);
            break;
        }

        case 4:
        {
            char name[50];
            printf("Enter the patient name: ");
            scanf("%s", name);
            searchByName(name);
            break;
        }

        case 5:
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}

void searchByName(const char* name)
{
    struct node1* p = root;
    int found = 0;

    while (p != NULL)
    {
        if (strcmp(p->patient_name, name) == 0)
        {
            printf("Patient Number: %d\n", p->patient_no);
            printf("Patient Name: %s\n", p->patient_name);
            printf("Patient Gender: %s\n", p->gender);
            printf("Age of Patient: %d\n", p->age);

            struct node2* q = p->ptr;

            while (q != NULL)
            {
                printf("Visit Date: %s\n", q->date);
                printf("Weight: %.2f\n", q->weight);
                printf("Disease: %s\n", q->disease);
                printf("Medicine Recommended: %s\n", q->medicine);
                printf("\n");
                q = q->link;
            }

            found = 1;
        }
        p = p->link;
    }

    if (!found)
    {
        printf("No patient records found for the given name.\n");
    }
}

void calculateFee(const char date[])
{
    int fee = 500;
    printf("The fee for checking is: %d", fee);
    
}

void scheduleAppointment()
{
    struct node1* p = (struct node1*)malloc(sizeof(struct node1));
    struct node1* t;
    struct node2* q = (struct node2*)malloc(sizeof(struct node2));
    struct node2* q_head = NULL; // Initialize a head for the node2 list
    int count = 0;

    printf("Enter the name of the patient: ");
    scanf("%s", p->patient_name);
    printf("Enter patient's gender: ");
    scanf("%s", p->gender);
    printf("Enter patient's age: ");
    scanf("%d", &p->age);

    p->ptr = NULL;
    p->link = NULL;

    if (root == NULL)
    {
        root = p;
    }
    else
    {
        t = root;

        while (t->link != NULL)
        {
            t = t->link;
            count = count + 1;
        }
        count = count + 1;

        t->link = p;
    }

    p->patient_no = count + 1;

    time_t t1;
    time(&t1);
    struct tm* data;
    data = localtime(&t1);
    strftime(p->appointment_date, 11, "%Y-%m-%d", data);
    strftime(p->appointment_time, 6, "%H:%M", data);

    printf("\nAppointment Scheduled Successfully!\n");
    printf("Appointment Date: %s\n", p->appointment_date);
    printf("Appointment Time: %s\n", p->appointment_time);

    q->link = NULL;

    if (p->ptr == NULL)
    {
        p->ptr = q;
    }
    else
    {
        q = p->ptr;
        while (q->link != NULL)
        {
            q = q->link;
        }
        q->link = q_head;
    }
}

void add_new_patient()
{
    int ch;
    printf("\nSchedule an appointment\n");
    

    
        scheduleAppointment();
        //break;

    
}

void add_patient_info()
{
    int number, i;
    printf("Enter patient number: ");
    scanf("%d", &number);

    struct node1* p = root;
    struct node2* q;

    while (p != NULL)
    {
        if (p->patient_no == number)
        {
            q = p->ptr;

            while (q->link != NULL)
            {
                q = q->link;
            }

            struct node2* r = (struct node2*)malloc(sizeof(struct node2));

            printf("Enter the visit date: ");
            scanf("%s", r->date);
            printf("Enter the weight of the patient: ");
            scanf("%f", &r->weight);
            printf("Enter the disease diagnosed: ");
            scanf("%s", r->disease);
            printf("Enter the medicine recommended: ");
            scanf("%s", r->medicine);

            r->link = NULL;
            q->link = r;

            printf("\nPatient Information Added Successfully!\n");
            return;
        }

        p = p->link;
    }

    printf("No patient found with the given number.\n");
}


void display(int number)
{
    struct node1* p = root;

    while (p != NULL)
    {
        if (p->patient_no == number)
        {
            printf("Patient Number: %d\n", p->patient_no);
            printf("Patient Name: %s\n", p->patient_name);
            printf("Patient Gender: %s\n", p->gender);
            printf("Age of Patient: %d\n", p->age);

            struct node2* q = p->ptr;

            while (q != NULL)
            {
                printf("Visit Date: %s\n", q->date);
                printf("Weight: %.2f\n", q->weight);
                printf("Disease: %s\n", q->disease);
                printf("Medicine Recommended: %s\n", q->medicine);
                printf("The fee for checking is INR 500\n");
                q = q->link;
            }

            return;
        }

        p = p->link;
    }

    printf("No patient found with the given number.\n");
}

void delete_patient(int number)
{
    struct node1* p = root, * prev = NULL, *r;

    while (p != NULL)
    {
        if (p->patient_no == number)
        {
            if (prev == NULL)
            {
                root = p->link;
                p->link = NULL;
            }
            else
            {
                prev->link = p->link;
                p->link = NULL;
            }
            r = prev->link;
            while (r != NULL)
            {
                r->patient_no = r->patient_no - 1;
                r = r->link;
            }

            free(p);

            printf("Patient information deleted successfully!\n");
            return;
        }

        prev = p;
        p = p->link;
    }

    printf("No patient found with the given number.\n");
}


