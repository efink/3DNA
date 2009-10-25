#ifndef _WIIMOTE_LIB_H
#define _WIIMOTE_LIB_H

#if (WINVER < 0x0501)
#error Need to compile for Win XP
#endif

#include <windows.h>
#ifdef __GNUC__
#include <ddk\hidsdi.h>
/* mingw doesn't have this defined?? (as of w32api-3.8) */
WINHIDSDI BOOL WINAPI HidD_SetOutputReport(HANDLE, PVOID, ULONG);
#else
/* winddk build wants these included */
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <hidsdi.h> 
#endif // __GNUC__


/* 
 * Process a report from the wiimote.
 * If IR is enabled, it'll control the mouse.
 * ProcessAndGetReport writes the HID report to a BYTE array.
 * Make sure the array has at least space for 22 characters.
 */
int WiiM_ProcessEvent();
int WiiM_ProcessAndGetReport(LPBYTE);

void WiiM_TogRumble();
void WiiM_TogLED(int);
/* Toggles IR to control the mouse with absolute positioning (like the Wii) */
void WiiM_TogIR_Abs();
/* control mouse with relative positioning (for FPS) */
void WiiM_TogIR_Rel(); /* TODO */
void WiiM_MapKeys(); /* TODO */

int WiiM_ConnectWiimote(LPBYTE);
void WiiM_CloseConn();


#endif // _WIIMOTE_LIB_H

