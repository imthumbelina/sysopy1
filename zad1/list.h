#ifndef UNTITLED2_LIST_H
#define UNTITLED2_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct node {
    struct node *next;
    struct node *prev;
    char*firstname;
    char*lastname;
    char*email;
    char*phone;
    char*birthdate;
    char*address;
}node_t;

typedef struct list{
    node_t*head;
}list_t;

typedef struct BSTNode{
    struct BSTNode*parent;
    struct BSTNode*left;
    struct BSTNode*right;
    char*firstname;
    char*lastname;
    char*email;
    char*phone;
    char*birthdate;
    char*address;
}BSTNode;

typedef struct BSTTree{
    BSTNode*root;
}BSTTree;



list_t*createList();
void deleteList(list_t*list) ;

node_t*createNode(char*firstname, char*lastname,char*email,char*phone,char*address,char*birthdate);

void printList(list_t*l);

void printListL(list_t*l);

void addNodeEnd(list_t*list,char*firstname,char*lastname,char*email,char*phone,char*address,char*birthdate);




bool findElement(list_t*list,node_t*node);

bool findContact(list_t*list,char*firstname, char*lastname);

void deleteElement(list_t*list,node_t*q);

void deleteContact(list_t*list,char*firstname,char*lastname);

//You can choose how  you would like to sort.
//Option 0 - firstname, 1-lastname, 2-email, 3-phone

bool compare(node_t*current,node_t*maxval,int option);

list_t* selection_sort(list_t*list,int option);

/////////////////////////////////////DRZEWO

BSTNode* createBSTNode(char*firstname,char*lastname,char*email,char*phone,char*birthdate,char*address);

BSTNode* createTree();





bool insert(BSTNode**root,char*firstname, char*lastname,char*email,char*phone,char*birthdate,char*address);

void printTree(BSTNode*node);

BSTNode * TreeMax(BSTTree* tree);

BSTNode * TreeMin(BSTTree* tree);



BSTNode*FindInTree2(BSTNode*node,char*name);


bool FindInTreeb(BSTTree*tree,char*name);

BSTNode*findMin(BSTNode*node);

BSTNode*findMax(BSTNode*node);


BSTNode*succ(BSTNode*node);

BSTNode*anc(BSTNode*node);       //poprzednik


BSTNode* delete(BSTNode*root,char*firstname);


void deleteTree(BSTNode*root);

void deleteTreeAll(BSTTree*tree);


#endif //UNTITLED2_LIST_H
