#pragma once
#include <string.h>
#include <math.h>
#include <string>

std::string alaska_pass(int len) {

	std::string password = "";
	char letter = 'A';
	int number;

	for (int i = 0; i != len; i++) {
		number = rand() % 61 + (-32);

		letter += number;

		password += letter;

		letter = 'A';
	}


	return password;

}
