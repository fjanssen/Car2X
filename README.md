# Car2X
This repository contains software, hardware configuration and documentation of the __Car2X communication__ group of the __Hardware/Software Codesign__ course in WS14.

## Getting started
Both the motor controller boards (DE0 "nano" board) and the central ECU (DE2 board) automatically load the FPGA hardware configuration and the software project from persistant memory on system power up, so you can control the car "out-of-the-box". Well, hopefully!

The batteries are wired in parallel, so make sure that **both batteries are fully charged** before you start!

Once everything is connected and powered up, the car wheels should spin forwards and backwards, signalling that the initialisation is complete. This means that the communication between the ECU and the motor controller is working, and that both are in the operational state. The car can now be controlled using the Java GUI found in `software/GUI/`.

### Development environment
Get the Quartus II 12.1 web edition from the [Altera website](https://www.altera.com/download/software/quartus-ii-we/12.1). The package includes the code editor "NIOS 2 Software Editor" (essentially eclipse), the FPGA configurator "Qsys", and the uninspiredly named FPGA programmer "Programmer". The C2X project is divided into two main components: hardware and software.

The hardware part deals with FPGA programming - you'll use Quartus/Qsys and the Programmer to change the hardware configuration and load it into the FPGA board. 

The software part consists of programming the NIOS II processor (essentially an ARM core), that you previously programmed into the FPGA, using C/C++ - you'll be using the NIOS II Eclipse for coding, programming and, if your lucky star is out, debugging.

### Making Software changes
Import all projects from the `software/` folder. There are 3 projects, each with their own board support package (<project_name>_bsp):

- `Car2X_communication` runs on Core 0 of the ECU, handles all communication matters
- `Car2X_carControl` runs on Core 1 of the ECU, calculates & modifies the car state
- `Car2X_nanoMotorCtrl` runs on the motor control boards, controls the ... motors

Once you've got the projects in your workspace, right click on the bsp of the project you want to build, `NIOS II` -> `Generate BSP`. Then right click on the actual project, `build`.

To load the `.elf` binary file onto a board, add a run configuration. Make sure that the `check system ID` and `check timestamp` options are disabled. Next, make sure that the board is connected and select the correct debugging device in the list on the `debugger` tab.

### Making Hardware changes
The git repository only contains the source files for the central ECU. In case you need to make changes to the hardware, do the following:

- Open the hardware/nios2.project into Quartus.
- Open the SOPC builder project and build it.
- Build the Quartus project.
- Open the Programmer (in the Tools menu), select your board and program the hardware config into the FPGA board.

## More info
There is lots of documentation, please read it! Our report can be found here: doc/final_report.pdf