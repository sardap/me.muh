#include <iostream>
#include <string>
#include <regex>
#include "Me_word.h"
#include "misc.h"

Me_word::E_Type Me_word::get_type(){
	return type;
}

std::string Me_word::E_Type_to_string(Me_word::E_Type toFind){
	std::string result;
	switch (toFind) {
		case ME: result = "me"; break;
		case MUH: result = "muh"; break;
		case NUMBER: result = "Number"; break;
	}
	return result;
}

std::string Me_word::info(){
	std::stringstream result;
	result << "TYPE:" << E_Type_to_string(type) << " NUMBER:" << wordNum << " CELLNUM:" << cellNum << " ACTION:" << action;
	return result.str();
}

std::ostream & operator<<(std::ostream &os, Me_word &object){
	std::string str;
	os << object.info();
	return os;
}

std::string Me_word::get_action(std::string word){
	std::stringstream result;
	switch (type) {
		case ME: result << "ary[" << cellNum << "]"; break;
		case MUH :
			switch (wordNum) {
				case 0: result << "="; break;
				case 1: result << "+"; break;
				case 2: result << "-"; break;
				case 3: result << "*"; break;
				case 4: result << "/"; break;
				case 5: result << "%"; break;
				case 6: result << "printf(\"%c\", ary[" << cellNum - 1 << "])"; break;
				case 7: result << "scanf(\" %c\", &ary[" << cellNum - 1 << "])"; break;
			}
			break ;
		case NUMBER :  result << word; break;
	}
	return result.str();
}

Me_word::E_Type Me_word::get_type(std::string word){
	E_Type result;
	if (is_number(word.c_str())){
		result = NUMBER;
	} else if (word == "me"){
		result = ME;
	} else {
		((wordNum >= 0) && (wordNum <= 7))? result = MUH: throw "invaild Entry for word";
	}
	return result;
}

Me_word::Me_word(std::string word, int wordNumAss, int cellNumAss){
	wordNum = wordNumAss;
	cellNum = cellNumAss;
	try {
		type = get_type(word);
	} catch (const char *msg){
		std::cout << msg << '\n';
	}
	action = get_action(word);
}
