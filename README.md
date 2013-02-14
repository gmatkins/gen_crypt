gen-crypt
Author:Gentry Atkinson
Date: 02/13/2013
Last Modified: 02/14/2013

Introduction:

This is a simple command line encryption tool using an 8-bit key. As such, it's not particularly secure and was written as an exercise. Feel free to distribute and reuse with attribution to the original source.

Encrypting a file:

From the command line type 'gen-crypt' followed by the path and name of a file. This will work with abritrary file types. The program will produce a second file with the same root name as the original with '.gnc' appended to the end. The original file will be left unchanged.

	Example: gen-crypt ~/folder/file

Decrypting a file:

From the command line type 'gen-crypt' followed by the name of a file ending with '.gnc'. A new file will be created with the same root name as the encrypted file with the .gnc identifier removed. The .gnc file will be left unaltered.

	Example: gen-crypt ~/folder/file.gnc
