#ifndef FLATUI_H
#define FLATUI_H

#include <QObject>

class QPushButton;
class QLineEdit;
class QProgressBar;
class QSlider;
class QRadioButton;
class QCheckBox;
class QScrollBar;

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5, 7, 0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT FlatUi : public QObject
#else
class FlatUi : public QObject
#endif
{
    Q_OBJECT
public:
    explicit FlatUi(QObject *parent = nullptr);
    static FlatUi *Instance();

private:
    static FlatUi *self;

public:
    //设置样式表
    void setPushButtonQss(QPushButton *btn,                             //按钮对象
                          int radius = 5,                               //圆角半径
                          int padding = 8,                              //间距
                          const QString &normalColor = "#34495E",       //正常颜色
                          const QString &normalTextColor = "#FFFFFF",   //文字颜色
                          const QString &hoverColor = "#4E6D8C",        //悬停颜色
                          const QString &hoverTextColor = "#F0F0F0",    //悬停文字颜色
                          const QString &pressedColor = "#2D3E50",      //按下颜色
                          const QString &pressedTextColor = "#B8C6D1"); //按下文字颜色

    //设置文本框颜色
    void setLineEditQss(QLineEdit *edit,                                //文本框颜色
                        int radius = 3,                                 //圆角半径
                        int borderWidth = 2,                            //边框大小
                        const QString &normalColor = "#DCE4EC",         //正常颜色
                        const QString &focusColor = "#34495E");         //选中颜色

    //设置进度条颜色
    void setProgressBarQss(QProgressBar *bar,                           //进度条对象
                           int barHeight = 8,                           //进度条高度
                           int barRadius = 5,                           //进度条半径
                           int fontSize = 9,                            //文字字号
                           const QString &normalColor = "#E8EDF2",      //正常颜色
                           const QString &chunkColor = "#E74C3C");     //进度颜色

    //设置滑块条样式
    void setSliderQss(QSlider *slider,
                      int sliderHeight = 8,
                      const QString &normalColor = "#E8EDF2",
                      const QString &grooveColor = "#1ABC9C",           //滑块颜色
                      const QString &handleColor = "#1ABC9C");          //指示器颜色


    //设置单选框颜色
    void setRadioButtonQss(QRadioButton *rbtn,                          //单选框对象
                           int indicatorRadius = 8,                     //指示器圆角角度
                           const QString &normalColor = "#D7DBDE",      //正常颜色
                           const QString &checkColor = "#34495e");      //选中颜色

    //设置滚动条样式
    void setScrollBarQss(QScrollBar *scorll,
                         int radius = 6,                                //圆角角度
                         int min = 120,                                 //指示器最小长度
                         int max = 12,                                  //滚动条最大长度
                         const QString &bgColor = "#606060",            //背景色
                         const QString &handleNormalColor = "#34495E",  //指示器正常颜色
                         const QString &handleHoverColor = "#1ABC9C",   //指示器悬停颜色
                         const QString &handlePressedColor = "#E74C3C");//指示器按下颜色)
signals:

public slots:
};

#endif // FLATUI_H
