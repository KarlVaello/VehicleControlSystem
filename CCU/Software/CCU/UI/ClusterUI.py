'''
Created on 18 feb. 2017

@author: c
'''

from PySide import QtGui, QtCore, QtSvg
import serial
from PySide.QtGui import *



class ClusterUI(QtGui.QWidget):
    
    def __init__(self):
        super(ClusterUI, self).__init__()
        global ser 
       # ser = serial.Serial('COM8',9600)
        self.setupUpdateThread()  # thread
        self.initUI()
        
       
    def initUI(self):
        self.speed = 0
        self.speedFade = 0
        global errorIconOn
        errorIconOn = 1
        
        self.renderer = QtSvg.QSvgRenderer('outiline.svg')        
        
        self.speedPointerRenderer = QtSvg.QSvgRenderer('speedPointer.svg')        
        self.beepSound = QSound("record.wav")
        self.beepSound.play()
        self.beepSound.setLoops(10)
        print QSound.isAvailable()
        QSound.play("record.wav")
        self.setGeometry(300, 200, 932,349)  # window size
        self.show()
        
    def paintEvent(self, event):
        
                       
        painter = QtGui.QPainter(self);
        self.renderer.render(painter);
        painter.end()
        
        qtime = QtGui.QPainter(self)
        atime = QtCore.QTime.currentTime()
        qtime.setPen(QtGui.QColor(220, 220, 220))
        qtime.setFont(QtGui.QFont('Decorative', 10))
        qtime.drawText(QtCore.QRect(360,10,80,50),QtCore.Qt.AlignCenter,str(atime.hour()) + ":" + str(atime.minute()) + ":" + str(atime.second()))
        qtime.end()
        
        qspeed = QtGui.QPainter(self)
        qspeed.setPen(QtGui.QColor(220, 220, 220))
        qspeed.setFont(QtGui.QFont('LCDMono2', 40))
        qspeed.drawText(QtCore.QRect(406,130,120,55),QtCore.Qt.AlignCenter, str(self.speed))
        qspeed.end()
                
        qp3 = QtGui.QPainter(self)
        qp3.translate(932/2,349/2)
        qp3.rotate(-209 + (int(self.speed)/1.175))
        self.speedPointerRenderer.render(qp3);
        qp3.end()
        
        

        if (errorIconOn == 1):
            qp3 = QtGui.QPainter(self)
            errorIconImage = QtGui.QImage("errorIcon.png")
            qp3.drawImage(QtCore.QRect(160,100,50,50),errorIconImage)
            qp3.end()
        

        self.update()
             
        # update GUI current time label  
    def updateSpeed(self,text):
        
        self.speed = int(text)
        self.update()

    # update GUI current time label
    def updateTime(self):
        time = QtCore.QTime.currentTime()
        self.timeLabel.setText(str(time.hour()) + ":" + str(time.minute()) + ":" + str(time.second())) 
            
    def setupUpdateThread(self):  
        self.updateThread = upateThread()  
        self.updateThread.progress.connect(self.updateSpeed, QtCore.Qt.QueuedConnection)  

        if not self.updateThread.isRunning():  # if the thread has not been started let's kick it off  
            self.updateThread.start() 


#inherit from Qthread and setup our own thread class  #
class upateThread(QtCore.QThread):  
    progress = QtCore.Signal(str)  # create a custom signal we can subscribe to to emit update commands  
    def __init__(self, parent=None):  
        super(upateThread, self).__init__(parent)  
        self.exiting = False  
    
    def run(self):
        while True:  
            self.msleep(0.1)
             #print (ser.readline().strip())
            #self.progress.emit(ser.readline().strip())
    