#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

list_t*createList(){
    list_t*myList=malloc(sizeof(list_t));
    myList->head=NULL;
    return myList;
}

void deleteList(list_t*list) {
    node_t*f=list->head;
    while(f!=NULL) {
        node_t *todelete = f;
        f = f->next;
        free(todelete);

    }

    free(list);
}

node_t*createNode(char*firstname, char*lastname,char*email,char*phone,char*address,char*birthdate){
    node_t*q=NULL;
    q=malloc(sizeof(node_t));
    q->next=NULL;
    q->prev=NULL;
    q->firstname=firstname;
    q->lastname=lastname;
    q->address=address;
    q->email=email;
    q->birthdate=birthdate;
    q->phone=phone;

    return q;
}

void printList(list_t*l){

    if(l->head==NULL){
        printf("%s","Lista jest pusta");
        return;
    }
    node_t*f=l->head;
    while(f!=NULL){
        printf("%s%s",f->firstname,"->");
        f=f->next;
    }
    printf("%s\n","NULL");
}

void printListL(list_t*l){

    if(l->head==NULL){
        printf("%s","Lista jest pusta");
        return;
    }
    node_t*f=l->head;
    while(f!=NULL){
        printf("%s%s",f->lastname,"->");
        f=f->next;
    }
    printf("%s\n","NULL");
}

void addNodeEnd(list_t*list,char*firstname,char*lastname,char*email,char*phone,char*address,char*birthdate){

    node_t*new_node=createNode(firstname,lastname,email,phone,address,birthdate);


    if(list->head==NULL){
        list->head=new_node;
        new_node->next=NULL;
        new_node->prev=NULL;
    }
    else {
        node_t*first=list->head;
        while (first->next != NULL) {
            first = first->next;
        }

        first->next = new_node;
        new_node->next = NULL;
        new_node->prev = first;
    }
}
//bool findElement po nodzie
bool findElement(list_t*list,node_t*node){
    if(list->head==NULL){
        printf("%s","The list is empty.Cannot find anything");
        return false;
    }

    node_t*first=list->head;
    while(first!=NULL){
        if(first->firstname==node->firstname && first->lastname==node->lastname){
            return true;
        }
        else{
            first=first->next;
        }
    }
    return false;
}

bool findContact(list_t*list,char*firstname, char*lastname){
    if(list->head==NULL){
        printf("%s","The list is empty.Cannot find anything");
        return false;
    }

    node_t*first=list->head;
    while(first!=NULL){
        if(first->firstname==firstname && first->lastname==lastname){
            return true;
        }
        else{
            first=first->next;
        }
    }
    return false;
}



void deleteElement(list_t*list,node_t*q){

    if(findElement(list,q)==false){
        printf("%s","The element is not in the list or the list is already empty");
        return;
    }

    node_t*first=list->head;

    while(first!=NULL && first!=q){
        first=first->next;
    }

    if(first==q) {
        if (first->prev == NULL) {


            node_t *todelete = first;
            list->head = first->next;
            if (list->head != NULL) {
                list->head->prev = NULL;
            }
            free(todelete);


        }

        else{
            node_t *todelete = first;
            first->prev->next = first->next;
            if (first->next != NULL) {
                first->next->prev = first->prev;
            }
            free(todelete);

        }
    }

}

void deleteContact(list_t*list,char*firstname,char*lastname){

    if(findContact(list,firstname,lastname)==false){
        printf("%s","The element is not in the list or the list is already empty");
        return;
    }

    node_t*first=list->head;

    while(first!=NULL && first->firstname!=firstname && first->lastname!=lastname){
        first=first->next;
    }

    if(first->firstname==firstname && first->lastname==lastname) {
        if (first->prev == NULL) {


            node_t *todelete = first;
            list->head = first->next;
            if (list->head != NULL) {
                list->head->prev = NULL;
            }
            free(todelete);


        }

        else{
            node_t *todelete = first;
            first->prev->next = first->next;
            if (first->next != NULL) {
                first->next->prev = first->prev;
            }
            free(todelete);

        }
    }

}


//You can choose how  you would like to sort.
//Option 0 - firstname, 1-lastname, 2-email, 3-phone

bool compare(node_t*current,node_t*maxval,int option){
    switch(option){
        case 0:
            if(strcmp(current->firstname,maxval->firstname)<0){
                return true;
            }
            else{
                return false;
            }

        case 1:
            if(strcmp(current->lastname,maxval->lastname)<0){
                return true;
            }
            else{
                return false;
            }
        case 3:
            if(strcmp(current->email,maxval->email)<0){
                return true;
            }
            else{
                return false;
            }
        case 4:
            if(strcmp(current->phone,maxval->phone)<0){
                return true;
            }
            else{
                return false;
            }
        default:
            return false;
    }

}

list_t* selection_sort(list_t*list,int option){


    list_t*sorted=createList();
    node_t*maxval;
    node_t*current;

    while(list->head!=NULL){

        maxval=list->head;
        current=list->head;

        while(current!=NULL){
            if(compare(current,maxval,option)){
                maxval=current;

            }
            current=current->next;
        }
        addNodeEnd(sorted,maxval->firstname,maxval->lastname,maxval->email,maxval->phone,maxval->address,maxval->birthdate);
        deleteElement(list,maxval);
    }
    return sorted;
}


/////////////////////////////////////DRZEWO

BSTNode* createBSTNode(char*firstname,char*lastname,char*email,char*phone,char*birthdate,char*address){
    BSTNode*node=malloc(sizeof(BSTNode));
    node->left=NULL;
    node->right=NULL;
    node->parent=NULL;
    node->firstname=firstname;
    node->lastname=lastname;
    node->address=address;
    node->email=email;
    node->birthdate=birthdate;
    node->phone=phone;
    return node;
}

BSTNode* createTree(){
    BSTNode*root=malloc(sizeof(BSTNode));

    root=NULL;
    return root;
}


bool insert(BSTNode**root_ptr,char*firstname, char*lastname,char*email,char*phone,char*birthdate,char*address){
      BSTNode* root= *root_ptr;
    if(root==NULL){
        BSTNode*node= createBSTNode(firstname, lastname,email,phone,birthdate,address);
        *root_ptr=node;
        return true;
    }
    //if(root->firstname==node->firstname) return false;
    if(strcmp(firstname,root->firstname)>0){
        if(root->right!=NULL) return insert(&root->right,firstname,lastname,email,phone,birthdate,address);
        BSTNode*node= createBSTNode(firstname, lastname,email,phone,birthdate,address);
        root->right=node;
        node->parent=root;
        node->right=NULL;
        node->left=NULL;
        return true;

    }
    else{
        if(root->left!=NULL) return insert(&root->left,firstname,lastname,email,phone,birthdate,address);
        BSTNode*node= createBSTNode(firstname, lastname,email,phone,birthdate,address);
        root->left=node;
        node->parent=root;
        node->right=NULL;
        node->left=NULL;
        return true;

    }

}


void printTree(BSTNode*node){
    if(node==NULL){
        return;
    }
    printTree(node->left);
    printf("%s%s",node->firstname," ");
    printTree(node->right);
}

BSTNode * TreeMax(BSTTree* tree){

    BSTNode * node = tree->root;
    if(node==NULL) return NULL;;

    while(node->right!=NULL){
        node=node->right;

    }
    return node;

}

BSTNode * TreeMin(BSTTree* tree){

    BSTNode * node = tree->root;
    if(node==NULL) return NULL;;

    while(node->left!=NULL){
        node=node->left;

    }
    return node;

}



BSTNode*FindInTree2(BSTNode*node,char*name){


    if(node==NULL) return NULL;

    while(node!=NULL){

        if(node->firstname==name) return node;

        if(strcmp(node->firstname,name)<0){
            node=node->right;
        }
        else if(strcmp(node->firstname,name)>0){
            node=node->left;
        }

    }
    return NULL;

}


bool FindInTreeb(BSTTree*tree,char*name) {

    BSTNode *node = tree->root;

    if (node == NULL) return false;

    while (node != NULL) {

        if (node->firstname == name) return true;

        if (strcmp(node->firstname, name) < 0) {
            node = node->left;
        } else if (strcmp(node->firstname, name) > 0) {
            node = node->right;
        }

    }
    return false;

}

BSTNode*findMin(BSTNode*node){

    if(node==NULL) return NULL;
    while(node->left!=NULL){
        node=node->left;
    }
    return node;
}

BSTNode*findMax(BSTNode*node){
    if(node==NULL) return NULL;
    while(node->right!=NULL){
        node=node->right;
    }
    return node;
}

BSTNode*succ(BSTNode*node){         //nastepca

    if(node==NULL){

        return NULL;
    }

    if(node->right!=NULL) return findMin(node->right);
    else {
        BSTNode *y = node->parent;
        BSTNode *x = node;

        while (y != NULL && y->right == x) {
            x = y;
            y = y->parent;
        }
        if(y==NULL){
            printf("%s","This node does not have succ");
        }
        return y;
    }

}

BSTNode*anc(BSTNode*node){         //poprzednik

    if(node==NULL){

        return NULL;
    }

    if(node->left!=NULL) return findMax(node->left);
    else {
        BSTNode *y = node->parent;
        BSTNode *x = node;

        while (y != NULL && y->left == x) {
            x = y;
            y = y->parent;
        }
        if(y==NULL){
            printf("%s","This node does not have ancestor");
        }
        return y;
    }

}

BSTNode* delete(BSTNode*root,char*firstname){


    if(root==NULL) return root;
    else if(strcmp(root->firstname,firstname)>0){

        root->left=delete(root->left,firstname);
    }
    else if(strcmp(root->firstname,firstname)<0){
        root->right=delete(root->right,firstname);
    }
    else{
        //there is no child

        if(root->left==NULL && root->right==NULL){

            free(root);
            root->firstname=NULL;
            root=NULL;


        }
            //there is one child
        else if(root->left == NULL){
            BSTNode*tmp=root;
            root=root->right;
            free(tmp);

        }
        else if(root->right == NULL){
            BSTNode*tmp=root;
            root=root->left;
            free(tmp);

        }
        else{
            BSTNode*tmp=findMin(root->right);
            root->firstname=tmp->firstname;
            root->right=delete(root->right,tmp->firstname);


        }
        return root;

    }

}  

void deleteTree(BSTNode*root){
    if(root==NULL) return;
        deleteTree(root->left);
        deleteTree(root->right);
        //free(root->firstname);
        //free(root->lastname);
        free(root);


}

void deleteTreeAll(BSTTree*tree){
    if(tree->root!=NULL) deleteTree(tree->root);
    tree->root=NULL;
}

//void treeSort(BSTTree*tree){

//}
