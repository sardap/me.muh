#include <regex>
#include <string>
#include <iostream>
#include <vector>
#include "Me_line.h"
#include "Me_word.h"
#include "misc.h"

std::string Me_line::info(){
	std::stringstream result;
	result << "LINE:" << lineNum << " " << line << "\n";
	for (auto element : words) {
		result << element.info() << "\n";
	}
	result << "output:\n" << output << '\n';
	return result.str();
}

std::ostream & operator<<(std::ostream &os, Me_line &object){
	os << object.info();
	return os;
}

std::string Me_line::print_line(){
	std::stringstream result;
	result << "ERROR@Line " << lineNum;
	return result.str();
}

int Me_line::check_line(){
	// these are the rules
	//1. There must be at least 2 words
	//2. The first word must be me
	//3. The last Cannot be me
	//4. if the last word is muh it must be closing a me
	size_t i;
	if (words.size() < 2) {
		std::cout  << print_line() << ": UNDER TWO WORDS " << random_insult(3) << '\n';
		return 0;
	}
	if (words[0].get_type() != Me_word::ME) {
		std::cout << print_line() << ": MISSING STARTING ME " << random_insult(rand()%5+2) <<'\n';
		return 0;
	}
	// ERROR CHECKING NEEDS WORK!!!
	//checks that the last word is not me
	i = words.size()-1;
	if (words[i].get_type() == Me_word::ME){
		std::cout << print_line() << ": MISSING ENDING MUH " << random_insult(rand()%5+2) <<'\n';
		return 0;
	//checks that muh is closing a me
	} else if (words[i].get_type() == Me_word::MUH) {
		if (words[i-1].get_type() != Me_word::ME) {
			std::cout  << print_line() << ": ENDING MUH WITHOUT ME " << random_insult(rand()%5+2) <<'\n';
			return 0;
		} else {
	//-------------------------FUCKING BULLSHIT-----------------------------//
			//Fix this shit a better way fucktard
			if((words.size() != 2) && (!words[i].action.find("printf"))){
				words.erase(words.begin()+i);
			}
		}
	}
	if ((words.size() > 2) && (words[words.size()-1].get_type() == Me_word::MUH)) {
		words.erase(words.begin() + words.size() - 1);
	}
	//-------------------------FUCKING BULLSHIT-----------------------------//
	return 1;
}

int Me_line::get_output(){
	unsigned int i;
	std::regex regAry ("(ary\\[[0-9]\\])");
	std::regex regOut (".*\\(*\\)");
	// std::cout << lineNum << '\n';
	std::stringstream result;
	result << "\t" << "//Line Num:" << lineNum << " Code:" << line << "\n" << "\t";
	for (i=0; i<words.size(); i++) {
		if (std::regex_match(words[i].action, regAry)) {
			if (std::regex_search(words[i+1].action, regOut)) {
				result << words[++i].action << ";" << "\n\t";
			} else {
				result << words[i].action;
				if (words[i+1].action != "=") {
					result << words[++i].action << "=";
				} else {
					result << words[++i].action;
				}
				result << words[++i].action;
				result << ";" << '\n' << "\t";
			}
		}
	}
	result << '\n';
	output = result.str();
	return 1;
}

void Me_line::clean_words_vector(){
	size_t i;
	for (i = 0; i < words.size()-1; /*std::cout << i << "<" << words.size()-2 << '\n'*/){
		// std::cout << "words[" << i << "]" << words[i].word << "== words[" << i << "]" << words[i+1].word  <<  '\n';
		if (words[i].get_type() == words[i+1].get_type()) {
			// std::cout << "Delteing " << i << " " << words.size() <<  "\n";
			words.erase(words.begin()+i);
			i = 0;
		} else {
			i++;
		}
	}
}

Me_line::Me_line(std::string str, int assLineNum){
	line = str;
	lineNum = assLineNum;
	output = "";
	//only matchs muh me and numbers
	std::regex phrase ("(muh)|(me)|(\\d+)");
	int wordNum = 0;
	int cellNum = 0;
	std::regex_search(line.c_str(), phrase);
	for (std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), phrase);
	i != std::sregex_iterator(); ++i){
		std::smatch match = *i;
		Me_word tempWord(match.str(), wordNum, cellNum);
		words.push_back(tempWord);
		if (tempWord.get_type() == Me_word::ME){
			wordNum = 0;
			cellNum++;
		} else {
			wordNum > NUM_OF_OPS ? wordNum = 0: wordNum++;
		}
	}
	clean_words_vector();
	vaild = check_line();
	if (vaild) {
		get_output();
	}

};
