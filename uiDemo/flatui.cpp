#pragma execution_character_set("utf-8")

#include "flatui.h"
#include <QMutex>
#include <QPushButton>
#include <QLineEdit>
#include <QProgressBar>
#include <QSlider>
#include <QCheckBox>
#include <QScrollBar>
#include <QRadioButton>
#include <QDebug>

FlatUi *FlatUi::self = 0;

FlatUi *FlatUi::Instance()
{
    static QMutex mutex;

    if (!self) {
        QMutexLocker locker(&mutex);

        if (!self) {
            self = new FlatUi;
        }
    }

    return self;
}

FlatUi::FlatUi(QObject *parent) : QObject(parent)
{
}

//设置样式表
void FlatUi::setPushButtonQss(QPushButton *btn,                             //按钮对象
                      int radius,                               //圆角半径
                      int padding,                              //间距
                      const QString &normalColor,       //正常颜色
                      const QString &normalTextColor,   //文字颜色
                      const QString &hoverColor,        //悬停颜色
                      const QString &hoverTextColor,    //悬停文字颜色
                      const QString &pressedColor,      //按下颜色
                      const QString &pressedTextColor) //按下文字颜色
{
    QStringList qss;
    qss.append(QString("QPushButton{border-style:none;padding:%1px;border-radius:%spx;color:%3;background:%4;}")
               .arg(padding).arg(radius).arg(normalTextColor).arg(normalColor));
    qss.append(QString("QPushButton:hover{color:%1;background:%2};")
               .arg(hoverTextColor).arg(hoverColor));
    qss.append(QString("QPushButton:pressed{color:%1;background:%2}")
               .arg(pressedTextColor).arg(pressedColor));

    btn->setStyleSheet(qss.join(""));
}

void FlatUi::setLineEditQss(QLineEdit *txt, int radius, int borderWidth,
                            const QString &normalColor, const QString &focusColor)
{
    QStringList qss;
    qss.append(QString("QLineEdit{border-style:none;padding:3px;border-radius:%1px;border:%2px solid %3;}")
               .arg(radius).arg(borderWidth).arg(normalColor));
    qss.append(QString("QLineEdit:focus{border:%1px solid %2;}")
               .arg(borderWidth).arg(focusColor));
    txt->setStyleSheet(qss.join(""));
}

void FlatUi::setProgressBarQss(QProgressBar *bar, int barHeight, int barRadius, int fontSize,
                               const QString &normalColor, const QString &chunkColor)
{
    QStringList qss;
    qss.append(QString("QProgressBar{font:%1pt;background:%2;max-height:3pt;border-radius:%4px;text-align:center;border:1px solid %2;}")
               .arg(fontSize).arg(normalColor).arg(barHeight).arg(barRadius));
    qss.append(QString("QProgressBar:chunk{border-radius:%2px;background-color:%1;}")
               .arg(chunkColor).arg(barRadius));
    bar->setStyleSheet(qss.join(""));
}

void FlatUi::setSliderQss(QSlider *slider, int sliderHeight,
                          const QString &normalColor, const QString &grooveColor,
                          const QString &handleColor)
{
    int sliderRadius = sliderHeight / 2;
    int handleWidth = (sliderHeight * 3) / 2 + (sliderHeight / 5);
    int handleRadius = handleWidth / 2;
    int handleOffset = handleRadius / 2;

    QStringList qss;
    qss.append(QString("QSlider::groove:horizontal{background:%1;height:%2px;border-radius:%3px;}")
               .arg(normalColor).arg(sliderHeight).arg(sliderRadius));
    qss.append(QString("QSlider::add-page:horizontal{background:%1;height:%2px;border-radius:%3px;}")
               .arg(normalColor).arg(sliderHeight).arg(sliderRadius));
    qss.append(QString("QSlider::sub-page:horizontal{background:%1;height:%2px;border-radius:%3px;}")
               .arg(grooveColor).arg(sliderHeight).arg(sliderRadius));
    qss.append(QString("QSlider::handle:horizontal{width:%2px;margin-top:-%3px;margin-bottom:-%3px;border-radius:%4px;"
                       "background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 #FFFFFF,stop:0.8 %1);}")
               .arg(handleColor).arg(handleWidth).arg(handleOffset).arg(handleRadius));

    //偏移一个像素
    handleWidth = handleWidth + 1;
    qss.append(QString("QSlider::groove:vertical{width:%2px;border-radius:%3px;background:%1;}")
               .arg(normalColor).arg(sliderHeight).arg(sliderRadius));
    qss.append(QString("QSlider::add-page:vertical{width:%2px;border-radius:%3px;background:%1;}")
               .arg(grooveColor).arg(sliderHeight).arg(sliderRadius));
    qss.append(QString("QSlider::sub-page:vertical{width:%2px;border-radius:%3px;background:%1;}")
               .arg(normalColor).arg(sliderHeight).arg(sliderRadius));
    qss.append(QString("QSlider::handle:vertical{height:%2px;margin-left:-%3px;margin-right:-%3px;border-radius:%4px;"
                       "background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 #FFFFFF,stop:0.8 %1);}")
               .arg(handleColor).arg(handleWidth).arg(handleOffset).arg(handleRadius));

    slider->setStyleSheet(qss.join(""));
}

void FlatUi::setRadioButtonQss(QRadioButton *rbtn, int indicatorRadius,
                               const QString &normalColor, const QString &checkColor)
{
    int indicatorWidth = indicatorRadius * 2;

    QStringList qss;
    qss.append(QString("QRadioButton::indicator{border-radius:%1px;width:%2px;height:%2px;}")
               .arg(indicatorRadius).arg(indicatorWidth));
    qss.append(QString("QRadioButton::indicator::unchecked{background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,"
                       "stop:0.6 #FFFFFF,stop:0.7 %1);}").arg(normalColor));
    qss.append(QString("QRadioButton::indicator::checked{background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,"
                       "stop:0 %1,stop:0.3 %1,stop:0.4 #FFFFFF,stop:0.6 #FFFFFF,stop:0.7 %1);}").arg(checkColor));

    rbtn->setStyleSheet(qss.join(""));
}

void FlatUi::setScrollBarQss(QScrollBar *scroll, int radius, int min, int max,
                             const QString &bgColor, const QString &handleNormalColor,
                             const QString &handleHoverColor, const QString &handlePressedColor)
{
    //滚动条离背景间隔
    int padding = 0;

    QStringList qss;

    //handle:指示器,滚动条拉动部分 add-page:滚动条拉动时增加的部分 sub-page:滚动条拉动时减少的部分 add-line:递增按钮 sub-line:递减按钮

    //横向滚动条部分
    qss.append(QString("QScrollBar:horizontal{background:%1;padding:%2px;border-radius:%3px;max-height:%4px;}")
               .arg(bgColor).arg(padding).arg(radius).arg(max));
    qss.append(QString("QScrollBar::handle:horizontal{background:%1;min-width:%2px;border-radius:%3px;}")
               .arg(handleNormalColor).arg(min).arg(radius));
    qss.append(QString("QScrollBar::handle:horizontal:hover{background:%1;}")
               .arg(handleHoverColor));
    qss.append(QString("QScrollBar::handle:horizontal:pressed{background:%1;}")
               .arg(handlePressedColor));
    qss.append(QString("QScrollBar::add-page:horizontal{background:none;}"));
    qss.append(QString("QScrollBar::sub-page:horizontal{background:none;}"));
    qss.append(QString("QScrollBar::add-line:horizontal{background:none;}"));
    qss.append(QString("QScrollBar::sub-line:horizontal{background:none;}"));

    //纵向滚动条部分
    qss.append(QString("QScrollBar:vertical{background:%1;padding:%2px;border-radius:%3px;max-width:%4px;}")
               .arg(bgColor).arg(padding).arg(radius).arg(max));
    qss.append(QString("QScrollBar::handle:vertical{background:%1;min-height:%2px;border-radius:%3px;}")
               .arg(handleNormalColor).arg(min).arg(radius));
    qss.append(QString("QScrollBar::handle:vertical:hover{background:%1;}")
               .arg(handleHoverColor));
    qss.append(QString("QScrollBar::handle:vertical:pressed{background:%1;}")
               .arg(handlePressedColor));
    qss.append(QString("QScrollBar::add-page:vertical{background:none;}"));
    qss.append(QString("QScrollBar::sub-page:vertical{background:none;}"));
    qss.append(QString("QScrollBar::add-line:vertical{background:none;}"));
    qss.append(QString("QScrollBar::sub-line:vertical{background:none;}"));

    scroll->setStyleSheet(qss.join(""));
}