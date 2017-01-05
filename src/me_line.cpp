#include "me_line.h"
#include "me_word.cpp"
#include "misc.cpp"

Me_line::Me_line(std::string str, int assLineNum){
	line = str;
	lineNum = assLineNum;
	output = "";
	//onlt matchs muh me and numbers
	std::regex phrase ("(muh)|(me)|(\\d+)");
	int wordNum = 0;
	int cellNum = 0;
	std::regex_search(line.c_str(), phrase);
	//Loops though matchs
	for(std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), phrase);
	i != std::sregex_iterator(); ++i){
		std::smatch match = *i;
		//creates a word with the appotie wordNum and cellNum
		Me_word tempWord(match.str(), wordNum, cellNum);
		words.push_back(tempWord);
		//Increments CellNum and or wordNum apporitely
		if(match.str() == "me"){
			wordNum = 0;
			cellNum++;
		} else {
			if(wordNum > NUM_OF_OPS){
				wordNum = 0;
			} else {
				wordNum++;
			}
		}
	}
	// std::cout << "Cleaned String" << '\n';
	//removes unsessarcy words then gerates the C Code
	sucess = clean_string() && check_line() && get_output();
};

std::string Me_line::info(){
	std::stringstream result;
	result << "LINE:" << lineNum << " " << line << "\n";
	for(auto element : words){
		result << element.info() << "\n";
	}
	return result.str();
}

std::ostream & operator<<(std::ostream &os, Me_line &object){
	std::string str;
	os << object.info();
	return os;
}

int Me_line::clean_string(){
	size_t i;
	for(i = 0; i < words.size()-1; /*std::cout << i << "<" << words.size()-2 << '\n'*/){
		// std::cout << "words[" << i << "]" << words[i].word << "== words[" << i << "]" << words[i+1].word  <<  '\n';
		if(words[i].word == words[i+1].word){
			// std::cout << "Delteing " << i << "\n";
			words.erase(words.begin()+i);
			i=0;
		} else {
			i++;
		}
	}
	return 1;
}

int Me_line::check_line(){
	// these are the rules
	//1. There must be at least 2 words
	//2. The first word must be me
	//3. The last Cannot be me
	//4. if the last word is muh it must be closing a me
	size_t i;
	if(words.size() >= 2){
		// std::cout << "size: "<< words.size() << '\n';
		//checks that the first word is me
		if(words[0].word != "me"){
			std::cout << "ERROR@ln " << lineNum << ": MISSING STARTING ME " << random_insult(rand()%5+2) <<'\n';
			return 0;
		}
		// ERROR CHECKING NEEDS WORK!!!
		//checks that the last word is not me
		i = words.size()-1;
		if(words[i].word == "me"){
			std::cout << "ERROR@ln " << lineNum << ": MISSING ENDING MUH " << random_insult(rand()%5+2) <<'\n';
			return 0;
		//checks that muh is closing a me
		} else if(words[i].word == "muh"){
			if(words[i-1].word != "me"){
				std::cout << "ERROR@ln " << lineNum << ": ENDING MUH WITHOUT ME " << random_insult(rand()%5+2) <<'\n';
				return 0;
			} else {
				//Fix this shit a better way fucktard
				if((words.size() != 2) && (!words[i].action.find("printf"))){
					words.erase(words.begin()+i);
				}
			}
		}

	} else {
		std::cout << "ERROR@ln" << lineNum << ": UNDER TWO WORDS " << random_insult(3) << '\n';
		return 0;
	}
	return 1;
}

int Me_line::get_output(){
	unsigned int i;
	std::regex regAry ("(ary\\[[0-9]\\])");
	std::regex regOut ("(printf.*)");
	// std::cout << lineNum << '\n';
	std::stringstream result;
	result << "\t" << "//Line Num:" << lineNum << " Code:" << line << "\n" << "\t";
	for(i=0; i<words.size(); i++){
		if(std::regex_match(words[i].action, regAry)){
			if(std::regex_search(words[i+1].action, regOut)){
				result << words[++i].action << ";" << "\n\t";
			} else {
				result << words[i].action;
				if(words[i+1].action != "="){
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
