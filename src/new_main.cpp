#include <iostream>
#include <string>
#include "Me_word.h"
#include "Me_line.h"
#include "misc.h"

int main(int argc, char const *argv[]) {
	std::string str;
	str = "fuck";
	if(is_number(str.c_str())){
		std::cout << "Is Number" << '\n';
	} else {
		std::cout << "Not Number" << '\n';
	}
	Me_line ln_test("me muh me muh muh muh muh", 3);
	std::cout << ln_test << '\n';
	return 0;
}
