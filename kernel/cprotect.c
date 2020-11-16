#include "util.h"
#include "const.h"
#include "type.h"
#include "memory.h"
#include "protect.h"
extern IDT idt_ptr;
void Init_8259(){
    out_byte(MASTER_8259_PORT1,ICW1);
    out_byte(CASCADE_8259_PORT1,ICW1);

    out_byte(MASTER_8259_PORT2,ICW2_MAST);
    out_byte(CASCADE_8259_PORT2,ICW2_CASCADE);
    
    out_byte(MASTER_8259_PORT2,ICW3_MAST);
    out_byte(CASCADE_8259_PORT2,ICW3_CASCADE);

    out_byte(MASTER_8259_PORT2,ICW4);
    out_byte(CASCADE_8259_PORT2,ICW4);

    //开启定时器中断
    out_byte(MASTER_8259_PORT2,OCW1_MAST);
    out_byte(CASCADE_8259_PORT2,OCW1_CASCADE);
}

void Init_RTC(){


}

void SetInt(int num,u32 addr){
    Int_Descriptor Idesc;
    Idesc.code_sel = Sele_Code_4GB;
    Idesc.low_off = addr;
    Idesc.high_off = (addr>>16);
    Idesc.attr = 0x8e00;
    u32 idt_address = u16_and_u16(idt_ptr.idt_high_addr,idt_ptr.idt_low_addr) + num*8;
    memcpy(idt_address,&Idesc,8);
}