#ifndef ME_LINE_H
	#define ME_LINE_H
	#include <string>
	#include <iostream>
	#include <vector>
	#include "Me_word.h"
	class Me_line {
		public:
			bool vaild;
			std::string output;
			Me_line(std::string str, int assLineNum);
			std::string info();
			friend std::ostream & operator<<(std::ostream &os, Me_line &object);
		private:
			std::string line;
			std::string print_line();
			int lineNum;
			std::vector<Me_word> words;
			void clean_words_vector();
			int check_line();
			int get_output();
	};
#endif
