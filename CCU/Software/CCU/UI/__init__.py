
import sys, random

import serial, time

from PySide import QtGui, QtCore

from ClusterUI import *
from CentralConsoleUI import *

          

            
class canBusSetup:
    
    def setSerialPort(self):
        print("CANbus")       


            
def main():
    app = QtGui.QApplication(sys.argv)
    
    ex = ClusterUI().initUI
    #ex2 = CentralConsoleUI().initUI
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
