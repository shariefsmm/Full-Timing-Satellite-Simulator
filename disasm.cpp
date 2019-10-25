#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#define NUM_INSTRUCTIONS 3

using namespace std;

int opcode(int arr[] ){
	int dec;
	dec = (arr[0]*2) + (arr[1]);
	return dec;
}

int opcode2(int arr[],int s,int e){
	int dec2;
	int start, end;
	end = 31 - e;	//7
	start = 31 - s; //9
	dec2 = (arr[end]*4) + (arr[end +1]*2) + (arr[end +2]);
	return dec2;
}

/*
 * bin is an array of 0 or 1
 * s is starting bit (inclusive)
 * e is ending bit (exclusive)
 * */
string binToHex(int bin[], int s, int e){
	string hex[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
	int len = e - s;
	int start = 31-e;
	int end = 31-s;
	string result = "";
	while(len > 0){
		int temp = 0;
		switch(len){
		case 1:
			temp = bin[end];
			break;
		case 2:
			temp = bin[end] + 2*bin[end - 1];
			break;
		case 3:
			temp = bin[end] + 2*bin[end - 1] + 4*bin[end - 2];
			break;
		default:
			temp = bin[end] + 2*bin[end - 1] + 4*bin[end - 2] + 8*bin[end - 3];
			break;
		}
			result = hex[temp] + result;
			len -= 4;
			end -= 4;
	}
	return result;
}

void FBfcccond(int arr[]){
	int cond;
	string FBfc[] = {
        "FBN", 
        "FBNE", 
        "FBLG", 
        "FBUL", 
        "FBL", 
        "FBUG", 
        "FBG", 
        "FBU", 
        "FBA", 
        "FBE", 
        "FBUG", 
        "FBGE", 
        "FBGUE", 
        "FBLE", 
        "FBULE", 
        "FBO"
    };

	//string 
	cond = (arr[3] * 8) + (arr[4]*4) + (arr[5]*2) + (arr[6]);
	cout << binToHex(arr,0,8) << " " << binToHex(arr,8,16) << " " << binToHex(arr,16,24) << " " << binToHex(arr,24,32) << "\t" ;
	cout << FBfc[cond] << " " << "Address_to_jump " << "address+offset" << "\n";
}

void Bicccond(int arr[]){
	int cond;
	string Bicc[] = {
        "BN", 
        "BE", 
        "BLE", 
        "BL", 
        "BLEU", 
        "BCS", 
        "BNEG", 
        "BVS", 
        "BA", 
        "BNE", 
        "BG", 
        "BGE", 
        "BGU", 
        "BCC", 
        "BPOS", 
        "BVC"
    };
	
    //string
	cond = (arr[3] * 8) + (arr[4]*4) + (arr[5]*2) + (arr[6]);
	printf(">>>>>-----------------------------------------------<<<<<\n");
	cout << "\t" <<binToHex(arr,0,8) << " " << binToHex(arr,8,16) << " " << binToHex(arr,16,24) << " " << binToHex(arr,24,32) << "\t" ;
	cout << Bicc[cond] << " " << "Address_to_jump " << "address+offset" << "\n";
	printf(">>>>>-----------------------------------------------<<<<<\n");
}

/*int disp30(int arr[]){

}*/

typedef struct Inst {
    unsigned short op;
    union {
        unsigned short rd;
        struct {
            unsigned short a;
            unsigned short cond;
        };
    } dest;

    unsigned short op2;
    unsigned short op3;
    unsigned short rs1;
    unsigned short i;
    unsigned short opf;
    unsigned short asi;
    unsigned short rs2;
    unsigned short simm13;
    unsigned short imm22;
    unsigned short disp22;
    unsigned short disp30;
} Inst;

void disassemble(Inst x_inst) {

    string out;

}


void decode(unsigned x_inst) {

    Inst inst;
    inst.op = x_inst >> 30;

    switch(inst.op) {
        case 0x0: 
            break;
        case 0x1:
            inst.disp30 = x_inst & 0x3FFFFFFF;
            break;
        case 0x2:
            break;
        
        case 0x3:
            break;
        default:
            cerr << "OPCODE length changed (not 2-bits anymore)?" << endl;
            exit(1);
    }

    disassemble(inst);
}


int main() {

    unsigned instructions[] = {0x12b7b2a7, 0xf2b7b2a7, 0x42b7b2a7};

    for(int i = 0; i < NUM_INSTRUCTIONS; i++) {
        decode(instructions[i]);
    }

    return 0;
}


#if 0
	switch(opcode(arr)){
		case 0:
			printf("we are entering opcode0, i.e branching or SETHI\n\n");
			switch(opcode2(arr,22,24)){
				case 0:
					printf("ERROR!!! Unidentified Argument while reading OPCODE2 with case 0\n");
					break;

				case 1:
					printf("ERROR!!! Unidentified Argument while reading OPCODE2 with case 1\n");
					break;

				case 2:
					printf("We are doing conditional branching with Bicc\n");
					Bicccond(arr);
					break;

				case 3:
					printf("ERROR!!! Unidentified Argument while reading OPCODE2 with case 3\n");
					break;

				case 4:
					temp = (arr[2] * 16) + (arr[3] * 8) + (arr[4]*4) + (arr[5]*2) + (arr[6]);
					if(temp < 8) reg = "%g";
					else if(temp <16) reg= "%o";
					else if(temp <24) reg= "%l";
					else if(temp <32) reg= "%i";
					value = binToHex(arr,0,22);
					printf("We are in SETHI right now \n");
					printf("decoded instruction is -> \n");
					printf(">>>>>-----------------------------------------------<<<<<\n");
					cout << binToHex(arr,0,8) << " " << binToHex(arr,8,16) << " " << binToHex(arr,16,24) << " " << binToHex(arr,24,32) << "\t" ;
					printf("sethi %chi(%s), %s%d\n",'%',value.c_str(),reg.c_str(),(temp%8));
					printf(">>>>>---------------------------------------------<<<<<\n");
					break;

				case 5:
					printf("ERROR!!! Unidentified Argument while reading OPCODE2 with case 5\n");
					break;

				case 6:
					printf("We are in FBfcc\n");
					FBfcccond(arr);
					break;

				case 7:
					printf("We are in CBccc\n");
					
					break;

			}
			break;

		case 1:
			printf("we are entering opcode1\n");
			/*//This deals with call function
			r[15] + PC;
			Pc+ nPc;
			nPc+ Pc + disp30[arr];
			*/
			printf("call address_in_program(hexadecimal) <Name_of_function>");
			printf("DECODED INSTRUCTION is ->\n");
			printf("call ");

		case 2:
		printf("we are entering opcode2");

		case 3:
		printf("we are entering opcode3");


	}
}

#endif
