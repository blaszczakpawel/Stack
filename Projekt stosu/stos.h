#pragma once
#include "stdafx.h"

struct stack {
	stack* next;
	void* elem;
};

void stack_push(void*);

void stack_print(void(*)(void*));

void * stack_pop();

void stack_free(void(*)(void*));

void stack_find(void*, bool(*)(void*, void*),void (*)(void*));

void stack_save(void(*)(void*, FILE *));

void stack_load(void* (*)(FILE*));