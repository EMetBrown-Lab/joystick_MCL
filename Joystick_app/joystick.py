from PyQt6 import QtWidgets

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
    main = MainWindow()
    main.show()
    sys.exit(app.exec())