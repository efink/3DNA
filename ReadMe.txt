Folders:
src\           - contains the source code. also the makefile to create the mingw version of the library.
src\ddk_build\ - contains the makefile and sources file to compile with the microsoft ddk's build utility 
                 (in the WinXP Free Build Environment)
bin\mingw\     - header file and mingw compiled library
bin\ddk_build\ - header file and ddk's build compiled library


Using the Wiimote API:
In addition to linking the wiimote-api library, you must also link to the hid library. 
For GCC, use "-lhid" as an option. For the build utility, make sure you have $(SDK_LIB_PATH)\hid.lib 
in your TARGETLIBS macro.
For example, 
gcc -mwindows -mconsole -L. -o wiimote-gui.exe wiimote-gui.o wiimote-gui.rc.o -lsetupapi -lwiimote-api -lhid

It's important that you list hid after wiimote-api or the linker won't like you.


|-------------------|
|Init. and Destroy  |
|-------------------|

WiiM_ConnectWiimote()        takes in a device path. A program must find a device path, the easiest way 
                             is currently to use the windows setupapi to obtain it. I may include something 
                             in the library to get a device path, but I am currently hesitant because Wiimotes
                             show up only as generic HIDs which could easily be something else.
                             Refer to http://msdn2.microsoft.com/en-us/library/ms789877.aspx

WiiM_CloseConn()             closes the connection to the wiimote. 


|-------------------| Reporting functions will timeout if no report is found (100ms). They will return 0 if no report 
|Reporting functions| is found, and 1 if a report is found. These are functions that you probably want to put in 
|-------------------| your main application loop to con

WiiM_ProcessEvent()        will pull an HID report from the Wiimote and try to process it using any keymappings 
                           currently set. If IR is currently enabled (by the api), then ProcessEvent will send mouse 
                           events which vary depending on which toggle was used.
 
WiiM_ProcessAndGetReport() is the same as ProcessEvent except it also writes the report to the array passed to it.

WiiM_GetReport()           will just retrieve the report and put in the array passed without doing anything processing.

|-------------------|
|     Functions     |
|-------------------|

WiiM_MapKeys()             Sets the internal keymap. If any button is set to something that is not 0, it will send a key 
                           event for the virtual key whenever the button is pressed and the report is processed by one of 
                           the processing functions.

WiiM_TogRumble()           toggles rumble

WiiM_TogLED()              toggles an LED given an index (from 0 - 3)

WiiM_TogIR_Abs()           toggles IR to let the Wiimote control the mouse with IR (Requires a sensor bar to be on). 
                           Currently it only uses one dot, so it could be run on just one IR source.



This library is provided AS-IS with no warranty. It sends data to your Wiimote. I currently don't have anything that 
touches the calibration data, but it's still writing data when enabling the IR, so it could somehow brick it. 

Use it at your own risk.