#include <iostream>
#include <string>
#include "me_word.h"
#include "me_line.h"
#include "misc.h"

int main(int argc, char const *argv[]) {
	std::string str;
	str = "fuck";
	if(is_number(str.c_str())){
		std::cout << "Is Number" << '\n';
	} else {
		std::cout << "Not Number" << '\n';
	}
	Me_word test("me", 6, 20);
	std::cout << test << '\n';
	return 0;
}
