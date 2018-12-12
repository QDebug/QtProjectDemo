初次使用opencv进行编译十分折腾，做下笔记吧.
编译工具:
1.mingw-w64-install.exe
网上说在64位系统下要使用这个版本的编译器，然而并不是，没有使用这个版本的编译器，使用的QT5.3.1 Tools文件夹下面的gcc,g++进行编译。

2.cmake-3.13.1-win64-x64.exe
在这个软件的gui下面进行编译配置比较方便。

3.opencv-3.4.4.zip
使用这个版本进行编译的，4.0.0刚开始失败了，所以换了一个版本。
使用opencv-4.0.0编译成功了，但是不知道为什么没有使用成功，懒得去琢磨了。

主要参考的资料：https://blog.csdn.net/moxiaonuo/article/details/77823990

注意：::
1.进行mingw32 make install 之后生成的install目录就是我自己要使用的目录，有动态库、头文件等。
2.在QT项目配置里面的path文件也要检查，qt貌似不自动更新，导致老是运行时出错。
3.确定代码读取的文件实在当前目录下，不然还是会出现运行时错误提示。
4.在.pro文件中导入链接库文件时需要注意格式，不然弄死不对，具体如下所示：

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
