# Example for TCP socket over Ethernet on Nuvoton's Mbed CE enabled boards

This is an example to demo TCP socket over Ethernet
on Nuvoton's Mbed CE enabled boards.

Check out [Mbed CE](https://github.com/mbed-ce)
for details on Mbed OS community edition.

## Support development tools

Use cmake-based build system.
Check out [hello world example](https://github.com/mbed-ce/mbed-ce-hello-world) for getting started.

> **⚠️ Warning**
>
> Legacy development tools below are not supported anymore.
> - [Arm's Mbed Studio](https://os.mbed.com/docs/mbed-os/v6.15/build-tools/mbed-studio.html)
> - [Arm's Mbed CLI 2](https://os.mbed.com/docs/mbed-os/v6.15/build-tools/mbed-cli-2.html)
> - [Arm's Mbed CLI 1](https://os.mbed.com/docs/mbed-os/v6.15/tools/developing-mbed-cli.html)

For [VS Code development](https://github.com/mbed-ce/mbed-os/wiki/Project-Setup:-VS-Code)
or [OpenOCD as upload method](https://github.com/mbed-ce/mbed-os/wiki/Upload-Methods#openocd),
install below additionally:

-   [NuEclipse](https://github.com/OpenNuvoton/Nuvoton_Tools#numicro-software-development-tools): Nuvoton's fork of Eclipse
-   Nuvoton forked OpenOCD: Shipped with NuEclipse installation package above.
    Checking openocd version `openocd --version`, it should fix to `0.10.022`.

## Developer guide

In the following, we take **NuMaker-IoT-M467** board as an example for Mbed CE support.

### Hardware requirements

-   NuMaker-IoT-M467 board
-   Host OS: Windows or others
-   Ethernet cable (RJ45)

### Build the example

1.  Clone the example and navigate into it
    ```
    $ git clone https://github.com/mbed-nuvoton/NuMaker-mbed-ce-eth-tcp-example
    $ cd NuMaker-mbed-ce-eth-tcp-example
    $ git checkout -f master
    ```

1.  Deploy necessary libraries
    ```
    $ git submodule update --init
    ```
    Or for fast install:
    ```
    $ git submodule update --init --filter=blob:none
    ```

1.  Compile with cmake/ninja
    ```
    $ mkdir build; cd build
    $ cmake .. -GNinja -DCMAKE_BUILD_TYPE=Develop -DMBED_TARGET=NUMAKER_IOT_M467
    $ ninja
    $ cd ..
    ```

### Flash the image

Flash by drag-n-drop built image `NuMaker-mbed-ce-eth-tcp-example.bin` or `NuMaker-mbed-ce-eth-tcp-example.hex` onto **NuMaker-IoT-M467** board

### Verify the result

On host terminal (115200/8-N-1), you should see:

```
Start TCP test
mac address <MAC-ADDRESS>
PHY ID 1:<PHY-ID-1>
PHY ID 2:<PHY-ID-2>
TCP client IP Address is <IP-ADDRESS>
HTTP: Connected to www.ifconfig.io:80
```
