#ifndef _MICRODRIVE_H_
#define _MICRODRIVE_H_

#define	MCL_SUCCESS			 	0
#define	MCL_GENERAL_ERROR		-1
#define	MCL_DEV_ERROR			-2
#define	MCL_DEV_NOT_ATTACHED	-3
#define	MCL_USAGE_ERROR			-4
#define	MCL_DEV_NOT_READY		-5
#define	MCL_ARGUMENT_ERROR		-6
#define	MCL_INVALID_AXIS		-7
#define	MCL_INVALID_HANDLE		-8

#ifdef __cplusplus
	extern"C"{
#endif

#define MD2_API

MD2_API int MCL_MD_InitHandle();
MD2_API	int MCL_MD_GrabHandle(short device);
MD2_API	int MCL_MD_InitHandleOrGetExisting();
MD2_API	int MCL_MD_GrabHandleOrGetExisting(short device);
MD2_API int MCL_MD_GetHandleBySerial(short serial);
MD2_API int MCL_MD_GrabAllHandles();
MD2_API int MCL_MD_GetAllHandles(int *handles, int size);
MD2_API int MCL_MD_NumberOfCurrentHandles();
MD2_API void MCL_MD_ReleaseHandle(int handle);
MD2_API void MCL_MD_ReleaseAllHandles();

MD2_API int MCL_MD_Status(unsigned short* status, int handle);
MD2_API int MCL_MD_Stop(unsigned short* status, int handle);
MD2_API	int MCL_MD_MicroDriveMoveStatus(int *isMoving, int handle);
MD2_API	int MCL_MD_MicroDriveWait(int handle);

MD2_API int MCL_MD_MoveThreeAxesM(
	int axis1, double velocity1, int microSteps1,
	int axis2, double velocity2, int microSteps2,
	int axis3, double velocity3, int microSteps3,
	int handle);
MD2_API int MCL_MD_MoveThreeAxesR(
	int axis1, double velocity1, double distance1, int rounding1,
	int axis2, double velocity2, double distance2, int rounding2, 
	int axis3, double velocity3, double distance3, int rounding3,
	int handle);
MD2_API int MCL_MD_MoveThreeAxes(
	int axis1, double velocity1, double distance1,
	int axis2, double velocity2, double distance2,
	int axis3, double velocity3, double distance3,
	int handle);
MD2_API int MCL_MD_MoveM(unsigned int axis, double velocity, int microSteps, int handle);
MD2_API int MCL_MD_MoveR(unsigned int axis, double velocity, double distance, int rounding, int handle);
MD2_API int MCL_MD_Move(unsigned int axis, double velocity, double distance, int handle);
MD2_API int MCL_MD_SingleStep(unsigned int axis, int direction, int handle);

MD2_API int MCL_MD_ResetEncoders(unsigned short* status, int handle);
MD2_API int MCL_MD_ResetEncoder(unsigned int axis, unsigned short* status, int handle);
MD2_API int MCL_MD_ReadEncoders(double* e1, double* e2, double *e3, double *e4, int handle);
MD2_API int MCL_MD_CurrentPositionM(unsigned int axis, int *microSteps, int handle);
MD2_API int MCL_MD_Information(double* encoderResolution,
	double* stepSize,
	double* maxVelocity,
	double* maxVelocityTwoAxis,
	double* maxVelocityThreeAxis,
	double* minVelocity,
	int handle);
MD2_API int MCL_MD_EncodersPresent(unsigned char* encoderBitmap,
	int handle);

MD2_API	int MCL_MD_GetFirmwareVersion(short *version, short *profile, int handle);
MD2_API	void MCL_MD_PrintDeviceInfo(int handle); 
MD2_API	int MCL_MD_GetSerialNumber(int handle);
MD2_API void MCL_MD_DLLVersion(short *version, short *revision);
MD2_API int MCL_MD_GetProductID(unsigned short *PID, int handle);
MD2_API int MCL_MD_GetAxisInfo(unsigned char *axis_bitmap, int handle);
MD2_API int MCL_MD_GetFullStepSize(double *stepSize, int handle);
MD2_API	int MCL_MD_GetTirfModuleCalibration(double *calMM, int handle);
MD2_API	int MCL_GetTirfModuleAxis(int *tirfAxis, int handle);

#ifdef __cplusplus
	}
#endif

#endif
