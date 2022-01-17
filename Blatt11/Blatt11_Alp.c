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

void sort_list(){  
    student *current = NULL, *ptr = NULL, *temp = NULL;  
     
    if(head == NULL) {  
        return;  
    }  
    else {  
        for(current = head; current->next != NULL; current = current->next) {  
            for(ptr = current->next; ptr->next != NULL; ptr = ptr->next) {    
                if(strcmp(current->Nachname,ptr->Nachname) > 0) {  
                    temp = current;  
                    current = ptr;  
                    ptr = temp;  
                }  
            }  
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
    sort_list();
    print_list();

}