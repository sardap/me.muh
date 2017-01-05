#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "misc.h"

int is_number(const char *str){
	while(*str){
		if(!((*str >= '0') && (*str <= '9'))){
			return 0;
		}
		str++;
	}
	return 1;
}

std::string random_insult(int strength){
	std::string insult = "you";
	std::string temp = "";
	int x;
	int i;
	//makes insult length is strength
	for(i = 0; i < strength; i++){
		// dowhile loop used to ensure there are no doubles in the insult
		do{
			x = rand() % 12;
			switch (x) {
				case 0:  temp = " Fucking";   break;	case 5:  temp = " Trump"; 		break;
				case 1:  temp = " enchilada"; break;	case 6:  temp = " Idiot"; 		break;
				case 2:  temp = " Jerry"; 	break;	case 7:  temp = " Piss head"; 	break;
				case 3:  temp = " Fattie"; 	break;	case 8:  temp = " Cunt"; 		break;
				case 4:  temp = " Stupid"; 	break;	case 9:  temp = " Shithead"; 		break;
				case 10: temp = " Drugoo"; 	break;	case 11: temp = " Captalist Pig"; 	break;
			}
		}while(insult.find(temp) != std::string::npos);
		insult += temp;
	}
	return insult;
}
