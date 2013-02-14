/*******************************
*Author:Gentry Atkinson
*Date:02/13/2013
*Gen Crypt: a simple command line encryption-decryption tool
*written with Linux in mind.
*******************************/

#include<iostream>
#include<fstream>
#include<cstring>

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
    if (strcmp(fileName + strlen(fileName) - 4, ".gnc") == 0)
       //gen_crypt produces a plain text file from the .gnc file
    else
        //gen_crypt produces a .gnc file from the plain text
	return 0;
}
