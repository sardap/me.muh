#include <iostream>
#include <string>
#include <regex>
#include "me_word.h"
#include "misc.h"

std::string Me_word::info(){
	std::stringstream result;
	result << "NUM:" << wordNum << " CELLNUM:" << cellNum << " ACTION:" << action;
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
		case EQL: result << "="; break;	case PUS: result << "+"; break;
		case MUN: result << "-"; break;	case MUL: result << "*"; break;
		case DIV: result << "/"; break;	case MOD: result << "%"; break;
		case PRT: result << "printf(\"%c\", ary[" << cellNum - 1 << "])"; break;
		case NUM: result << word; break;	case INV: result << "INVAILD"; break;
		case ACS: result << "ary[" << cellNum << "]";
	}
	return result.str();
}

Me_word::E_Type Me_word::get_type(std::string word){
	if (is_number(word.c_str())){
		return NUM;
	} else if (word == "me"){
		return ACS;
	} else {
		switch (wordNum) {
			case 0: return EQL; break;	case 1: return PUS; break;
			case 2: return MUN; break;	case 3: return MUL; break;
			case 4: return DIV; break;	case 5: return MOD; break;
			case 6: return PRT; break;	default: return INV; break;
		}
	}
}

Me_word::Me_word(std::string assWord, int wordNumAss, int cellNumAss){
	word = assWord;
	wordNum = wordNumAss;
	cellNum = cellNumAss;
	type = get_type(word);
	action = get_action(word);
}
