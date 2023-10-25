# RISC-V based Magnetic Intruder Detection System
## Aim
To make a simple intruder alert system allowing monitoring of multiple points of entry with alarms triggered due to magnetic reed switches, utilizing a specialized RISCV processor.

## Description
The Magnetic Intruder Alert System with Multi-Door/Window Monitoring is a practical and versatile security solution that allows you to monitor multiple entry points in your home or workspace.
This DIY project utilizes magnetic reed switches, LEDs and a piezo-electric buzzer to provide real-time feedback on which door or window has been triggered, alerting you to potential intruders or unauthorized access.

## Working
1. Reed switches are attached to each door/window using magnets. When the door/window opens, the magnet moves away triggering the reed switch. Reed switches are connected to digital input pins. Each switch is monitored separately.
2. Corresponding LEDs are connected to digital output pins - one LED per input switch. The RISC-V processor code continuously monitors the state of each input pin.
3. When a pin reads 'LOW' due to a switch disconnection on opening of a door, the code lights up the respective LED. This helps identify visually which sensor/door has been triggered.
4. A piezo buzzer is also sounded on detection for an audible alert.

## Block Diagram

![alt text](https://github.com/aamodbk/RISCV_magnetic_intruder_detector/blob/main/blockdiagram.png)

## C Code

```
#define MAG0 1
#define MAG1 2
#define MAG2 4
#define LED0 8
#define LED1 16
#define LED2 32
#define BUZZER 64

int main()
{
    int ledpin_val[3] = {0xFFFFFFF7, 0xFFFFFFEF, 0xFFFFFFDF};   // LED0 - 11111111111111111111111111110111
                                                            // LED1 - 11111111111111111111111111101111
                                                            // LED2 - 11111111111111111111111111011111

    int buzzerpin_val = 0xFFFFFFBF;   // BUZZ - 11111111111111111111111110111111

    // Output pins
    int buzzerpin = 0;
    int ledpin[3] = {0};

    // Input pins 
    int magpin[3] = {0};

    while(1){
        // Read from the magnetic reed switches
        asm (
            "and %0, x30, 1"        //MAG0
            : "=r"(magpin[0])
        );

        asm (
            "and %0, x30, 2"        //MAG1
            : "=r"(magpin[1])
        );

        asm (
            "and %0, x30, 4"        //MAG2
            : "=r"(magpin[2])
        );

        if(!magpin[0]){
            buzzerpin = 1;
            asm (
                "and x30, x30, %0\n\t"
                "or x30, x30, 64"       //BUZZER
                :
                :"r"(buzzerpin_val)
                :"x30"
            );
            ledpin[0] = 1;
            asm (
                "and x30, x30, %0\n\t"
                "or x30, x30, 8"         //LED0
                :
                :"r"(ledpin_val[0])
                :"x30"
            );
        }
        if(!magpin[1]){
            buzzerpin = 1;
            asm (
                "and x30, x30, %0\n\t"
                "or x30, x30, 64"       //BUZZER
                :
                :"r"(buzzerpin_val)
                :"x30"
            );
            ledpin[1] = 1;
            asm (
                "and x30, x30, %0\n\t"
                "or x30, x30, 16"         //LED1
                :
                :"r"(ledpin_val[1])
                :"x30"
            );
        }
        if(!magpin[2]){
            buzzerpin = 1;
            asm (
                "and x30, x30, %0\n\t"
                "or x30, x30, 64"       //BUZZER
                :
                :"r"(buzzerpin_val)
                :"x30"
            );
            ledpin[2] = 1;
            asm (
                "and x30, x30, %0\n\t"
                "or x30, x30, 32"         //LED2
                :
                :"r"(ledpin_val[2])
                :"x30"
            );
        }
        if(magpin[0] && magpin[1] && magpin[2]){
            buzzerpin = 0;
            asm (
                "and x30, x30, %0\n\t"
                "or x30, x30, 0"       //BUZZER
                :
                :"r"(buzzerpin_val)
                :"x30"
            );
            ledpin[0] = 0;
            ledpin[1] = 0;
            ledpin[2] = 0;
            asm (
                "and x30, x30, %0\n\t"
                "or x30, x30, 0"         //LED0
                :
                :"r"(ledpin_val[0])
                :"x30"
            );
            asm (
                "and x30, x30, %0\n\t"
                "or x30, x30, 0"         //LED1
                :
                :"r"(ledpin_val[1])
                :"x30"
            );
            asm (
                "and x30, x30, %0\n\t"
                "or x30, x30, 0"         //LED2
                :
                :"r"(ledpin_val[2])
                :"x30"
            );
        }
    }

    return 0;
}
```
## Assembly Code
To obtain assembly code type the following commands in the terminal:
```
riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o out intruder_detector.c
riscv32-unknown-elf-objdump -d -r out > asm.txt
```

The below `asm.txt` file is obtained:

```


out:     file format elf32-littleriscv


Disassembly of section .text:

00010074 <main>:
   10074:	fc010113          	addi	sp,sp,-64
   10078:	02812e23          	sw	s0,60(sp)
   1007c:	04010413          	addi	s0,sp,64
   10080:	ff700793          	li	a5,-9
   10084:	fcf42e23          	sw	a5,-36(s0)
   10088:	fef00793          	li	a5,-17
   1008c:	fef42023          	sw	a5,-32(s0)
   10090:	fdf00793          	li	a5,-33
   10094:	fef42223          	sw	a5,-28(s0)
   10098:	fbf00793          	li	a5,-65
   1009c:	fef42623          	sw	a5,-20(s0)
   100a0:	fe042423          	sw	zero,-24(s0)
   100a4:	fc042823          	sw	zero,-48(s0)
   100a8:	fc042a23          	sw	zero,-44(s0)
   100ac:	fc042c23          	sw	zero,-40(s0)
   100b0:	fc042223          	sw	zero,-60(s0)
   100b4:	fc042423          	sw	zero,-56(s0)
   100b8:	fc042623          	sw	zero,-52(s0)
   100bc:	001f7793          	andi	a5,t5,1
   100c0:	fcf42223          	sw	a5,-60(s0)
   100c4:	002f7793          	andi	a5,t5,2
   100c8:	fcf42423          	sw	a5,-56(s0)
   100cc:	004f7793          	andi	a5,t5,4
   100d0:	fcf42623          	sw	a5,-52(s0)
   100d4:	fc442783          	lw	a5,-60(s0)
   100d8:	02079663          	bnez	a5,10104 <main+0x90>
   100dc:	00100793          	li	a5,1
   100e0:	fef42423          	sw	a5,-24(s0)
   100e4:	fec42783          	lw	a5,-20(s0)
   100e8:	00ff7f33          	and	t5,t5,a5
   100ec:	040f6f13          	ori	t5,t5,64
   100f0:	00100793          	li	a5,1
   100f4:	fcf42823          	sw	a5,-48(s0)
   100f8:	fdc42783          	lw	a5,-36(s0)
   100fc:	00ff7f33          	and	t5,t5,a5
   10100:	008f6f13          	ori	t5,t5,8
   10104:	fc842783          	lw	a5,-56(s0)
   10108:	02079663          	bnez	a5,10134 <main+0xc0>
   1010c:	00100793          	li	a5,1
   10110:	fef42423          	sw	a5,-24(s0)
   10114:	fec42783          	lw	a5,-20(s0)
   10118:	00ff7f33          	and	t5,t5,a5
   1011c:	040f6f13          	ori	t5,t5,64
   10120:	00100793          	li	a5,1
   10124:	fcf42a23          	sw	a5,-44(s0)
   10128:	fe042783          	lw	a5,-32(s0)
   1012c:	00ff7f33          	and	t5,t5,a5
   10130:	010f6f13          	ori	t5,t5,16
   10134:	fcc42783          	lw	a5,-52(s0)
   10138:	02079663          	bnez	a5,10164 <main+0xf0>
   1013c:	00100793          	li	a5,1
   10140:	fef42423          	sw	a5,-24(s0)
   10144:	fec42783          	lw	a5,-20(s0)
   10148:	00ff7f33          	and	t5,t5,a5
   1014c:	040f6f13          	ori	t5,t5,64
   10150:	00100793          	li	a5,1
   10154:	fcf42c23          	sw	a5,-40(s0)
   10158:	fe442783          	lw	a5,-28(s0)
   1015c:	00ff7f33          	and	t5,t5,a5
   10160:	020f6f13          	ori	t5,t5,32
   10164:	fc442783          	lw	a5,-60(s0)
   10168:	f4078ae3          	beqz	a5,100bc <main+0x48>
   1016c:	fc842783          	lw	a5,-56(s0)
   10170:	f40786e3          	beqz	a5,100bc <main+0x48>
   10174:	fcc42783          	lw	a5,-52(s0)
   10178:	f40782e3          	beqz	a5,100bc <main+0x48>
   1017c:	fe042423          	sw	zero,-24(s0)
   10180:	fec42783          	lw	a5,-20(s0)
   10184:	00ff7f33          	and	t5,t5,a5
   10188:	000f6f13          	ori	t5,t5,0
   1018c:	fc042823          	sw	zero,-48(s0)
   10190:	fc042a23          	sw	zero,-44(s0)
   10194:	fc042c23          	sw	zero,-40(s0)
   10198:	fdc42783          	lw	a5,-36(s0)
   1019c:	00ff7f33          	and	t5,t5,a5
   101a0:	000f6f13          	ori	t5,t5,0
   101a4:	fe042783          	lw	a5,-32(s0)
   101a8:	00ff7f33          	and	t5,t5,a5
   101ac:	000f6f13          	ori	t5,t5,0
   101b0:	fe442783          	lw	a5,-28(s0)
   101b4:	00ff7f33          	and	t5,t5,a5
   101b8:	000f6f13          	ori	t5,t5,0
   101bc:	f01ff06f          	j	100bc <main+0x48>


```

## Unique Instructions
Using the python script `instr_counter.py`, the following unique instructions are observed:

```
List of unique instructions:
beqz
j
bnez
li
addi
andi
ori
and
lw
sw
```

## References
1. https://github.com/SakethGajawada/RISCV_GNU/tree/main
