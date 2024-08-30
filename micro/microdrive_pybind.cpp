#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "microdrive.h"

namespace py = pybind11;

PYBIND11_MODULE(microdrive, m) {
    m.doc() = "Bindings for the MicroDrive C++ API";

    // Binding the MCL MD Init Handle functions
    m.def("MCL_MD_InitHandle", &MCL_MD_InitHandle);
    m.def("MCL_MD_GrabHandle", &MCL_MD_GrabHandle);
    m.def("MCL_MD_InitHandleOrGetExisting", &MCL_MD_InitHandleOrGetExisting);
    m.def("MCL_MD_GrabHandleOrGetExisting", &MCL_MD_GrabHandleOrGetExisting);
    m.def("MCL_MD_GetHandleBySerial", &MCL_MD_GetHandleBySerial);
    m.def("MCL_MD_GrabAllHandles", &MCL_MD_GrabAllHandles);
    m.def("MCL_MD_GetAllHandles", [](int size) {
        std::vector<int> handles(size);
        MCL_MD_GetAllHandles(handles.data(), size);
        return handles;
    });
    m.def("MCL_MD_NumberOfCurrentHandles", &MCL_MD_NumberOfCurrentHandles);
    m.def("MCL_MD_ReleaseHandle", &MCL_MD_ReleaseHandle);
    m.def("MCL_MD_ReleaseAllHandles", &MCL_MD_ReleaseAllHandles);

    // Binding the MCL MD Status functions
    m.def("MCL_MD_Status", [](int handle) {
        unsigned short status;
        int result = MCL_MD_Status(&status, handle);
        return std::make_tuple(result, status);
    });
    m.def("MCL_MD_Stop", [](int handle) {
        unsigned short status;
        int result = MCL_MD_Stop(&status, handle);
        return std::make_tuple(result, status);
    });
    m.def("MCL_MD_MicroDriveMoveStatus", [](int handle) {
        int isMoving;
        int result = MCL_MD_MicroDriveMoveStatus(&isMoving, handle);
        return std::make_tuple(result, isMoving);
    });
    m.def("MCL_MD_MicroDriveWait", &MCL_MD_MicroDriveWait);

    // Binding movement functions
    m.def("MCL_MD_MoveThreeAxesM", &MCL_MD_MoveThreeAxesM);
    m.def("MCL_MD_MoveThreeAxesR", &MCL_MD_MoveThreeAxesR);
    m.def("MCL_MD_MoveThreeAxes", &MCL_MD_MoveThreeAxes);
    m.def("MCL_MD_MoveM", &MCL_MD_MoveM);
    m.def("MCL_MD_MoveR", &MCL_MD_MoveR);
    m.def("MCL_MD_Move", &MCL_MD_Move);
    m.def("MCL_MD_SingleStep", &MCL_MD_SingleStep);

    // Binding encoder functions
    m.def("MCL_MD_ResetEncoders", [](int handle) {
        unsigned short status;
        int result = MCL_MD_ResetEncoders(&status, handle);
        return std::make_tuple(result, status);
    });
    m.def("MCL_MD_ResetEncoder", [](unsigned int axis, int handle) {
        unsigned short status;
        int result = MCL_MD_ResetEncoder(axis, &status, handle);
        return std::make_tuple(result, status);
    });
    m.def("MCL_MD_ReadEncoders", [](int handle) {
        double e1, e2, e3, e4;
        int result = MCL_MD_ReadEncoders(&e1, &e2, &e3, &e4, handle);
        return std::make_tuple(result, e1, e2, e3, e4);
    });
    m.def("MCL_MD_CurrentPositionM", [](unsigned int axis, int handle) {
        int microSteps;
        int result = MCL_MD_CurrentPositionM(axis, &microSteps, handle);
        return std::make_tuple(result, microSteps);
    });

    // Binding additional functions
    m.def("MCL_MD_Information", [](int handle) {
        double encoderResolution, stepSize, maxVelocity, maxVelocityTwoAxis, maxVelocityThreeAxis, minVelocity;
        int result = MCL_MD_Information(&encoderResolution, &stepSize, &maxVelocity, &maxVelocityTwoAxis,
                                        &maxVelocityThreeAxis, &minVelocity, handle);
        return std::make_tuple(result, encoderResolution, stepSize, maxVelocity, maxVelocityTwoAxis, maxVelocityThreeAxis, minVelocity);
    });
    m.def("MCL_MD_EncodersPresent", [](int handle) {
        unsigned char encoderBitmap;
        int result = MCL_MD_EncodersPresent(&encoderBitmap, handle);
        return std::make_tuple(result, encoderBitmap);
    });

    // Binding firmware-related functions
    m.def("MCL_MD_GetFirmwareVersion", [](int handle) {
        short version, profile;
        int result = MCL_MD_GetFirmwareVersion(&version, &profile, handle);
        return std::make_tuple(result, version, profile);
    });
    m.def("MCL_MD_PrintDeviceInfo", &MCL_MD_PrintDeviceInfo);
    m.def("MCL_MD_GetSerialNumber", &MCL_MD_GetSerialNumber);
    m.def("MCL_MD_DLLVersion", [](int handle) {
        short version, revision;
        MCL_MD_DLLVersion(&version, &revision);
        return std::make_tuple(version, revision);
    });
    m.def("MCL_MD_GetProductID", [](int handle) {
        unsigned short PID;
        int result = MCL_MD_GetProductID(&PID, handle);
        return std::make_tuple(result, PID);
    });
    m.def("MCL_MD_GetAxisInfo", [](int handle) {
        unsigned char axis_bitmap;
        int result = MCL_MD_GetAxisInfo(&axis_bitmap, handle);
        return std::make_tuple(result, axis_bitmap);
    });
    m.def("MCL_MD_GetFullStepSize", [](int handle) {
        double stepSize;
        int result = MCL_MD_GetFullStepSize(&stepSize, handle);
        return std::make_tuple(result, stepSize);
    });
    m.def("MCL_MD_GetTirfModuleCalibration", [](int handle) {
        double calMM;
        int result = MCL_MD_GetTirfModuleCalibration(&calMM, handle);
        return std::make_tuple(result, calMM);
    });
    // m.def("MCL_GetTirfModuleAxis", [](int handle) {
    //     int tirfAxis;
    //     int result = MCL_GetTirfModuleAxis(&tirfAxis, handle);
    //     return std::make_tuple(result, tirfAxis);
    // });
}
