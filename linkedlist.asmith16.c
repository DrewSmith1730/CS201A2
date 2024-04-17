#include "linkedlist.asmith16.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int insertStudent(Record **list, char *name, int id){
    // check if the list and name are null () and makes sure id is greater then 0
    if (list != NULL && name != NULL && id > 0){
        // Create record for data given
        Record *newRec = malloc(sizeof(Record));
        strcpy(newRec->name, name);
        newRec->id = id;
        newRec->next = NULL;

        // check if the list has elements yet or not.
        if (*list != NULL){
            // if there are elements in the list already.

            // make a record to track the one im on and the one before it
            Record *prev = malloc(sizeof(Record));
            Record *curr = malloc(sizeof(Record));
            curr = *list;
            
            // loop to find where the id goes in the list
            while(curr != NULL && id > curr->id) {
                prev = curr;
                curr = curr->next;
            }
            // check right away if the id is already there
            if(curr != NULL && id == curr->id){ 
                // if it is already in the list with that id change nothing and return 1
                return 1;
            }
            // check if the id is already in the list
            if (id < (*list)->id){
                // checking if the inserted is less then the first node
                // makes newRec the first node
                newRec->next = *list;
                *list = newRec;
            // if there are more nodes in the list
            } else if (curr != NULL && curr->id != id){
                // if it reaches the end of the list of nodes...
                // puts it imbetween the 2 nodes in accending order
                newRec->next = curr;
                prev->next = newRec;
                return 0;
            // the end of the list
            } else if (curr == NULL && prev->id != id){
                prev->next = newRec;
                return 0;
            }
        } else {
            // if it is the first in the list.
            *list = newRec;
            return 0;
        }
        return 0;
    } else {
        return 1;
    }
}

int deleteStudent(Record **list, int id){
    Record *tempList = malloc(sizeof(Record));
    Record *prev = malloc(sizeof(Record));
    prev = NULL;
    tempList = *list;

    // check if the id exists in the list
    while (tempList != NULL && tempList->id != id){
        prev = tempList;
        tempList = tempList->next;
    }
    // if the first node is selected
    if (tempList != NULL && prev == NULL && tempList->id == id){
        prev = tempList->next;
        tempList->next = NULL;
        *list = prev;
        return 0;
    }
    // exits at the end of the list and if the id's match
    // if the id is found anywhere except the end of the list
    if (tempList != NULL && id == tempList->id){
        prev->next = tempList->next;
        return 0;
    }
    // if removing the last node in the list
    if (prev != NULL && tempList == NULL && prev->id == id){
        prev->next = NULL;
        return 0;
    }
    return 1;
}

int getStudent(Record *list, int id, char *buffer){
    Record *tempList = malloc(sizeof(Record));
    Record *prev = malloc(sizeof(Record));
    prev = NULL;
    tempList = list;
    
    while (tempList != NULL && tempList->id != id){
        prev = tempList;
        tempList = tempList->next;
    }

    // if the first node is selected
    if (tempList != NULL && prev == NULL && tempList->id == id){
        strcpy(buffer, tempList->name);
        return 0;
    }
    // exits at the end of the list and if the id's match
    // if the id is found anywhere except the end of the list
    if (tempList != NULL && id == tempList->id){
        strcpy(buffer, tempList->name);
        return 0;
    }
    // if it is in the last node on the list
    if (prev != NULL && tempList == NULL && prev->id == id){
        strcpy(buffer, prev->name);
        return 0;
    }
    
    return 1;
}

int countStudents(Record *list){
    Record *tempList = malloc(sizeof(Record));
    tempList = list;
    int count = 0;

    while (tempList != NULL){
        tempList = tempList->next;
        count++;
    }
    return count;
}


int printStudents(Record *list){
    Record *tempList = malloc(sizeof(Record));
    tempList = list;
    
    if (tempList == NULL){
        printf("(list is empty)\n");
        return 0;
    }

    while (tempList != NULL){
        printf("|%s| id = %d\n", tempList->name, tempList->id);
        tempList = tempList->next;
    }
    
    return 0;
}