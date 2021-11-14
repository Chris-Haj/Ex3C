//
// Created by chris on 11/15/2021.
//

#ifndef EX3_COMPANY_H
#define EX3_COMPANY_H

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

void HireCandidate(Developer *candidates[], Developer *employees[]);

void start(Developer *candidates[],Developer *employees[]);

#endif //EX3_COMPANY_H
