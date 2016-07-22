

/*
Mohamed Mayow
Extra credit C
USER INPUT CANT TAKE SPACES
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct new_Event {
    char* title;
    int unique_ID;
    int year;
    int month;
    int day;

    //uses a double linked list
    struct new_Event* next;
    struct new_Event* prev;

} new_Event;

void insert(new_Event *current, char title[], int unique_ID, int day, int month, int year);
void print(new_Event *current);
void deleteNode(new_Event *current, int intID);
void printToScreen(new_Event *current);


int main(){

    new_Event *e=(new_Event*)malloc(sizeof(new_Event));

    e->next=NULL;
    e->prev=NULL;

    //variable for the title name
    char title[55];

    //int variables for the date
    int year;
    int month;
    int day;

    //int variable
    int ID;
    int num=0;
    FILE * fPointer;
    //imports the file in read mode
    fPointer = fopen("calender.txt", "r");


    if( fPointer != NULL ){

        //scans in the currents events in the calender until it reaches the end
        while(!feof(fPointer)){

                fscanf(fPointer, "%s\n", title);
                fscanf(fPointer, "%d\n", &ID);
                fscanf(fPointer, "%d\n", &day);
                fscanf(fPointer, "%d\n", &month);
                fscanf(fPointer, "%d", &year);
                insert(e, title, ID, day, month, year);
                }
    }
    else{
            num++;
        }

     if(num==1){
        printf("BRAND NEW Event planner.");
        printf("\nTo create a new event (enter n, NO SPACES ) or exit program (enter e): \n");
     }
     else{
        printf("Create a new event (enter n, NO SPACES ), delete an event(enter d), display all events(enter a) or exit(enter e): \n");
     }

    char decision;
    scanf("%c", &decision);

if (decision == 'n'){

repeat:

    srand (time(NULL));
    int random1= ( rand()%999999999999);
    int random= ( rand()%random1);
    ID = ( rand()%random);
    e->unique_ID=ID;

    printf("Whats the title of the event:\n ");
    //scanf("%s", title);


    scanf("%s", title);

    e->title=title;

    //inputs the date of the code
    printf("Create a date. Using format mm dd yyyy: ");

    scanf("%d %d %d", &month, &day, &year);

    //makes sure that there is a valid month input
    if(month != 1 && month != 2 && month != 3 && month != 4 && month != 5 && month != 6 && month != 7 && month != 8 && month != 9 && month != 10 && month != 11 && month != 12  ){

        printf("INVALID MONTH DATE. Please Enter Again. Create a date. Using format mm dd yyyy: ");
        scanf("%d %d %d", &month, &day, &year);

        while(month != 1 && month != 2 && month != 3 && month != 4 && month != 5 && month != 6 && month != 7 && month != 8 && month != 9 && month != 10 && month != 11 && month != 12  ){

            printf("INVALID MONTH DATE. Please Enter Again. Create a date. Using format mm dd yyyy: ");
            scanf("%d %d %d", &month, &day, &year);
            }
    }
    //makes sure that there is a valid day input
    if(day >31){
        printf("INVALID DAY DATE. Please Enter Again. Create a date. Using format mm dd yyyy: ");
        scanf("%d %d %d", &month, &day, &year);

        while(day>31){
            printf("INVALID DAY DATE. Please Enter Again. Create a date. Using format mm dd yyyy: ");
            scanf("%d %d %d", &month, &day, &year);
        }
    }

    //makes sure that there is a valid year input
    if(year < 2016){
        printf("INVALID YEAR DATE. Please Enter Again. Create a date. Using format mm dd yyyy: ");
        scanf("%d %d %d", &month, &day, &year);

        while(year < 2016){
            printf("INVALID YEAR DATE. Please Enter Again. Create a date. Using format mm dd yyyy: ");
            scanf("%d %d %d", &month, &day, &year);

        }
    }

    //saves the month, day and year for that particular date
    e->month=month;
    e->day=day;
    e->year=year;

    //creates a new node with the following parameters
    insert(e, title, ID, day, month, year);
        goto screen;


}

else if (decision == 'd'){

    del:
    printf("What is the UniqueID of the event you want to delete? ");
    int deleteID;
    scanf(" %d", &deleteID);

   deleteNode(e, deleteID);

}

else if (decision == 'a'|| decision == 'A'){
        printToScreen(e->next);
}

else if (decision == 'e'){

    leave:
    stop:
    printf("\nEXIT\n");
    exit(0);
}

   NEW:
    printf("Create a new event (enter n, NO SPACES) , delete an event (enter d), display all events (enter a) or exit(enter e): \n");

   //Go to statements used, instead of a while loop. Performs the same task as a while loop
    char choice;
    scanf(" %c", &choice);

    if (choice == 'n'){
    goto repeat;
    }
    else if (choice == 'd'){
    goto del;
    }
    else if (choice == 'a'){
    goto screen;
    }
    else if (choice == 'e'){
    goto leave;
    }
    else if (choice != 'n'&& decision != 'd'&& decision != 'a' &&decision != 'e'){
    goto stop;
    }

screen:
print(e->next);

goto NEW;

return 0;
}

//function used to add new events to the double linked list
void insert(new_Event *current,char title[], int unique_ID, int day, int month, int year){

    while(current->next != NULL) {
            current = current->next;
        }

        current->next = (new_Event *)malloc(sizeof(new_Event));
        (current->next)->prev = current;
        current = current->next;

        current->unique_ID=unique_ID;
        current->title=strdup(title);
        current->month=month;
        current->day=day;
        current->year=year;
        current->next = NULL;
}

//function used to delete an event off the double linked list
void deleteNode(new_Event *current, int intID){

    while (current->next != NULL && (current->next)->unique_ID != intID) {
            current = current->next;
        }
    new_Event *temp = current->next;
    if(temp->next == NULL) {
            current->next = NULL;
        } else {
            current->next = temp->next;
            (current->next)->prev = temp->prev;
        }
        temp->prev = current;
}

void print(new_Event *current) {

    FILE * fPointer2;
    fPointer2 = fopen("calender.txt", "w");

    while(current != NULL) {

        fprintf(fPointer2,"\n\n%s",current->title);
        fprintf(fPointer2,"\n%d", current->unique_ID);
        fprintf(fPointer2,"\n%d",current->day);
        fprintf(fPointer2,"\n%d",current->month);
        fprintf(fPointer2,"\n%d",current->year);

        current = current->next;
    }

    //closes the file
    fclose(fPointer2);

    char title[200];
    //int variables for the date
    int year;
    int month;
    int day;
    //int variable
    int ID;

    printf("\n");

        FILE * fPointer5;

    fPointer5 = fopen("calender.txt", "r");

    while(!feof(fPointer2)){

            fscanf(fPointer5, "%s\n", title);
            fscanf(fPointer5, "%d\n", &ID);
            fscanf(fPointer5, "%d\n", &day);
            fscanf(fPointer5, "%d\n", &month);
            fscanf(fPointer5, "%d", &year);

            printf("Event name: %s\n", title);
            printf("ID: %d\n",ID);
            printf("DAY: %d\n",day);
            printf("MONTH: %d\n",month);
            printf("YEAR: %d\n\n",year);
    }

        fclose(fPointer2);

}


//prints all the events to the screen
void printToScreen(new_Event *current) {


    char title[200];
    //int variables for the date
    int year;
    int month;
    int day;
    //int variable
    int ID;

    printf("\n");

    FILE * fPointer2;
    fPointer2 = fopen("calender.txt", "r");

    //loops through entire file, until it reaches the end
    while(!feof(fPointer2)){

            fscanf(fPointer2, "%s\n", title);
            fscanf(fPointer2, "%d\n", &ID);
            fscanf(fPointer2, "%d\n", &day);
            fscanf(fPointer2, "%d\n", &month);
            fscanf(fPointer2, "%d", &year);

            printf("Event name: %s\n", title);
            printf("ID: %d\n",ID);
            printf("DAY: %d\n",day);
            printf("MONTH: %d\n",month);
            printf("YEAR: %d\n\n",year);
    }
}

