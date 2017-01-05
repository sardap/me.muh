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
			int check_line();
			int clean_string();
			int get_output();
	};
#endif
