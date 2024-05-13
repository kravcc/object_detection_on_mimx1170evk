# Author: Marina Kravchuk
# 
# GUI for the object detection application
# 
# Bachelor's thesis 2024
# Faculty of Information Technology 

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QApplication, QMainWindow, QGridLayout, QWidget, QTableWidget, QTableWidgetItem, QFormLayout
from PyQt5.QtCore import QSize, Qt, QThread, pyqtSignal
from PyQt5.QtGui import QIcon, QPixmap, QMovie
from table import Ui_MainWindow
import qrc_resources
from settingWindow import *
import random
import time
import socket

start = 0.0 # Variable for the timer

HOST = "192.168.0.102"  # The server's hostname or IP address
PORT = 7  # The port used by the server
i = 0

# counters for checkbox logic
ColorCBCount = 3
FormCBCount = 3

objects = [
           {'name' : 'Blue Circle', 'isSelectedForm' : True, 'isSelectedColor' : True, 'alias': ':blue_circle.png'},
           {'name' : 'Blue Square', 'isSelectedForm' : True, 'isSelectedColor' : True, 'alias': ':blue_square.png'},
           {'name' : 'Blue Star', 'isSelectedForm' : True, 'isSelectedColor' : True, 'alias': ':blue_star.png'},
           {'name' : 'Green Circle', 'isSelectedForm' : True, 'isSelectedColor' : True, 'alias': ':green_circle.png'},
           {'name' : 'Green Square', 'isSelectedForm' : True, 'isSelectedColor' : True, 'alias': ':green_square.png'},
           {'name' : 'Green Star', 'isSelectedForm' : True, 'isSelectedColor' : True, 'alias': ':green_star.png'},
           {'name' : 'Orange Circle', 'isSelectedForm' : True, 'isSelectedColor' : True, 'alias': ':orange_circle.png'},
           {'name' : 'Orange Square', 'isSelectedForm' : True, 'isSelectedColor' : True, 'alias': ':orange_square.png'},
           {'name' : 'Orange Star', 'isSelectedForm' : True, 'isSelectedColor' : True, 'alias': ':orange_star.png'}
]

# variable for storing data received from the server
objectdetecteddata = []

# variable for storing processed data
objectsfromdata = []

# Thread called when the detect button is pressed
# Thread creates a TCP socket, connects to the server and receives data
class Thread(QThread):
    dataThread = pyqtSignal(str)
    
    def __init__(self):
        QThread.__init__(self)

    def run(self):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((HOST, PORT))

            data = s.recv(2024)

            if not data:
                print("NODATA")
                return

            objectdetecteddata = list(data)
            objectsfromdata.clear()
            
            for x in range(0,63,4):
                if objectdetecteddata[x] == 0:
                    continue

                udata = dict.fromkeys(['name', 'scores', 'x', 'y', 'index', 'alias'])
                udata['name'] = objects[objectdetecteddata[x]-1]['name'] #object name
                udata['scores']= objectdetecteddata[x+1] # prediction
                udata['x'] = round(objectdetecteddata[x+2] / 96 * 3 + 0.05) + 1
                udata['y'] = round(objectdetecteddata[x+3] / 96 * 3 + 0.05) + 1
                udata['index'] = int(x/4) # index
                udata['alias'] = objects[objectdetecteddata[x]-1]['alias']
                
                # add only objects selected by the user
                for checkbox in objects:
                    if checkbox['name'] == udata['name'] and checkbox['isSelectedForm'] == True and checkbox['isSelectedColor'] == True:
                        objectsfromdata.append(udata)
            s.sendall(b"C")
            self.dataThread.emit(f"successfully")
        
# Main Window class
class MainWindow(QMainWindow, Ui_MainWindow):

    def __init__(self, parent=None, satellite=None):

        super(MainWindow, self).__init__(parent)
        self.setupUi(self)
        self.selectedObjects = []
        self.w_sat = satellite

        self.movie = QMovie("resources/loading.gif")
        self.movie.setScaledSize(QtCore.QSize(50, 50)) 
        self.loading.setMovie(self.movie)
        self.movie.start()
        self.loading.hide()

        col_names = ['name', '%', 'x', 'y']
        #self.checkBox.toggle()
        self.pushButton.clicked.connect(self.openSettingWindow)
        self.pushButton_2.clicked.connect(self.detectButton)

        self.adjust_table(col_names, 0)
    
    # detect button function
    def detectButton(self):
        global start 
        start = time.time()
        if ColorCBCount == 0 and FormCBCount == 0:
            self.label_info.setText('Select objects in the settings')
            self.pushButton.setStyleSheet('border: 0px;\nborder-radius: 25px;\nbackground-color: rgb(255, 0, 0);')
        else:
            self.pushButton_2.setDisabled(True)
            self.loading.show()
            self.worker = Thread()    
            self.worker.dataThread.connect(self.data_validation)
            self.worker.start() 
        
    # function to be started on successful completion of the thread Thread
    def data_validation(self):

        self.loading.hide()        
        self.pushButton_2.setDisabled(False)
        
        self.regenerate_table()
        self.regenerate_grid()
        end = time.time() - start 
        print(end)

    # table inicialization
    def adjust_table(self, col_names, rows):

        self.tableWidget.setRowCount(rows)
        self.tableWidget.setColumnCount(len(col_names))
        self.tableWidget.setColumnWidth(1, 40)
        self.tableWidget.setColumnWidth(2, 60)
        self.tableWidget.setColumnWidth(3, 60)
        self.tableWidget.setHorizontalHeaderLabels(col_names)
        self.tableWidget.sizeHintForColumn(1)

    # setting button
    def openSettingWindow(self):

        self.pushButton.setStyleSheet('border: 0px;\nborder-radius: 25px;\nbackground-color: rgb(92, 85, 82);')
        if self.w_sat is not None:
            self.w_sat.show()
            self.close()
        # self.close()

    # regenerating the table when objects are found
    def regenerate_table(self):

        rows = len(objectsfromdata)
        self.tableWidget.setRowCount(rows)
        for row in range(rows):
            self.tableWidget.setRowHeight(row, 40)
            for column in range(self.tableWidget.columnCount()):
                item = QTableWidgetItem('')
                item.setText(str(objectsfromdata[row][list(objectsfromdata[row].keys())[column]]))
                item.setTextAlignment(Qt.AlignHCenter)
                self.tableWidget.setItem(row, column, item)

    # regenerating the board when objects are found
    def regenerate_grid(self):

        self.grid_1.clear()
        self.grid_2.clear()
        self.grid_3.clear()
        self.grid_4.clear()
        self.grid_5.clear()
        self.grid_6.clear()
        self.grid_7.clear()
        self.grid_8.clear()
        self.grid_9.clear()
        self.grid_10.clear()
        self.grid_11.clear()
        self.grid_12.clear()
        self.grid_13.clear()
        self.grid_14.clear()
        self.grid_15.clear()
        self.grid_16.clear()
        for object in objectsfromdata:
            pixmap = QPixmap(object['alias'])
            if "square" in object['alias']:
                pixmap = pixmap.scaled(55,55)

            if object['index'] == 0:
                self.grid_1.setPixmap(pixmap)
            elif object['index'] == 1:
                self.grid_2.setPixmap(pixmap)
            elif object['index'] == 2:
                self.grid_3.setPixmap(pixmap)
            elif object['index'] == 3:
                self.grid_4.setPixmap(pixmap)

            elif object['index'] == 4:
                self.grid_5.setPixmap(pixmap)
            elif object['index'] == 5:
                self.grid_6.setPixmap(pixmap)
            elif object['index'] == 6:
                self.grid_7.setPixmap(pixmap)
            elif object['index'] == 7:
                self.grid_8.setPixmap(pixmap)
            
            elif object['index'] == 8:
                self.grid_9.setPixmap(pixmap)
            elif object['index'] == 9:
                self.grid_10.setPixmap(pixmap)
            elif object['index'] == 10:
                self.grid_11.setPixmap(pixmap)
            elif object['index'] == 11:
                self.grid_12.setPixmap(pixmap)

            elif object['index'] == 12:
                self.grid_13.setPixmap(pixmap)
            elif object['index'] == 13:
                self.grid_14.setPixmap(pixmap)
            elif object['index'] == 14:
                self.grid_15.setPixmap(pixmap)
            elif object['index'] == 15:
                self.grid_16.setPixmap(pixmap)

# Setting Window class
class SettingWindow(QMainWindow, Ui_MainWindow2):

    def __init__(self, parent=None, satellite=None):
        super(SettingWindow, self).__init__(parent)
        self.setupUi(self)
        self.w_sat = satellite

        self.allcheckBoxesForms = [self.checkBox_Circle, self.checkBox_Star, self.checkBox_Square]
        self.allcheckBoxesColors = [self.checkBox_Orange, self.checkBox_Blue, self.checkBox_Green]

        self.pushButton.clicked.connect(self.openMainWindow)

        self.checkBox_Circle.stateChanged.connect(lambda:self.changeStateForm(self.checkBox_Circle))
        self.checkBox_Star.stateChanged.connect(lambda:self.changeStateForm(self.checkBox_Star))
        self.checkBox_Square.stateChanged.connect(lambda:self.changeStateForm(self.checkBox_Square))

        self.checkBox_Orange.stateChanged.connect(lambda:self.changeStateColor(self.checkBox_Orange))
        self.checkBox_Blue.stateChanged.connect(lambda:self.changeStateColor(self.checkBox_Blue))
        self.checkBox_Green.stateChanged.connect(lambda:self.changeStateColor(self.checkBox_Green))

        self.checkBox_AllForms.stateChanged.connect(self.allChangeForms)
        self.checkBox_AllColors.stateChanged.connect(self.allChangeColors)

    # open main window
    def openMainWindow(self):
        if self.w_sat is not None:
            self.w_sat.show()
            self.close()
        # self.close()
    
    # checkbox logic
    def allChangeColors(self, state):
        if ColorCBCount == 0 or ColorCBCount == 3 or state==2:
            for checkBox in self.allcheckBoxesColors:
                checkBox.setCheckState(state)

    # checkbox logic
    def allChangeForms(self, state):
        if FormCBCount == 0 or FormCBCount == 3 or state==2:
            for checkBox in self.allcheckBoxesForms:
                checkBox.setCheckState(state)

    # checkbox logic
    def changeStateColor(self, box):
        if box.isChecked() == True:
            for object in objects:
                if box.text() in object['name']:
                    object['isSelectedColor'] = True
        else:
            for object in objects:
                if box.text() in object['name']:
                    object['isSelectedColor'] = False
        count = 0
        for checkBox in self.allcheckBoxesColors:
            if checkBox.checkState() != 0:
                count = count+1
                # print('checkbox state ', checkBox.checkState())
                # print("ColorCBCount = ", ColorCBCount)
        ColorCBCount = count
        if ColorCBCount == 3:
            self.checkBox_AllColors.setChecked(True)
        else:
            self.checkBox_AllColors.setChecked(False)

    # checkbox logic
    def changeStateForm(self, box):
        if box.isChecked() == True:
            for object in objects:
                if box.text() in object['name']:
                    object['isSelectedForm'] = True
        else:
            for object in objects:
                if box.text() in object['name']:
                    object['isSelectedForm'] = False
        count = 0
        for checkBox in self.allcheckBoxesForms:
            if checkBox.checkState() != 0:
                count = count+1
                # print('checkbox state ', checkBox.checkState())
                # print("FormCBCount = ", FormCBCount)
        FormCBCount = count
        if FormCBCount == 3:
            self.checkBox_AllForms.setChecked(True)
        else:
            self.checkBox_AllForms.setChecked(False)

if __name__ == "__main__":
    import sys
 
    app = QApplication(sys.argv)
    mw = MainWindow()
    mw.show()
    sw = SettingWindow(satellite=mw)
    mw.w_sat = sw
    sys.exit(app.exec())