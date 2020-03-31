#include "stdafx.h"
#include "stos.h"
#include <malloc.h>
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include "My_Errors.h"

#pragma warning(disable: 4996)

static struct stack* first_elem = NULL;

void stack_push(void* new_elem) {
	if (new_elem != NULL) {
		struct stack* new_stack = (struct stack*)(malloc(sizeof(struct stack)));
		if (new_stack == NULL) {
			my_error(MEM_ALLOC_ERROR);
		}
		new_stack->elem = new_elem;
		new_stack->next = first_elem;
		first_elem = new_stack;
	}
	else {
		my_error(NEW_ELEM_IS_NULL);
	}
}

void stack_print(void  (*print_fun) (void*)) {
	if ((*print_fun) != NULL) {
		struct stack* element = first_elem;
		if (element == NULL) {
			std::cout << "Stos jest pusty, nie da sie go wyswietlic" << std::endl;
		}
		else {
			while (element != NULL) {
				(*print_fun)(element->elem);
				element = element->next;
			}
		}
	}
	else {
		my_error(NO_PRINT_FUN);
	}
}

void * stack_pop() {
	if (first_elem == NULL) {
		std::cout << "Stos pusty, nie da sie wyciagnac zadnego elementu" << std::endl;
		return NULL;
	}
	else {
		void* pom = first_elem->elem;
		struct stack* pom_s = first_elem;
		first_elem = first_elem->next;
		pom_s->next = NULL;
		pom_s->elem = NULL;
		free(pom_s);
		return pom;
	}
}
void stack_free(void(*fre)(void*)) {
	if ((*fre == NULL)) {
		my_error(NO_DEL_FUN);
	}
	else if (first_elem != NULL) {
		struct stack *pom = first_elem;
		first_elem = NULL;
		while (pom != NULL) {
			struct stack *pom_next = pom->next;
			pom->next = NULL;
			(*fre)(pom->elem);
			pom->elem = NULL;
			free(pom);
			pom = pom_next;
			pom_next = NULL;
		}
	}
	else {
		std::cout << "Nie da siê usunac pustego stosu\n";
	}
}
void stack_find(void*cp_new, bool(*cp)(void*, void*), void(*print)(void*)) {
	if(cp_new==NULL){
		my_error(NO_CP_ELEM);
	}
	else if ((*cp) == NULL) {
		my_error(NO_COMP_FUN);
	}
	else if ((*print) == NULL) {
		my_error(NO_PRINT_FUN);
	}
	else if (first_elem == NULL) {
		my_error(THERE_IS_NO_ANY_ELEM);
	}
	else {
		struct stack * pom = first_elem;
		while (pom != NULL) {
			if ((*cp)(cp_new, pom->elem)) {
				(*print)(pom->elem);
			}
			pom = pom->next;
		}
	}
}

void stack_save(void(*save)(void*, FILE *)) {
	if ((*save) == NULL) {
		my_error(NO_SAVE_FUN);
	}
	else {
		FILE * file = NULL;
		file = fopen("stos.bin", "wb");
		if (file == NULL) {
			my_error(FILE_ALLOC_ERROR);
		}
		int licz = 0;
		fwrite(&licz, sizeof(int), 1, file);
		struct stack* pom = first_elem;
		while (pom != NULL) {
			licz++;
			(*save)(pom->elem, file);
			pom = pom->next;
		}
		fseek(file, 0, SEEK_SET);
		fwrite(&licz, sizeof(int), 1, file);
		fclose(file);
	}
}

void stack_load(void* (*load)(FILE*)) {
	if (first_elem == NULL) {
		FILE * file;
		file = fopen("stos.bin", "rb");
		if (file == NULL) {
			my_error(FILE_ALLOC_ERROR);
		}
		int licz = 0;
		fread(&licz, sizeof(int), 1, file);
		if (licz > 0) {
			first_elem =(struct stack*) malloc(sizeof(struct stack));
			if (first_elem == NULL) {
				my_error(MEM_ALLOC_ERROR);
			}
			first_elem->elem = (*load)(file);
			first_elem->next = NULL;
			struct stack* pom = first_elem;
			for (int i = 1;i < licz;i++) {
				pom->next = (struct stack*) malloc(sizeof(struct stack));
				if (pom->next == NULL) {
					my_error(MEM_ALLOC_ERROR);
				}
				pom = pom->next;
				pom->next = NULL;
				pom->elem = (*load)(file);
			}
			pom = NULL;
		}
		fclose(file);
	}
	else {
		std::cout << "Nie mozna wczytac nowych elementow bo stos nie jest pusty\n";
	}
}

