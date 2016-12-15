# Getting started sample with ethernet TCP on mbed OS


### Import NuMaker-mbed-tcp from on-line IDE
1. Please choose Nuvoton NuMaker-PFM-XXX as your target platform.
2. Please press the left-up icon "New", then choose "NuMaker Ethernet TCP" from the template list.
3. Your NuMaker-mbed-tcp program is existed.

#### Now compile
Please press compile icon.

#### Burn Code & Execute
1. Connect the board NuMaker-PFM-XXX with your PC by USB cable, then there will be one "mbed" disk.
2. Copy the built binary file into "mbed" disk on you PC.
3. Press device's reset button to execute, and you could get the below log by uart console.
-------------------------------------------------------------------------------
Start TCP test 
100 full
        Link Up
TCP client IP Address is 10.28.10.14
--------------------------------------------------------------------------
   User could use tool or "ping" command to test RX/TX of TCP.
   