#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
//#include "structdef.h"
#define LINE_LIMIT 128
#define INIT_SIZE 1

typedef struct{
char* ID; //watchtower ID
char* postcode;
int population;
char* name; //watchtower name
double x;
double y;
}Watchtower;

void printValues(Watchtower ptrArray[]);

int main(){

Watchtower **ptrArray = malloc(INIT_SIZE*sizeof(Watchtower*)); //this is a dynamic memory allocation depending on how many watchtowers 
    if (ptrArray == NULL) {
        printf ("malloc failed\n");
            exit(1);
    } /*else {
        ptrArray = realloc(ptrArray, 10*INIT_SIZE*sizeof(Watchtower*)); //this realloc doesnt work, but basically everytime its not big enough (presume NULL return) it should reallocate
        if(ptrArray == NULL) {
            printf("Memory reallocation failed\n");
        } else {
            printf("Memory reallocation successful\n");
        }
    }*/
    

 FILE *fp = fopen("dataset_2.csv", "r");
    if(!fp) {
        perror("Error occured");
        exit(1);
    }
    char buff[LINE_LIMIT]; //stores the line limit into the buff
    int row_count = 0;
    int field_count = 0;
    char* delimeter = ",";

    int i = 0;

    while(fgets(buff, LINE_LIMIT, fp)) {
        field_count = 0;
        row_count++;
        if(row_count == 1)
            continue; //this is to not include the headers of the csv
        int slength = strlen(buff);
        ptrArray[i] = malloc(INIT_SIZE*sizeof(Watchtower));//this is the memory for the structure itself, so we can point to it
        if (ptrArray[i] == NULL) {
        printf ("malloc failed\n");
            exit(1);
        } /*else {
        ptrArray[i] = realloc(ptrArray[i], 10*INIT_SIZE*sizeof(Watchtower*));
        if(ptrArray[i] == NULL) {
            printf("Memory reallocation failed\n");
        } else {
            printf("Memory reallocation successful\n");
        }
    }*/

        char *field = strtok(buff,delimeter);
        while(field) {
            if(field_count == 0) {
               ptrArray[i]->ID = strdup(field); //this does malloc for the string, copying it and then allocating memory, we don't know how long words will be (does this need realloc though if it creates a new length for each one?)
               assert(ptrArray[i]->ID);
            }
            if(field_count == 1) {
                ptrArray[i]->postcode = strdup(field);
                assert(ptrArray[i]->postcode);
            }
            if(field_count == 2) {
               ptrArray[i]->population = atoi(field);
        }
            if(field_count == 3) {
                ptrArray[i]->name = strdup(field);
                assert(ptrArray[i]->name);
            }
            if(field_count == 4) {
                ptrArray[i]->x = atof(field);
            }   
            if(field_count == 5) {
                ptrArray[i]->y = atof(field);
            }
            field = strtok(NULL, delimeter); //update field value
            field_count++;
        }
        i++;
        printf("loop %d\n",i);
    }
    fclose(fp);

    printValues(*ptrArray);

    for ( i = 0; i < LINE_LIMIT; i++) {
    free ( ptrArray[i]->ID);
    free ( ptrArray[i]->postcode);
    free ( ptrArray[i]->name);
    free ( ptrArray[i]);
}
free ( ptrArray);

    return 0;
}

void printValues(Watchtower ptrArray[]) {
    for(int i = 0; i < 10; i++) {
        printf("ID %s, postcode %s, population %d, name %s, x %f, y %f\n",ptrArray[i].ID,ptrArray[i].postcode,ptrArray[i].population,ptrArray[i].name,ptrArray[i].x,ptrArray[i].y);
    }
}