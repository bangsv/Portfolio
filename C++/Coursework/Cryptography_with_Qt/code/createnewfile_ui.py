# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'd:\Desktop\Portfolio\C++\Coursework\Cryptography_with_Qt\code\createnewfile.ui'
#
# Created by: PyQt5 UI code generator 5.15.9
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_CreateNewFile(object):
    def setupUi(self, CreateNewFile):
        CreateNewFile.setObjectName("CreateNewFile")
        CreateNewFile.resize(490, 162)
        CreateNewFile.setMinimumSize(QtCore.QSize(490, 162))
        CreateNewFile.setMaximumSize(QtCore.QSize(490, 162))
        CreateNewFile.setStyleSheet("QWidget {\n"
" background-color: rgb(45, 45, 48);\n"
"}")
        self.str_input = QtWidgets.QLineEdit(CreateNewFile)
        self.str_input.setGeometry(QtCore.QRect(30, 70, 350, 71))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.str_input.sizePolicy().hasHeightForWidth())
        self.str_input.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setFamily("Franklin Gothic Medium Cond")
        font.setPointSize(12)
        font.setBold(False)
        font.setItalic(False)
        font.setUnderline(False)
        font.setWeight(50)
        self.str_input.setFont(font)
        self.str_input.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.str_input.setStyleSheet("QLineEdit{\n"
"border: 2px solid rgb(61, 61, 68);\n"
"border-radius: 20px;\n"
"color: rgb(0, 0, 0);\n"
"padding-left: 20px;\n"
"padding-right: 20px;\n"
"background-color: rgb(220, 220, 220);\n"
"}\n"
"\n"
"QLineEdit::hover{\n"
"border: 2px solid rgb(61, 61, 68);\n"
"}")
        self.str_input.setObjectName("str_input")
        self.pushButton = QtWidgets.QPushButton(CreateNewFile)
        self.pushButton.setGeometry(QtCore.QRect(400, 80, 75, 23))
        self.pushButton.setStyleSheet("QPushButton{\n"
"background-color: rgb(220, 220, 220);\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"border: 1px solid  rgb(181, 181, 181);\n"
"    background-color: rgb(181, 181, 181);\n"
"}")
        self.pushButton.setObjectName("pushButton")
        self.pushButton_2 = QtWidgets.QPushButton(CreateNewFile)
        self.pushButton_2.setGeometry(QtCore.QRect(400, 112, 75, 21))
        self.pushButton_2.setStyleSheet("QPushButton{\n"
"background-color: rgb(220, 220, 220);\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"border: 1px solid  rgb(181, 181, 181);\n"
"    background-color: rgb(181, 181, 181);\n"
"}")
        self.pushButton_2.setObjectName("pushButton_2")
        self.label = QtWidgets.QLabel(CreateNewFile)
        self.label.setEnabled(True)
        self.label.setGeometry(QtCore.QRect(90, 20, 231, 41))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(231)
        sizePolicy.setVerticalStretch(41)
        sizePolicy.setHeightForWidth(self.label.sizePolicy().hasHeightForWidth())
        self.label.setSizePolicy(sizePolicy)
        self.label.setMinimumSize(QtCore.QSize(231, 41))
        self.label.setMaximumSize(QtCore.QSize(231, 41))
        self.label.setSizeIncrement(QtCore.QSize(231, 41))
        self.label.setBaseSize(QtCore.QSize(231, 41))
        font = QtGui.QFont()
        font.setPointSize(12)
        font.setKerning(False)
        self.label.setFont(font)
        self.label.setStyleSheet("background-color: rgb(220, 220, 220);")
        self.label.setAlignment(QtCore.Qt.AlignCenter)
        self.label.setObjectName("label")

        self.retranslateUi(CreateNewFile)
        QtCore.QMetaObject.connectSlotsByName(CreateNewFile)

    def retranslateUi(self, CreateNewFile):
        _translate = QtCore.QCoreApplication.translate
        CreateNewFile.setWindowTitle(_translate("CreateNewFile", "Form"))
        self.str_input.setPlaceholderText(_translate("CreateNewFile", "Input text"))
        self.pushButton.setText(_translate("CreateNewFile", "Ok"))
        self.pushButton_2.setText(_translate("CreateNewFile", "Cancel"))
        self.label.setText(_translate("CreateNewFile", "Enter text"))