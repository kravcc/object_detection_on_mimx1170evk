Overview
========
FOMO model based implementation of object detector based on
NXP TFLite label image example [2] and NXP LwIP example [3] adjusted to run on MCUs.

A 3-channel color image is set as an input to a quantized FOMO (Faster Objects, More Objects)
convolutional neural network model [1] that detects objects in the input image into
one of 9 output classes. The result is then transmitted over a TCP connection to a connected client 
(a desktop application providing a Graphical User Interface).

HOW TO USE THE APPLICATION:
To detect objects in the image, place the objects in front of the camera so that it fits into 
the white rectangle in the center of the display. After launching the application on the microcontroller (see "prepare the demo"), it is necessary to launch the second part of the application, the GUI. In the application you can start detection of objects and also change the settings for detection.
Note semihosting implementation causes slower or discontinuous video experience. 
Select UART in 'Project Options' during project import for using external debug console 
via UART (virtual COM port).

[1] https://docs.edgeimpulse.com/docs/edge-impulse-studio/learning-blocks/object-detection/fomo-object-detection-for-constrained-devices

[2] https://github.com/nxp-mcuxpresso/mcux-sdk-examples/tree/main/evkbmimxrt1170/eiq_examples/tflm_label_image

[3] https://github.com/nxp-mcuxpresso/mcux-sdk-examples/tree/main/evkbmimxrt1170/lwip_examples/lwip_ipv4_ipv6_echo/freertos/cm7

Files:
BP_mimxrt1170/
  source/
- main.cpp - main file, entry point of the application in the main function
- labels.h - names of object classes
- timer.c - timer source code
- image/* - image capture and pre-processing code
- model/model_data.h - model data from the .tflite file
      converted to a C language array using the xxd tool
- model/model.cpp - model initialization and inference code
- model/model_all_ops_micro.cpp - model operations registration
- model/output_postproc.cpp - model output processing
- video/* - camera and display handling

  lwip/

- contrib/apps/tcpsrv/tcpsrv.cpp - main application cycle, TCP client-server logic code

BP_gui/
- resources/* - pictures for visualization
- main.py - the main file that starts the application
- qrc_resources.py - binary representation of pictures
- settingWindow.py - setting view, geterated from QT Designer 
- table.py - main view, geterated from QT Designer


Toolchain supported
===================
- MCUXpresso  11.9.0+

Hardware requirements
=====================
- Mini/micro USB cable
- EVK-MIMXRT1170 board
- Personal computer
- OV5640 camera
- RK055AHD091 or RK055MHD091 display (optional)

Board settings
==============
- Connect the display to J48 (optional)
- Connect the camera to J2
- Connect external 5V power to J43, set J38 to 1-2

Prepare the Demo
================
1. Connect a USB cable between the host PC and the OpenSDA USB port on the target board. 

2. Open a serial terminal with the following settings:

   - 115200 baud rate
   - 8 data bits
   - No parity
   - One stop bit
   - No flow control
3. Insert the Ethernet Cable into the target board's RJ45 port and connect it to your PC network adapter.
4. Configure the host PC IP address to 192.168.0.103.
3. Build the project. (The project expects the RK055MHD091 panel by default. To use the RK055AHD091 panel,
    change #define DEMO_PANEL DEMO_PANEL_RK055MHD091 to #define DEMO_PANEL MIPI_PANEL_RK055AHD091
    in eiq_display_conf.h.)
4. Download the program to the target board.
5. Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.
6. Run the gui ($ python3 BP_gui/main.py)


Running the demo
================
The log below shows the output of the demo in the terminal window (compiled with ARM GCC):

Initializing PHY...

************************************************
 PROGRAMM START
************************************************
 IPv4 Address     : 192.168.0.102

 IPv4 Subnet mask : 255.255.255.0

 IPv4 Gateway     : 192.168.0.100
************************************************
Waiting for a new connection at port: 7
```diff
+here you need to start the GUI and press the detect button
```
Accepted a new connection!

Data for inference are ready

Object detection bounding boxes:

  Green square

  Orange square 

  Blue circle 

  Blue star
```diff
+the found objects will be displayed in the application
```