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
// #include<stdio.h>
// #include<stdlib.h>

int main()
{
    // int test0, test1, test2, test3;

    int ledpin_mask[3] = {0xFFFFFFF7,   // LED0 - 11111111111111111111111111110111
                            0xFFFFFFEF,     // LED1 - 11111111111111111111111111101111
                            0xFFFFFFDF};    // LED2 - 11111111111111111111111111011111

    int buzzerpin_mask = 0xFFFFFFBF;   // BUZZ - 11111111111111111111111110111111
    
    // Output pins
    int buzzerpin = 0;
    int ledpin[3] = {0};

    // Input pins 
    int magpin[3] = {0};

    // Registers for each outputs
    int buzzer_reg;
    int led_reg[3];

    buzzerpin = 0;
    buzzer_reg = buzzerpin*64;
    asm volatile (
        "and x30, x30, %0\n\t"
        "or x30, x30, %1"       //BUZZER
        :
        :"r"(buzzerpin_mask), "r"(buzzer_reg)
        :"x30"
    );
    ledpin[0] = 0;
    led_reg[0] = ledpin[0]*8;
    ledpin[1] = 0;
    led_reg[1] = ledpin[1]*16;
    ledpin[2] = 0;
    led_reg[2] = ledpin[2]*32;
    asm volatile (
        "and x30, x30, %0\n\t"
        "or x30, x30, %1"         //LED0
        :
        :"r"(ledpin_mask[0]), "r"(led_reg[0])
        :"x30"
    );
    asm volatile (
        "and x30, x30, %0\n\t"
        "or x30, x30, %1"         //LED1
        :
        :"r"(ledpin_mask[1]), "r"(led_reg[1])
        :"x30"
    );
    asm volatile (
        "and x30, x30, %0\n\t"
        "or x30, x30, %1"         //LED2
        :
        :"r"(ledpin_mask[2]), "r"(led_reg[2])
        :"x30"
    );
    // asm volatile (
    //         "addi %0, x30, 0\n\t"
    //         :"=r"(test0)
    //         :
    //         :"x30"
    // 	);
    // 	printf("\nx30 reg value in setup = %d\n", test0);
    // printf("During Setup: Buzzer = %d, LED0 = %d, LED1 = %d, LED2 = %d\n", buzzerpin, ledpin[0], ledpin[1], ledpin[2]);

    // for(int i=0; i<1; i++){
    while(1){
        // Read from the magnetic reed switches
        asm volatile (
            "andi %0, x30, 1"        //MAG0
            : "=r"(magpin[0])
        );

        asm volatile (
            "andi %0, x30, 2"        //MAG1
            : "=r"(magpin[1])
        );

        asm volatile (
            "andi %0, x30, 4"        //MAG2
            : "=r"(magpin[2])
        );

        // asm volatile (
        //     "addi %0, x30, 0\n\t"
        //     :"=r"(test1)
        //     :
        //     :"x30"
    	// );
    	// printf("\nx30 reg value before = %d\n", test1);
        // magpin[0] = 0;
        // magpin[1] = 0;
        // magpin[2] = 0;

        if(!magpin[0]){
            buzzerpin = 1;
            buzzer_reg = buzzerpin*64;
            asm volatile (
                "and x30, x30, %0\n\t"
                "or x30, x30, %1"       //BUZZER
                :
                :"r"(buzzerpin_mask), "r"(buzzer_reg)
                :"x30"
            );
            ledpin[0] = 1;
            led_reg[0] = ledpin[0]*8;
            asm volatile (
                "and x30, x30, %0\n\t"
                "or x30, x30, %1"         //LED0
                :
                :"r"(ledpin_mask[0]), "r"(led_reg[0])
                :"x30"
            );
        }
        if(!magpin[1]){
            buzzerpin = 1;
            buzzer_reg = buzzerpin*64;
            asm volatile (
                "and x30, x30, %0\n\t"
                "or x30, x30, %1"       //BUZZER
                :
                :"r"(buzzerpin_mask), "r"(buzzer_reg)
                :"x30"
            );
            ledpin[1] = 1;
            led_reg[1] = ledpin[1]*16;
            asm volatile (
                "and x30, x30, %0\n\t"
                "or x30, x30, %1"         //LED1
                :
                :"r"(ledpin_mask[1]), "r"(led_reg[1])
                :"x30"
            );
        }
        if(!magpin[2]){
            buzzerpin = 1;
            buzzer_reg = buzzerpin*64;
            asm volatile (
                "and x30, x30, %0\n\t"
                "or x30, x30, %1"       //BUZZER
                :
                :"r"(buzzerpin_mask), "r"(buzzer_reg)
                :"x30"
            );
            ledpin[2] = 1;
            led_reg[2] = ledpin[2]*32;
            asm volatile (
                "and x30, x30, %0\n\t"
                "or x30, x30, %1"         //LED2
                :
                :"r"(ledpin_mask[2]), "r"(led_reg[2])
                :"x30"
            );
        }

        if(magpin[0] && magpin[1] && magpin[2]){
            buzzerpin = 0;
            buzzer_reg = buzzerpin*64;
            asm volatile (
                "and x30, x30, %0\n\t"
                "or x30, x30, %1"       //BUZZER
                :
                :"r"(buzzerpin_mask), "r"(buzzer_reg)
                :"x30"
            );
            ledpin[0] = 0;
            led_reg[0] = ledpin[0]*8;
            ledpin[1] = 0;
            led_reg[1] = ledpin[1]*16;
            ledpin[2] = 0;
            led_reg[2] = ledpin[2]*32;
            asm volatile (
                "and x30, x30, %0\n\t"
                "or x30, x30, %1"         //LED0
                :
                :"r"(ledpin_mask[0]), "r"(led_reg[0])
                :"x30"
            );
            asm volatile (
                "and x30, x30, %0\n\t"
                "or x30, x30, %1"         //LED1
                :
                :"r"(ledpin_mask[1]), "r"(led_reg[1])
                :"x30"
            );
            asm volatile (
                "and x30, x30, %0\n\t"
                "or x30, x30, %1"         //LED2
                :
                :"r"(ledpin_mask[2]), "r"(led_reg[2])
                :"x30"
            );
        }

        // asm volatile(
        //     "addi %0, x30, 0\n\t"
        //     :"=r"(test2)
        //     :
        //     :"x30"
        // );
        // printf("\nx30 reg value after = %d\n", test2);

        // printf("After one loop: Buzzer = %d, LED0 = %d, LED1 = %d, LED2 = %d\n", buzzerpin, ledpin[0], ledpin[1], ledpin[2]);
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

00010054 <main>:
   10054:	fb010113          	addi	sp,sp,-80
   10058:	04812623          	sw	s0,76(sp)
   1005c:	05010413          	addi	s0,sp,80
   10060:	ff700793          	li	a5,-9
   10064:	fcf42c23          	sw	a5,-40(s0)
   10068:	fef00793          	li	a5,-17
   1006c:	fcf42e23          	sw	a5,-36(s0)
   10070:	fdf00793          	li	a5,-33
   10074:	fef42023          	sw	a5,-32(s0)
   10078:	fbf00793          	li	a5,-65
   1007c:	fef42623          	sw	a5,-20(s0)
   10080:	fe042423          	sw	zero,-24(s0)
   10084:	fc042623          	sw	zero,-52(s0)
   10088:	fc042823          	sw	zero,-48(s0)
   1008c:	fc042a23          	sw	zero,-44(s0)
   10090:	fc042023          	sw	zero,-64(s0)
   10094:	fc042223          	sw	zero,-60(s0)
   10098:	fc042423          	sw	zero,-56(s0)
   1009c:	fe042423          	sw	zero,-24(s0)
   100a0:	fe842783          	lw	a5,-24(s0)
   100a4:	00679793          	slli	a5,a5,0x6
   100a8:	fef42223          	sw	a5,-28(s0)
   100ac:	fec42783          	lw	a5,-20(s0)
   100b0:	fe442703          	lw	a4,-28(s0)
   100b4:	00ff7f33          	and	t5,t5,a5
   100b8:	00ef6f33          	or	t5,t5,a4
   100bc:	fc042623          	sw	zero,-52(s0)
   100c0:	fcc42783          	lw	a5,-52(s0)
   100c4:	00379793          	slli	a5,a5,0x3
   100c8:	faf42a23          	sw	a5,-76(s0)
   100cc:	fc042823          	sw	zero,-48(s0)
   100d0:	fd042783          	lw	a5,-48(s0)
   100d4:	00479793          	slli	a5,a5,0x4
   100d8:	faf42c23          	sw	a5,-72(s0)
   100dc:	fc042a23          	sw	zero,-44(s0)
   100e0:	fd442783          	lw	a5,-44(s0)
   100e4:	00579793          	slli	a5,a5,0x5
   100e8:	faf42e23          	sw	a5,-68(s0)
   100ec:	fd842783          	lw	a5,-40(s0)
   100f0:	fb442703          	lw	a4,-76(s0)
   100f4:	00ff7f33          	and	t5,t5,a5
   100f8:	00ef6f33          	or	t5,t5,a4
   100fc:	fdc42783          	lw	a5,-36(s0)
   10100:	fb842703          	lw	a4,-72(s0)
   10104:	00ff7f33          	and	t5,t5,a5
   10108:	00ef6f33          	or	t5,t5,a4
   1010c:	fe042783          	lw	a5,-32(s0)
   10110:	fbc42703          	lw	a4,-68(s0)
   10114:	00ff7f33          	and	t5,t5,a5
   10118:	00ef6f33          	or	t5,t5,a4
   1011c:	001f7793          	andi	a5,t5,1
   10120:	fcf42023          	sw	a5,-64(s0)
   10124:	002f7793          	andi	a5,t5,2
   10128:	fcf42223          	sw	a5,-60(s0)
   1012c:	004f7793          	andi	a5,t5,4
   10130:	fcf42423          	sw	a5,-56(s0)
   10134:	fc042783          	lw	a5,-64(s0)
   10138:	04079663          	bnez	a5,10184 <main+0x130>
   1013c:	00100793          	li	a5,1
   10140:	fef42423          	sw	a5,-24(s0)
   10144:	fe842783          	lw	a5,-24(s0)
   10148:	00679793          	slli	a5,a5,0x6
   1014c:	fef42223          	sw	a5,-28(s0)
   10150:	fec42783          	lw	a5,-20(s0)
   10154:	fe442703          	lw	a4,-28(s0)
   10158:	00ff7f33          	and	t5,t5,a5
   1015c:	00ef6f33          	or	t5,t5,a4
   10160:	00100793          	li	a5,1
   10164:	fcf42623          	sw	a5,-52(s0)
   10168:	fcc42783          	lw	a5,-52(s0)
   1016c:	00379793          	slli	a5,a5,0x3
   10170:	faf42a23          	sw	a5,-76(s0)
   10174:	fd842783          	lw	a5,-40(s0)
   10178:	fb442703          	lw	a4,-76(s0)
   1017c:	00ff7f33          	and	t5,t5,a5
   10180:	00ef6f33          	or	t5,t5,a4
   10184:	fc442783          	lw	a5,-60(s0)
   10188:	04079663          	bnez	a5,101d4 <main+0x180>
   1018c:	00100793          	li	a5,1
   10190:	fef42423          	sw	a5,-24(s0)
   10194:	fe842783          	lw	a5,-24(s0)
   10198:	00679793          	slli	a5,a5,0x6
   1019c:	fef42223          	sw	a5,-28(s0)
   101a0:	fec42783          	lw	a5,-20(s0)
   101a4:	fe442703          	lw	a4,-28(s0)
   101a8:	00ff7f33          	and	t5,t5,a5
   101ac:	00ef6f33          	or	t5,t5,a4
   101b0:	00100793          	li	a5,1
   101b4:	fcf42823          	sw	a5,-48(s0)
   101b8:	fd042783          	lw	a5,-48(s0)
   101bc:	00479793          	slli	a5,a5,0x4
   101c0:	faf42c23          	sw	a5,-72(s0)
   101c4:	fdc42783          	lw	a5,-36(s0)
   101c8:	fb842703          	lw	a4,-72(s0)
   101cc:	00ff7f33          	and	t5,t5,a5
   101d0:	00ef6f33          	or	t5,t5,a4
   101d4:	fc842783          	lw	a5,-56(s0)
   101d8:	04079663          	bnez	a5,10224 <main+0x1d0>
   101dc:	00100793          	li	a5,1
   101e0:	fef42423          	sw	a5,-24(s0)
   101e4:	fe842783          	lw	a5,-24(s0)
   101e8:	00679793          	slli	a5,a5,0x6
   101ec:	fef42223          	sw	a5,-28(s0)
   101f0:	fec42783          	lw	a5,-20(s0)
   101f4:	fe442703          	lw	a4,-28(s0)
   101f8:	00ff7f33          	and	t5,t5,a5
   101fc:	00ef6f33          	or	t5,t5,a4
   10200:	00100793          	li	a5,1
   10204:	fcf42a23          	sw	a5,-44(s0)
   10208:	fd442783          	lw	a5,-44(s0)
   1020c:	00579793          	slli	a5,a5,0x5
   10210:	faf42e23          	sw	a5,-68(s0)
   10214:	fe042783          	lw	a5,-32(s0)
   10218:	fbc42703          	lw	a4,-68(s0)
   1021c:	00ff7f33          	and	t5,t5,a5
   10220:	00ef6f33          	or	t5,t5,a4
   10224:	fc042783          	lw	a5,-64(s0)
   10228:	ee078ae3          	beqz	a5,1011c <main+0xc8>
   1022c:	fc442783          	lw	a5,-60(s0)
   10230:	ee0786e3          	beqz	a5,1011c <main+0xc8>
   10234:	fc842783          	lw	a5,-56(s0)
   10238:	ee0782e3          	beqz	a5,1011c <main+0xc8>
   1023c:	fe042423          	sw	zero,-24(s0)
   10240:	fe842783          	lw	a5,-24(s0)
   10244:	00679793          	slli	a5,a5,0x6
   10248:	fef42223          	sw	a5,-28(s0)
   1024c:	fec42783          	lw	a5,-20(s0)
   10250:	fe442703          	lw	a4,-28(s0)
   10254:	00ff7f33          	and	t5,t5,a5
   10258:	00ef6f33          	or	t5,t5,a4
   1025c:	fc042623          	sw	zero,-52(s0)
   10260:	fcc42783          	lw	a5,-52(s0)
   10264:	00379793          	slli	a5,a5,0x3
   10268:	faf42a23          	sw	a5,-76(s0)
   1026c:	fc042823          	sw	zero,-48(s0)
   10270:	fd042783          	lw	a5,-48(s0)
   10274:	00479793          	slli	a5,a5,0x4
   10278:	faf42c23          	sw	a5,-72(s0)
   1027c:	fc042a23          	sw	zero,-44(s0)
   10280:	fd442783          	lw	a5,-44(s0)
   10284:	00579793          	slli	a5,a5,0x5
   10288:	faf42e23          	sw	a5,-68(s0)
   1028c:	fd842783          	lw	a5,-40(s0)
   10290:	fb442703          	lw	a4,-76(s0)
   10294:	00ff7f33          	and	t5,t5,a5
   10298:	00ef6f33          	or	t5,t5,a4
   1029c:	fdc42783          	lw	a5,-36(s0)
   102a0:	fb842703          	lw	a4,-72(s0)
   102a4:	00ff7f33          	and	t5,t5,a5
   102a8:	00ef6f33          	or	t5,t5,a4
   102ac:	fe042783          	lw	a5,-32(s0)
   102b0:	fbc42703          	lw	a4,-68(s0)
   102b4:	00ff7f33          	and	t5,t5,a5
   102b8:	00ef6f33          	or	t5,t5,a4
   102bc:	e61ff06f          	j	1011c <main+0xc8>

```

## Unique Instructions
Using the python script `instr_counter.py`, the following unique instructions are observed:

```
Number of different instructions: 11
List of unique instructions:
li
andi
beqz
slli
bnez
and
j
or
sw
addi
lw
```

## Spike Simulation
The following code is used for spike simulation:

```
#include<stdio.h>
#include<stdlib.h>

int main()
{
    int test0, test1, test2, test3;

    int ledpin_mask[3] = {0xFFFFFFF7,   // LED0 - 11111111111111111111111111110111
                            0xFFFFFFEF,     // LED1 - 11111111111111111111111111101111
                            0xFFFFFFDF};    // LED2 - 11111111111111111111111111011111

    int buzzerpin_mask = 0xFFFFFFBF;   // BUZZ - 11111111111111111111111110111111
    
    // Output pins
    int buzzerpin = 0;
    int ledpin[3] = {0};

    // Input pins 
    int magpin[3] = {0};

    // Registers for each outputs
    int buzzer_reg;
    int led_reg[3];

    buzzerpin = 0;
    buzzer_reg = buzzerpin*64;
    asm volatile (
        "and x30, x30, %0\n\t"
        "or x30, x30, %1"       //BUZZER
        :
        :"r"(buzzerpin_mask), "r"(buzzer_reg)
        :"x30"
    );
    ledpin[0] = 0;
    led_reg[0] = ledpin[0]*8;
    ledpin[1] = 0;
    led_reg[1] = ledpin[1]*16;
    ledpin[2] = 0;
    led_reg[2] = ledpin[2]*32;
    asm volatile (
        "and x30, x30, %0\n\t"
        "or x30, x30, %1"         //LED0
        :
        :"r"(ledpin_mask[0]), "r"(led_reg[0])
        :"x30"
    );
    asm volatile (
        "and x30, x30, %0\n\t"
        "or x30, x30, %1"         //LED1
        :
        :"r"(ledpin_mask[1]), "r"(led_reg[1])
        :"x30"
    );
    asm volatile (
        "and x30, x30, %0\n\t"
        "or x30, x30, %1"         //LED2
        :
        :"r"(ledpin_mask[2]), "r"(led_reg[2])
        :"x30"
    );
    asm volatile (
            "addi %0, x30, 0\n\t"
            :"=r"(test0)
            :
            :"x30"
    	);
    	printf("\nx30 reg value in setup = %d\n", test0);
    printf("During Setup: Buzzer = %d, LED0 = %d, LED1 = %d, LED2 = %d\n", buzzerpin, ledpin[0], ledpin[1], ledpin[2]);

    for(int i=0; i<1; i++){
    // while(1){
        // Read from the magnetic reed switches
        asm volatile (
            "andi %0, x30, 1"        //MAG0
            : "=r"(magpin[0])
        );

        asm volatile (
            "andi %0, x30, 2"        //MAG1
            : "=r"(magpin[1])
        );

        asm volatile (
            "andi %0, x30, 4"        //MAG2
            : "=r"(magpin[2])
        );

        asm volatile (
            "addi %0, x30, 0\n\t"
            :"=r"(test1)
            :
            :"x30"
    	);
    	printf("\nx30 reg value before = %d\n", test1);
        magpin[0] = 0;
        magpin[1] = 0;
        magpin[2] = 0;

        if(!magpin[0]){
            buzzerpin = 1;
            buzzer_reg = buzzerpin*64;
            asm volatile (
                "and x30, x30, %0\n\t"
                "or x30, x30, %1"       //BUZZER
                :
                :"r"(buzzerpin_mask), "r"(buzzer_reg)
                :"x30"
            );
            ledpin[0] = 1;
            led_reg[0] = ledpin[0]*8;
            asm volatile (
                "and x30, x30, %0\n\t"
                "or x30, x30, %1"         //LED0
                :
                :"r"(ledpin_mask[0]), "r"(led_reg[0])
                :"x30"
            );
        }
        if(!magpin[1]){
            buzzerpin = 1;
            buzzer_reg = buzzerpin*64;
            asm volatile (
                "and x30, x30, %0\n\t"
                "or x30, x30, %1"       //BUZZER
                :
                :"r"(buzzerpin_mask), "r"(buzzer_reg)
                :"x30"
            );
            ledpin[1] = 1;
            led_reg[1] = ledpin[1]*16;
            asm volatile (
                "and x30, x30, %0\n\t"
                "or x30, x30, %1"         //LED1
                :
                :"r"(ledpin_mask[1]), "r"(led_reg[1])
                :"x30"
            );
        }
        if(!magpin[2]){
            buzzerpin = 1;
            buzzer_reg = buzzerpin*64;
            asm volatile (
                "and x30, x30, %0\n\t"
                "or x30, x30, %1"       //BUZZER
                :
                :"r"(buzzerpin_mask), "r"(buzzer_reg)
                :"x30"
            );
            ledpin[2] = 1;
            led_reg[2] = ledpin[2]*32;
            asm volatile (
                "and x30, x30, %0\n\t"
                "or x30, x30, %1"         //LED2
                :
                :"r"(ledpin_mask[2]), "r"(led_reg[2])
                :"x30"
            );
        }

        if(magpin[0] && magpin[1] && magpin[2]){
            buzzerpin = 0;
            buzzer_reg = buzzerpin*64;
            asm volatile (
                "and x30, x30, %0\n\t"
                "or x30, x30, %1"       //BUZZER
                :
                :"r"(buzzerpin_mask), "r"(buzzer_reg)
                :"x30"
            );
            ledpin[0] = 0;
            led_reg[0] = ledpin[0]*8;
            ledpin[1] = 0;
            led_reg[1] = ledpin[1]*16;
            ledpin[2] = 0;
            led_reg[2] = ledpin[2]*32;
            asm volatile (
                "and x30, x30, %0\n\t"
                "or x30, x30, %1"         //LED0
                :
                :"r"(ledpin_mask[0]), "r"(led_reg[0])
                :"x30"
            );
            asm volatile (
                "and x30, x30, %0\n\t"
                "or x30, x30, %1"         //LED1
                :
                :"r"(ledpin_mask[1]), "r"(led_reg[1])
                :"x30"
            );
            asm volatile (
                "and x30, x30, %0\n\t"
                "or x30, x30, %1"         //LED2
                :
                :"r"(ledpin_mask[2]), "r"(led_reg[2])
                :"x30"
            );
        }

        asm volatile(
            "addi %0, x30, 0\n\t"
            :"=r"(test2)
            :
            :"x30"
        );
        printf("\nx30 reg value after = %d\n", test2);

        printf("After one loop: Buzzer = %d, LED0 = %d, LED1 = %d, LED2 = %d\n", buzzerpin, ledpin[0], ledpin[1], ledpin[2]);
    }

    return 0;
}
```

The above code is compiled and simulated with teh following commands:

```
riscv64-unknown-elf-gcc -march=rv64i -mabi=lp64 -ffreestanding -o out intruder_detector.c
spike $(which pk) out
```

Here different set of inputs are given for magpins. The outputs for all of them are correct as observed below:

For magpins = {1, 1, 1}:

![alt text](https://github.com/aamodbk/RISCV_magnetic_intruder_detector/blob/main/magpin111.png)

For magpins = {0, 1, 1}:

![alt text](https://github.com/aamodbk/RISCV_magnetic_intruder_detector/blob/main/magpin011.png)

For magpins = {1, 0, 1}:

![alt text](https://github.com/aamodbk/RISCV_magnetic_intruder_detector/blob/main/magpin101.png)

For magpins = {1, 1, 0}:

![alt text](https://github.com/aamodbk/RISCV_magnetic_intruder_detector/blob/main/magpin110.png)

For magpins = {0, 0, 0}:

![alt text](https://github.com/aamodbk/RISCV_magnetic_intruder_detector/blob/main/magpin000.png)

Similarly the outputs of the x30 register is verfied for all other combinations.

## References
1. https://github.com/SakethGajawada/RISCV_GNU/tree/main
