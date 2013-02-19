/*******************************
*Author:Gentry Atkinson
*Date:02/13/2013
*Gen Crypt: a simple command line encryption-decryption tool
*written in c++ with Linux in mind.
*******************************/

#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>

using namespace std;

typedef unsigned char byte;
typedef byte nibble;

int hexToInt(char* hexVal);

void encipher(char* fileName, char* key);
void decipher(char* fileName, char* key);

void sBox(byte& text, int key);

void spinLeft(byte& text, int key);
void spinRight(byte& text, int key);

nibble getLeftNibble(byte in);
nibble getRightNibble(byte in);

void shiftIntoKey(char* text);


int main(int argc, char** argv){
    if (argc < 2){
       cerr << "No file specified." << endl;
       return 0;
    }
    if (argc < 3){
       cerr << "No key value specified." << endl;
       return 0;
    }
    if (argc > 3){
       cerr << "File command not recognized." << endl;
       return 0;
    }
    char * fileName = argv[1];
    if (strcmp(fileName + strlen(fileName) - 4, ".gnc") == 0)
       ;//gen_crypt produces a plain text file from the .gnc file
    else
        cout << hexToInt(argv[2]) << endl;
        //gen_crypt produces a .gnc file from the plain text
	return 0;
}

//This funciton converts a two byte hexadecimale value into an
//integer value. Assumes ASCII values.
int hexToInt(char* hexVal){
    if (strlen(hexVal) != 2){
       cerr << "Key value improper length. Two bytes, please." << endl;
       exit(0);
    }
    
    int lByte, rByte;
    lByte = static_cast<int>(hexVal[0]);
    rByte = static_cast<int>(hexVal[1]);
    toupper(lByte);
    toupper(rByte);
    if (lByte > (int)'F' || rByte > (int)'F'){
       cerr << "Hexadecimal, please" << endl;
       exit(0);
    }
    if (lByte < 58) lByte -= 48;
    if (rByte < 58) rByte -= 48;
    if (lByte > 64) lByte -= 55;
    if (rByte > 64) rByte -= 55;
    return 16*lByte + rByte; 
}
