#include <stdio.h>




const int N = 20;

typedef struct recommender{

    char f_name[20];
    char l_name[20];
    char email[20];
    char *OutsideRcmndr1;
    char *OutsideRcmndr2;

}Recommender;

typedef struct developer{

    char f_name[20];
    char l_name[20];
    char info[20];
    char *InsideRcmndr1;
    char *InsideRcmndr2;

}Developer;

int welcome();
void PrintCandidates(Developer *candidates[]);
void PrintWorkers();
void InsertCandidate();
void HireCandidate();

int main() {

    Developer *employees[N], *candidates[N];

    int option = welcome();

    switch(option){
        case 1:
            PrintCandidates(candidates);
            break;
        case 2:
            PrintWorkers();
            break;
        case 3:
            InsertCandidate();
            break;
        case 4:
            HireCandidate();
            break;
        case 5:
            printf("You have exited the program.");
            break;
    }


    return 0;
}

// Function to print welcome message and options.
int welcome(){

    int option=0;

    printf("Welcome, what do you want to do?\n");
    printf("1. Print candidates.\n");
    printf("2. Print workers.\n");
    printf("3. Insert new candidate.\n");
    printf("4. Hire candidate\n");
    printf("5. Exit\n");

    while(option<1||option>5){
        scanf("%d",&option);
        if(option>5||option<1)
            printf("Please pick an available option!");
    }
    return option;
}

void PrintCandidates(Developer *candidates[]){

    for(int i=0;i<N;i++){

    }

}
void PrintWorkers(){

}
void InsertCandidate(){

}
void HireCandidate(){

}