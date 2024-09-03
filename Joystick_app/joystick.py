from PyQt6 import QtWidgets, QtGui

from joystick_ui import MainWindow

import sys
import os, sys

try:
    os.chdir(sys._MEIPASS)
    print(sys._MEIPASS)
except:
    pass

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    app.setWindowIcon(QtGui.QIcon('logo.svg'))
    main = MainWindow()
    main.setWindowTitle("MadCity Labs joystick")
    main.show()
    sys.exit(app.exec())