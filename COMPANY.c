#include "COMPANY.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20

int numOfCans=0;
int numOfDevs=0;

int welcome() {

    int option = 0;

    printf("Welcome, what do you want to do?\n");
    printf("1. Print candidates.\n");
    printf("2. Print workers.\n");
    printf("3. Insert new candidate.\n");
    printf("4. Hire candidate\n");
    printf("5. Exit\n");

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

    /*
     * This for loop will pass over all the candidates array and print out their first name and last name and their degree.
     * If the candidate has any recommenders from the company or outside it will also print them out.
     * */

    for (int i = 0; i < numOfCans; i++) {
        printf("Candidate %d details:\n\tFirst name: %s \n\tLast name: %s \n\tDegree: %s\n", i + 1, candidates[i]->fname, candidates[i]->lname, candidates[i]->degree);
        if (candidates[i]->d1 != NULL) {
            printf("\tRecommender 1 from company for %s %s is %s %s\n", candidates[i]->fname, candidates[i]->lname, candidates[i]->d1->fname, candidates[i]->d1->lname);
            if (candidates[i]->d2 != NULL)
                printf("\tRecommender 2 from company for %s %s is %s %s\n", candidates[i]->fname, candidates[i]->lname, candidates[i]->d2->fname, candidates[i]->d2->lname);
        }
        if (candidates[i]->r1 != NULL) {
            printf("\tRecommender 1 from outside the company for %s %s is %s %s\n", candidates[i]->fname, candidates[i]->lname, candidates[i]->r1->fname, candidates[i]->r1->lname);
            if (candidates[i]->r2 != NULL) {
                printf("\tRecommender 2 from outside the company for %s %s is %s %s\n", candidates[i]->fname, candidates[i]->lname, candidates[i]->r2->fname, candidates[i]->r2->lname);
            }
        }

    }

    printf("\n");
}

void PrintEmployees(Developer *employees[]) {

    //If there are 0 employees.
    if (numOfDevs == 0) {
        printf("There are currently 0 employees.\n");
        return;
    }
//This will pass over the employees array and print out their first and last names.
    for (int i = 0; i < numOfDevs; i++) {
        printf("Employee %d: \n\tFirst name: %s \n\tLast name: %s \n", i + 1, employees[i]->fname, employees[i]->lname);
    }
    printf("\n");
}

void InsertCandidate(Developer *candidates[], Developer *employees[]) {

    //If the candidates array is already full then the function will immediately stop and return void.
    if (numOfCans > N) {
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

    //All the pointers within the new candidate struct will point to null
    candidates[numOfCans]->d1 = NULL;
    candidates[numOfCans]->d2 = NULL;
    candidates[numOfCans]->r1 = NULL;
    candidates[numOfCans]->r2 = NULL;

    printf("Does this candidate have any recommenders from inside the company? Answer with yes/no.\n");
    char answer[4] = "";
    char recommender[2][20];
    int found = 0;

    //This while loop will keep going, until the user enters yes/no.
    while (1) {

        scanf("%s", answer);

        if (strcmp(answer, "yes") == 0 || strcmp(answer, "Yes") == 0) {
            printf("Please enter their recommenders first and last name.\n");

            for (int i = 0; i < 2; i++)
                scanf("%s", recommender[i]);

            for (int i = 0; i < numOfDevs; i++) {
                if (strcmp(employees[i]->fname, recommender[0]) == 0 && strcmp(employees[i]->lname, recommender[1]) == 0) {
                    candidates[numOfCans]->d1 = employees[i];
                    found = 1;
                    break;
                }
            }

            //This if block is used to check if the recommender name that was entered is an employee at the company, if not, it will
            //keep both pointers pointing to null.
            if(found==0){
                printf("The name you have entered \"%s %s\" does not work at our company!\n", recommender[0], recommender[1]);
                printf("It will be assumed that the candidate does not have any recommenders from inside the company!\n");
            }

            break;
        } else if (strcmp(answer, "no") == 0 || strcmp(answer, "No") == 0)
            break;
        else
            printf("Please only answer with yes/no.\n");
    }

    //If the recommender name entered is an employee at the company, then it will continue to ask if there is another recommender that company.
    if (found == 1) {
        found = 0;
        printf("Does this candidate have another recommender from inside the company? Answer with yes/no.\n");
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
                }

                if (found == 0) {
                    printf("The name you have entered \"%s %s\" does not work at our company!\n", recommender[0], recommender[1]);
                }

                break;
            } else if (strcmp(answer, "no") == 0 || strcmp(answer, "No") == 0)
                break;
            else
                printf("Please only answer with yes/no.\n");
        }
    }

    found = 0;
    printf("Does this candidate have any recommenders from outside the company? Answer with yes/no.\n");
    strcpy(answer, "");

    char OutRecommender[3][20];
//This will ask the user if the candidate has a recommender from outside the company.
    while (1) {

        scanf("%s", answer);

        if (strcmp(answer, "yes") == 0 || strcmp(answer, "Yes") == 0) {
            found = 1;
            printf("Please enter the recommender's first and last name, and their email as well.\n");

            for (int i = 0; i < 3; i++)
                scanf("%s", OutRecommender[i]);

            //If the user enters "yes", meaning that the candidate does have a recommender from outside the company then it will create a new
            //block of memory of type Recommender and make the first recommender type pointer of the current candidate point to it.
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
    if (found == 1) {
        strcpy(answer, "");
        printf("Does this candidate have another recommender from outside the company? Answer with yes/no.\n");

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
    }
    found=0;
    numOfCans++;
}

void HireCandidate(Developer *candidates[], Developer *employees[]) {

    //If the employees array is already full then it will immediately stop the function and return void.
    if (numOfDevs > N) {
        printf("The employees team is full, candidate cannot be hired!\n");
        return;
    }

    int found=0;
    char details[2][20];

    printf("Please enter the candidate's first and last name.\n");

    //The names that the user enters will be stored into details and if the first and last names exist in the candidates array then it will
    //set found to 1, meaning that the name entered was also found in the candidates array.
    for (int i = 0; i < 2; i++)
        scanf("%s", details[i]);

    for(int i=0;i<numOfCans;i++){
        if(strcmp(candidates[i]->fname,details[0])==0 && strcmp(candidates[i]->lname,details[1])==0)
            found = 1;
    }

    //If the name that the user enters was not found in the candidates array, then it will stop running the function and return void.
    if(found==0){
        printf("The name you have entered does not exist in our candidates list!\n");
        return;
    }

    employees[numOfDevs] = (Developer *) calloc(1, sizeof(Developer));
    int i;

    for (i = 0; i < numOfCans; i++) {
        if (strcmp(candidates[i]->fname, details[0]) == 0 && strcmp(candidates[i]->lname, details[1]) == 0) {
            printf("Candidate %s %s has been hired as an employee!\n", details[0], details[1]);
            strcpy(employees[numOfDevs]->fname, details[0]);
            strcpy(employees[numOfDevs]->lname, details[1]);
            for (; i < numOfCans - 1; i++) {
                candidates[i] = candidates[i + 1];
            }
            free(candidates[i]->r1);
            free(candidates[i]->r2);
            free(candidates[i]);
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

void start(Developer *candidates[],Developer *employees[]){
    int exit=0;

    while(!exit){
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
                HireCandidate(candidates, employees);
                break;
            case 5:
                printf("You have exited the program.");
                for (int i = 0; i < N; i++){
                    free(candidates[i]->r1);
                    free(candidates[i]->r2);
                    free(candidates[i]);
                    free(employees[i]);
                }
                exit = 1;
                break;
        }
    }


}