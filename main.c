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

char dir [8][100] = {
	"START","END","BYTE","WORD","RESB","RESW","RESR","EXPORTS"
};


int IsAnInstruction( char* test ){
	int result = 0;
	int index =0;

	for ( index =0; index < 28; index ++ ){
		if ( strcmp( test, Opcodes[index].Name ) == 0 ) {

			result = 1;
			break;
		}

	}

	return result;

}

int IsinSymtab( char* test, int line)
{
	int result = 0;
	int index =0;

	for ( index =0; index < 50; index ++ ){
		if ( strcmp( test, Symtab[index].Name ) == 0 ) {

			result = 1;
			//printf("(line: %d)ERROR: %s is a duplicate symbol\n", line, test);
			break;
		}


	}

	return result;

}

int IsADirective( char* test ){
	int result = 0;
	int index =0;

	for ( index =0; index < 8; index ++ ){
		if ( strcmp(test, dir[index]) == 0 ) {

			result = 1;
			break;
		}

	}

	return result;


}


int IsValidSymbol( char* test, int line ) {
	int result = 1;
	int Len =0;
	int index =0;
	Len = strlen( test );
	if ( Len > 6 ) {
		result = 0;
		printf("(line: %d)ERROR: Symbol %s is longer than six characters.\n",line, test);
		return result;
	}
	if(IsAnInstruction(test))
	{
		result = 0;
		printf("(line: %d)ERROR: Symbol %s is not a valid symbol. Symbol can not be an instruction\n",line, test);
		return result;
	}
	if(IsADirective(test))
	{
		result = 0;
		printf("(line: %d)ERROR: Symbol %s is not a valid symbol. Symbol can not be an directive\n",line, test);
		return result;
	}
	for ( index =0; index < Len; index++ ) {

		if ( test[index] < 65 ) {
		result = 0;
		printf("(line: %d)ERROR: Symbol %s has a non-alpha character.\n",line, test);
		return result;


		}

	}



	return result;

}
void createtable()
{
	for ( int index =0; index < 52; index ++ )
	{
		memset( Symtab, '\0', 53 * sizeof(struct Symbol)     );
		//strcpy(Symtab[index].Name, NULL);
	}
		
}
int validhex(char string[2048], int line)
{
	int result = 1;
	int starting_point = 0;
	int ending_point = 0;
	for (int index =0; index < 2048; index ++ )
	{
		//printf("Char: %s", string[index]);
		if(starting_point == 0)
		{
			if((string[index]) == 39 )
			{
				starting_point = index;
				//printf("THIS IS STARTING_POINT: %d\n", starting_point);
			}
		}
		else
		{
			if((string[index]) == 39 )
			{
				ending_point = index;
				//printf("THIS IS ENDING_POINT: %d\n", ending_point);
				//int len = ((ending_point - starting_point)- 1);
				for(int start = (starting_point + 1); start < ending_point; start++)
				{
					if((string[start] < 48) && (string[start] > 57)||(string[start] < 65)&& (string[start] > 70))
					{
						result = 0;
						printf("(Line: %d) ERROR invalid Hex constant\n", line);
						return result;
						break;
					}
				}
				
			}
		} 
	}	
	return result;
}

int findlength(char string[2048])
{
	int starting_point = 0;
	int ending_point = 0;
	for (int index =0; index < 2048; index ++ )
	{
		//printf("Char: %s", string[index]);
		if(starting_point == 0)
		{
			if((string[index]) == 39 )
			{
				starting_point = index;
				//printf("THIS IS STARTING_POINT: %d\n", starting_point);
			}
		}
		else
		{
			if((string[index]) == 39 )
			{
				ending_point = index;
				//printf("THIS IS ENDING_POINT: %d\n", ending_point);
				int len = ((ending_point - starting_point)- 1);
				//printf("this is len: %d\n",len);
				return len;
			}
		} 
	}
	
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
	int initialized = 0;
	int SourceLineNumber =1;
	int LocationCounter = 0;
	int index;
	int IsCommentLine;
	int starting_address;
	char *starting_symbol;
	int end;
	char *tokens;
	int file_length;
	char line[2048];
	/*for ( index = 0; index < argc; index++) {
		printf("%d\t%s\n", index, argv[index] );

	}*/


	if ( argc != 2 ) {
		printf("USAGE: %s filename\n", argv[0] );
		return 0;

	}



/* We got here, so the user specified a filename */


	/* does the file exist and can I read it */

	InputFile = fopen( argv[1], "r");


	if ( InputFile == NULL ) {
		printf("ERROR %s either does not exist or cannot be opened for reading\n", argv[1] );
		return 0;

	}


	PopulateOpcodes();
	//createtable();


	while (  fgets( line, 2048, InputFile)  ) {

		if ( line[0] == 35 ) {
			IsCommentLine = 1;
		} else { IsCommentLine = 0; }


		//printf("%4d\t%X\t%s", SourceLineNumber, LocationCounter, line );

		if  ( ! IsCommentLine ) {

			char linecopy[2048];
			memset( linecopy, '\0', 2048 );
			strcpy( linecopy, line );


			char *token;

			token = strtok( linecopy, " \t\n\r");
			//if (( line[0] < 65 ) && ( line[0] > 122 ) )
			
			if (( line[0] >= 65 ) && ( line[0] <= 122 ) ) {
				/* token contains as symbol definition*/

				if  (! IsValidSymbol( token, SourceLineNumber ) ) {
					//printf("ERROR(line: %d) %s is not a valid symbold\n", SourceLineNumber, token);
					return 0;
				}
				tokens = token;
				token = strtok(NULL, " \t\n\r");
				char* opcode = token;

				if (! initialized)
				{
					
					if(strcmp(opcode, "START") == 0)
					{
						initialized = 1;
					}
					else
					{
						printf("(Line: %d) ERROR: START HAS NOT BEEN INITIALIZED\n", SourceLineNumber);
						return 0;
					}


				}
				if(! IsAnInstruction(opcode) && ! IsADirective(opcode))
				{
					printf("(line: %d) %s is not a valid opcode\n", SourceLineNumber, opcode);
					return 0;
				}

				//printf("Attempt to add symbol %s at %d\n", token, LocationCounter);
				if( (IsinSymtab( tokens, SourceLineNumber )) == 1 )
				{
					printf("(line: %d)ERROR: %s is a duplicate symbol \n",SourceLineNumber, tokens);
					return 0;

				}
				if( (IsinSymtab( tokens, SourceLineNumber )) == 0 )
				{
					//printf("%s is not in the symbol table Value: %d\n", tokens, IsinSymtab( tokens, SourceLineNumber ));
					
					Symtab[SourceLineNumber].SourceLineNumber = SourceLineNumber;
					Symtab[SourceLineNumber].Address = LocationCounter;
					strcpy(Symtab[SourceLineNumber].Name, tokens);
					
				}
				

				//this gets to the opcode 
				//token = strtok(NULL, " \t\n\r");
				//printf("This is the token in the if statement: %s\n", tokens);
				if ( IsAnInstruction( token ) ) {
					//printf("IT IS REACHING HERE\n");
					LocationCounter += 3;
				}
				if (IsADirective( token )){
					char *opcode = token;
					printf("%s is a directive\n", opcode);
					token = strtok(NULL, " \t\n\r");
					char* opand = token;
					printf("\t%s: is the opand\n", opand);
					//printf("----------\n" );
					
					if(strcmp(opcode, "START") == 0)
					{
						long dec = strtol(opand, NULL, 16);
						//printf("This is the starting address: %X\n", dec);
						starting_address = dec;
						LocationCounter = starting_address;
						if(LocationCounter == 8000)
						{
							printf("(Line: %d)ERROR no memory to assemble SIC file. Chamge starting address\n",SourceLineNumber );
							return 0;
						}
						Symtab[SourceLineNumber].Address = LocationCounter;

					}

					if(strcmp(opcode, "WORD") == 0)
					{
						int temp_opand = atoi(opand);
						if(temp_opand > 8388607)
						{
							printf("(Line: %d) Word constant is too large for 24 bit limitation\n", SourceLineNumber);
							return 0;
						}
						LocationCounter += 3;
					}
					if(strcmp(opcode, "RESB") == 0)
					{
						int temp_opand = atoi(opand);
						LocationCounter = (LocationCounter + temp_opand);

					}
					if(strcmp(opcode, "RESW") == 0)
					{
						int temp_opand = atoi(opand);
						LocationCounter = (LocationCounter + (3 * temp_opand));
					}
					if(strcmp(opcode, "BYTE") == 0)
					{
						int indexed = 0;
						char *byte = strtok( opand, "'");
						validhex(line, SourceLineNumber);
						printf("%d value of valid hex\n", validhex(line, SourceLineNumber));
						if(strcmp(byte, "X")== 0){
							indexed = 1;
							LocationCounter = (LocationCounter + indexed);
						}else{
						byte = strtok(NULL, "'");
						int len = findlength(line);
						//printf("This is indexed: %d\n", indexed);
						LocationCounter = (LocationCounter + len + indexed);
						//printf("####################\n");
						//printf("This is the length of byte: %d\n", len);
						//printf("this is len + indexed: %d\n",len + indexed);
						//printf("This is byte after splitting opeand: %s\n", byte);
						}
					}
					if(strcmp(opcode, "END") == 0)
					{
						//printf("I made it to END\n");
						end = LocationCounter;
						file_length = (end - starting_address); 
						//printf("THis is ends opand: %s\n", opand);
						char *starting_symbol = opand;
					
						if(end > 32768)
						{
							//printf("Value of end: %d\n", end);
							printf("ERROR: FILE DOES NOT FIT IN MEMORY CHANGE STARTING ADDRESS\n");
							return 0;
						}
					}
				}

			} else {
				if((line[0] < 65)&&(line[0] > 9) || line[0] > 122)
				{
				printf("(Line: %d) ERROR %s This is not a valid symbol\n", SourceLineNumber, token);
				return 0;
				}
				// has no symbol

				/* token has a directive or an instruction */
//				printf("DIR OR INSTRUCTION: %s\t", token );
				//printf("This is token in the else statement: %s\n", token);
				if(! IsAnInstruction(token) && ! IsADirective(token))
				{
					printf("(line: %d) %s is not a valid opcode\n", SourceLineNumber, token);
					return 0;
				}
				if ( IsAnInstruction( token ) ) {
					//printf("IT IS REACHING HERE\n");
					LocationCounter += 3;
				}
				if(IsADirective( token )){
					char* opcode = token;
					token = strtok(NULL, " \t\n\r");
					char* opand = token;
					if(strcmp(opcode, "END") == 0)
					{
						//printf("I made it to END\n");
						end = LocationCounter;
						file_length = (end - starting_address); 
						starting_symbol = opand;
						//printf("Value of end: %d\n",end);
						if(end > 32768)
						{
							//printf("Value of end: %d\n", end);
							printf("ERROR: FILE DOES NOT FIT IN MEMORY CHANGE STARTING ADDRESS\n");
							return 0;
						}
					}
				}
				
			}



		}



		//printf("%4d\t%4d\t%s", SourceLineNumber, LocationCounter, line );



		SourceLineNumber+=1;


	}

	
	fclose( InputFile );
	for ( index =0; index < 53; index ++ ){
		if(Symtab[index].Address == 0)
		{
			continue;
			//printf("(Line: %d)\t%s\t%X\n",Symtab[index].SourceLineNumber, Symtab[index].Name, Symtab[index].Address);
		}
		if(Symtab[index].Name != NULL){
			printf("%s\t%X\n",Symtab[index].Name, Symtab[index].Address);
		}
	}
	printf("File Length: %X\n",file_length);
	//printf("this is the starting_address: %X\n",starting_address );
	//printf("This is the end in hex: %X\n", end);

}




