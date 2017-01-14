#include <iostream>
#include <string>
#include <fstream>
#include "misc.h"
#include "Me_word.h"
#include "Me_line.h"
#include "Me_code.h"

void compile_c_file(std::string cName, std::string exName){
	std::stringstream command;
	command << "gcc " << cName << " -o " << exName;
	// std::cout << command.str() << '\n';
	system(command.str().c_str());
}

void write_to_output_file(std::ofstream &outFile, Me_code &code){
	std::cout << '\n' << "Writing to File" << '\n';
	if (outFile.is_open()) {
		outFile << "#include<stdio.h>" << "\n";
		outFile << "int main(void){" << "\n";
		outFile << "\t" << "char ary[" << code.out_number_of_me() << "]; \n";
		outFile  << code.output();
		outFile << "}";
	}
}

std::string isloate_file_name(const char *assFileName){
	std::string fileName;
	fileName = assFileName;
	if (fileName.find(".\\") != std::string::npos){
		fileName = fileName.substr(2, fileName.length());
	}
	if (fileName.find(".") != std::string::npos){
		fileName = fileName.substr(0, fileName.find("."));
	}
	return fileName;
}

std::string get_exe_file_name(const char *assFileName){
	std::string fileName;
	fileName = isloate_file_name(assFileName);
	fileName += ".exe";
	return fileName;
}

std::string get_c_file_name(const char *assFileName){
	std::string fileName;
	fileName = isloate_file_name(assFileName);
	fileName += ".c";
	return fileName;
}

void genrate_output_file(const char *fileName, Me_code &code){
	std::ofstream outFile;
	outFile.open(get_c_file_name(fileName).c_str());
	write_to_output_file(outFile, code);
	outFile.close();
	std::cout << "Finshed creaing C File called " << fileName << '\n';
	compile_c_file(get_c_file_name(fileName), get_exe_file_name(fileName));
}

void read_input_file(const char *fileName, Me_code &code){
	std::ifstream inputFile;
	inputFile.open(fileName);
	if(!inputFile.good()){
		throw "Unable to open file";
	}
	std::string line;
	std::cout << "reading " << fileName << std::endl;
	while(std::getline(inputFile, line)){
		code.add_line(line);
	}

	inputFile.close();
}

int muhterpret(const char *fileName){
	Me_code code;
	try {
		read_input_file(fileName, code);
	} catch (const char *errorUnableToOpenFile) {
		std::cout << errorUnableToOpenFile << '\n';
	}
	std::cout << code.info();
	genrate_output_file(fileName, code);
	return 0;
}


int main(int argc, char const *argv[]) {
	Me_code code;
	muhterpret(argv[1]);
	std::cout << code << '\n';
	return 0;
}
