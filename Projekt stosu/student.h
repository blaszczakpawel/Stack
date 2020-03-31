
#include "stdafx.h"

#pragma once

enum Kierunek {
	informatyka=0,
	fizyka=1,
	fizyka_techniczna=2,
	matematyka=3,
	informatyka_stosowana=4,
	total=5
};

struct My_Student{
	char* name;  //SF proszę zamiast string uzyc char *
	//Jesli z STL uzyc std::dequeue, to wtedy niema projektu
	int wiek;
	enum Kierunek kierunek;

};

//SF nazwy funkcji powinni niesc informacje nie tylko dla autora.
bool My_Student_comparing(void* jeden, void* dwa);

void* My_Student_comparing_new();

void My_Student_print(void*arg);


void My_Student_save(void * arg, FILE*);

void* My_Student_load(FILE*);

My_Student* My_Student_init();

void My_Student_delete(void*);