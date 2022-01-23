#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct student{
    struct student *prev;
    char* Vorname;
    char* Nachname;
    int Mnmr;
    char* Adresse;
    int Kurse;
    struct student *next;
} student;

student *head = NULL;
student *last = NULL;

bool isEmpty(){
    return head == NULL;
}

void push_student(char* Vorname, char* Nachname, int Mnmr, char* Adresse, int Kurse){
    student *link = (student*) malloc(sizeof(student));
    link->Vorname = Vorname;
    link->Nachname = Nachname;
    link->Mnmr = Mnmr;
    link->Adresse = Adresse;
    link->Kurse = Kurse;

    if(isEmpty()){
        last = link;
    }
    else{
        head->prev = link;
        link->next = head;
    }
        
        head = link;
        head->prev = NULL;
}

void delete_student(int n){
    student *ptr = head;
    student *prev = NULL;

    for(int i = 0; i < n-1; i++){
        prev = ptr;
        ptr = ptr->next;
    }
    prev->next = ptr->next;
    (ptr->next)->prev = prev;

}

void print_list(){
    student *ptr = head;

    while (ptr != NULL){
        printf("\n%s, %s, %d, %s, %d\n",ptr->Vorname, ptr->Nachname, ptr->Mnmr, ptr->Adresse, ptr->Kurse);
        ptr = ptr->next;
    } 
    printf("\n------------------------\n");
}

void reverse_list(){
    student *current = head;
    student *temp;

    while(current != NULL){

        temp = current->next;
        current->next = current->prev;
        current->prev = temp;

        current = temp;
    }

    temp = head;
    head = last;
    last = temp;
}

void refreshPointers(student *A) {
    if (A->prev != NULL)
        A->prev->next = A;

    if (A->next != NULL)
        A->next->prev = A;
}

void swap(student *A,student *B) {
    student *swapperVector[4];
    student *temp;

    if (A == B) return;

    if (B->next == A) {
        temp = A;
        A = B;
        B = temp;
    }
    
            /*
                 A B               A B 
            prev X A    =>    prev B X
            next B Y          next Y A

                 0 1     --\       2 0
                 2 3     --/       3 1
            */

    swapperVector[0] = A->prev;
    swapperVector[1] = B->prev;
    swapperVector[2] = A->next;
    swapperVector[3] = B->next;

    if ( (A->next == B && B->prev == A ) || ( A->prev == B && B->next == A) ) {
        A->prev = swapperVector[2];
        B->prev = swapperVector[0];
        A->next = swapperVector[3];
        B->next = swapperVector[1];
    } else {
        A->prev = swapperVector[1];
        B->prev = swapperVector[0];
        A->next = swapperVector[3];
        B->next = swapperVector[2];
    }

    refreshPointers(A);
    refreshPointers(B);
}

void sort_list(){  
    student *ptr = head;
    int loop = 1;

    while(loop){
        loop = 0;
        while(ptr->next != NULL){    
            if(strcmp(ptr->Nachname, ptr->next->Nachname) > 0) {  
                loop = 1;
                swap(ptr, ptr->next);  
                }  
            ptr=ptr->next;  
        }  
    } 
}  



int main(){

    push_student("Anna", "Musterfrau", 22222, "Am Schwarzenberg-Campus 3", 4);
    push_student("Hans", "Peter",      44444 , "Kasernenstrasse 12",       2);
    push_student("Lisa", "Lustig",     66666 , "Denickestrasse 15",        8);
    push_student("Max", "Mustermann",  88888,  "Seminarstrasse 10",         3);
    push_student("Peter", "Schaf",     12345,  "Bakerstreet 221b",         9);

    print_list();
    printf("- sort list alphabetically -\n------------------------\n");
    //swap(head->next->next, head->next->next->next);
    sort_list();
    print_list();

}