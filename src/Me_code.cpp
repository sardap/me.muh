#include "Me_code.h"

unsigned long int Me_code::count_me_in_line(std::string line){
	std::regex phrase("(me)");
	std::smatch match;
	unsigned long int lineMe;
	lineMe = 0;
	std::regex_search(line.c_str(), phrase);
	for (std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), phrase); i != std::sregex_iterator(); ++i) {
		lineMe++;
	}
	// std::cout << temp << " matches found:" << std::endl;
	return lineMe;
}

void Me_code::add_line(std::string line){
	if(count_me_in_line(line) > numberOfMe){
		numberOfMe = count_me_in_line(line);
	}
	Me_line tempLine(line, lineNum);
	lineNum++;
	if (tempLine.vaild) {
		lines.push_back(tempLine);
	}
}

std::string Me_code::out_number_of_me(){
	std::stringstream result;
	result << numberOfMe;
	return result.str();
}

std::string Me_code::output(){
	std::stringstream result;
	for(auto element: lines){
		result  << element.output;
	}
	return result.str();
}

std::string Me_code::info(){
	std::stringstream result;
	for (auto element : lines) {
		result << element.info();
	}
	return result.str();
}

std::ostream & operator<<(std::ostream &os, Me_code &object){
	os << object.info();
	return os;
}

Me_code::Me_code(){
	numberOfMe = 0;
	lineNum = 1;
}
