#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <map>
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
		me_word(std::string str, int wordNumAss, int cellNumAss){
			word = str;
			wordNum = wordNumAss;
			cellNum = cellNumAss;
			//checks if word is a number
			if(is_number(str)){
				action = "num";
			} else {
				action = get_action();
			}
		}
		std::string info(){
			std::stringstream result;
			result << "WORD:" << word << " NUM:" << wordNum << " CELLNUM:" << cellNum << " ACTION:" << action;
			return result.str();
		}
		void set_end(){
			action = "END";
		}
	private:
		int wordNum;
		int cellNum;
		std::string action;
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
					case 6: str = "printf(\"%c\", ary[" + to_string(cellNum) + "]);\n"; break;
				}
			}
			return str;
		}
};
//each line contains many words
class me_line {
	public:
		me_line(std::string str, int assLineNum){
			line = str;
			lineNum = assLineNum;
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
			std::cout << "Cleaned String" << '\n';
			//Not sure how to handle erros :/
			if(!clean_string()){
				// exit(EXIT_FAILURE);
			} else {
				//prints all of the words in the line
				for(auto element : words){
					std::cout << element.info() << "\n";
				}
				// std::cout << '\n';
			}
		};
	private:
		std::string line;
		int lineNum;
		std::vector<me_word> words;
		int clean_string(){
			unsigned int i;
			if(words.size() >= 2){
				std::cout << "size: "<< words.size() << '\n';
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
				//checks that the last word is muh then sets to END
				if(words[i].word == "muh"){
					words[i].set_end();
				} else {
					std::cout << "ERROR@ln " << lineNum << ": MISSING ENDING MUH " << random_insult(5) <<'\n';
					return 0;
				}
			} else {
				std::cout << "ERROR@ln" << lineNum << ": UNDER TWO WORDS " << random_insult(3) << '\n';
				return 0;
			}
			return 1;
		}
};

class me_code {
	public:
		//adds a line to the code
		int add_line(string line){
			me_line tempLine(line, lineNum);
			lineNum++;
			lines.push_back(tempLine);
			return 1;
		}
		me_code(){
			lineNum = 1;
		}
	private:
		int lineNum;
		std::vector<me_line> lines;
};

class me_file {
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
			switch(type){
				case 'i':
					name = str;
					break;
				case 'o':
					if (str.find(".\\") != string::npos){
						str = str.substr(2, str.length());
					}
					if (str.find(".") != string::npos){
						name = str.substr(0, str.find("."));
					} else {
						name = str;
					}
					name += ".c";

			}
			std::cout << name << '\n';
			return 1;
		}
		//opens the file
		int open(){
			file.open(name.c_str());
			if(file.is_open()){
				return 1;
			}
			cout << "Unable to open " << name << endl;
			return 0;
		}
		//checks if open
		int is_open(){
			if(file.is_open()){
				return 1;
			}
			return 0;
		}
		me_file(char typeAss): type(typeAss) {};
	private:
		char type;
};

class ca_intr_options {
	public:
		me_file inFile {'i'};
		me_file outFile {'o'};
		me_code code;
		int read_file(){
			std::string line;
			std::string::size_type sz;
			while(std::getline(inFile.file, line)){
				std::cout << '\n' << line << '\n';
				code.add_line(line);
			}
			return 0;
		}
};

int get_parma(int argc, char *argv[], ca_intr_options *options){
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
	ca_intr_options options;
	if (get_parma(argc, argv, &options)){
		cout << "reading " << options.inFile.name << " with a total of " << options.inFile.lines() << " Lines " << endl;
		options.read_file();
	}

	return 0;
}
