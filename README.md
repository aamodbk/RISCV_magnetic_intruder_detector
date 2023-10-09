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

int ledpin_val[3] = {0xFFFFFFF7, 0xFFFFFFEF, 0xFFFFFFDF};   // LED0 - 11111111111111111111111111110111
                                                            // LED1 - 11111111111111111111111111101111
                                                            // LED2 - 11111111111111111111111111011111

int buzzerpin_val = 0xFFFFFFBF;   // BUZZ - 11111111111111111111111110111111

// Output pins
int buzzerpin = 0;
int ledpin[3] = {0};

// Input pins 
int magpin[3] = {0};

int main()
{

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

```

intruder_detector:     file format elf32-littleriscv


Disassembly of section .text:

00010074 <main>:
   10074:	ff010113          	addi	sp,sp,-16
   10078:	00812623          	sw	s0,12(sp)
   1007c:	01010413          	addi	s0,sp,16
   10080:	001f7713          	andi	a4,t5,1
   10084:	82018793          	addi	a5,gp,-2016 # 11210 <magpin>
   10088:	00e7a023          	sw	a4,0(a5)
   1008c:	002f7713          	andi	a4,t5,2
   10090:	82018793          	addi	a5,gp,-2016 # 11210 <magpin>
   10094:	00e7a223          	sw	a4,4(a5)
   10098:	004f7713          	andi	a4,t5,4
   1009c:	82018793          	addi	a5,gp,-2016 # 11210 <magpin>
   100a0:	00e7a423          	sw	a4,8(a5)
   100a4:	82018793          	addi	a5,gp,-2016 # 11210 <magpin>
   100a8:	0007a783          	lw	a5,0(a5)
   100ac:	02079c63          	bnez	a5,100e4 <main+0x70>
   100b0:	00100713          	li	a4,1
   100b4:	80e1a823          	sw	a4,-2032(gp) # 11200 <_edata>
   100b8:	80c1a783          	lw	a5,-2036(gp) # 111fc <buzzerpin_val>
   100bc:	00ff7f33          	and	t5,t5,a5
   100c0:	040f6f13          	ori	t5,t5,64
   100c4:	81418793          	addi	a5,gp,-2028 # 11204 <ledpin>
   100c8:	00100713          	li	a4,1
   100cc:	00e7a023          	sw	a4,0(a5)
   100d0:	000117b7          	lui	a5,0x11
   100d4:	1f078793          	addi	a5,a5,496 # 111f0 <ledpin_val>
   100d8:	0007a783          	lw	a5,0(a5)
   100dc:	00ff7f33          	and	t5,t5,a5
   100e0:	008f6f13          	ori	t5,t5,8
   100e4:	82018793          	addi	a5,gp,-2016 # 11210 <magpin>
   100e8:	0047a783          	lw	a5,4(a5)
   100ec:	02079c63          	bnez	a5,10124 <main+0xb0>
   100f0:	00100713          	li	a4,1
   100f4:	80e1a823          	sw	a4,-2032(gp) # 11200 <_edata>
   100f8:	80c1a783          	lw	a5,-2036(gp) # 111fc <buzzerpin_val>
   100fc:	00ff7f33          	and	t5,t5,a5
   10100:	040f6f13          	ori	t5,t5,64
   10104:	81418793          	addi	a5,gp,-2028 # 11204 <ledpin>
   10108:	00100713          	li	a4,1
   1010c:	00e7a223          	sw	a4,4(a5)
   10110:	000117b7          	lui	a5,0x11
   10114:	1f078793          	addi	a5,a5,496 # 111f0 <ledpin_val>
   10118:	0047a783          	lw	a5,4(a5)
   1011c:	00ff7f33          	and	t5,t5,a5
   10120:	010f6f13          	ori	t5,t5,16
   10124:	82018793          	addi	a5,gp,-2016 # 11210 <magpin>
   10128:	0087a783          	lw	a5,8(a5)
   1012c:	02079c63          	bnez	a5,10164 <main+0xf0>
   10130:	00100713          	li	a4,1
   10134:	80e1a823          	sw	a4,-2032(gp) # 11200 <_edata>
   10138:	80c1a783          	lw	a5,-2036(gp) # 111fc <buzzerpin_val>
   1013c:	00ff7f33          	and	t5,t5,a5
   10140:	040f6f13          	ori	t5,t5,64
   10144:	81418793          	addi	a5,gp,-2028 # 11204 <ledpin>
   10148:	00100713          	li	a4,1
   1014c:	00e7a423          	sw	a4,8(a5)
   10150:	000117b7          	lui	a5,0x11
   10154:	1f078793          	addi	a5,a5,496 # 111f0 <ledpin_val>
   10158:	0087a783          	lw	a5,8(a5)
   1015c:	00ff7f33          	and	t5,t5,a5
   10160:	020f6f13          	ori	t5,t5,32
   10164:	82018793          	addi	a5,gp,-2016 # 11210 <magpin>
   10168:	0007a783          	lw	a5,0(a5)
   1016c:	f0078ae3          	beqz	a5,10080 <main+0xc>
   10170:	82018793          	addi	a5,gp,-2016 # 11210 <magpin>
   10174:	0047a783          	lw	a5,4(a5)
   10178:	f00784e3          	beqz	a5,10080 <main+0xc>
   1017c:	82018793          	addi	a5,gp,-2016 # 11210 <magpin>
   10180:	0087a783          	lw	a5,8(a5)
   10184:	ee078ee3          	beqz	a5,10080 <main+0xc>
   10188:	8001a823          	sw	zero,-2032(gp) # 11200 <_edata>
   1018c:	80c1a783          	lw	a5,-2036(gp) # 111fc <buzzerpin_val>
   10190:	00ff7f33          	and	t5,t5,a5
   10194:	000f6f13          	ori	t5,t5,0
   10198:	81418793          	addi	a5,gp,-2028 # 11204 <ledpin>
   1019c:	0007a023          	sw	zero,0(a5)
   101a0:	81418793          	addi	a5,gp,-2028 # 11204 <ledpin>
   101a4:	0007a223          	sw	zero,4(a5)
   101a8:	81418793          	addi	a5,gp,-2028 # 11204 <ledpin>
   101ac:	0007a423          	sw	zero,8(a5)
   101b0:	000117b7          	lui	a5,0x11
   101b4:	1f078793          	addi	a5,a5,496 # 111f0 <ledpin_val>
   101b8:	0007a783          	lw	a5,0(a5)
   101bc:	00ff7f33          	and	t5,t5,a5
   101c0:	000f6f13          	ori	t5,t5,0
   101c4:	000117b7          	lui	a5,0x11
   101c8:	1f078793          	addi	a5,a5,496 # 111f0 <ledpin_val>
   101cc:	0047a783          	lw	a5,4(a5)
   101d0:	00ff7f33          	and	t5,t5,a5
   101d4:	000f6f13          	ori	t5,t5,0
   101d8:	000117b7          	lui	a5,0x11
   101dc:	1f078793          	addi	a5,a5,496 # 111f0 <ledpin_val>
   101e0:	0087a783          	lw	a5,8(a5)
   101e4:	00ff7f33          	and	t5,t5,a5
   101e8:	000f6f13          	ori	t5,t5,0
   101ec:	e95ff06f          	j	10080 <main+0xc>
```

## Unique Instructions

```
Number of different instructions: 11
List of unique instructions:
li
bnez
lui
and
sw
andi
beqz
j
lw
addi
ori
```

## References
1. https://github.com/SakethGajawada/RISCV_GNU/tree/main
