'''
Created on 20 feb. 2017

@author: c
'''
from PySide import QtGui, QtCore

class CentralConsoleUI(QtGui.QWidget):
    
    def __init__(self):
        super(CentralConsoleUI, self).__init__()
        self.initUI()
        
    def initUI(self):

        
        self.setGeometry(900, 300, 400,800)  # window size
        self.show()
                        
    def paintEvent(self, event):
        print("hey")
        
        qtext = QtGui.QPainter(self)
        qtext.setPen(QtGui.QColor(220, 220, 220))
        qtext.setFont(QtGui.QFont('LCDMono2', 40))
        qtext.drawText(QtCore.QRect(339,105,120,55),"HOLA")
        qtext.end()
        
        #self.update()
