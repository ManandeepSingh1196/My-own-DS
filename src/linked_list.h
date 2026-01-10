//Unsorted Linked List //
//
//TODO:
//1. Allocation Failure Handling
//
//


#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include<stddef.h>
#include<stdlib.h>


//Modes
typedef enum InsertMode { 
    INSERT_BY_VALUE,
    INSERT_BY_POSITION
} InsertMode;

typedef enum DeleteMode {
	DELETE_BY_VALUE,
    DELETE_BY_POSITION
} DeleteMode;


//Node
typedef struct Node 
{ 
    int value;
	struct Node* next;
} Node;




/*
 _     ___ ____ _____   _____ _   _ _   _  ____ _____ ___ ___  _   _ ____  
| |   |_ _/ ___|_   _| |  ___| | | | \ | |/ ___|_   _|_ _/ _ \| \ | / ___| 
| |    | |\___ \ | |   | |_  | | | |  \| | |     | |  | | | | |  \| \___  
| |___ | | ___) || |   |  _| | |_| | |\  | |___  | |  | | |_| | |\  |___) |
|_____|___|____/ |_|   |_|    \___/|_| \_|\____| |_| |___\___/|_| \_|____/ 
*/


//Insertion Functions
static inline void InsertAtBeginning (Node** head, int val)
{
    //edge test

	struct Node* newNode = malloc(sizeof *newNode);
	newNode->value = val;

	newNode->next = *head;
	*head = newNode;
}

static inline void InsertAtEnd (Node** head, int val)
{
    //edge test

	struct Node* iter = *head;
	while (iter->next != NULL)
		iter = iter->next;
	
	struct Node* newNode = malloc(sizeof *newNode);
	newNode->value = val;
	newNode->next = NULL;
	iter->next = newNode;
}


//Deletion Functions
static inline void DeleteAtBegininning (Node** head)
{
    //edge test

	struct Node* temp = *head;
	*head = temp->next;

	free(temp);
}

static inline void DeleteAtEnd (Node** head)
{
    //edge test

	struct Node* iter = *head;
	while (iter->next->next != NULL)
		iter = iter->next;
	
	struct Node* temp = iter->next;
	iter->next = NULL;
	free(temp);
}


//Function to perform insertion at both position or at value
static inline void InsertAtPosition(Node** head, int n, InsertMode mode)
{
    struct Node* newNode = malloc(sizeof *newNode);
    newNode->next = NULL;

    if (mode == INSERT_BY_POSITION)
    {
        if (n == 0 || *head == NULL) {
            newNode->next = *head;
            *head = newNode;
            return;
        }

        struct Node* iter = *head;
        int idx = 0;

        while (iter->next != NULL && idx < n - 1) {
            iter = iter->next;
            idx++;
        }
        newNode->next = iter->next;
        iter->next = newNode;
    }
    else if (mode == INSERT_BY_VALUE)
    {
        struct Node* iter = *head;
        while (iter != NULL && iter->value != n)
            iter = iter->next;

        if (iter == NULL)
            return;

        newNode->next = iter->next;
        iter->next = newNode;
    }
}


//Function to perform deletion at both position or at value
static inline void DeleteAtPosition (Node** head, int n, DeleteMode mode)
{
   //edge test 
   //
   //add head checks (if only head is to be deleted)

    if (mode == DELETE_BY_POSITION)
    {
        int idx = 0;
        struct Node* iter = *head;

        while (idx < n - 1)
        {
            if (iter->next == NULL)
                return;              //make proper error here

            iter = iter->next;
            ++idx;
        }
        
        struct Node* temp = iter->next;
        iter->next = temp->next;
        free(temp); 
    }
    
    else if (mode == DELETE_BY_VALUE)
    {   
        struct Node* iter = *head;
        struct Node* prev;

        while (iter->value != n)
        {
            if (iter->next == NULL)
                return;             //make proper error here
            
            prev = iter;
            iter = iter->next;
        }

        prev->next = iter->next;
        free(iter); 
    }
}

//Initialize Linked List from array of elements
static inline struct Node* initList (const int*  array, size_t size)
{
    if (size == 0)
        return NULL;

    struct Node* head = malloc(sizeof *head);
    head->value = array[0];
    head->next = NULL;

    for (size_t idx = 1; idx < size; ++idx)
    {
        InsertAtEnd(&head, array[idx]);
    }

    return head;
}

//Destruction function for memory management
static inline void destroyList (Node** head)
{
    Node* curr = *head;

    while (curr != NULL) 
    {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }

    *head = NULL;
}

#endif
