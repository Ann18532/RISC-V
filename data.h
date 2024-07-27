#include<bits/stdc++.h>
using namespace std;

map<string,string> opCode;//opCode for different instructions
map<string,string> funct3;//funct3 type for different R-type instructions and branch instructions
map<string,string> funct7;//for R-type
map<string,int> indicesOfLabels;//contains the line index number in the assembly code at which the labels first appeared, needed for branch/jump


/*  Instr.   opCode
    label :  0000000
    rtype :  0110011
    imm   :  0010011
    lw    :  0000011
    st    :  0100011
    jump :  1101111
    branch:  1100011 

    operations supported:
    add
    sub
    xor
    or
    and

    funct3(for r type):
    add: 000
    sub: 000
    or:  110
    xor: 100
    and: 111

    funct3(for branch type):
    beq: 000 (branch if equal)
    bne: 001 (branch if not equal)
    blt: 100 (branch if less than)
    bge: 101 (branch if greater than or equal)

    funct7:
    add: 0000000
    sub: 0100000
    or:  0000000
    xor: 0000000
    and: 0000000

    note: load and store use direct memory access for simplicity instead of register relative
      */   


void init(){
    opCode.insert({"rtype", "0110011"});
    opCode.insert({"imm", "0010011"});
    opCode.insert({"lw", "0000011"});
    opCode.insert({"st", "0100011"});
    opCode.insert({"jal", "1101111"});
    opCode.insert({"branch", "1100011"});
                                            
    funct3.insert({"add", "000"});
    funct3.insert({"sub", "000"});
    funct3.insert({"or", "110"});
    funct3.insert({"xor", "100"});
    funct3.insert({"and", "111"});

    funct3.insert({"beq", "000"}); 
    funct3.insert({"bne", "001"}); 
    funct3.insert({"blt", "100"}); 
    funct3.insert({"bge", "101"}); 

    funct7.insert({"add", "0000000"});
    funct7.insert({"sub", "0100000"});
    funct7.insert({"or", "0000000"});
    funct7.insert({"xor", "0000000"});
    funct7.insert({"and", "0000000"});
}