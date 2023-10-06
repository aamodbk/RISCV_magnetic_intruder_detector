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

## C code

## Assembly code

## Unique Instructions


## References
1. https://github.com/SakethGajawada/RISCV_GNU/tree/main
