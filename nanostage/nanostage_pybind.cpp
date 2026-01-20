#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "madlib.h"

namespace py = pybind11;

PYBIND11_MODULE(nanostage, m) {
    m.doc() = "Bindings for the Nanostage C++ API";

    // Binding the MCL MD Init Handle functions
    m.def("MCL_InitHandle", &MCL_InitHandle);
    m.def("MCL_InitHandleOrGetExisting", &MCL_InitHandleOrGetExisting);
    m.def("MCL_GrabHandle", &MCL_GrabHandle);
    m.def("MCL_GrabHandleOrGetExisting", &MCL_GrabHandleOrGetExisting);
    m.def("MCL_GrabAllHandles", &MCL_GrabAllHandles);
    m.def("MCL_GetAllHandles", [](int size) {
        std::vector<int> handles(size);
        MCL_GetAllHandles(handles.data(), size);
        return handles;
    });
    m.def("MCL_NumberOfCurrentHandles", &MCL_NumberOfCurrentHandles);
    m.def("MCL_GetHandleBySerial", &MCL_GetHandleBySerial);
    m.def("MCL_ReleaseHandle", &MCL_ReleaseHandle);
    m.def("MCL_ReleaseAllHandles", &MCL_ReleaseAllHandles);

    // Binding the standard device movement functions
    m.def("MCL_SingleReadZ", &MCL_SingleReadZ);
    m.def("MCL_SingleReadN", &MCL_SingleReadN);
    m.def("MCL_SingleWriteZ", &MCL_SingleWriteZ);
    m.def("MCL_SingleWriteN", &MCL_SingleWriteN);
    m.def("MCL_MonitorZ", [](double position, int handle){
        double result = MCL_MonitorZ(position, handle);
        return result;
    });
    m.def("MCL_MonitorN", &MCL_MonitorN);
    m.def("MCL_ReadEncoderZ", &MCL_ReadEncoderZ);
    m.def("MCL_ResetEncoderZ", &MCL_ResetEncoderZ);
    m.def("MCL_ThetaX", [](double milliradians, int handle){
        double actual;
        int result = MCL_ThetaX(milliradians, &actual, handle);
        return std::make_tuple(result, actual);
    });
    m.def("MCL_ThetaY", [](double milliradians, int handle){
        double actual;
        int result = MCL_ThetaY(milliradians, &actual, handle);
        return std::make_tuple(result, actual);
    });
    m.def("MCL_MoveZCenter", [](double position, int handle){
        double actual;
        int result = MCL_ThetaY(position, &actual, handle);
        return std::make_tuple(result, actual);
    });
    m.def("MCL_LevelZ", &MCL_LevelZ);
    m.def("MCL_CFocusSetFocusMode", &MCL_CFocusSetFocusMode);
    m.def("MCL_CFocusStep", &MCL_CFocusStep);
    m.def("MCL_CFocusGetFocusMode", [](int handle){
        int focusLocked;
        int result = MCL_CFocusGetFocusMode(&focusLocked, handle);
        return std::make_tuple(result, focusLocked);
    });

    // Binding waveformm acquisition functions
    // m.def("MCL_ReadWaveFormN", [](unsigned int axis,unsigned int DataPoints,double milliseconds, int handle){
    //     double waveform;
    //     int result = MCL_ReadWaveFormN(axis, DataPoints, milliseconds, &waveform, handle);
    //     return std::make_tuple(result, waveform);
    // });
    // m.def("MCL_Setup_ReadWaveFormN", &MCL_Setup_ReadWaveFormN);
    // m.def("MCL_LoadWaveFormN", &MCL_LoadWaveFormN);
    // m.def("MCL_Trigger_ReadWaveFormN", [](unsigned int axis,unsigned int DataPoints, int handle){
    //     double waveform;
    //     int result = MCL_Trigger_ReadWaveFormN(axis, DataPoints, &waveform, handle);
    //     return std::make_tuple(result, waveform);
    // });
    // m.def("MCL_LoadWaveFormN", [](unsigned int axis,unsigned int DataPoints,double milliseconds, int handle){
    //     double waveform;
    //     int result = MCL_LoadWaveFormN(axis, DataPoints, milliseconds, &waveform, handle);
    //     return std::make_tuple(result, waveform);
    // })
    // m.def("MCL_Setup_LoadWaveFormN", [](unsigned int axis,unsigned int DataPoints,double milliseconds, int handle){
    //     double waveform;
    //     int result = MCL_Setup_LoadWaveFormN(axis, DataPoints, milliseconds, &waveform, handle);
    //     return std::make_tuple(result, waveform);
    // });
    // m.def("MCL_Trigger_LoadWaveFormN", &MCL_Trigger_LoadWaveFormN);
    // m.def("MCL_TriggerWaveformAcquisition", [](unsigned int axis, unsigned int DataPoints, int handle){
    //     double waveform;
    //     int result = MCL_TriggerWaveformAcquisition(axis, DataPoints, &waveform, handle);
    //     return std::make_tuple(result, waveform);
    // });

    // // Binding multi axis waveform acquisition functions
    // m.def("MCL_WfmaSetup", [](int dataPointsPerAxis, double milliseconds, unsigned short iterations, int handle){
    //     double wfDacX;
    //     double wfDacY;
    //     double wfDacZ;
    //     int result = MCL_WfmaSetup(&wfDacX, &wfDacY, &wfDacZ, dataPointsPerAxis, milliseconds, iterations, handle);
    //     return std::make_tuble(result, wfDacX, wfDacY, wfDacZ);
    // });

    // Binding the waveform-related functions
    m.def("MCL_ReadWaveFormN", [](unsigned int axis, unsigned int DataPoints, double milliseconds, int handle) {
        std::vector<double> waveform(DataPoints);
        int result = MCL_ReadWaveFormN(axis, DataPoints, milliseconds, waveform.data(), handle);
        return std::make_tuple(result, waveform);
    });

    m.def("MCL_Setup_ReadWaveFormN", &MCL_Setup_ReadWaveFormN);

    m.def("MCL_Trigger_ReadWaveFormN", [](unsigned int axis, unsigned int DataPoints, int handle) {
        std::vector<double> waveform(DataPoints);
        int result = MCL_Trigger_ReadWaveFormN(axis, DataPoints, waveform.data(), handle);
        return std::make_tuple(result, waveform);
    });

    m.def("MCL_LoadWaveFormN", [](unsigned int axis, unsigned int DataPoints, double milliseconds, double waveform, int handle) {
        // std::vector<double> waveform(DataPoints);
        int result = MCL_LoadWaveFormN(axis, DataPoints, milliseconds, &waveform, handle);
        return std::make_tuple(result, waveform);
    });

    // m.def("MCL_Setup_LoadWaveFormN", &MCL_Setup_LoadWaveFormN);

    m.def("MCL_Trigger_LoadWaveFormN", &MCL_Trigger_LoadWaveFormN);

    m.def("MCL_TriggerWaveformAcquisition", [](unsigned int axis, unsigned int DataPoints, int handle) {
        std::vector<double> waveform(DataPoints);
        int result = MCL_TriggerWaveformAcquisition(axis, DataPoints, waveform.data(), handle);
        return std::make_tuple(result, waveform);
    });

    // Binding the waveform acquisition functions
    m.def("MCL_WfmaSetup", &MCL_WfmaSetup);
    m.def("MCL_WfmaTriggerAndRead", [](int handle) {
        std::vector<double> wfAdcX, wfAdcY, wfAdcZ;
        int result = MCL_WfmaTriggerAndRead(wfAdcX.data(), wfAdcY.data(), wfAdcZ.data(), handle);
        return std::make_tuple(result, wfAdcX, wfAdcY, wfAdcZ);
    });
    m.def("MCL_WfmaTrigger", &MCL_WfmaTrigger);
    m.def("MCL_WfmaRead", [](int handle) {
        std::vector<double> wfAdcX, wfAdcY, wfAdcZ;
        int result = MCL_WfmaRead(wfAdcX.data(), wfAdcY.data(), wfAdcZ.data(), handle);
        return std::make_tuple(result, wfAdcX, wfAdcY, wfAdcZ);
    });
    m.def("MCL_WfmaStop", &MCL_WfmaStop);

    // Binding the clock-related functions
    m.def("MCL_IssBindClockToAxis", &MCL_IssBindClockToAxis);
    m.def("MCL_IssConfigurePolarity", &MCL_IssConfigurePolarity);
    m.def("MCL_IssSetClock", &MCL_IssSetClock);
    m.def("MCL_IssResetDefaults", &MCL_IssResetDefaults);
    m.def("MCL_ChangeClock", &MCL_ChangeClock);
    m.def("MCL_PixelClock", &MCL_PixelClock);
    m.def("MCL_LineClock", &MCL_LineClock);
    m.def("MCL_FrameClock", &MCL_FrameClock);
    m.def("MCL_AuxClock", &MCL_AuxClock);
    m.def("MCL_GetClockFrequency", &MCL_GetClockFrequency);

    // Binding the calibration and configuration functions
    m.def("MCL_GetCalibration", &MCL_GetCalibration);
    m.def("MCL_TipTiltHeight", &MCL_TipTiltHeight);
    m.def("MCL_TipTiltWidth", &MCL_TipTiltWidth);
    m.def("MCL_MinMaxThetaX", &MCL_MinMaxThetaX);
    m.def("MCL_MinMaxThetaY", &MCL_MinMaxThetaY);
    m.def("MCL_GetTipTiltThetaX", &MCL_GetTipTiltThetaX);
    m.def("MCL_GetTipTiltThetaY", &MCL_GetTipTiltThetaY);
    m.def("MCL_GetTipTiltCenter", &MCL_GetTipTiltCenter);
    m.def("MCL_CurrentMinMaxThetaX", &MCL_CurrentMinMaxThetaX);
    m.def("MCL_CurrentMinMaxThetaY", &MCL_CurrentMinMaxThetaY);
    m.def("MCL_CurrentMinMaxCenter", &MCL_CurrentMinMaxCenter);
    m.def("MCL_GetFirmwareVersion", &MCL_GetFirmwareVersion);
    m.def("MCL_GetSerialNumber", &MCL_GetSerialNumber);
    m.def("MCL_GetProductInfo", &MCL_GetProductInfo);
    m.def("MCL_PrintDeviceInfo", &MCL_PrintDeviceInfo);
    m.def("MCL_DeviceAttached", &MCL_DeviceAttached);
    m.def("MCL_GetCommandedPosition", &MCL_GetCommandedPosition);

    // Binding the sequence-related functions
    m.def("MCL_SequenceLoad", &MCL_SequenceLoad);
    m.def("MCL_SequenceClear", &MCL_SequenceClear);
    m.def("MCL_SequenceStart", &MCL_SequenceStart);
    m.def("MCL_SequenceStop", &MCL_SequenceStop);
    m.def("MCL_SequenceGetMax", &MCL_SequenceGetMax);

}