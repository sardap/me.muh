#ifndef ME_LINE_H
#define ME_LINE_H
	#include <string>
	#include <iostream>
	#include <vector>
	#include "me_word.h"
	class Me_line {
		public:
			bool sucess;
			std::string output;
			Me_line(std::string str, int assLineNum);
			std::string info();
			friend std::ostream & operator<<(std::ostream &os, const Me_line &object);
		private:
			std::string line;
			int lineNum;
			std::vector<Me_word> words;
			int clean_string();
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
#endif
