#include "stdafx.h"
#include "interface.h"
#include "stos.h"
#include "student.h"
#include <iostream>

void my_interface() {
	bool czy = true;
	while (czy) {
		std::cout << "1-dodaj element do stosu\n";
		std::cout << "2-pobierz element ze stosu\n";
		std::cout << "3-wyswietl stos\n";
		std::cout << "4-znajdz w stosie\n";
		std::cout << "5-usun stos\n";
		std::cout << "6-wczytaj stos\n";
		std::cout << "7-zapisz stos\n";
		std::cout << "8-wyjdz\n";
		int a;
		std::cin >> a;
		system("cls");
		if ((a > 8) or (a < 1)) {
			continue;
		}
		void *pom = NULL;
		switch (a) {
		case 1: stack_push(My_Student_init()); break;
		case 2:
			pom = stack_pop();
			std::cout << "Usuniety element ze stosu:\n";
			My_Student_print(pom);
			My_Student_delete(pom);
			pom = NULL;
			break;

		case 3: stack_print(My_Student_print); break;
		case 4: pom = My_Student_comparing_new(); stack_find(pom, My_Student_comparing, My_Student_print); My_Student_delete(pom); pom = NULL; break;
		case 5: stack_free(My_Student_delete); break;
		case 6: stack_load(My_Student_load); break;
		case 7: stack_save(My_Student_save); break;
		case 8: czy = false; break;
		}
		system("pause");
		system("cls");
	}
	stack_free(My_Student_delete);
	system("cls");
}