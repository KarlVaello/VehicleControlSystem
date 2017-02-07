
import sys, random
import serial

from PySide import QtGui, QtCore

class Base(QtGui.QWidget):
    
    def __init__(self):
        super(Base, self).__init__()
        
        self.initUI()
        
    def initUI(self):

        #base image
        baseImage = QtGui.QPixmap("base.png")
        self.lbl = QtGui.QLabel(self)
        self.lbl.setPixmap(baseImage)
        self.lbl.move(0,0)
        
        #speed
        self.speedLabel = QtGui.QLabel('150', self)
        speedFont = QtGui.QFont( "Arial", 50);
        self.speedLabel.setFont(speedFont);
        self.speedLabel.setAlignment(QtCore.Qt.AlignCenter)
        self.speedLabel.move(360, 90)
        
        #time
        time = QtCore.QTime.currentTime()
        self.timeLabel = QtGui.QLabel( str(time.hour()) + ":"+ str(time.minute()) + ":"+ str(time.second()), self)
        timeFont = QtGui.QFont( "Arial", 15);
        self.timeLabel.setFont(timeFont);
        self.timeLabel.setAlignment(QtCore.Qt.AlignCenter)
        self.timeLabel.move(372, 25)
        
        # label colors
        palette = QtGui.QPalette()
        palette.setColor(QtGui.QPalette.Foreground,QtCore.Qt.white)
        self.speedLabel.setPalette(palette) 
        self.timeLabel.setPalette(palette) 
        
        self.setupUpdateThread()  #thread
        
        self.setGeometry(300, 300, 800, 300) #window size
        self.show()
        
    #update GUI current time label  
    def updateSpeed(self,text):
        self.speedLabel.setText(str(text))
    
    #update GUI current time label
    def updateTime(self):
        time = QtCore.QTime.currentTime()
        self.timeLabel.setText( str(time.hour()) + ":"+ str(time.minute()) + ":"+ str(time.second())) 
         
    def setupUpdateThread(self):  
        self.updateThread = upateThread()  
        #connect our update functoin to the progress signal of the update thread  
        self.updateThread.progress.connect(self.updateSpeed,QtCore.Qt.QueuedConnection)  
        self.updateThread.progress.connect(self.updateTime,QtCore.Qt.QueuedConnection)  
        if not self.updateThread.isRunning():#if the thread has not been started let's kick it off  
            self.updateThread.start()  
            
#inherit from Qthread and setup our own thread class  
class upateThread(QtCore.QThread):  
    progress = QtCore.Signal(str) #create a custom sygnal we can subscribe to to emit update commands  
    def __init__(self,parent=None):  
        super(upateThread,self).__init__(parent)  
        self.exiting = False  
  
    def run(self):  
        while True:  
            self.msleep(10)
            self.progress.emit(str(random.randint(0,100)))              


class serialSetup:
    
    def setSerialPort(self):
        ser = serial.Serial('/dev/tty.usbmodem1d11', 9600) # Establish the connection on a specific port

        print(4)
        

class canBusSetup:
    
    def setSerialPort(self):
        print(4)       
            
def main():
    app = QtGui.QApplication(sys.argv)
    ex = Base()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()