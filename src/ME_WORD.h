#ifndef ME_WORD_H
#define ME_WORD_H
	#include <string>
	#include <iostream>
	#include "me_word.cpp"
	class Me_word {
		public:
			std::string word;
			std::string action;
			Me_word(std::string str, int wordNumAss, int cellNumAss);
			friend std::ostream & operator<<(std::ostream &os, const Me_word &object);
			std::string info();
		private:
			enum E_Type {EQL, PUS, MUN, MUL, DIV, MOD, PRT, ACS, NUM, INV};
			E_Type type;
			int wordNum;
			int cellNum;
			std::string get_action(std::string word);
			E_Type get_type(std::string word);
	};
#endif
