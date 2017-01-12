#ifndef ME_WORD_H
#define ME_WORD_H
	#include <iostream>
	#include <string>
	class Me_word {
		public:
			enum E_Type {ME, MUH, NUMBER};
			E_Type get_type();
			std::string action;
			Me_word(std::string str, int wordNumAss, int cellNumAss);
			friend std::ostream & operator<<(std::ostream &os, Me_word &object);
			std::string info();
		private:
			E_Type type;
			std::string E_Type_to_string(E_Type toFind);
			int wordNum;
			int cellNum;
			std::string get_action(std::string word);
			E_Type get_type(std::string word);
	};
#endif
