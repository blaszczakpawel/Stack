#include "stdafx.h"
#include "My_Errors.h"
#include <iostream>



void my_error(enum MY_ERROR pom) {
	bool log = false;
	switch (pom) { //C-3 E-8 W-1
	case 0: std::cout << "C01 Memory not alloc corectly" << std::endl; log = true;break;
	case 1: std::cout << "C02 File not open corectly" << std::endl; log = true;break;
	case 2: std::cout << "E01 Print fun is NULL" << std::endl; break;
	case 3: std::cout << "E02 Save fun is NULL" << std::endl; break;
	case 4: std::cout << "E03 Load fun is NULL" << std::endl; break;
	case 5: std::cout << "E04 Compare fis NULL" << std::endl; break;
	case 6: std::cout << "C03 The data got lost" << std::endl; log = true; break;
	case 7: std::cout << "E05 New element is NULL, this element can`t be push to stack" << std::endl; break;
	case 8: std::cout << "E06 Stack is empty" << std::endl; break;
	case 9: std::cout << "W01 You can`t load stack if it isn`t empty" << std::endl; break;
	case 10: std::cout << "E07 Delete fun is NULL" << std::endl; break;
	case 11: std::cout << "E08 Compare element is NULL" << std::endl; break;
	}
	if (log) {
		exit(1);
	}
}