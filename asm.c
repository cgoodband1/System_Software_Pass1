#include <stdio.h>
#include <stdlib.h>
#include <string.h>

	struct	Symbol{
		int SourceLineNumber;
		int Address;
		char Name[7]; };


	struct OpTab{
		int  InstructionLength;
		int  OpCode;
		char Name[10];
	};

	struct OpTab Opcodes[28];
	struct Symbol Symtab[50];


int IsAnInstruction( char* test ){
	int result = 0;
	int index =0;

	for ( index =0; index < 28; index ++ ){

        //int value =  strcmp( test, Opcodes[index].Name);
        //printf("This is the test %s\t this is the symbol in opcodes: %s\n", test, Opcodes[index]);
        //printf("This is cmp value: %d\n", value);

		if ( strcmp( test, Symtab[index].Name ) == 0 ) {

			result = 1;
			break;
		}

	}

	return result;

}

int IsinSymtab( char* test)
{
	int result = 0;
	int index =0;

	for ( index =0; index < 50; index ++ ){
		if ( strcmp( test, Opcodes[index].Name ) == 0 ) {

			result = 1;
			break;
		}


	}

	return result;

}

int IsADirective( char* test ){

}


int IsValidSymbol( char* test ) {
	int result = 1;
	int Len =0;
	int index =0;
	Len = strlen( test );
	if ( Len > 6 ) {
		result = 0;
		printf("ERROR: Symbol %s is longer than six characters.\n", test);
		return result;
	}
	for ( index =0; index < Len; index++ ) {

		if ( test[index] < 65 ) {
		result = 0;
		printf("ERROR: Symbol %s has a non-alpha character.\n", test);
		return result;


		}

	}




	return result;

}


void PopulateOpcodes() {
	memset( Opcodes, '\0', 28 * sizeof(struct OpTab)     );
	Opcodes[0].InstructionLength = 3;
	Opcodes[0].OpCode = 44;
	strcpy(Opcodes[0].Name , "TIX\0");

	Opcodes[1].InstructionLength = 3;
	Opcodes[1].OpCode = 56;
	strcpy(Opcodes[1].Name , "JLT\0");

	Opcodes[2].InstructionLength = 3;
	Opcodes[2].OpCode = 24;
	strcpy(Opcodes[2].Name , "ADD\0");

	Opcodes[3].InstructionLength = 3;
	Opcodes[3].OpCode = 64;
	strcpy(Opcodes[3].Name , "AND\0");

	Opcodes[4].InstructionLength = 3;
	Opcodes[4].OpCode = 40;
	strcpy(Opcodes[4].Name , "COMP\0");

	Opcodes[5].InstructionLength = 3;
	Opcodes[5].OpCode = 36;
	strcpy(Opcodes[5].Name , "DIV\0");

	Opcodes[6].InstructionLength = 3;
	Opcodes[6].OpCode = 60;
	strcpy(Opcodes[6].Name , "J\0");

	Opcodes[7].InstructionLength = 3;
	Opcodes[7].OpCode = 48;
	strcpy(Opcodes[7].Name , "JEQ\0");

	Opcodes[8].InstructionLength = 3;
	Opcodes[8].OpCode = 52;
	strcpy(Opcodes[8].Name , "JGT\0");

	Opcodes[9].InstructionLength = 3;
	Opcodes[9].OpCode = 72;
	strcpy(Opcodes[9].Name , "JSUB\0");

	Opcodes[10].InstructionLength = 3;
	Opcodes[10].OpCode = 00;
	strcpy(Opcodes[10].Name , "LDA\0");

	Opcodes[11].InstructionLength = 3;
	Opcodes[11].OpCode = 80;
	strcpy(Opcodes[11].Name , "LDCH\0");

	Opcodes[12].InstructionLength = 3;
	Opcodes[12].OpCode = 8;
	strcpy(Opcodes[12].Name , "LDL\0");

	Opcodes[13].InstructionLength = 3;
	Opcodes[13].OpCode = 4;
	strcpy(Opcodes[13].Name , "LDX\0");

	Opcodes[14].InstructionLength = 3;
	Opcodes[14].OpCode = 32;
	strcpy(Opcodes[14].Name , "MUL\0");

	Opcodes[15].InstructionLength = 3;
	Opcodes[15].OpCode = 68;
	strcpy(Opcodes[15].Name , "OR\0");

	Opcodes[16].InstructionLength = 3;
	Opcodes[16].OpCode = 216;
	strcpy(Opcodes[16].Name , "RD\0");

	Opcodes[17].InstructionLength = 3;
	Opcodes[17].OpCode = 76;
	strcpy(Opcodes[17].Name , "RSUB\0");

	Opcodes[18].InstructionLength = 3;
	Opcodes[18].OpCode = 12;
	strcpy(Opcodes[18].Name , "STA\0");

	Opcodes[19].InstructionLength = 3;
	Opcodes[19].OpCode = 84;
	strcpy(Opcodes[19].Name , "STCH\0");

	Opcodes[20].InstructionLength = 3;
	Opcodes[20].OpCode = 20;
	strcpy(Opcodes[20].Name , "STL\0");

	Opcodes[21].InstructionLength = 3;
	Opcodes[21].OpCode = 232;
	strcpy(Opcodes[21].Name , "STSW\0");

	Opcodes[22].InstructionLength = 3;
	Opcodes[22].OpCode = 16;
	strcpy(Opcodes[22].Name , "STX\0");

	Opcodes[23].InstructionLength = 3;
	Opcodes[23].OpCode = 28;
	strcpy(Opcodes[23].Name , "SUB\0");

	Opcodes[24].InstructionLength = 3;
	Opcodes[24].OpCode = 224;
	strcpy(Opcodes[24].Name , "TD\0");

	Opcodes[25].InstructionLength = 3;
	Opcodes[25].OpCode = 220;
	strcpy(Opcodes[25].Name , "WD\0");


}


int main( int argc, char* argv[]){

	FILE *InputFile;
	int SourceLineNumber =1;
	int LocationCounter = 0;
	int index;
	int IsCommentLine;
	char line[2048];
	for ( index = 0; index < argc; index++) {
		printf("%d\t%s\n", index, argv[index] );

	}


//uncomment


	if ( argc != 2 ) {
		printf("USAGE: %s filename\n", argv[0] );
		return 0;

	}



/* We got here, so the user specified a filename */


	/* does the file exist and can I read it */



	//testing on server
	InputFile = fopen( argv[1], "r");


	if ( InputFile == NULL ) {
		printf("ERROR %s either does not exist or cannot be opened for reading\n", argv[1] );
		return 0;

	}


	PopulateOpcodes();


	while (  fgets( line, 2048, InputFile)  ) {

		if ( line[0] == 35 ) {
			IsCommentLine = 1;
		} else { IsCommentLine = 0; }


		printf("%4d\t%4d\t%s", SourceLineNumber, LocationCounter, line );

		if  ( ! IsCommentLine ) {

			char linecopy[2048];
			memset( linecopy, '\0', 2048 );
			strcpy( linecopy, line );


			char *token;

			token = strtok( linecopy, " \t\n");
			if (( line[0] >= 65 ) && ( line[0] <= 122 ) ) {
				/* token contains as symbol definition*/
//				printf("NEW SYMBOL---%s\t", token);

				printf("Attempt to add symbol %s at %d\n", token, LocationCounter);

				if(! IsinSymtab( token ) )
				{
					printf("%s is not in the symbol table\n", token);
					/*
					Symtab[SourceLineNumber].SourceLineNumber = SourceLineNumber;
					Symtab[SourceLineNumber].Address = LocationCounter;
					strcpy(Symtab[SourceLineNumber].Name, token);
					*/
				}
				/*else{
					printf("ERROR: %s is a duplicate symbol (line: %d)\n", token, SourceLineNumber);
					return 0;

				}*/

				token = strtok(NULL, " \t\n\r");
				printf("This is the token in the if statement: %s\n", token);
				if ( IsAnInstruction( token ) ) {

					LocationCounter += 3;
				}

				if  (! IsValidSymbol( token ) ) {

					return 0;
				}

			} else {

				/* token has a directive or an instruction */
//				printf("DIR OR INSTRUCTION: %s\t", token );
				printf("This is token in the else statement: %s\n", token);
				if ( IsAnInstruction( token ) ) {

					LocationCounter += 3;
				}
			}



		}



		//printf("%4d\t%4d\t%s", SourceLineNumber, LocationCounter, line );



		SourceLineNumber+=1;


	}




	printf("Testing insert for FIRST: %s\n", Symtab[6].Name);
	printf("Testing insert for CLOOP: %s\n", Symtab[7].Name);
	fclose( InputFile );



}



