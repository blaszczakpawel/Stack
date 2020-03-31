#include "stdafx.h"
#include "My_Errors.h"
#include"student.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <Windows.h>
#include <malloc.h>

#pragma warning (disable: 4996)

bool My_Student_comparing(void* jeden, void* dwa) {
	struct My_Student* jj = (struct My_Student*)jeden;
	struct My_Student*  dd = (struct My_Student*)dwa;
	if (jj->wiek == dd->wiek) return true;
	if (jj->kierunek == dd->kierunek) return true;
	if ((strlen(jj->name) != 0) and (strlen(dd->name) != 0) and (strlen(jj->name) == strlen(dd->name))) {
		if (strncmp(jj->name, dd->name, strlen(jj->name)) == 0) return true;
	}

	return false;
}

void* My_Student_comparing_new() {
	system("cls");
	struct My_Student* new_s = (struct My_Student*)malloc(sizeof(struct My_Student));
	if (new_s == NULL) {
		my_error(MEM_ALLOC_ERROR);
	}
	new_s->kierunek = total;
	new_s->wiek = -1;
	char pom[256];
	memset(pom, 0, 256);
	std::cout << "Po czym chcesz wyszkiwac?\n1-nazwisku\n2-wieku\n3-kierunku\n";
	int n;
	std::cin >> n;
	switch (n) {
	case 1:std::cout << "Podaj nazwisko: "; std::cin.ignore();std::cin.getline(pom, 256);  break;
	case 2:std::cout << "Podaj wiek: ";std::cin >> n;new_s->wiek = n;break;
	case 3:
		std::cout << "Podaj kierunek:\n0-informatyka\n1-fizyka\n2-fizyka techniczna\n3-matematyka\n4-informatyka stosowana\n";
		std::cin >> n;
		switch (n) {
		case 0: new_s->kierunek = informatyka; break;
		case 1: new_s->kierunek = fizyka; break;
		case 2: new_s->kierunek = fizyka_techniczna; break;
		case 3: new_s->kierunek = matematyka; break;
		case 4: new_s->kierunek = informatyka_stosowana; break;
		}
		break;
	}
	new_s->name = (char*)malloc(sizeof(char)*(strlen(pom) + 1));
	if (new_s == NULL) {
		my_error(MEM_ALLOC_ERROR);
	}
	strcpy(new_s->name, pom);
	std::cout << std::endl << pom;
	system("cls");
	return new_s;
}

void My_Student_print(void*arg) {
	if (arg != NULL) {
		struct My_Student* pom = (struct My_Student*)arg;
		std::cout << "Nazwisko: " << pom->name << ", wiek: " << pom->wiek << ", kierunek: ";
		switch (pom->kierunek) {
		case 0: std::cout << "informatyka"; break;
		case 1: std::cout << "fizyka"; break;
		case 2: std::cout << "fizyka techniczna"; break;
		case 3: std::cout << "matematyka"; break;
		case 4: std::cout << "informatyka stosowana"; break;
		}
		std::cout << std::endl;
	}
}

void My_Student_save(void * arg, FILE* plik) {
	struct My_Student* pom = (struct My_Student*)arg;
	int poma = pom->kierunek;
	size_t size_name = strlen(pom->name);
	fwrite(&size_name, sizeof(int), 1, plik);
	fwrite(pom->name,sizeof(char) , size_name, plik);
	fwrite(&pom->wiek, sizeof(int), 1, plik);
	fwrite(&poma, sizeof(int), 1, plik);
	////SF to jest zapis sformatowany - tworzy się plik tekstowy, a nie binarny.
	//W zadaniu bylo - plik binarny, zapis/odczyt - na dolnym poziomie (niesformatowany).
}

void* My_Student_load(FILE* plik) {
	struct My_Student* pom = NULL;
	
	int size_name; ////SF to jest odczyt sformatowany
	fread(&size_name, sizeof(int), 1, plik);
	
		pom = (struct My_Student*)malloc(sizeof(struct My_Student));
		if (pom == NULL) {
			my_error(MEM_ALLOC_ERROR);
		}

		pom->name = (char*)malloc(sizeof(char)*(size_name + 1));
		if (pom->name == NULL) {
			my_error(MEM_ALLOC_ERROR);
		}
		int aaa = 0;
		memset(pom->name, 0, size_name + 1);
		fread(pom->name, sizeof(char), size_name, plik);
		fread(&pom->wiek, sizeof(int), 1, plik);
		fread(&aaa, sizeof(int), 1, plik);
		switch (aaa) {
		case 0: pom->kierunek = informatyka; break;
		case 1: pom->kierunek = fizyka; break;
		case 2: pom->kierunek = fizyka_techniczna; break;
		case 3: pom->kierunek = matematyka; break;
		case 4: pom->kierunek = informatyka_stosowana; break;
		}
	
	
	return (void*)pom;
}

My_Student* My_Student_init() {
	system("cls");
	std::cin.ignore();
	int w;
	char pom[256];
	memset(pom, 0, 256);
	enum Kierunek kr = total;
	std::cout << "Podaj nazwisko studenta:\n";
	std::cin.getline(pom, 256);
	std::cout << "Podaj wiek studenta:\n";
	std::cin >> w;
	std::cout << "Wybierz kierunek\n";
	for (int i = 0;i < kr;i++) {
		std::cout << i << ": ";
		switch (i) {
		case 0: std::cout << "informatyka\n"; break;
		case 1: std::cout << "fizyka\n";break;
		case 2: std::cout << "fizyka techniczna\n";break;
		case 3: std::cout << "matematyka\n";break;
		case 4: std::cout << "informatyka stosowana\n";break;
		}
	}
	My_Student* new_s = (My_Student*)malloc(sizeof(My_Student));
	if (new_s == NULL) {
		my_error(MEM_ALLOC_ERROR);
	}
	new_s->name = (char*)malloc(sizeof(char)*(strlen(pom) + 1));
	if (new_s->name == NULL) {
		my_error(MEM_ALLOC_ERROR);
	}
	strcpy(new_s->name, pom);
	new_s->wiek = w;
	std::cin >> w;
	switch (w) {
	case 0: new_s->kierunek = informatyka; break;
	case 1: new_s->kierunek = fizyka; break;
	case 2: new_s->kierunek = fizyka_techniczna; break;
	case 3: new_s->kierunek = matematyka; break;
	case 4: new_s->kierunek = informatyka_stosowana; break;
	}
	std::cin.ignore();
	return new_s;
}
void My_Student_delete(void* st) {
	if (st != NULL) {
		struct My_Student* student = (struct My_Student*)st;
		if (student->name) {
			free(student->name);
		}
		free(student);
	}
}