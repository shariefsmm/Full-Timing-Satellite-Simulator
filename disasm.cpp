#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#define NUM_INSTRUCTIONS 3

using namespace std;

typedef struct{
        int32_t disp30;
    } format1;

typedef struct{
        uint32_t op2;

        union 
        {
            struct
            {
                uint32_t rd;
                int32_t imm22;
            } sethi;

            struct 
            {
                int32_t a;
                int32_t cond;
                int32_t disp22;  
            } branch; 
        
        } target;
    } format2;

typedef struct{
        int32_t op3; 
        uint32_t rd;
        uint32_t rs1;

        union 
        {
            struct 
            {
                int i;
                union 
                {
                        uint32_t rs2;
                        int32_t simm13;
                } rs2;
                
            } intg;

            struct 
            {
                uint32_t rs2;
                uint32_t opf;
            } fp;

        } operand2;
    } format3; //FMT1 or FMT2 or FMT3

typedef struct {
        uint32_t op;
        union 
        {
            format1 a;
            format2 b;
            format3 c; 
        } inst_type;
    } inst;



void Bicccond(inst x_inst){
	//int cond;
	uint32_t cond;
	uint32_t temp;
	uint32_t temp2;
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
	

	cond = x_inst.inst_type.b.target.branch.cond;
	temp  = x_inst.inst_type.b.target.branch.a << 2;
	temp2 = x_inst.inst_type.b.target.branch.disp22 << 2;
	printf(" %s \"PC + %08jx\" \n",Bicc[cond].c_str(), (uintmax_t)temp2);
	return;  
}

void FBfcccond(inst x_inst){
	uint32_t cond;
	uint32_t temp;
	uint32_t temp2;
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

/*	//string 
	cond = (arr[3] * 8) + (arr[4]*4) + (arr[5]*2) + (arr[6]);
	cout << binToHex(arr,0,8) << " " << binToHex(arr,8,16) << " " << binToHex(arr,16,24) << " " << binToHex(arr,24,32) << "\t" ;
	cout << FBfc[cond] << " " << "Address_to_jump " << "address+offset" << "\n";
*/
  	cond = x_inst.inst_type.b.target.branch.cond;
	temp  = x_inst.inst_type.b.target.branch.a << 2;
	temp2 = x_inst.inst_type.b.target.branch.disp22 << 2;
	printf(" %s \"PC + %08jx\" \n",FBfc[cond].c_str(), (uintmax_t)temp2);  
	return;
}

void CBccccond(inst x_inst){
	uint32_t cond;
	uint32_t temp;
	uint32_t temp2;
	string cbc[] = {
        "CBN", 
        "CB123", 
        "CB12", 
        "CB13", 
        "CB1", 
        "CB23", 
        "CB2", 
        "CB3", 
        "CBA", 
        "CB0", 
        "CB03", 
        "CB02", 
        "CB023", 
        "CB01", 
        "CB013", 
        "CB012"
    };

/*	//string 
	cond = (arr[3] * 8) + (arr[4]*4) + (arr[5]*2) + (arr[6]);
	cout << binToHex(arr,0,8) << " " << binToHex(arr,8,16) << " " << binToHex(arr,16,24) << " " << binToHex(arr,24,32) << "\t" ;
	cout << FBfc[cond] << " " << "Address_to_jump " << "address+offset" << "\n";
*/
  	cond = x_inst.inst_type.b.target.branch.cond;
	temp  = x_inst.inst_type.b.target.branch.a << 2;
	temp2 = x_inst.inst_type.b.target.branch.disp22 << 2;
	printf(" %s \"PC + %08jx\" \n",cbc[cond].c_str(), (uintmax_t)temp2);  
	return;
}

void op3two(inst x_inst){
	uint32_t op3; 
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs2;
	uint32_t i;
	int k,l;
	uint32_t opf;
	uint32_t simm13;
	uint32_t op354;
	uint32_t op024;
	string RegRd;
	string RegRs1;
	string RegRs2;
	string cbc[][4] = {
						{"ADD"  ,"ADDcc"  ,"TADDcc"    ,"WRASR | WRY"},
					  	{"AND"  ,"ANDcc"  ,"TSUBCC"    ,"WRPSR"},
			 			{"OR"   ,"ORcc"   ,"TADDccTV"  ,"WRWIM"},
		        		{"XOR"  ,"XORcc"  ,"TSUBccTV"  ,"WRTBR"},
		        		{"SUB"  ,"SUBCC"  ,"MULScc"    ,"//FPop1"},
		        		{"ANDN" ,"ANDNcc" ,"SLL"       ,"//FPop2"},
		        		{"ORN"  ,"ORNcc"  ,"SRL"       ," CPop1"},
		        		{"XNOR" ,"XNORcc" ,"SRA"       ,"CPop2"},
		        		{"ADDX" ,"ADDXcc" ,"RDASR|RDY  |STBAR", "JMPL"}, 
		        		{"NULL" ,"NULL"   ,"RDPSR" ,"RETT"},
		        		{"UMUL" ,"UMULcc" ,"RDWIM" ,"Ticc"},
		        		{"SMUL" ,"SMULcc" ,"RDTBR" ,"FLUSH"},
		        		{"SUBX" ,"SUBXcc" ,"NULL"  ,"SAVE"},
		        		{"NULL" ,"NULL"   , "NULL" ,"RESTORE"},
		        		{"UDIV" ,"UDIVcc" ,"NULL"  ,"NULL"},
				        {"SDIV" ,"SDIVcc" ,"NULL"  ,"NULL"}
    };
    rd = x_inst.inst_type.c.rd;
    rs1= x_inst.inst_type.c.rs1;
    op3= x_inst.inst_type.c.op3;
	i  = x_inst.inst_type.c.operand2.intg.i; 
	

	string fpop2[]{
		"51 FCMPs",
		"52 FCMPd",
		"53 FCMPq",
		"55 FCMPEs",
		"56 FCMPEd",
		"57 FCMPEq"
	};

    if(op3==0x34){
    	string fpop[] = {
    		"01 FMOVs",
			"05 FNEGs",
			"09 FABSs",
			"29 FSQRTs",
			"2A FSQRTd",
			"2B FSQRTq",
			"41 FADDs",
			"42 FADDd",
			"43 FADDq",
			"45 FSUBs",
			"46 FSUBd",
			"47 FSUBq",
			"49 FMULs",
			"4A FMULd",
			"4B FMULq",
			"4D FDIVs",
			"4E FDIVd",
			"4F FDIVq",
			"69 FsMULd",
			"6E FdMULq",
			"C4 FiTOs",
			"C6 FdTOs",
			"C7 FqTOs",
			"C8 FiTOd",
			"C9 FsTOd",
			"CB FqTOd",
			"CC FiTOq",
			"CD FsTOq",
			"CE FdTOq",
			"D1 FsTOi",
			"D2 FdTOi",
			"D3 FqTOi"
    	};

    	if(rd < 8) RegRd = "%f";
		else if(rd <16) RegRd= "%f";
		else if(rd <24) RegRd= "%f";
		else if(rd <32) RegRd= "%f";

		if(rs1 < 8) RegRs1 = "%f";
		else if(rs1 <16) RegRs1= "%f";
		else if(rs1 <24) RegRs1= "%f";
		else if(rs1 <32) RegRs1= "%f";


	  	if(rs2 < 8) RegRs2 = "%f";
		else if(rs2 <16) RegRs2= "%f";
		else if(rs2 <24) RegRs2= "%f";
		else if(rs2 <32) RegRs2= "%f";


    	k = x_inst.inst_type.c.operand2.fp.opf;
    	// k == 09 is also with the below code
    	if(k==01 || k==05  || k==41 || k==42 || k==43 || k==196 || k==198 || k==199 || k==200 || k==201 ||k==203 || k==204 || k==205 ||k==206 ||  k==209 || k==210 ||k==211){
    		printf("%s %s%d %s%d \n",fpop2[k].c_str(),RegRs2.c_str(),(rs2),RegRd.c_str(),(rd));
			return;
    	}

			printf("%s %s%d %s%d %s%d \n",fpop[k].c_str(),RegRd.c_str(),(rd%8),RegRs2.c_str(),(rs2%8),RegRs1.c_str(),(rs1%8));



    	return;

    }
    else if(op3==0x35){

    	if(rd < 8) RegRd = "%f";
		else if(rd <16) RegRd= "%f";
		else if(rd <24) RegRd= "%f";
		else if(rd <32) RegRd= "%f";

		if(rs1 < 8) RegRs1 = "%f";
		else if(rs1 <16) RegRs1= "%f";
		else if(rs1 <24) RegRs1= "%f";
		else if(rs1 <32) RegRs1= "%f";

		if(rs2 < 8) RegRs2 = "%f";
		else if(rs2 <16) RegRs2= "%f";
		else if(rs2 <24) RegRs2= "%f";
		else if(rs2 <32) RegRs2= "%f";

		printf("%s %s%d %s%d %s%d \n",fpop2[k].c_str(),RegRd.c_str(),(rd%8),RegRs2.c_str(),(rs2%8),RegRs1.c_str(),(rs1%8));
		
    	return;

    }

    op354 = x_inst.inst_type.c.op3 >> 4;
    op024 = (x_inst.inst_type.c.op3 << 2)>>2;

  	k = op354;
  	l = op024;

  	if(rd < 8) RegRd = "%g";
	else if(rd <16) RegRd= "%o";
	else if(rd <24) RegRd= "%l";
	else if(rd <32) RegRd= "%i";

	if(rs1 < 8) RegRs1 = "%g";
	else if(rs1 <16) RegRs1= "%o";
	else if(rs1 <24) RegRs1= "%l";
	else if(rs1 <32) RegRs1= "%i";

	/*
	//excptions
	if(l==0 && k ==3){
		if(i==0){printf("WRY %s%d %d %s%d \n",RegRd.c_str(),(rd%8), simm13 ,RegRs1.c_str(),(rs1%8));};
		else if(i==1){printf("WRASR %s%d %d %s%d \n",RegRd.c_str(),(rd%8), simm13 ,RegRs1.c_str(),(rs1%8));};
	}
	else if (l == 1 && k ==3){
		printf("WPRSR %s%d %d %s%d \n",RegRd.c_str(),(rd%8), simm13 ,RegRs1.c_str(),(rs1%8));	
	}
	*/
	i  = x_inst.inst_type.c.operand2.intg.i; 
	if(i=1){
		 rs2= x_inst.inst_type.c.operand2.intg.rs2.rs2;
	  	if(rs2 < 8) RegRs2 = "%g";
		else if(rs2 <16) RegRs2= "%o";
		else if(rs2 <24) RegRs2= "%l";
		else if(rs2 <32) RegRs2= "%i";

		printf("%s %s%d %s%d %s%d \n",cbc[l][k].c_str(),RegRs1.c_str(),(rs1%8),RegRs2.c_str(),(rs2%8),RegRd.c_str(),(rd%8));
	}
	else if(i=0){
		simm13 = x_inst.inst_type.c.operand2.intg.rs2.simm13 << 2;
		printf("%s %s%d %d %s%d \n",cbc[l][k].c_str(),RegRd.c_str(),(rd%8), simm13 ,RegRs1.c_str(),(rs1%8));
	}
    return;
}

void op3one(inst x_inst){
	uint32_t op3; 
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs2;
	uint32_t i;
	int k,l;
	uint32_t opf;
	uint32_t simm13;
	uint32_t op354;
	uint32_t op024;
	string RegRd;
	string RegRs1;
	string RegRs2;
	string cbc[][4] = {
						{"LD"    ,"LDA"    ,"LDF"   ,"LDC"},
					  	{"LDUB"  ,"LDUBA"  ,"LDFSR" ,"LDCSR"},
			 			{"LDUH"  ,"LDUHA"  ,"NULL"  ,"NULL"},
		        		{"LDD"   ,"LDDA"   ,"LDDF"  ,"LDDC"},
		        		{"ST"    ,"STA"    ,"STF"   ,"STC"},
		        		{"STB"   ,"STBA"   ,"STFSR" ,"STCSR"},
		        		{"STH"   ,"STHA"   ,"STDFQ" ," STDCQ"},
		        		{"STD"   ,"STDA"   ,"STDF"  ,"STDC"},
		        		{"NULL"  ,"NULL"   ,"NULL"  , "NULL"}, 
		        		{"LDSB"  ,"LDSBA"  ,"NULL"  ,"NULL"},
		        		{"LDSH"  ,"LDSHA"  ,"NULL"  ,"NULL"},
		        		{"NULL"  ,"NULL"   ,"NULL"  ,"NULL"},
		        		{"NULL"  ,"NULL"   ,"NULL"  ,"NULL"},
		        		{"LDSTUB","LDSTUBA","NULL"  ,"NULL"},
		        		{"NULL"  ,"NULL"   ,"NULL"  ,"NULL"},
				        {"SWAP"  ,"SWAPA"  ,"NULL"  ,"NULL"}
    };
    rd = x_inst.inst_type.c.rd;
    rs1= x_inst.inst_type.c.rs1;
    op3= x_inst.inst_type.c.op3;
	i  = x_inst.inst_type.c.operand2.intg.i; 

    op354 = x_inst.inst_type.c.op3 >> 4;
    op024 = (x_inst.inst_type.c.op3 << 2)>>2;

  	k = op354;
  	l = op024;

  	if(rd < 8) RegRd = "%g";
	else if(rd <16) RegRd= "%o";
	else if(rd <24) RegRd= "%l";
	else if(rd <32) RegRd= "%i";

	if(rs1 < 8) RegRs1 = "%g";
	else if(rs1 <16) RegRs1= "%o";
	else if(rs1 <24) RegRs1= "%l";
	else if(rs1 <32) RegRs1= "%i";

	i  = x_inst.inst_type.c.operand2.intg.i; 
	if(i=0){
		 rs2= x_inst.inst_type.c.operand2.intg.rs2.rs2;
	  	if(rs2 < 8) RegRs2 = "%g";
		else if(rs2 <16) RegRs2= "%o";
		else if(rs2 <24) RegRs2= "%l";
		else if(rs2 <32) RegRs2= "%i";

		printf("%s [%s%d + %s%d], %s%d \n",cbc[l][k].c_str(),RegRs1.c_str(),(rs1%8),RegRs2.c_str(),(rs2%8),RegRd.c_str(),(rd%8));
	}
	else if(i=1){
		simm13 = x_inst.inst_type.c.operand2.intg.rs2.simm13 << 2;
		printf("%s [%s%d + %d], %s%d \n",cbc[l][k].c_str(),RegRs1.c_str(),(rs1%8), simm13,RegRd.c_str(),(rd%8));
	}
    return;
}



void disassemble(inst x_inst) {
	uint32_t r;		// random which will be used to store some imp values
	uint32_t eop;	//extra opcode like op2 and op3
	uint32_t temp;
	uint32_t temp2;
	string reg;
	switch(x_inst.op){
		case 1:
			
			//printf("we are in opcode1\n");
			r = x_inst.inst_type.a.disp30 << 2;
			printf("call \"PC + %08jx\" \n", (uintmax_t)r);
			break;


		case 0:
			//printf("we are in opcode0\n");
			eop = x_inst.inst_type.b.op2;
			if (eop ==0 || eop == 1 || eop == 3 || eop == 5)
			{
				printf("ERROR!!! Unidentified Argument while reading OPCODE2");
			}
			else if(eop == 2){
				//printf("We have to write for Bicc\n");
				r = x_inst.inst_type.b.target.branch.disp22 << 2;
				temp2 = x_inst.inst_type.b.target.branch.cond;
				temp  = x_inst.inst_type.b.target.branch.a << 2;
				Bicccond(x_inst);
			}

			else if (eop == 4)
			{
				r = x_inst.inst_type.b.target.sethi.imm22 << 2;
				temp = x_inst.inst_type.b.target.sethi.rd;
				if(temp < 8) reg = "%g";
				else if(temp <16) reg= "%o";
				else if(temp <24) reg= "%l";
				else if(temp <32) reg= "%i";
				printf("sethi %chi(%08jx), %s%d \n",'%',(uintmax_t)r,reg.c_str(),(temp%8));
			}

			else if(eop == 6){
				FBfcccond(x_inst);
			}

			else if(eop == 7){
				CBccccond(x_inst);
			}

			break;

		case 2:
			eop = x_inst.inst_type.c.op3 >> 4; //getting op3[5:4]
			op3two(x_inst);
			break;


		case 3:
			//printf("we are in opcode 2 or 3\n");
			eop = x_inst.inst_type.c.op3 >> 4;
			op3one(x_inst);
			break;


        default:
            //cerr << "OPCODE length changed (not 2-bits anymore)?" << endl;
            exit(1);		

	}
    //string out;

}

/*
void decode(uint32_t x_inst) {

    Inst inst;
    inst.op = x_inst >> 30;

    switch(inst.op) {
        case 0x0: 
        	inst.inst_type.b.op2 = x_inst << 7;
        	inst.inst_type.b.op2 = inst.inst_type.b.op2 >> 29;
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
}*/

void decode(uint32_t instr){
	uint32_t instr_copy = instr;

    inst d;

    uint32_t op = instr_copy >> 30;
    d.op = op;

    switch (op)
    {
        case 1:
            d.inst_type.a.disp30 = (((1 << 22) - 1) & (instr_copy >> (0)));
            break;

        case 0:
            d.inst_type.b.op2 = (((1 << 3) - 1) & (instr_copy >> (22)));

            if(d.inst_type.b.op2 == 4)
            {   
                d.inst_type.b.target.sethi.rd = (((1 << 5) - 1) & (instr_copy >> (25)));
                d.inst_type.b.target.sethi.imm22 = (((1 << 22) - 1) & (instr_copy >> (0)));
            }

            else
            {   
                d.inst_type.b.target.branch.a = (((1) & (instr_copy >> (29))));
                d.inst_type.b.target.branch.cond = (((1 << 4) - 1) & (instr_copy >> (25)));;;


                d.inst_type.b.target.branch.disp22 = (((1 << 22) - 1) & (instr_copy >> (0)));
            }

            break;
        
        case 2:
        case 3:
            d.inst_type.c.op3 = (((1 << 6) - 1) & (instr_copy >> (19)));
            d.inst_type.c.rd = (((1 << 5) - 1) & (instr_copy >> (25)));
            d.inst_type.c.rs1 = (((1 << 5) - 1) & (instr_copy >> (14)));

            if(d.inst_type.c.op3 >= 0x00000034 && d.inst_type.c.op3 <= 0x00000037)
            {
                d.inst_type.c.operand2.fp.rs2 = (((1 << 5) - 1) & (instr_copy >> (0)));
                d.inst_type.c.operand2.fp.opf = (((1 << 9) - 1) & (instr_copy >> (5)));
            }

            else
            {
                d.inst_type.c.operand2.intg.i = ((1) & (instr_copy >> (13)));
                if( d.inst_type.c.operand2.intg.i)
                {
                    d.inst_type.c.operand2.intg.rs2.simm13 = (((1 << 13) - 1) & (instr_copy >> (0)));
                }
                else
                {
                    d.inst_type.c.operand2.intg.rs2.rs2 = (((1 << 5) - 1) & (instr_copy >> (0)));
                }
            }
            break;

        default:
        	//cerr << "OPCODE length changed (not 2-bits anymore)?" << endl;
            break;
    }


    disassemble(d);
}


int main() {

    uint32_t instructions[] = {0x1a80000c,0xba274001, 0x92004009};
    // ,0x03bffebf,0x40025642,0xee4e6002
    //0xc208e001,0xa200e001,8216c002
    //

    for(int j = 0; j < 3; j++) {
    	printf("%08jx ", (uintmax_t)instructions[j]);
        decode(instructions[j]);
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
			error: a function-definition is not allowed here before ‘{’ token
 int main() {error: a function-definition is not allowed here before ‘{’ token
 int main() {		break;

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

#endif
