#include <bits/stdc++.h>
#include "pipeline.cpp"
using namespace std;

string dummy_instruction = "00100111111100000000000000000000";

int main(){
    vector<string> v;
    Assembler* assembler = new Assembler();
    Fetch* f=new Fetch();
    v=assembler->generateMachineCode();
    f->setMachineCode(v);
    ControlUnit* c=new ControlUnit();
    ALU* alu=new ALU();
    Cache* cache=new Cache();
    Memory* mem=new Memory(*cache);
    Writeback* wb=new Writeback();

    int cnt=0, meaningfulInstructions=0;
    bool skip=0;
    while(!finito){
        if(!skip){
            f->setInstruction(v);
            if(f->getIn(0,32) != dummy_instruction) meaningfulInstructions++; //if not addi $31,$0,0 which is our dummy instruction
        }

        c->takeFromRegister();
        alu->takeFromRegister();
        mem->takeFromRegister();
        wb->takeFromRegister();
        if(skip){
            skip=0;
            cnt++;
        }

        f->giveToRegister();
        c->giveToRegister();
        alu->giveToRegister();
        mem->giveToRegister();
        wb->writeBackToRegister();

        if(cnt<1)skip=stall(f);
        else cnt=0;
        
        Clock++;
    }
    out<<"Clocks: "<<Clock<<"\n";
    out<<"CPI : "<<setprecision(10)<<float(float(Clock)/meaningfulInstructions)<<"\n";
    return 0;
}