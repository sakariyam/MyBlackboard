#include<stdio.h> 
#include<stdlib.h>

typedef struct Program{//Vad vill hab med den här
    char *Name;
    char *Responsible;
    char *ResponsibleEmail;
} program;

typedef struct Student{
    char *Name;
    program Program;
    int Age;
} student;

typedef struct LinkedList{
    student data;
    struct LinkedList *Next; //Nästa nod i vår list struct
} linkedList;

//head behöver vara en global pekare så att vi alltid kan nå början på listan i alla våra funktioner. :^D
linkedList *head;

void PrintStudentLinkedList() {
    int numOfStudents = 0;
    linkedList *p = head;
    p = p->Next;//Börja på första noden.
    while (p != NULL) {
        numOfStudents++;
        printf("%d. Age of student: %d\n", numOfStudents, p->data.Age);//Jag kan inte få namnet att sparas rätt i det här bajs språket. printar ålder istället
        p = p->Next;
    }

    if(numOfStudents == 0){
        printf("No students in database!");
    }
}

void AddNewStudentToLinkedList(){
    char name[30];
    int age;
    printf("Please enter the student name (max 30 characters.): \n");
    scanf("%s", &name);
    printf("Please enter the student age: \n");
    scanf("%d", &age);

    //create student (Edit: Egentligen kanske man borde skapa en "student nyStudent; nyStudent.Age = age; [...]" men jag kunde inte sätta data på noden på det sättet... ;/ )
    linkedList *nodeToAddToLinkedList = malloc(sizeof(linkedList));
    nodeToAddToLinkedList->data.Age = age;
    nodeToAddToLinkedList->data.Name = name;

    //add student to end of list
    //min pointer börjar på head, och går till sista noden. 
    //Sen får jag den sista nodens Next att peka på vår nya student-nod
    linkedList *listTraversingPointer = head;
    while(listTraversingPointer->Next != NULL){
        listTraversingPointer = listTraversingPointer->Next;
    }
    listTraversingPointer->Next = nodeToAddToLinkedList;
    nodeToAddToLinkedList->Next = NULL;

    //vill vi istället att studenten ska läggas in i början
    // nodeToAddToLinkedList->Next = head->Next. Sedan 
    // head->Next = nodeToAddToLinkedList
    // Alltså, det som head pekar på nu, ska student istället peka på. Sen flytta om så att head pekar på student

    //Att lägga studenten i början är mer effektivt. Om vi lägger student i end of list, kommer vi behöva traversera alla noder till slutet innan vi lägger till något.
    //Det skalar dåligt. Ju fler studenter, desto dyrare operation. Såvida vi inte lägger till en tail pointer på slutet av listan, då kan man fylla på där bak istället.

    printf("\n\nStudent: %s, aged %d, has successfully been added", name, age);
};

//Vår meny
int InitMenu(){
    int selectedUserOption = -1;
    printf("\n\n---------------\nWelcome to MyBlackboard!\n---------------\n\nWhat do you wish to do?\n1. Add a new student\n2. View Student database\n\n---------------\n0. Exit program\n---------------\n\n");
    scanf("%d", &selectedUserOption);
    return selectedUserOption;
}

//Skriver ut en text för att fylla konsolen på ett snyggt sätt;
void PrintFunctionHeaderText(char *functionName){
    printf("|||---------------|||\n");
    printf("---------%s-------\n", functionName);
    printf("|||---------------|||\n");
}

void main()   
{  
    int selectedOption = -1;
    head = malloc(sizeof(linkedList));
    head->Next = NULL;

    while(selectedOption != 0){ 
        selectedOption = InitMenu();
        switch(selectedOption){
            case 0:
                selectedOption = 0;
                break;
            case 1:
                PrintFunctionHeaderText("Add");
                AddNewStudentToLinkedList();
                break;
            case 2:
                PrintFunctionHeaderText("View Users");
                PrintStudentLinkedList();
                break;
            default:
                printf("---------------");
                printf("\nSorry that option was not recognized: %d", selectedOption);
                break;
        }
    }
    printf("------------------------------\nProgram exited!");
    return;
}  
