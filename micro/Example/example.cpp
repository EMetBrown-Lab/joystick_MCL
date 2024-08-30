/*
	Simple C++ example.
	Refer to the MicroDrive_x_x.pdf file for function documentation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "microdrive.h"

int main ()
{
	int j, handle;
	unsigned char axis_bitmap = 0;
	unsigned char encoder_bitmap = 0;
	double encoderResolution = 0.0;
	double stepSize = 0.0;
	double maxVelocity = 0.0;
	double maxVelocityTwoAxis = 0.0;
	double maxVelocityThreeAxis = 0.0;
	double minVelocity = 0.0;

	// A handle identifies which device to communicate with.  This example 
	// assumes that only one device is connected.  MCL_MD_InitHandle will return
	// a handle to the first device it finds.
	handle = MCL_MD_InitHandle();
	if(handle == 0) {
		printf("Cannot get a handle to the device.  Exiting.\n");
		return 1;
	}

	// Prints some information about the device to a console.
	MCL_MD_PrintDeviceInfo(handle);

	// Find out what axes and encoders are available
	MCL_MD_GetAxisInfo(&axis_bitmap, handle);
	MCL_MD_EncodersPresent(&encoder_bitmap, handle);
	MCL_MD_Information(&encoderResolution,
		&stepSize,
		&maxVelocity,
		&maxVelocityTwoAxis,
		&maxVelocityThreeAxis,
		&minVelocity,
		handle);

	// For each valid axis perform a few simple operations.
	for(j = 0; j < 3; j++)
	{
		unsigned int axis;
		// Checks if an axis is valid.
		//		axis_bitmap = 0x --65 4321
		//		3 = M3 Axis
		//		2 = M2 Axis
		//		1 = M1 Axis
		if((axis_bitmap & (0x01 << j)) == 0)		
			continue;

		// Move the axis to 50% of its range of motion.
		axis = j+1;

		// Read the position of the axis.
		if((encoder_bitmap & (0x01 << j)) == 0)
		{
			// No encoder is present read the current microstep position.
			int microSteps = 0;
			MCL_MD_CurrentPositionM(axis, &microSteps, handle);
			printf("M%d position in millimeters %f\n", axis, microSteps * stepSize);		
		} else {
			// Encoder present
			double e[4];
			MCL_MD_ReadEncoders(&e[0], &e[1], &e[2], &e[3], handle);
			printf("M%d position in millimeters %f\n", axis, e[j]);	
		}

		// Move the axis forward a millimeter.
		MCL_MD_Move(axis, maxVelocity, 1.0, handle);
		// Wait for the motion to complete.
		MCL_MD_MicroDriveWait(handle);

		// Read the new position.
		if((encoder_bitmap & (0x01 << j)) == 0)
		{
			// No encoder is present read the current microstep position.
			int microSteps = 0;
			MCL_MD_CurrentPositionM(axis, &microSteps, handle);
			printf("M%d position in millimeters %f\n", axis, microSteps * stepSize);		
		} else {
			// Encoder present
			double e[4];
			MCL_MD_ReadEncoders(&e[0], &e[1], &e[2], &e[3], handle);
			printf("M%d position in millimeters %f\n", axis, e[j]);	
		}

		// Move the axis back a millimeter.
		MCL_MD_Move(axis, maxVelocity, -1.0, handle);
		// Wait for the motion to complete.
		MCL_MD_MicroDriveWait(handle);	

		// Read the new position.
		if((encoder_bitmap & (0x01 << j)) == 0)
		{
			// No encoder is present read the current microstep position.
			int microSteps = 0;
			MCL_MD_CurrentPositionM(axis, &microSteps, handle);
			printf("M%d position in millimeters %f\n", axis, microSteps * stepSize);		
		} else {
			// Encoder present
			double e[4];
			MCL_MD_ReadEncoders(&e[0], &e[1], &e[2], &e[3], handle);
			printf("M%d position in millimeters %f\n", axis, e[j]);	
		}		
	}

	// MCL_MD_ReleaseHandle should be called to properly release shared object resources.
	MCL_MD_ReleaseHandle(handle);

	return 0;
}
