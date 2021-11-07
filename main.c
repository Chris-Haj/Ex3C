#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int N = 20;

//At the start of the program we have 0 candidates and 0 developers, each time a candidate is inserted, numOfCans increments by 1
//and each time a developer is inserted, numOfDevs is incremented by 1.
int numOfCans = 0, numOfDevs = 0;

typedef struct recommender {

    char fname[20];
    char lname[20];
    char email[20];

} Recommender;

typedef struct developer {

    char fname[20];
    char lname[20];
    char degree[20];
    struct developer *d1, *d2;
    struct recommender *r1, *r2;

} Developer;


int welcome();

void PrintCandidates(Developer *candidates[]);

void PrintEmployees(Developer *employees[]);

void InsertCandidate(Developer *candidates[], Developer *employees[]);

void HireCandidate(Developer *candidates[],Developer *employees[]);

int main() {

    Developer *employees[N], *candidates[N];

    int exit = 0;

/*
 * A loop to keep listing the welcome options until the user chooses the exit option
 * and by using the switch statement I can call the needed function according to what option (case) is entered.
 * Once the exit option is chosen all allocated memory is freed.
  */
    while (!exit) {
        int option = welcome();

        switch (option) {
            case 1:
                PrintCandidates(candidates);
                break;
            case 2:
                PrintEmployees(employees);
                break;
            case 3:
                InsertCandidate(candidates, employees);
                break;
            case 4:
                HireCandidate(candidates,employees);
                break;
            case 5:
                printf("You have exited the program.");
                for (int i = 0; i < numOfCans; i++)
                    free(candidates[i]);
                exit = 1;
                break;
        }
    }

    return 0;
}

// Function to print welcome message and options.
int welcome() {

    int option = 0;

    printf("Welcome, what do you want to do?\n");
    printf("1. Print candidates.\n");
    printf("2. Print workers.\n");
    printf("3. Insert new candidate.\n");
    printf("4. Hire candidate\n");
    printf("5. Exit\n");

    //A while loop that keeps going until the user entered an option from the menu.

    while (1 > option || option > 5) {

        scanf("%d", &option);

        if (option > 5 || option < 1)
            printf("Please pick an available option!\n");
    }
    return option;
}

void PrintCandidates(Developer *candidates[]) {

    if (numOfCans == 0) {
        printf("There are currently 0 candidates.\n");
        return;
    }

    for (int i = 0; i < numOfCans; i++) {
        printf("Candidate %d:\n\tFirst name: %s \n\tLast name: %s \n\tDegree: %s\n\n", i + 1, candidates[i]->fname, candidates[i]->lname, candidates[i]->degree);
    }

    printf("\n");
}

void PrintEmployees(Developer *employees[]) {

    if (numOfDevs == 0) {
        printf("There are currently 0 employees.\n");
        return;
    }

    for (int i = 0; i < numOfDevs; i++) {
        printf("Employee %d: \n\tFirst name: %s \n\tLast name: %s \n\t", i + 1, employees[i]->fname, employees[i]->lname);
    }
    printf("\n");
}

void InsertCandidate(Developer *candidates[], Developer *employees[]) {

    if (numOfCans > 20) {
        printf("Candidates team is full!\n");
        return;
    }
/*
 * The details array is used to store the full name of the new candidate and their degree.
 * And we also allocate a new memory block for the new candidate.
 * */
    char details[3][20];
    candidates[numOfCans] = (Developer *) calloc(1, sizeof(Developer));

    printf("Please enter a first name, last name of the person and their degree\n");
    for (int i = 0; i < 3; i++) {
        scanf("%s", details[i]);
    }

    strcpy(candidates[numOfCans]->fname, details[0]);
    strcpy(candidates[numOfCans]->lname, details[1]);
    strcpy(candidates[numOfCans]->degree, details[2]);

    printf("Does this candidate have any recommenders from inside the company?\nAnswer with yes/no\n");
    char answer[4] = "";
    char recommender[2][20];
    int found = 0;

    while (1) {

        scanf("%s", answer);

        if (strcmp(answer, "yes") == 0 || strcmp(answer, "Yes") == 0) {
            printf("Please enter their recommenders first and last name.\n");

            for (int i = 0; i < 2; i++)
                scanf("%s", recommender[i]);

            for (int i = 0; i < numOfDevs; i++) {
                if (strcmp(employees[i]->fname, recommender[0]) == 0 && strcmp(employees[i]->lname, recommender[1]) == 0) {
                    candidates[numOfCans]->d2 = employees[i];
                    found = 1;
                    break;
                }
                if (i == numOfDevs - 1 && found == 0) {
                    printf("The name you have entered \"%s %s\" does not work at our company!\n", recommender[0], recommender[1]);
                }
            }
            break;
        } else if (strcmp(answer, "no") == 0 || strcmp(answer, "No") == 0)
            break;
        else
            printf("Please only answer with yes/no.\n");
    }

    if (found == 1) {

        found = 0;
        printf("Does this candidate have another recommender from inside the company?\n");
        strcpy(answer, "");

        while (1) {
            scanf("%s", answer);

            if (strcmp(answer, "yes") == 0 || strcmp(answer, "Yes") == 0) {
                printf("Please enter their recommenders first and last name.\n");

                for (int i = 0; i < 2; i++)
                    scanf("%s", recommender[i]);

                for (int i = 0; i < numOfDevs; i++) {
                    if (strcmp(employees[i]->fname, recommender[0]) == 0 && strcmp(employees[i]->lname, recommender[1]) == 0) {
                        candidates[numOfCans]->d2 = employees[i];
                        found = 1;
                        break;
                    }
                    if (i == numOfDevs - 1 && found == 0) {
                        printf("The name you have entered \"%s %s\" does not work at our company!\n", recommender[0], recommender[1]);
                    }
                }

                break;
            } else if (strcmp(answer, "no") == 0 || strcmp(answer, "No") == 0)
                break;
            else
                printf("Please only answer with yes/no.\n");
        }
    }

    printf("Does this candidate have any recommenders from outside the company?\n");
    strcpy(answer, "");

    char OutRecommender[3][20];

    while (1) {

        scanf("%s", answer);

        if (strcmp(answer, "yes") == 0 || strcmp(answer, "Yes") == 0) {

            printf("Please enter the recommender's first and last name, and their email as well.\n");

            for (int i = 0; i < 3; i++)
                scanf("%s", OutRecommender[i]);
            candidates[numOfDevs]->r1 = (Recommender *) calloc(1, sizeof(Recommender));

            strcpy(candidates[numOfDevs]->r1->fname, OutRecommender[0]);
            strcpy(candidates[numOfDevs]->r1->lname, OutRecommender[1]);
            strcpy(candidates[numOfDevs]->r1->email, OutRecommender[2]);

            break;
        } else if (strcmp(answer, "no") == 0 || strcmp(answer, "No") == 0)
            break;

        else
            break;
    }
    strcpy(answer, "");
    printf("Does this candidate have another recommender from outside the company?\n");

    while (1) {

        scanf("%s", answer);

        if (strcmp(answer, "yes") == 0 || strcmp(answer, "Yes") == 0) {

            printf("Please enter the recommender's first and last name, and their email as well.\n");
            for (int i = 0; i < 3; i++)
                scanf("%s", OutRecommender[i]);
            candidates[numOfDevs]->r2 = (Recommender *) calloc(1, sizeof(Recommender));

            strcpy(candidates[numOfDevs]->r2->fname, OutRecommender[0]);
            strcpy(candidates[numOfDevs]->r2->lname, OutRecommender[1]);
            strcpy(candidates[numOfDevs]->r2->email, OutRecommender[2]);

            break;
        } else if (strcmp(answer, "no") == 0 || strcmp(answer, "No") == 0)
            break;

        else
            break;
    }

    numOfCans++;
}

void HireCandidate(Developer *candidates[],Developer *employees[]) {

    if (numOfDevs >= 20) {
        printf("The employees team is full, candidate cannot be hired!\n");
        return;
    }

    employees[numOfDevs] = (Developer *) calloc(1, sizeof(Developer));
    char details[2][20];

    printf("Please enter the candidate's first and last name.\n");

    for (int i = 0; i < 2; i++)
        scanf("%s ", details[i]);

    int i;

    for(i=0;i<numOfCans;i++){
        if(strcmp(candidates[i]->fname,details[0])==0 && strcmp(candidates[i]->lname,details[1])==0){
            printf("Candidate %s %s has been hired as an employee!\n",details[0],details[1]);
            for(;i<numOfCans-1;i++){
                candidates[i]=candidates[i+1];
            }
            numOfCans--;
            break;
        }
    }

    employees[numOfDevs]->d1 = NULL;
    employees[numOfDevs]->d2 = NULL;
    employees[numOfDevs]->r1 = NULL;
    employees[numOfDevs]->r2 = NULL;

    numOfDevs++;

}