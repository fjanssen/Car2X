#!/bin/sh
#
# This file was automatically generated.
#
# It can be overwritten by nios2-flash-programmer-generate or nios2-flash-programmer-gui.
#

#
# Converting SOF File: C:\Users\Florian\Documents\GitHub\SafetyCar\firmware\main\application\sopc_info\DE0_Nano_20131216.sof to: "..\flash/DE0_Nano_20131216_epcs.flash"
#
sof2flash --input="C:/Users/Florian/Documents/GitHub/SafetyCar/firmware/main/application/sopc_info/DE0_Nano_20131216.sof" --output="../flash/DE0_Nano_20131216_epcs.flash" --epcs 

#
# Programming File: "..\flash/DE0_Nano_20131216_epcs.flash" To Device: epcs
#
nios2-flash-programmer "../flash/DE0_Nano_20131216_epcs.flash" --base=0x4000000 --epcs --sidp=0x5000060 --id=0x0 --accept-bad-sysid --device=1 --instance=0 '--cable=USB-Blaster on localhost [USB-0]' --program 

#
# Converting ELF File: C:\Users\Florian\Documents\GitHub\SafetyCar\firmware\main\application\motor_control\motor_control.elf to: "..\flash/motor_control_epcs.flash"
#
elf2flash --input="C:/Users/Florian/Documents/GitHub/SafetyCar/firmware/main/application/motor_control/motor_control.elf" --output="../flash/motor_control_epcs.flash" --epcs --after="../flash/DE0_Nano_20131216_epcs.flash" 

#
# Programming File: "..\flash/motor_control_epcs.flash" To Device: epcs
#
nios2-flash-programmer "../flash/motor_control_epcs.flash" --base=0x4000000 --epcs --sidp=0x5000060 --id=0x0 --accept-bad-sysid --device=1 --instance=0 '--cable=USB-Blaster on localhost [USB-0]' --program 

