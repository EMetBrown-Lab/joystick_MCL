# Import necessary libraries
from PyQt6 import QtWidgets, uic, QtCore
from PyQt6.QtWidgets import QMessageBox
import microdrive
import time


# Define the MainWindow class
class MainWindow(QtWidgets.QMainWindow):
    def __init__(self, *args, **kwargs) -> None:
        # Initialize the parent class
        super(MainWindow, self).__init__(*args, **kwargs)
        # Load the UI page
        uic.loadUi("joystick_ui.ui", self)

        self.reset_progress_bar.setStyleSheet("""
            QProgressBar {
                border-style: solid;
                border-color: grey;
                border-radius: 7px;
                border-width: 2px;
                text-align: center;
            }
            QProgressBar::chunk {
                width: 2px;
                background-color: #de7c09;
                margin: 3px;
            }
        """)
        self.reset_progress_bar.hide()
        # Define error codes
        self.errorcodes = {
            0: "No Error",
            -1: "General Error",
            -2: "Dev Error",
            -3: "Dev not attached",
            -4: "Usage error",
            -5: "Dev not ready",
            -6: "Argument error",
            -7: "Invalid axis",
            -8: "Invalid handle",
            -9: "Failed to connect the microdrive",
            -10: "Speed value should be < to 2 mm/s",
            -11: "Increment should be < to 50 mm",
        }
        self.x0 = 0
        self.y0 = 0
        self.z0 = 0
        # Connect to the microdrive
        # Initialize the device handle
        self.handle = microdrive.MCL_MD_InitHandle()

        # Check if the handle is valid
        if self.handle == 0:
            self.ErrorBox(-9)

        # Get axis and encoder information
        error, self.axis_bitmap = microdrive.MCL_MD_GetAxisInfo(self.handle)
        if error != 0:
            self.ErrorBox(error)
        error, self.encoderbitmap = microdrive.MCL_MD_EncodersPresent(self.handle)
        if error != 0:
            self.ErrorBox(error)

        # Get device information
        (
            error,
            self.encoderResolution,
            self.stepSize,
            self.maxVelocity,
            self.maxVelocityTwoAxis,
            self.maxVelocityThreeAxis,
            self.minVelocity,
        ) = microdrive.MCL_MD_Information(self.handle)

        # Check for errors
        if error != 0:
            self.ErrorBox(error)

        # Connect buttons to their respective functions
        self.left_y.clicked.connect(lambda: self.positive_displacement_button(2))
        self.left_x.clicked.connect(lambda: self.positive_displacement_button(1))
        self.right_y.clicked.connect(lambda: self.negative_displacement_button(2))
        self.right_x.clicked.connect(lambda: self.negative_displacement_button(1))
        self.up_z.clicked.connect(lambda: self.negative_displacement_button(3))
        self.down_z.clicked.connect(lambda: self.positive_displacement_button(3))

        self.left_y.pressed.connect(lambda: self.positive_displacement_pushed(2))
        self.left_x.pressed.connect(lambda: self.positive_displacement_pushed(1))
        self.right_y.pressed.connect(lambda: self.negative_displacement_pushed(2))
        self.right_x.pressed.connect(lambda: self.negative_displacement_pushed(1))
        self.up_z.pressed.connect(lambda: self.negative_displacement_pushed(3))
        self.down_z.pressed.connect(lambda: self.positive_displacement_pushed(3))

        # Connect button releases to their respective functions
        self.left_y.released.connect(lambda: self.release_displacement_button())
        self.right_y.released.connect(lambda: self.release_displacement_button())
        self.left_x.released.connect(lambda: self.release_displacement_button())
        self.right_x.released.connect(lambda: self.release_displacement_button())
        self.down_z.released.connect(lambda: self.release_displacement_button())
        self.up_z.released.connect(lambda: self.release_displacement_button())

        # Verify the range of input values
        self.speed_value.textChanged.connect(lambda: self.changing_input_values(0))
        self.increment_value.textChanged.connect(lambda: self.changing_input_values(1))

        ## The menus

        self.actionGo_home.triggered.connect(self.go_home)
        self.actionReset_axis.triggered.connect(self.reset_axis)
        self.actionzero_axis.triggered.connect(self.zero_axis)

        ## Loop measure position
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self.actuate_position)
        self.timer.start(100)

        ## Stop button

        self.stop.clicked.connect(lambda: microdrive.MCL_MD_Stop(self.handle))

    # Function to handle positive displacement button clicks
    def positive_displacement_button(self, axis):
        # Get speed and displacement values
        speed = float(self.speed_value.text())
        displacement = float(self.increment_value.text())

        # Check if continuous mode is enabled
        if self.Continuous_CheckBox.isChecked():
            pass
        else:
            error = microdrive.MCL_MD_Move(axis, speed, displacement, self.handle)

    def negative_displacement_pushed(self, axis):
        speed = float(self.speed_value.text())
        displacement = -float(self.increment_value.text())

        if self.Continuous_CheckBox.isChecked():
            # Move the axis continuously
            error = microdrive.MCL_MD_Move(axis, speed, -50, self.handle)

    def positive_displacement_pushed(self, axis):
        speed = float(self.speed_value.text())
        displacement = -float(self.increment_value.text())

        if self.Continuous_CheckBox.isChecked():
            # Move the axis continuously
            error = microdrive.MCL_MD_Move(axis, speed, 50, self.handle)

    # Function to handle negative displacement button clicks
    def negative_displacement_button(self, axis):
        # Get speed and displacement values
        speed = float(self.speed_value.text())
        displacement = -float(self.increment_value.text())

        # Check if continuous mode is enabled
        if self.Continuous_CheckBox.isChecked():
            pass
        else:
            microdrive.MCL_MD_Move(axis, speed, displacement, self.handle)

    # Function to handle button releases
    def release_displacement_button(self):
        # Check if continuous mode is enabled
        if self.Continuous_CheckBox.isChecked():
            time.sleep(0.1)
            # Stop the axis movement
            for i in range(10):
                error, _ = microdrive.MCL_MD_Stop(self.handle)

    # Function to display error messages
    def ErrorBox(self, error) -> None:
        if error == 0:
            return 0
        # Create a message box
        msg = QMessageBox()
        # Set the icon to critical
        msg.setIcon(QMessageBox.Icon.Critical)
        # Set the window title
        msg.setWindowTitle("Error")
        # Set the text to the error message
        msg.setText(self.errorcodes[error])
        # Execute the message box
        msg.exec()

    # Function to check input values
    def changing_input_values(self, value):
        """
        0 -> speed
        1 -> increment
        """
        if self.increment_value.text().isalpha() or self.increment_value.text() == "":
            return 0
        # Print a test message
        # Check if the value is 0 (speed)
        if value == 0:
            # Check if the speed value is greater than 2
            if float(self.speed_value.text()) > 2:
                # Display an error message
                self.ErrorBox(-10)

        # Check if the value is 1 (increment)
        if value == 1:
            # Check if the increment value is greater than 50

            if float(self.increment_value.text()) > 50:
                # Display an error message
                self.ErrorBox(-11)

    # Function to update the position display
    def actuate_position(self):
        # Get the current position of each axis
        error, x = microdrive.MCL_MD_CurrentPositionM(1, self.handle)
        error, y = microdrive.MCL_MD_CurrentPositionM(2, self.handle)
        error, z = microdrive.MCL_MD_CurrentPositionM(3, self.handle)
        # Display an error message if there is an error
        # Update the position display for each axis
        if error !=0:
            return 0
        self.x_position.display((x - self.x0) * self.stepSize)
        self.y_position.display((y - self.y0) * self.stepSize)
        self.z_position.display((z - self.z0) * self.stepSize)

    # Function to reset the axes
    def reset_axis(self):
        # Move each axis to a specific position
        def _reset_axis():
            microdrive.MCL_MD_MoveThreeAxes(
                1,
                self.maxVelocity,
                25,
                2,
                self.maxVelocity,
                25,
                3,
                self.maxVelocity,
                50,
                self.handle,
            )

            # Move each axis to another specific position
            func_back = lambda: microdrive.MCL_MD_MoveThreeAxes(
                1,
                self.maxVelocity,
                -12.5,
                2,
                self.maxVelocity,
                -12.5,
                3,
                self.maxVelocity,
                -25,
                self.handle,
            )
            
            self.timer_back = QtCore.QTimer.singleShot(26 * 1000, func_back)

            self.timer_reset_position = QtCore.QTimer.singleShot(
                (26 + 13) * 1000, self.zero_axis
            )
        
        msgBox = QtWidgets.QMessageBox()
        msgBox.setIcon(QMessageBox.Icon.Warning)
        msgBox.setText("Please remove the objective before resetting the axes.")
        msgBox.setWindowTitle("Warning")
        msgBox.setStandardButtons(QMessageBox.StandardButton.Ok | QMessageBox.StandardButton.Cancel)

        returnValue = msgBox.exec()
        if returnValue == QMessageBox.StandardButton.Ok:
            _reset_axis()
        
        self.pbar_timer = QtCore.QTimer()
        self.pbar_timer.timeout.connect(self.handle_timer)
        self.pbar_interval = 40*1000  / 100 # 40 * 1000 ms / 100 steps
        self.start_progress()


    # Function to move the axes to the home position
    def go_home(self):
        # Get the current position of each axis
        error, x = microdrive.MCL_MD_CurrentPositionM(1, self.handle)
        error, y = microdrive.MCL_MD_CurrentPositionM(2, self.handle)
        error, z = microdrive.MCL_MD_CurrentPositionM(3, self.handle)
        # Display an error message if there is an error
        self.ErrorBox(error)
        # Move each axis to the home position
        microdrive.MCL_MD_MoveThreeAxes(
            1,
            self.maxVelocity,
            -(x - self.x0) * self.stepSize,
            2,
            self.maxVelocity,
            -(y - self.y0) * self.stepSize,
            3,
            self.maxVelocity,
            -(z - self.z0) * self.stepSize,
            self.handle,
        )


    def zero_axis(self):
        # Get the current position of each axis
        error, x = microdrive.MCL_MD_CurrentPositionM(1, self.handle)
        error, y = microdrive.MCL_MD_CurrentPositionM(2, self.handle)
        error, z = microdrive.MCL_MD_CurrentPositionM(3, self.handle)

        self.x0 = x
        self.y0 = y
        self.z0 = z
        # Display an error message if there is an error
        self.ErrorBox(error)
        microdrive.MCL_MD_ResetEncoders(self.handle)
        self.actuate_position()

    def start_progress(self):
        self.reset_progress_bar.setRange(0, 100)
        self.reset_progress_bar.setValue(0)
        self.reset_progress_bar.show()
        self.pbar_timer.start(self.pbar_interval)

    def handle_timer(self):
        value = self.reset_progress_bar.value()
        if value < 100:
            self.reset_progress_bar.setValue(value+1)
        else:
            self.pbar_timer.stop()
            self.reset_progress_bar.hide()
        

