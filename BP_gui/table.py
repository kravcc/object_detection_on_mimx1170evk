# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '/Users/marina/Desktop/table.ui'
#
# Created by: PyQt5 UI code generator 5.15.9
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(783, 523)
        MainWindow.setStyleSheet("\n"
"background-color: rgb(92, 85, 82);")
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(80, 40, 211, 41))
        font = QtGui.QFont()
        font.setFamily("Heiti SC")
        font.setPointSize(21)
        font.setBold(False)
        font.setItalic(False)
        font.setWeight(50)
        font.setKerning(True)
        self.label.setFont(font)
        self.label.setStyleSheet("color: rgb(203, 203, 203);")
        self.label.setObjectName("label")
        self.tableWidget = QtWidgets.QTableWidget(self.centralwidget)
        self.tableWidget.setGeometry(QtCore.QRect(60, 90, 270, 341))
        font = QtGui.QFont()
        font.setFamily("Skia")
        font.setPointSize(15)
        self.tableWidget.setFont(font)
        self.tableWidget.setSelectionMode(0)
        self.tableWidget.viewport().setProperty("cursor", QtGui.QCursor(QtCore.Qt.ArrowCursor))
        self.tableWidget.setStyleSheet("border: 0px ;\n"
"color: rgb(203, 203, 203);")
        self.tableWidget.setHorizontalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        self.tableWidget.setEditTriggers(QtWidgets.QAbstractItemView.NoEditTriggers)
        
        self.tableWidget.setShowGrid(False)
        self.tableWidget.setObjectName("tableWidget")
        self.tableWidget.setColumnCount(0)
        self.tableWidget.setRowCount(0)
        self.tableWidget.verticalHeader().setVisible(False)
        self.tableWidget.verticalHeader().setHighlightSections(True)
        self.grid_1 = QtWidgets.QLabel(self.centralwidget)
        self.grid_1.setGeometry(QtCore.QRect(400, 90, 64, 64))
        self.grid_1.setStyleSheet("background-color: rgb(203, 203, 203);")
        self.grid_1.setText("")
        self.grid_1.setObjectName("grid_1")
        self.grid_1.setAlignment(QtCore.Qt.AlignCenter)
        self.grid_2 = QtWidgets.QLabel(self.centralwidget)
        self.grid_2.setGeometry(QtCore.QRect(470, 90, 64, 64))
        self.grid_2.setStyleSheet("background-color: rgb(203, 203, 203);")
        self.grid_2.setText("")
        self.grid_2.setObjectName("grid_2")
        self.grid_2.setAlignment(QtCore.Qt.AlignCenter)
        self.grid_3 = QtWidgets.QLabel(self.centralwidget)
        self.grid_3.setGeometry(QtCore.QRect(540, 90, 64, 64))
        self.grid_3.setStyleSheet("background-color: rgb(203, 203, 203);")
        self.grid_3.setText("")
        self.grid_3.setObjectName("grid_3")
        self.grid_3.setAlignment(QtCore.Qt.AlignCenter)
        self.grid_5 = QtWidgets.QLabel(self.centralwidget)
        self.grid_5.setGeometry(QtCore.QRect(400, 160, 64, 64))
        self.grid_5.setStyleSheet("background-color: rgb(203, 203, 203);")
        self.grid_5.setText("")
        self.grid_5.setObjectName("grid_5")
        self.grid_5.setAlignment(QtCore.Qt.AlignCenter)
        self.grid_6 = QtWidgets.QLabel(self.centralwidget)
        self.grid_6.setGeometry(QtCore.QRect(470, 160, 64, 64))
        self.grid_6.setStyleSheet("background-color: rgb(203, 203, 203);")
        self.grid_6.setText("")
        self.grid_6.setObjectName("grid_6")
        self.grid_6.setAlignment(QtCore.Qt.AlignCenter)
        self.grid_4 = QtWidgets.QLabel(self.centralwidget)
        self.grid_4.setGeometry(QtCore.QRect(610, 90, 64, 64))
        self.grid_4.setStyleSheet("background-color: rgb(203, 203, 203);")
        self.grid_4.setText("")
        self.grid_4.setObjectName("grid_4")
        self.grid_4.setAlignment(QtCore.Qt.AlignCenter)
        self.grid_7 = QtWidgets.QLabel(self.centralwidget)
        self.grid_7.setGeometry(QtCore.QRect(540, 160, 64, 64))
        self.grid_7.setStyleSheet("background-color: rgb(203, 203, 203);")
        self.grid_7.setText("")
        self.grid_7.setObjectName("grid_7")
        self.grid_7.setAlignment(QtCore.Qt.AlignCenter)
        self.grid_8 = QtWidgets.QLabel(self.centralwidget)
        self.grid_8.setGeometry(QtCore.QRect(610, 160, 64, 64))
        self.grid_8.setStyleSheet("background-color: rgb(203, 203, 203);")
        self.grid_8.setText("")
        self.grid_8.setObjectName("grid_8")
        self.grid_8.setAlignment(QtCore.Qt.AlignCenter)
        self.grid_9 = QtWidgets.QLabel(self.centralwidget)
        self.grid_9.setGeometry(QtCore.QRect(400, 230, 64, 64))
        self.grid_9.setStyleSheet("background-color: rgb(203, 203, 203);")
        self.grid_9.setText("")
        self.grid_9.setObjectName("grid_9")
        self.grid_9.setAlignment(QtCore.Qt.AlignCenter)
        self.pushButton = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton.setGeometry(QtCore.QRect(620, 380, 55, 55))
        self.pushButton.setStyleSheet("border: 0px;\n"
"border-radius: 25px; ")
        self.pushButton.setText("")
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap("resources/gear.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButton.setIcon(icon)
        self.pushButton.setIconSize(QtCore.QSize(50, 50))
        self.pushButton.setObjectName("pushButton")
        self.pushButton_2 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_2.setGeometry(QtCore.QRect(390, 390, 191, 41))
        self.pushButton_2.setStyleSheet("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 198, 108);\n"
"border-radius: 20px;                     /* <----  20px  */ \n"
"border: 2px solid #AE8E5F;")
        self.pushButton_2.setObjectName("pushButton_2")
        self.label_info = QtWidgets.QLabel(self.centralwidget)
        self.label_info.setGeometry(QtCore.QRect(430, 20, 221, 51))
        self.label_info.setStyleSheet("color:rgb(203, 203, 203);")
        self.label_info.setText("")
        self.label_info.setObjectName("label_info")

        self.loading = QtWidgets.QLabel(self.centralwidget)
        self.loading.setGeometry(QtCore.QRect(655, 20, 50, 50))
        self.loading.setStyleSheet("color:rgb(203, 203, 203);")
        self.loading.setText("")
        self.loading.setObjectName("label_info")

        self.grid_10 = QtWidgets.QLabel(self.centralwidget)
        self.grid_10.setGeometry(QtCore.QRect(470, 230, 64, 64))
        self.grid_10.setStyleSheet("background-color: rgb(203, 203, 203);")
        self.grid_10.setText("")
        self.grid_10.setObjectName("grid_10")
        self.grid_10.setAlignment(QtCore.Qt.AlignCenter)
        self.grid_11 = QtWidgets.QLabel(self.centralwidget)
        self.grid_11.setGeometry(QtCore.QRect(540, 230, 64, 64))
        self.grid_11.setStyleSheet("background-color: rgb(203, 203, 203);")
        self.grid_11.setText("")
        self.grid_11.setObjectName("grid_11")
        self.grid_11.setAlignment(QtCore.Qt.AlignCenter)
        self.grid_12 = QtWidgets.QLabel(self.centralwidget)
        self.grid_12.setGeometry(QtCore.QRect(610, 230, 64, 64))
        self.grid_12.setStyleSheet("background-color: rgb(203, 203, 203);")
        self.grid_12.setText("")
        self.grid_12.setObjectName("grid_12")
        self.grid_12.setAlignment(QtCore.Qt.AlignCenter)
        self.grid_13 = QtWidgets.QLabel(self.centralwidget)
        self.grid_13.setGeometry(QtCore.QRect(400, 300, 64, 64))
        self.grid_13.setStyleSheet("background-color: rgb(203, 203, 203);")
        self.grid_13.setText("")
        self.grid_13.setObjectName("grid_13")
        self.grid_13.setAlignment(QtCore.Qt.AlignCenter)
        self.grid_14 = QtWidgets.QLabel(self.centralwidget)
        self.grid_14.setGeometry(QtCore.QRect(470, 300, 64, 64))
        self.grid_14.setStyleSheet("background-color: rgb(203, 203, 203);")
        self.grid_14.setText("")
        self.grid_14.setObjectName("grid_14")
        self.grid_14.setAlignment(QtCore.Qt.AlignCenter)
        self.grid_15 = QtWidgets.QLabel(self.centralwidget)
        self.grid_15.setGeometry(QtCore.QRect(540, 300, 64, 64))
        self.grid_15.setStyleSheet("background-color: rgb(203, 203, 203);")
        self.grid_15.setText("")
        self.grid_15.setObjectName("grid_15")
        self.grid_15.setAlignment(QtCore.Qt.AlignCenter)
        self.grid_16 = QtWidgets.QLabel(self.centralwidget)
        self.grid_16.setGeometry(QtCore.QRect(610, 300, 64, 64))
        self.grid_16.setStyleSheet("background-color: rgb(203, 203, 203);")
        self.grid_16.setText("")
        self.grid_16.setObjectName("grid_16")
        self.grid_16.setAlignment(QtCore.Qt.AlignCenter)
        self.textBrowser = QtWidgets.QTextBrowser(self.centralwidget)
        self.textBrowser.setGeometry(QtCore.QRect(390, 80, 294, 294))
        self.textBrowser.setStyleSheet("border: 0px ;\n"
"background-color: rgb(174, 142, 95);")
        self.textBrowser.setObjectName("textBrowser")

        self.label_2 = QtWidgets.QLabel(self.centralwidget)
        self.label_2.setGeometry(QtCore.QRect(520, 49, 31, 31))
        font = QtGui.QFont()
        font.setPointSize(20)
        font.setBold(False)
        font.setWeight(50)
        self.label_2.setFont(font)
        self.label_2.setAlignment(QtCore.Qt.AlignCenter)
        self.label_2.setObjectName("label_2")
        self.label_3 = QtWidgets.QLabel(self.centralwidget)
        self.label_3.setGeometry(QtCore.QRect(690, 220, 31, 16))
        font = QtGui.QFont()
        font.setPointSize(20)
        font.setBold(False)
        font.setWeight(50)
        self.label_3.setFont(font)
        self.label_3.setAlignment(QtCore.Qt.AlignCenter)
        self.label_3.setObjectName("label_3")
        self.label_4 = QtWidgets.QLabel(self.centralwidget)
        self.label_4.setGeometry(QtCore.QRect(370, 60, 31, 16))
        font = QtGui.QFont()
        font.setPointSize(16)
        self.label_4.setFont(font)
        self.label_4.setObjectName("label_4")
        self.label_5 = QtWidgets.QLabel(self.centralwidget)
        self.label_5.setGeometry(QtCore.QRect(690, 380, 31, 16))
        font = QtGui.QFont()
        font.setPointSize(16)
        self.label_5.setFont(font)
        self.label_5.setObjectName("label_5")

        self.textBrowser.raise_()
        self.label.raise_()
        self.tableWidget.raise_()
        self.grid_1.raise_()
        self.grid_2.raise_()
        self.grid_3.raise_()
        self.grid_5.raise_()
        self.grid_6.raise_()
        self.grid_4.raise_()
        self.grid_7.raise_()
        self.grid_8.raise_()
        self.grid_9.raise_()
        self.pushButton.raise_()
        self.pushButton_2.raise_()
        self.label_info.raise_()
        self.grid_10.raise_()
        self.grid_11.raise_()
        self.grid_12.raise_()
        self.grid_13.raise_()
        self.grid_14.raise_()
        self.grid_15.raise_()
        self.grid_16.raise_()

        self.label_2.raise_()
        self.label_3.raise_()
        self.label_4.raise_()
        self.label_5.raise_()
        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.label.setText(_translate("MainWindow", "Detected objects"))
        self.pushButton_2.setText(_translate("MainWindow", "DETECT"))
        self.label_2.setText(_translate("MainWindow", "X"))
        self.label_3.setText(_translate("MainWindow", "Y"))
        self.label_4.setText(_translate("MainWindow", "1:1"))
        self.label_5.setText(_translate("MainWindow", "4:4"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
