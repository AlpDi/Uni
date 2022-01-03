#include <stdio.h>

typedef struct {
	char* Vorname;
	char* Nachname;
	unsigned int Matrikelnummer;
	char* Wohnaddresse;
	unsigned int Pflichtkurse
} student;

void print_students(student print_list[]) {
	for (int i = 0; i < 3; i++) {
		printf("Vorname:\t%s\nNachname:\t%s\nMatrikelnummer:\t%u\nWohnaddresse:\t%s\nPflichtkurse:\t%u\n\n", print_list[i].Vorname, print_list[i].Nachname, print_list[i].Matrikelnummer, print_list[i].Wohnaddresse, print_list[i].Pflichtkurse);
	}
}

int main(void) {
	student students[3];
	students[0] = (student) { "Anna", "Musterfrau", 22222, "Am Schwarzenberg-Campus 3", 4 };
	students[1] = (student) { "Hans", "Peter", 44444, "Kasernenstraße 12", 2 };
	students[2] = (student){ "Lisa", "Lustig", 66666, "Denickestraße 15", 8 };

	print_students(students);

	printf("Switching first with last...\n\n");
	student temp_student = students[2];
	students[2] = students[0];
	students[0] = temp_student;

	print_students(students);

	return 0;
}
