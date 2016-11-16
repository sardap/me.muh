#include<iostream>
#include<fstream>
#include<string>
#include <regex>

using namespace std;

typedef struct{
	int length;
	string *value;
} stringArray;

typedef struct {
	string inFileName;
	string outFileName;
	stringArray code;
} intr_options;

int get_num_line(string inFileName){
	ifstream file(inFileName.c_str());
	int numLine = 0;
	string temp;
	while(getline(file, temp)){
		numLine++;
	}
	file.close();
	return numLine;
}

int muhterpret(intr_options *options){
	ofstream outFile(options->outFileName.c_str());
	int i;
	if(outFile.is_open()){
		for(i=0; i < options->code.length; i++){
			cout << "muhterpreting " << options->code.value[i] << "\n";
		}
	}
	return 1;
}

int read_file(intr_options *options){
	int numLine = get_num_line(options->inFileName);
	ifstream codeFile(options->inFileName.c_str());
	int i;
	string line;
	if (codeFile.is_open()){
		cout << "File Open \n";
		options->code.length = numLine;
		options->code.value = new string[options->code.length];
		for(i=0; getline(codeFile, line);i++){
			options->code.value[i] = line;
		}
		codeFile.close();
		return 1;
	}
	cout << "File Could not be opend \n";
	return 0;
}

int get_parma(int argc, char *argv[], intr_options *options){
	if (argc >= 2){
		options->inFileName = argv[1];
		if (argc == 3){
			options->outFileName = argv[2];
		} else
			if (options->inFileName.find(".") != string::npos){
				options->outFileName = options->inFileName.substr(0, options->inFileName.find("."));
			} else {
				options->outFileName = options->inFileName;
			}
			options->outFileName = options->outFileName + ".exe";
		return 1;
	} else{
		return 0;
	}
}

int main(int argc, char *argv[]){
	intr_options options;
	if (get_parma(argc, argv, &options)){
		cout << "input File " << options.inFileName << " Output File " << options.outFileName << "\n";
		if (read_file(&options)){
			cout << "File Read " << options.code.length << " lines" << "\n";
			muhterpret(&options);
		}
	} else {
		cout << "must select Input File \n";
	}
	return 0;
}
