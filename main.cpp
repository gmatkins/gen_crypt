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

typedef unsigned short int byte;
typedef byte nibble;

byte hexToByte(char* hexVal); //x
byte charToByte(char charVal); //x
byte nibblesToByte(nibble lNibble, nibble rNibble); //x
char nibblesToChar(nibble lNibble, nibble rNibble); //x

void encipher(char& plainText, byte& key); //x
void decipher(char& cipherText, byte& key); //x

void sBox(nibble& text, int key); //x

void XORwithKey(nibble& in, nibble key); //x

void getNibblesFromByte(byte in, nibble& lNibble, nibble& rNibble); //x

void shiftIntoKey(byte& key, byte plainText); //x


int main(int argc, char** argv){
    nibble rKeyNibble=0, lKeyNibble=0;
    byte key;
    fstream inFile, outFile;
    char processing;
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
    key = hexToByte(argv[2]);
    getNibblesFromByte(key, lKeyNibble, rKeyNibble);
    if (strcmp(fileName + strlen(fileName) - 4, ".gnc") == 0){
       //gen_crypt produces a plain text file from the .gnc file
       inFile.open(fileName, fstream::in);
       outFile.open("plain.txt", fstream::out);
       cout << "Decipher!" << endl;
       while(inFile){
                      inFile >> processing;
                      cout << processing << " ";
                      decipher(processing, key);
                      cout << processing << endl;
                      outFile << processing;
       }
    }
    else{
         inFile.open(fileName, fstream::in);
       outFile.open("cipher.gnc", fstream::out);
       cout << "Encipher!" << endl;
       while(inFile){
                      inFile >> processing;
                      cout << processing << " ";
                      encipher(processing, key);
                      cout << processing << endl;
                      outFile << processing;
       }    
    }
	return 0;
}

//This funciton converts a two byte hexadecimale value into an
//integer value. Assumes ASCII values.
byte hexToByte(char* hexVal){
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

byte charToByte(char charVal){
        return (int)charVal;
}

//This function divides a byte into the most sig(left) and least
//sig(right) four-bit value.
void getNibblesFromByte(byte in, nibble& lNibble, nibble& rNibble){
     //cout << in << endl;
     lNibble = in/16;
     rNibble = in%16;
     return;     
}

//This is a substitution function which maps the input plaintext onto
//an output ciphertext in a fashion dependent on a key nibble
void sBox(nibble& text, nibble key){
     static nibble sBox[16][16] = {
            {13, 6, 14, 7, 5, 4, 1, 3, 11, 12, 15, 8, 9, 0, 2, 10},
            {6, 11, 7, 13, 10, 9, 0, 2, 12, 5, 4, 1, 8, 3, 15, 14},
            {8, 10, 13, 7, 6, 12, 4, 3, 0, 14, 1, 15, 5, 2, 9, 11},
            {6, 5, 3, 2, 11, 1, 0, 15, 12, 10, 9, 4, 8, 14, 13, 7},
            {10, 13, 5, 7, 9, 2, 14, 3, 11, 4, 0, 8, 15, 1, 6, 12},
            {13, 4, 9, 14, 1, 10, 15, 8, 7, 2, 5, 12, 11, 0, 3, 6},
            {3, 2, 1, 0, 14, 12, 11, 9, 15, 7, 13, 6, 5, 10, 4, 8},
            {6, 5, 12, 10, 7, 1, 0, 4, 15, 11, 3, 9, 2, 14, 13, 8},
            {13, 4, 10, 5, 1, 3, 9, 8, 7, 6, 2, 14, 15, 0, 11, 12},
            {6, 9, 5, 14, 15, 2, 0, 13, 10, 1, 8, 12, 11, 7, 3, 4},
            {12, 13, 11, 8, 5, 4, 10, 9, 3, 7, 6, 2, 0, 1, 15, 14},
            {6, 5, 15, 13, 9, 1, 0, 10, 11, 4, 7, 8, 14, 3, 12, 2},
            {7, 13, 8, 11, 5, 4, 15, 0, 2, 10, 9, 3, 14, 1, 12, 6},
            {13, 11, 6, 12, 15, 10, 2, 8, 7, 14, 5, 1, 3, 0, 9, 4},
            {11, 6, 8, 14, 9, 10, 1, 12, 2, 4, 5, 0, 7, 15, 3, 13},
            {15, 4, 7, 10, 1, 6, 5, 2, 12, 13, 3, 14, 8, 9, 11, 0}
            };
     text = sBox[key][text];
     return;     
}

void XORwithKey(nibble& in, nibble key){
     in = in^key;
     return;     
}

//shift the key two bits left, discard the two most sig bits,
//and pad with two bits of plaintext on the right side
void shiftIntoKey(byte& key, byte plainText){
     key = (key*4)%256;
     plainText = plainText%4;
     key += plainText;
     return;
}

char nibblesToChar(nibble lNibble, nibble rNibble){
     return static_cast<char>(16*lNibble + rNibble);
}

byte nibblesToByte(nibble lNibble, nibble rNibble){
     return 16*lNibble + rNibble;
}



void encipher(char& plainText, byte& key){
     nibble lKey, rKey;
     nibble lText, rText;
     byte plain = charToByte(plainText);
     getNibblesFromByte(key, lKey, rKey);
     getNibblesFromByte(plain, lText, rText);
     sBox(lText, lKey);
     sBox(rText, rKey);
     XORwithKey(lText, rKey);
     XORwithKey(rText, lKey);
     //shiftIntoKey(key, plain);
     plainText = nibblesToChar(lText, rText);
     return;     
}

void decipher(char& cipherText, byte& key){
     nibble lKey, rKey;
     nibble lText, rText;
     byte plain;
     byte cipher = charToByte(cipherText);
     getNibblesFromByte(key, lKey, rKey);
     getNibblesFromByte(cipher, lText, rText);
     XORwithKey(lText, rKey);
     XORwithKey(rText, lKey);
     sBox(lText, lKey);
     sBox(rText, rKey);
     plain = nibblesToByte(lText, rText);
     //shiftIntoKey(key, plain);
     return;
}
