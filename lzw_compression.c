#include <stdio.h>
#include <string.h>
char Input[256] = "THERE ARE ONLY TWO WAYS TO LIVE YOUR LIFE. ONE IS THOUGH NOTHING IS A MIRACLE. THE OTHER IS A THOUGH EVERYTHING IS A MIRACLE.";//Input stream
char Output[256] = "";//This is where the codes will be output
char String_buffer[256];//This buffer is used to store the sub string.

typedef struct {
	int code;
	char value[8];
} DictionaryPairs;
DictionaryPairs Dictionary[256];//This creates the structure of the code dictionary

//These variables are used to store position as the code loops through the input stream and the code dictionary
int OutputIndex = 0;
int InputIndex = 0;
int DictionaryIndex = 29;


void Read_SubString();
int Check_Dictionary();

int main() {
	int LengthOfInput = strlen(Input);//This variable holds the length of the input stream

	//Adds the already known values to the dictionary
	strcpy(Dictionary[0].value, "#"); Dictionary[0].code = 0;
	strcpy(Dictionary[1].value, "A"); Dictionary[1].code = 1;
	strcpy(Dictionary[2].value, "B"); Dictionary[2].code = 2;
	strcpy(Dictionary[3].value, "C"); Dictionary[3].code = 3;
	strcpy(Dictionary[4].value, "D"); Dictionary[4].code = 4;
	strcpy(Dictionary[5].value, "E"); Dictionary[5].code = 5;
	strcpy(Dictionary[6].value, "F"); Dictionary[6].code = 6;
	strcpy(Dictionary[7].value, "G"); Dictionary[7].code = 7;
	strcpy(Dictionary[8].value, "H"); Dictionary[8].code = 8;
	strcpy(Dictionary[9].value, "I"); Dictionary[9].code = 9;
	strcpy(Dictionary[10].value, "J"); Dictionary[10].code = 10;
	strcpy(Dictionary[11].value, "K"); Dictionary[11].code = 11;
	strcpy(Dictionary[12].value, "L"); Dictionary[12].code = 12;
	strcpy(Dictionary[13].value, "M"); Dictionary[13].code = 13;
	strcpy(Dictionary[14].value, "N"); Dictionary[14].code = 14;
	strcpy(Dictionary[15].value, "O"); Dictionary[15].code = 15;
	strcpy(Dictionary[16].value, "P"); Dictionary[16].code = 16;
	strcpy(Dictionary[17].value, "Q"); Dictionary[17].code = 17;
	strcpy(Dictionary[18].value, "R"); Dictionary[18].code = 18;
	strcpy(Dictionary[19].value, "S"); Dictionary[19].code = 19;
	strcpy(Dictionary[20].value, "T"); Dictionary[20].code = 20;
	strcpy(Dictionary[21].value, "U"); Dictionary[21].code = 21;
	strcpy(Dictionary[22].value, "V"); Dictionary[22].code = 22;
	strcpy(Dictionary[23].value, "W"); Dictionary[23].code = 23;
	strcpy(Dictionary[24].value, "X"); Dictionary[24].code = 24;
	strcpy(Dictionary[25].value, "Y"); Dictionary[25].code = 25;
	strcpy(Dictionary[26].value, "Z"); Dictionary[26].code = 26;
	strcpy(Dictionary[27].value, "."); Dictionary[27].code = 27;
	strcpy(Dictionary[28].value, " "); Dictionary[28].code = 28;

	//Loops over until it reaches the end of the input stream
	while (InputIndex < LengthOfInput) {
		int c, cNext;//Current char and next char
		Read_SubString(Input, InputIndex, InputIndex);
		c = Check_Dictionary(String_buffer);
		Read_SubString(Input, InputIndex, InputIndex + 1);//Reads char from input stream
		
		if ((cNext = Check_Dictionary(String_buffer)) < 0) { 
			Add_Dictionary(String_buffer, DictionaryIndex);
			Output[OutputIndex++] = c;
			InputIndex++;
		}
		else {
			c = cNext;//sets the current character to the next character in the input stream
			Read_SubString(Input, InputIndex, InputIndex + 2);//Reads the currents character and the next character
			if ((cNext = Check_Dictionary(String_buffer)) < 0) {
				Add_Dictionary(String_buffer, DictionaryIndex);//If the combined characters are not in the dictionary add them
				Output[OutputIndex++] = c;
				InputIndex++;
			}
			else {//If they are then combine the two characters with the next character and check if it is in the dictionary
				c = cNext;
				Read_SubString(Input, InputIndex, InputIndex + 3);
				if ((cNext = Check_Dictionary(String_buffer)) < 0) {
					Add_Dictionary(String_buffer, DictionaryIndex);
					Output[OutputIndex++] = c;
					InputIndex++;
				}
				else {//Combine the next character
					c = cNext;
					Read_SubString(Input, InputIndex, InputIndex + 4);
					if ((cNext = Check_Dictionary(String_buffer)) < 0) {
						Add_Dictionary(String_buffer, DictionaryIndex);
						Output[OutputIndex++] = c;
						InputIndex++;
					}
					else {//Only handle length up to 5
						Output[OutputIndex++] = cNext;
						InputIndex++;
					}
				}
			}
		}
	}

	return 0;
}

//This is a function to add new codes to the dicitonary
void Add_Dictionary(char* s, int c) {
	Dictionary[DictionaryIndex].code = c;
	strcpy(Dictionary[DictionaryIndex].value, s);
	DictionaryIndex++;
}

//This is a function to create the string buffer
void Read_SubString(char*Input, int from, int to) {
	int i;
	for (i = 0; ; i++) {
		String_buffer[i] = Input[from++];
		if (from > to) {
			break;
		}
	}
	String_buffer[i] = '\0';
}

//This functions loops over the code dictionary and checks if the value is already in the code dictionary
int Check_Dictionary(char*Input) {
	for (int i = 0; i < DictionaryIndex; i++) {
		if (strcmp(Input, Dictionary[i].value) == 0) {
			return Dictionary[i].code;
		}
	}

	return -1;//If the value is not in the dictionary it will return -1
}
