
# Getting started with NuMaker-mbed-tcp on mbed OS
 
The code works on an mbed OS platform. The code tests TCP network.
 
Please install [mbed CLI](https://github.com/ARMmbed/mbed-cli#installing-mbed-cli).
 
## Get the example application!

Obtain the mbed-OS library from Windows command prompt

git clone https://github.com/ARMmbed/mbed-os


From the command line of Git Bash, for example:
 
```
hg clone https://developer.mbed.org/teams/Nuvoton/code/NuMaker-mbed-tcp/
cd NuMaker-mbed-tcp

```

Make shortcut for mbed-os library within the folder NuMaker-mbed-tcp
 
### Now compile
 
Invoke `mbed compile` specifying the name of your platform and your favorite toolchain (`GCC_ARM`, `ARM`, `IAR`). For example, for the ARM Compiler 5:
 
```
mbed compile -m NUMAKER_PFM_NUC472 -t ARM
```
 
Your PC may take a few minutes to compile your code. At the end you should get the following result:
 
```
+------------------------+-------+-------+---------+
| Module                 | .text | .data |    .bss |
+------------------------+-------+-------+---------+
| Misc                   | 14316 |    32 | 1027512 |
| drivers                |  1289 |     4 |      28 |
| features/FEATURE_LWIP  | 42735 |   341 |   37131 |
| features/frameworks    |  5135 |   128 |     516 |
| features/netsocket     |  4043 |    85 |      60 |
| hal                    |   358 |     8 |       0 |
| platform               |  1641 |    16 |      92 |
| rtos                   |   198 |     8 |       0 |
| rtos/rtx               |  7994 |   100 |    8396 |
| targets/TARGET_NUVOTON |  9416 |   272 |     312 |
| Subtotals              | 87125 |   994 | 1074047 |
+------------------------+-------+-------+---------+
Allocated Heap: unknown
Allocated Stack: unknown
Total Static RAM memory (data + bss): 1075041 bytes
Total RAM memory (data + bss + heap + stack): 1075041 bytes
Total Flash memory (text + data + misc): 88119 bytes
```
 
### Program your board
 
1. Connect your mbed device to the computer over USB.
1. Copy the binary file to the mbed device .
1. Press the reset button to start the program.
 
Please refer to the documents at the path https://github.com/OpenNuvoton/NuMaker_NuWicam_Samples/
 
## Export the project to Keil MDK and debug your application
 
From the command line, run the following command:
 
```
mbed export -m NUMAKER_PFM_NUC472 -i uvision
```
 
To debug the application:
 
1. Start uVision.
1. Import the uVision project generated earlier.
1. Compile your application and generate an `.axf` file.
1. Make sure uVision is configured to debug over CMSIS-DAP (From the Project menu > Options for Target '...' > Debug tab > Use CMSIS-DAP Debugger).
1. Set breakpoints and start a debug session.
 
![Image of uVision](img/uvision.png)
 
## Troubleshooting
 
1. Make sure `mbed-cli` is working correctly and its version is greater than `0.8.9`
 
 ```
 mbed --version
 ```
 
 If not, you can update it easily:
 
 ```
 pip install mbed-cli --upgrade
 ```
 
2. If using Keil MDK, make sure you have a license installed. [MDK-Lite](http://www.keil.com/arm/mdk.asp) has a 32KB restriction on code size.
 
 