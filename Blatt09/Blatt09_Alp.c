#include <stdio.h>

#define N 3

typedef struct{
    char* Vorname;
    char* Nachname;
    int Mnmr;
    char* Adresse;
    int Kurse
} student;

void Ausgabe(student Student){
    printf("%s, %s, %d, %s, %d\n",Student.Vorname, Student.Nachname, Student.Mnmr, Student.Adresse, Student.Kurse);
}

int main(void){

    student temp;

    student Studenten[N];
    student Anna = {"Anna", "Musterfrau", 22222, "Am Schwarzenberg-Campus 3", 4};
    student Hans = {"Hans", "Peter",      44444 , "Kasernenstrasse 12",       2};
    student Lisa = {"Lisa", "Lustig",     66666 , "Denickestrasse 15",        8};

    Studenten[0] = Anna;
    Studenten[1] = Hans;
    Studenten[2] = Lisa;

    for(int i = 0; i < N; i++){
        Ausgabe(Studenten[i]);
    }
    //vertauschen des ersten und letzten elements
    temp = Studenten[0];
    Studenten[0] = Studenten[N-1];
    Studenten[N-1] = temp;

    printf("\nVertausche 1. und letzte Element!\n\n");

    for(int i = 0; i < N; i++){
        Ausgabe(Studenten[i]);
    }
}