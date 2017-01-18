#include<stdio.h>
int main(void){
	char ary[5]; 
	//Line Num:1 Code:me muh 83
	ary[0]=83;
	
	//Line Num:2 Code:me me me me muh 69
	ary[3]=69;
	
	//Line Num:3 Code:me muh muh muh muh muh muh muh
	printf("%c", ary[0]);
	
	//Line Num:4 Code:me me me me muh muh muh muh muh muh muh
	printf("%c", ary[3]);
	
	//Line Num:5 Code:me me me me muh muh 9
	ary[3]+=9;
	
	//Line Num:6 Code:me me me me muh muh muh muh muh muh muh
	printf("%c", ary[3]);
	
	//Line Num:7 Code:me me muh me me muh
	ary[1]=ary[3];
	
	//Line Num:8 Code:me me muh muh muh 10
	ary[1]-=10;
	
	//Line Num:9 Code:me me muh muh muh muh muh muh muh
	printf("%c", ary[1]);
	
	//Line Num:10 Code:me me me me me muh 32
	ary[4]=32;
	
	//Line Num:11 Code:me me me me me muh muh muh muh muh muh muh
	printf("%c", ary[4]);
	
	//Line Num:12 Code:me me me me muh muh muh muh muh muh muh
	printf("%c", ary[3]);
	
	//Line Num:13 Code:me muh muh 2
	ary[0]+=2;
	
	//Line Num:14 Code:me muh muh muh muh muh muh muh
	printf("%c", ary[0]);
	
	//Line Num:15 Code:me me muh muh muh muh muh muh muh
	printf("%c", ary[1]);
	
	//Line Num:16 Code:me me me me muh 69
	ary[3]=69;
	
	//Line Num:17 Code:me me me me muh muh muh muh muh muh muh
	printf("%c", ary[3]);
	
	//Line Num:18 Code:me muh muh muh 2
	ary[0]-=2;
	
	//Line Num:19 Code:me muh muh muh muh muh muh muh
	printf("%c", ary[0]);
	
}