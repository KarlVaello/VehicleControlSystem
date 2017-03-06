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
        #ser = serial.Serial('COM8',9600)
        self.setupUpdateThread()  # thread
        self.initUI()
        
       
    def initUI(self):
        self.speed = 0
        self.lastSpeed = 0
        self.gaugeSpeed = 0
        self.speedFade = 0
        self.menu = 0
        self.currentBattery  = 0
        global errorIconOn
        errorIconOn = 1
        
        
        print "Load data"
        self.renderer = QtSvg.QSvgRenderer('outiline.svg')        
        self.speedPointerRenderer = QtSvg.QSvgRenderer('speedPointer.svg')   
        self.gpsIconRenderer = QtSvg.QSvgRenderer('gpsIcon.svg')   
        self.musicIconRenderer = QtSvg.QSvgRenderer('musicIcon.svg')   
        self.errorIconRenderer = QtSvg.QSvgRenderer('errorIcon.svg')   
        self.batteryBarRenderer = QtSvg.QSvgRenderer('batteryBar.svg')   
        
             
        self.clusterDisplayHight = 480
        self.clusterDisplayWidth = 1280
        self.setGeometry(300, 200, 1280,480)  # window size
        self.show()
        
    def paintEvent(self, event):
             
        painter = QtGui.QPainter(self)
        self.renderer.render(painter)
        painter.end()
        
        if (self.menu==1):
            painter3 = QtGui.QPainter(self)
            painter3.translate(420 ,100)
            painter3.scale(0.045,0.1)
            self.gpsIconRenderer.render(painter3)
            painter3.end()
            
            painter2 = QtGui.QPainter(self)
            painter2.translate(400 ,160)
            painter2.scale(0.045,0.1)
            self.musicIconRenderer.render(painter2)
            painter2.end()
        
        qtime = QtGui.QPainter(self)
        atime = QtCore.QTime.currentTime()
        qtime.setPen(QtGui.QColor(220, 220, 220))
        qtime.setFont(QtGui.QFont('Decorative', 20))
        qtime.drawText(QtCore.QRect((self.clusterDisplayWidth / 2) -60,15,120,50),QtCore.Qt.AlignCenter,str(atime.hour()) + ":" + str(atime.minute()) + ":" + str(atime.second()))
        qtime.end()
        
        qspeed = QtGui.QPainter(self)
        qspeed.setPen(QtGui.QColor(220, 220, 220))
        qspeed.setFont(QtGui.QFont('LCDMono2', 50))
        qspeed.drawText(QtCore.QRect((self.clusterDisplayWidth / 2) -60,(self.clusterDisplayHight / 2) - 55 ,120,100),QtCore.Qt.AlignCenter, str(self.speed))
        qspeed.end()
        
        qBatteryBar = QtGui.QPainter(self)
        #0% width 0
        #100% width
        self.batteryBarRenderer.render(qBatteryBar,QtCore.QRect(543,373, (int(self.currentBattery) * 197)/100,15))
        qBatteryBar.end()
        
        qCurrentBateryPercent = QtGui.QPainter(self)
        qCurrentBateryPercent.setPen(QtGui.QColor(220, 220, 220))
        qCurrentBateryPercent.setFont(QtGui.QFont('Decorative', 10))
        qCurrentBateryPercent.drawText(QtCore.QRect(440,365,80,50),QtCore.Qt.AlignRight, str(self.currentBattery))
        qCurrentBateryPercent.end()
        
                     
        qp3 = QtGui.QPainter(self)
        qp3.translate((self.clusterDisplayWidth / 2) ,(self.clusterDisplayHight / 2))
        qp3.rotate(-209 + (int(self.gaugeSpeed)/1.175))
        self.speedPointerRenderer.render(qp3)
        qp3.end() 

        if (errorIconOn == 1):
            
            qerrorIconPainter = QtGui.QPainter(self)
            self.errorIconRenderer.render(qerrorIconPainter,QtCore.QRect(160,100,50,50))
            qerrorIconPainter.end()
            
        #self.update()
             
        # update GUI current time label  
    def updateSpeed(self,text):
        print text
        mn,speedR,batteryR = text.split(';')
        print mn
        print speedR
        print batteryR
        
        if(speedR != self.speed or mn != self.menu or batteryR!= self.currentBattery ):
            if(speedR > self.speed + 2 or speedR < self.speed - 2):
                self.speed = int(speedR)
            
            self.currentBattery = batteryR
            self.menu = int(mn)
            self.gaugeSpeed = speedR
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
        self.aSpeed = 0
        self.fadeSpeed = 0
        self.aCurrentBattery = 0;
        self.aB = 0;
        
    def run(self):
        while True:  
            self.msleep(10)
            #QSound.play("beep1.wav")
            #print QSound.isAvailable()
        
            
            if (self.fadeSpeed == 0):
                self.aSpeed = self.aSpeed + 1
                if (self.aSpeed >= 280):
                    self.fadeSpeed = 1
            else:
                self.aSpeed = self.aSpeed - 1
                if (self.aSpeed <= 0 ):
                    self.fadeSpeed = 0 
            #self.progress.emit(str(self.aSpeed))       
            

            if (self.aB == 0):
                self.aCurrentBattery = self.aCurrentBattery + 1
                if (self.aCurrentBattery >= 100):
                    self.aB = 1
            else:
                self.aCurrentBattery = self.aCurrentBattery - 1
                if (self.aCurrentBattery <= 0 ):
                    self.aB = 0 
            
            
            #print (ser.readline().strip())
            #self.progress.emit(str(ser.readline().strip())+ ";" + str(self.aCurrentBattery))
            self.progress.emit("0;" + str(self.aSpeed)+ ";30")
            #self.progress.emit("1;" + "40" + ";30")
            
    