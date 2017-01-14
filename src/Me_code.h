#ifndef ME_CODE_H
	#define ME_CODE_H
	#include <vector>
	#include <string>
	#include <regex>
	#include "Me_line.h"
	class Me_code {
		public:
			void add_line(std::string line);
			std::string info();
			std::string output();
			std::string out_number_of_me();
			friend std::ostream & operator<<(std::ostream &os, Me_code &object);
			Me_code();
		private:
			int lineNum;
			unsigned long int numberOfMe;
			unsigned long int count_me_in_line(std::string line);
			std::vector<Me_line> lines;

	};
#endif
