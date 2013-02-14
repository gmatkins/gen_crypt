#include<iostream>
#include<fstream>

using namespace std;

int main(int argc, char** argv){
    if (argc < 2){
       cerr << "No file specified." << endl;
       return 0;
    }
    if (argc > 2){
       cerr << "File command not recognized." << endl;
       return 0;
    }
    char * fileName = argv[1];
	return 0;
}
