
import sys, random

import serial

from PySide import QtGui, QtCore

class Base(QtGui.QWidget):
    
    def __init__(self):
        super(Base, self).__init__()
        
        self.initUI()
        
    def initUI(self):

        self.speed = 280
        global errorIconOn
        errorIconOn = 1
        # speed
        self.speedLabel = QtGui.QLabel(str(self.speed), self)
        speedFont = QtGui.QFont("Arial", 40);
        self.speedLabel.setFont(speedFont);
        self.speedLabel.setAlignment(QtCore.Qt.AlignHCenter)
        self.speedLabel.move(356, 100)

        
        # time
        self.timeLabel = QtGui.QLabel("00:00:00", self)
        time = QtCore.QTime.currentTime()
        self.timeLabel.setText(str(time.hour()) + ":" + str(time.minute()) + ":" + str(time.second())) 
        timeFont = QtGui.QFont("Arial", 10);
        self.timeLabel.setFont(timeFont);
        self.timeLabel.setAlignment(QtCore.Qt.AlignCenter)
        self.timeLabel.move(374, 25)
        
        # label colors
        palette = QtGui.QPalette()
        palette.setColor(QtGui.QPalette.Foreground, QtCore.Qt.white)
        self.speedLabel.setPalette(palette) 
        self.timeLabel.setPalette(palette) 
    
        updateSerial().setSerialPort()

    
        self.setupUpdateThread()  # thread
        self.serialUpdateThread()  # thread
        
        self.setGeometry(300, 300, 800, 300)  # window size
        self.show()
        
        self.blinkTime = 0
        
    def paintEvent(self, event):
        
        qp = QtGui.QPainter(self)
        baseImage = QtGui.QImage("base.png")
        qp.drawImage(0,0,baseImage)
        qp.end()
        qp2 = QtGui.QPainter(self)
        speedPointerImage = QtGui.QImage("speedPointer.png")
        qp2.translate(400,150)
        qp2.rotate(-222 + (int(self.speed)/1.261))
        qp2.drawImage(0,0,speedPointerImage)
        qp2.end()

        if (errorIconOn == 1):
            qp3 = QtGui.QPainter(self)
            errorIconImage = QtGui.QImage("errorIcon.png")
            qp3.drawImage(QtCore.QRect(160,100,50,50),errorIconImage)
            qp3.end()

        
        self.update()

    # update GUI current time label  
    def updateSpeed(self, text):
        self.speed = int(text)
        self.speedLabel.setText(str(text))

    # update GUI current time label
    def updateTime(self):
        time = QtCore.QTime.currentTime()
        self.timeLabel.setText(str(time.hour()) + ":" + str(time.minute()) + ":" + str(time.second())) 
            
    def setupUpdateThread(self):  
        self.updateThread = upateThread()  
        # connect our update functoin to the progress signal of the update thread  
        self.updateThread.progress.connect(self.updateTime, QtCore.Qt.QueuedConnection)  
        #self.updateThread.progress.connect(self.updateSerial, QtCore.Qt.QueuedConnection)  
        if not self.updateThread.isRunning():  # if the thread has not been started let's kick it off  
            self.updateThread.start()     
    
    
    def serialUpdateThread(self):  
        self.updateSerial = updateSerial()  
        # connect our update functoin to the progress signal of the update thread  
        self.updateSerial.progress.connect(self.updateSpeed, QtCore.Qt.QueuedConnection)
        #self.updateThread.progress.connect(self.updateSerial, QtCore.Qt.QueuedConnection)  
        if not self.updateSerial.isRunning():  # if the thread has not been started let's kick it off  
            self.updateSerial.start()     
                            
# inherit from Qthread and setup our own thread class  
class upateThread(QtCore.QThread):  
    progress = QtCore.Signal(str)  # create a custom sygnal we can subscribe to to emit update commands  
    def __init__(self, parent=None):  
        super(upateThread, self).__init__(parent)  
        self.exiting = False  
  
    def run(self):  
        while True:  
            self.msleep(10)
            self.progress.emit(str(random.randint(0, 280)))              

# inherit from Qthread and setup our own thread class  
class updateSerial(QtCore.QThread):  
    progress = QtCore.Signal(str)  # create a custom sygnal we can subscribe to to emit update commands  
    def __init__(self, parent=None):  
        super(updateSerial, self).__init__(parent)  
        self.exiting = False  

    
    def setSerialPort(self):
        global PuertoSerie
        PuertoSerie = serial.Serial("/dev/cu.usbmodemfa131",9600)
    try: 
        PuertoSerie.open()
    except Exception, e:
        print "error open serial port: " + str(e)

    def run(self):  
        while True:
            self.msleep(.1)
            # leemos hasta que encontarmos el final de linea
            sArduino = PuertoSerie.readline()
            # Mostramos el valor leido y eliminamos el salto de linea del final
            #print "Valor Arduino: " + sArduino.rstrip('\n')
            self.progress.emit(sArduino)
      
 
class canBusSetup:
    
    def setSerialPort(self):
        print("CANbus")       
            
def main():
    app = QtGui.QApplication(sys.argv)

    ex = Base()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
