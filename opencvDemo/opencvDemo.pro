#-------------------------------------------------
#
# Project created by QtCreator 2018-12-11T09:50:21
#
#-------------------------------------------------

QT       += core gui


INCLUDEPATH += D:\QtProject\opencv\opencv-3.4.4-qt\install\include

LIBS += D:/QtProject/opencv/opencv-3.4.4-qt/install/x86/mingw/lib/libopencv_calib3d344.dll.a
LIBS += D:/QtProject/opencv/opencv-3.4.4-qt/install/x86/mingw/lib/libopencv_core344.dll.a
LIBS += D:/QtProject/opencv/opencv-3.4.4-qt/install/x86/mingw/lib/libopencv_dnn344.dll.a
LIBS += D:/QtProject/opencv/opencv-3.4.4-qt/install/x86/mingw/lib/libopencv_features2d344.dll.a
LIBS += D:/QtProject/opencv/opencv-3.4.4-qt/install/x86/mingw/lib/libopencv_flann344.dll.a
LIBS += D:/QtProject/opencv/opencv-3.4.4-qt/install/x86/mingw/lib/libopencv_highgui344.dll.a
LIBS += D:/QtProject/opencv/opencv-3.4.4-qt/install/x86/mingw/lib/libopencv_imgcodecs344.dll.a
LIBS += D:/QtProject/opencv/opencv-3.4.4-qt/install/x86/mingw/lib/libopencv_imgproc344.dll.a
LIBS += D:/QtProject/opencv/opencv-3.4.4-qt/install/x86/mingw/lib/libopencv_ml344.dll.a
LIBS += D:/QtProject/opencv/opencv-3.4.4-qt/install/x86/mingw/lib/libopencv_objdetect344.dll.a
LIBS += D:/QtProject/opencv/opencv-3.4.4-qt/install/x86/mingw/lib/libopencv_photo344.dll.a
LIBS += D:/QtProject/opencv/opencv-3.4.4-qt/install/x86/mingw/lib/libopencv_stitching344.dll.a
LIBS += D:/QtProject/opencv/opencv-3.4.4-qt/install/x86/mingw/lib/libopencv_video344.dll.a
LIBS += D:/QtProject/opencv/opencv-3.4.4-qt/install/x86/mingw/lib/libopencv_videoio344.dll.a

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opencvDemo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    readme.txt

RESOURCES += \
    resource.qrc
