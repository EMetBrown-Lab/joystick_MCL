import time
import microdrive

def main():
    # Initialize the device handle
    handle = microdrive.MCL_MD_InitHandle()
    if handle == 0:
        print("Cannot get a handle to the device. Exiting.")
        return 1

    # Print device information
    # microdrive.MCL_MD_PrintDeviceInfo(handle)

    # Get axis and encoder information
    axis_bitmap = microdrive.MCL_MD_GetAxisInfo(handle)
    encoder_bitmap = microdrive.MCL_MD_EncodersPresentss(handle)

    encoderResolution, stepSize, maxVelocity, maxVelocityTwoAxis, maxVelocityThreeAxis, minVelocity = microdrive.MCL_MD_Information(handle)

    # For each valid axis, perform operations
    for j in range(3):
        # Checks if an axis is valid
        if (axis_bitmap & (0x01 << j)) == 0:
            continue

        axis = j + 1

        # Read the position of the axis
        if (encoder_bitmap & (0x01 << j)) == 0:
            # No encoder present, read the current microstep position
            microSteps = microdrive.MCL_MD_CurrentPositionM(axis, handle)
            print(f"M{axis} position in millimeters {microSteps * stepSize}")
        else:
            # Encoder present
            e = microdrive.MCL_MD_ReadEncoders(handle)
            print(f"M{axis} position in millimeters {e[j]}")

        # Move the axis forward by 1 millimeter
        microdrive.MCL_MD_Move(axis, maxVelocity, 1.0, handle)
        microdrive.MCL_MD_MicroDriveWait(handle)

        # Read the new position
        if (encoder_bitmap & (0x01 << j)) == 0:
            microSteps = microdrive.MCL_MD_CurrentPositionM(axis, handle)
            print(f"M{axis} position in millimeters {microSteps * stepSize}")
        else:
            e = microdrive.MCL_MD_ReadEncoders(handle)
            print(f"M{axis} position in millimeters {e[j]}")

        # Move the axis back by 1 millimeter
        microdrive.MCL_MD_Move(axis, maxVelocity, -1.0, handle)
        microdrive.MCL_MD_MicroDriveWait(handle)

        # Read the new position
        if (encoder_bitmap & (0x01 << j)) == 0:
            microSteps = microdrive.MCL_MD_CurrentPositionM(axis, handle)
            print(f"M{axis} position in millimeters {microSteps * stepSize}")
        else:
            e = microdrive.MCL_MD_ReadEncoders(handle)
            print(f"M{axis} position in millimeters {e[j]}")

    # Release the device handle
    microdrive.MCL_MD_ReleaseHandle(handle)

    return 0

if __name__ == "__main__":
    main()
