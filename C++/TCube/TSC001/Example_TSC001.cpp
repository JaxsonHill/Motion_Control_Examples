/*
TSC001 Simple Example
Date of Creation(YYYY-MM-DD): 2022-01-18
Date of Last Modification on Github: 2022-09-21
C++ Version Used: ISO C++ 14
Kinesis Version Tested: 1.14.40
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// Include device specific header file
#include "Thorlabs.MotionControl.TCube.Solenoid.h"

int __cdecl wmain(int argc, wchar_t* argv[])
{
	// Uncomment this line (and TLI_UnitializeSimulations at the bottom of the page)
	// If you are using a simulated device
	//TLI_InitializeSimulations();

	// Change this line to reflect your device's serial number
	int serialNo = 85000001;

	// identify and access device
	char testSerialNo[16];
	sprintf_s(testSerialNo, "%d", serialNo);

	// Build list of connected device
    if (TLI_BuildDeviceList() == 0)
    {
		// get device list size 
        short n = TLI_GetDeviceListSize();
		// get BBD serial numbers
        char serialNos[100];
		TLI_GetDeviceListByTypeExt(serialNos, 100, 85);

		// Search serial numbers for given serial number
		if (strstr(serialNos, testSerialNo)) {
			printf("Device %s found", testSerialNo);
		}
		else {
			printf("Device %s Not Found", testSerialNo);
			return -1;
		}

		// open device
		if(SC_Open(testSerialNo) == 0)
		{
			// start the device polling at 200ms intervals
			SC_StartPolling(testSerialNo, 200);

			Sleep(1000);

			// set operating mode to SC_OperatingModes::SC_Manual
			SC_SetOperatingMode(testSerialNo, SC_OperatingModes::SC_Manual);
			Sleep(1000);

			// set operating state to SC_OperatingStates::SC_Active
			SC_SetOperatingState(testSerialNo, SC_OperatingStates::SC_Active);
			Sleep(200);
			int state1 = SC_GetOperatingState(testSerialNo);
			int state2 = SC_GetSolenoidState(testSerialNo);
			printf("Device %s state is %d, solenoid is %d\r\n", testSerialNo, state1, state2);

			Sleep(1000);

			// set operating state to SC_OperatingStates::SC_Inactive
			SC_SetOperatingState(testSerialNo, SC_OperatingStates::SC_Inactive);
			Sleep(200);
			state1 = SC_GetOperatingState(testSerialNo);
			state2 = SC_GetSolenoidState(testSerialNo);
			printf("Device %s state is %d, solenoid is %d\r\n", testSerialNo, state1, state2);

			Sleep(1000);

			// stop polling
			SC_StopPolling(testSerialNo);
			// close device
			SC_Close(testSerialNo);
	    }
    }

	// Uncomment this line if you are using simulations
	//TLI_UnitializeSimulations;
	char c = _getch();
	return 0;
}
