#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#define NUM_OF_OPS 6

using namespace std;

bool is_number(const string& str){
	return !str.empty() && find_if(str.begin(), str.end(), [](char ch) { return !isdigit(ch); }) == str.end();
}

std::string random_insult(int strength){
	std::string insult = "you";
	std::string temp = "";
	int x;
	int i;
	//makes insult length is strength
	for(i=0; i<strength; i++){
		// dowhile loop used to ensure there are no doubles in the insult
		do{
			x = rand() % 12;
			switch (x) {
				case 0:  temp = " Fucking";   break;		case 5:  temp = " Trump"; break;
				case 1:  temp = " enchilada"; break;		case 6:  temp = " Idiot"; 				break;
				case 2:  temp = " Jerry"; 		break;		case 7:  temp = " Piss head"; 		break;
				case 3:  temp = " Fattie"; 		break;		case 8:  temp = " Cunt"; 					break;
				case 4:  temp = " Stupid"; 		break;		case 9:  temp = " Shithead"; 			break;
				case 10: temp = " Drugoo"; 		break;		case 11: temp = " Captalist Pig"; break;
			}
		}while(insult.find(temp) != std::string::npos);
		insult += temp;
	}
	return insult;
}
//each word is a me_word
class me_word {
	public:
		//stores the stirng
		std::string word;
		std::string action;
		me_word(std::string str, int wordNumAss, int cellNumAss){
			word = str;
			wordNum = wordNumAss;
			cellNum = cellNumAss;
			//checks if word is a number
			if(is_number(str)){
				action = word;
			} else {
				action = get_action();
			}
		}
		std::string info(){
			std::stringstream result;
			result << "WORD:" << word << " NUM:" << wordNum << " CELLNUM:" << cellNum << " ACTION:" << action;
			return result.str();
		}
	private:
		int wordNum;
		int cellNum;
		std::string get_action(){
			std::string str;
			//based on word and wordNumber retruns the apporite tokken
			if(word == "me"){
				str = "ary["+to_string(cellNum)+"]";
			} else {
				switch (wordNum) {
					case 0: str = "="; break;		case 1: str = "+"; break;
					case 2: str = "-"; break;		case 3: str = "*"; break;
					case 4: str = "/"; break;		case 5: str = "%"; break;
					case 6: str = "printf(\"%c\", ary[" + to_string(cellNum-1) + "])"; break;
				}
			}
			return str;
		}
};
//each line contains many words
class me_line {
	public:
		bool sucess;
		std::string output;
		me_line(std::string str, int assLineNum){
			line = str;
			lineNum = assLineNum;
			output = "";
			//onlt matchs muh me and numbers
			std::regex phrase ("(muh)|(me)|([0-9][^ ]+)");
			int wordNum = 0;
			int cellNum = 0;
			std::regex_search(line.c_str(), phrase);
			//Loops though matchs
			for(std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), phrase);
			i != std::sregex_iterator(); ++i){
				std::smatch match = *i;
				//creates a word with the appotie wordNum and cellNum
				me_word tempWord(match.str(), wordNum, cellNum);
				words.push_back(tempWord);
				//Increments CellNum and or wordNum apporitely
				if(match.str() == "me"){
					wordNum = 0;
					cellNum++;
				} else {
					if(wordNum>NUM_OF_OPS){
						wordNum = 0;
					} else {
						wordNum++;
					}
				}
			}
			// std::cout << "Cleaned String" << '\n';
			//removes unsessarcy words then gerates the C Code
			sucess = clean_string() && get_output();
		};
		std::string info(){
			std::stringstream result;
			result << "LINE:" << lineNum << " " << line << "\n";
			for(auto element : words){
				result << element.info() << "\n";
			}
			return result.str();
		}
	private:
		std::string line;
		int lineNum;
		std::vector<me_word> words;
		int clean_string(){
			unsigned int i;
			if(words.size() >= 2){
				// std::cout << "size: "<< words.size() << '\n';
				//checks that the first word is me
				if(words[0].word != "me"){
					std::cout << "ERROR@ln " << lineNum << ": MISSING STARTING ME " << random_insult(rand()%5+2) <<'\n';
					return 0;
				}
				//removes all but the last word
				for(i=0; i<words.size()-1; /*std::cout << i << "<" << words.size()-2 << '\n'*/){
					// std::cout << "words[" << i << "]" << words[i].word << "== words[" << i << "]" << words[i+1].word  <<  '\n';
					if(words[i].word == words[i+1].word){
						// std::cout << "Delteing " << i << "\n";
						words.erase(words.begin()+i);
						i=0;
					} else {
						i++;
					}
				}
				// ERROR CHECKING NEEDS WORK!!!
				//checks that the last word is not me
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
		int get_output(){
			unsigned int i;
			std::regex regAry ("(ary\\[[0-9]\\])");
			std::regex regOut ("(printf.*)");
			// std::cout << lineNum << '\n';
			std::stringstream str;
			str << "\t" << "//Line Num:" << lineNum << " Code:" << line << "\n" << "\t";
			for(i=0; i<words.size(); i++){
				if(std::regex_match(words[i].action, regAry)){
					if(std::regex_search(words[i+1].action, regOut)){
						str << words[++i].action << ";" << "\n\t";
					} else {
						str << words[i].action;
						if(words[i+1].action != "="){
							str << words[++i].action << "=";
						} else {
							str << words[++i].action;
						}
						str << words[++i].action;
						str << ";" << '\n' << "\t";
					}
				}
			}
			str << '\n';
			output = str.str();
			return 1;
		}
};

class me_code {
	public:
		std::vector<me_line> lines;
		unsigned long int nom; //number of me's
		//adds a line to the code
		int add_line(std::string line){
			me_code::get_me(line);
			me_line tempLine(line, lineNum);
			lineNum++;
			if(tempLine.sucess){
				lines.push_back(tempLine);
				return 1;
			}
			return 0;
		}
		void print_all(){
			std::stringstream str;
			for(auto element : lines){
				str << element.info();
			}
			std::cout << str.str() << '\n';
		}
		void get_me(std::string str){
			std::regex phrase ("(me)");
			std::smatch match;
			unsigned long int temp = 0;
			std::regex_search(str.c_str(), phrase);
			for(std::sregex_iterator i = std::sregex_iterator(str.begin(), str.end(), phrase);
			i != std::sregex_iterator(); ++i){
				temp++;
			}
			// std::cout << temp << " matches found:" << std::endl;
			if(temp > nom){
				nom = temp;
			}
		}
		me_code(){
			nom = 0;
			lineNum = 1;
		}
	private:
		int lineNum;
};

class in_me_file {
	public:
		std::string name;
		std::ifstream file;
		//returns number of lines in file
		int lines(){
			int numLine = 0;
			if (file.is_open()){
				file.seekg (0, file.beg);
				std::string temp;
				while(std::getline(file, temp)){
					numLine++;
				}
				file.clear();
				file.seekg (0, std::ios::beg);
				return numLine;
			}
			return 0;
		};
		//assigns a name to the file with the apptorite File ending
		int assign_name(string str){
			name = str;
			std::cout << name << '\n';
			return 1;
		}
		//opens the file
		int open(){
			file.open(name.c_str());
			if(file.is_open()){
				return 1;
			}
			std::cout << "Unable to open " << name << endl;
			return 0;
		}
		//checks if open
		int is_open(){
			if(file.is_open()){
				return 1;
			}
			return 0;
		}
		void close(){
			file.close();
		}
		int read(me_code *code){
			std::string line;
			std::string::size_type sz;
			std::cout << "reading " << name << " with a total of " << lines() << " Lines " << std::endl;
			while(std::getline(file, line)){
				code->add_line(line);
			}
			close();
			return 1;
		}
		in_me_file(){

		};
};

class out_me_file {
	public:
		std::string cName;
		std::string exName;
		std::ofstream file;
		//assigns a name to the file with the apptorite File ending
		int assign_name(string str){
			cName = str;
			if (str.find(".\\") != string::npos){
				str = str.substr(2, str.length());
			}
			if (str.find(".") != string::npos){
				cName = str.substr(0, str.find("."));
			} else {
				cName = str;
			}
			exName = cName + ".exe";
			cName += ".c";
			std::cout << cName << '\n';
			return 1;
		}
		//opens the file
		int open(){
			file.open(cName.c_str());
			if(file.is_open()){
				return 1;
			}
			cout << "Unable to open " << cName << endl;
			return 0;
		}
		int write(me_code const code){
			file.open(cName.c_str());
			std::cout << '\n' << "Writing to File" << '\n';
			if (file.is_open()) {
				file << "#include<stdio.h>" << "\n";
				file << "int main(void){" << "\n";
				file << "\t" << "char ary[" << code.nom << "]; \n";
				for(auto element: code.lines){
					file  << element.output;
				}
				file << "}";
				file.close();
			}
			return 1;
		}
		out_me_file(){

		};
};

class intr_options {
	public:
		in_me_file inFile;
		out_me_file outFile;
		int muhterpret(){
			if(inFile.read(&code)){
				code.print_all();
				if(outFile.write(code)){
					std::cout << "Finshed creaing C File" << '\n';
					compile(outFile.cName, outFile.exName);
					return 1;
				}
			}
			return 0;
		}

	private:
		me_code code;
		void compile(std::string cName, std::string exName){
			std::stringstream command;
			command << "gcc " << cName << " -o " << exName;
			// std::cout << command.str() << '\n';
			system(command.str().c_str());
		}
};

int get_parma(int argc, char *argv[], intr_options *options){
	string strTemp;
	int i=1;
	if (argc >= 2){
		options->inFile.assign_name(argv[i]);
		if (argc >= 3){
			i++;
		}
		options->outFile.assign_name(argv[i]);
		options->inFile.open();
		return options->inFile.is_open();
	} else {
		cout << "must select input file" << endl;
	}
	return 0;
}

int main(int argc, char *argv[]){
	srand (time(NULL));
	intr_options options;
	if (get_parma(argc, argv, &options)){
		options.muhterpret();
	}

	return 0;
}
