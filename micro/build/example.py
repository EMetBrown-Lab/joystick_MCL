import time
import microdrive

def main():
    # Initialize the device handle
    handle = microdrive.MCL_MD_InitHandle()
    if handle == 0:
        print("Cannot get a handle to the device. Exiting.")
        return 1

    # Print device information
    microdrive.MCL_MD_PrintDeviceInfo(handle)

    # Get axis and encoder information
    err, axis_bitmap = microdrive.MCL_MD_GetAxisInfo(handle)
    err, encoder_bitmap = microdrive.MCL_MD_EncodersPresent(handle)

    error ,encoderResolution, stepSize, maxVelocity, maxVelocityTwoAxis, maxVelocityThreeAxis, minVelocity = microdrive.MCL_MD_Information(handle)
    print(maxVelocity)
    # For each valid axis, perform operations
    for j in range(1):
        # Checks if an axis is valid
        print(axis_bitmap)
        print((0x01 << j))
        if (axis_bitmap & (0x01 << j)) == 0:
            print("no")
            continue
        j = 2
        axis = j + 1

        # Read the position of the axis
        if (encoder_bitmap & (0x01 << j)) == 0:
            
            # No encoder present, read the current microstep position
            err, microSteps = microdrive.MCL_MD_CurrentPositionM(axis, handle)
            print(f"microsteps = {microSteps}")
            print(f"M{axis} position in millimeters {microSteps * stepSize}")
    #     else:
    #         # Encoder present
    #         e = microdrive.MCL_MD_ReadEncoders(handle)
    #         print(f"M{axis} position in millimeters {e[j]}")

        # Move the axis forward by 1 millimeter
        err = microdrive.MCL_MD_Move(axis, maxVelocity, -5, handle)
        time.sleep(5/maxVelocity + 1)
        # microdrive.MCL_MD_MicroDriveWait(handle)
        print("test")

    #     # Read the new position
        if (encoder_bitmap & (0x01 << j)) == 0:
            err, microSteps = microdrive.MCL_MD_CurrentPositionM(axis, handle)
            print(f"M{axis} position in millimeters {microSteps * stepSize}")
        else:
            err, e = microdrive.MCL_MD_ReadEncoders(handle)
            print(f"M{axis} position in millimeters {e[j]}")

    #     # Move the axis back by 1 millimeter
        err, microdrive.MCL_MD_Move(axis, maxVelocity, 25, handle)
        time.sleep(25/maxVelocity + 1)

        # Read the new position
        if (encoder_bitmap & (0x01 << j)) == 0:
            err, microSteps = microdrive.MCL_MD_CurrentPositionM(axis, handle)
            print(f"M{axis} position in millimeters {microSteps * stepSize}")
        else:
            err, e = microdrive.MCL_MD_ReadEncoders(handle)
            print(f"M{axis} position in millimeters {e[j]}")

    # Release the device handle
    microdrive.MCL_MD_ReleaseHandle(handle)

    # return 0

if __name__ == "__main__":
    main()
