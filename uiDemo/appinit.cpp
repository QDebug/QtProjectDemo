#include "appinit.h"
#include <QApplication>
#include <QEvent>
#include <QWidget>
#include <QMouseEvent>

AppInit *AppInit:: self = 0;
AppInit::AppInit(QObject *parent) :
    QObject(parent)
{
}

AppInit* AppInit::Instance()
{
    static QMutex mutex;
    if (!self)
    {
        QMutexLocker locker(&mutex);
        if (!self)
        {
            self = new AppInit;
        }
    }
    return self;
}

void AppInit::start()
{
    qApp->installEventFilter(this);
}

bool AppInit::eventFilter(QObject *obj, QEvent *evt)
{
    QWidget *w = (QWidget *)obj;
    if (!w->property("canMove").toBool())
        return QObject::eventFilter(obj, evt);

    static QPoint mousePoint;
    static bool mousePressed = false;

    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (event->button() == Qt::LeftButton)
        {
            mousePressed = true;
            mousePoint = event->globalPos() - w->pos();
            return true;
        }
    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
        mousePressed = false;
        return true;
    }
    else if (event->type() == QEvent::MouseMove)
    {
        if (mousePressed && (event->buttons() && Qt::LeftButton))
        {
            w->move(event->globalPos() - mousePoint);
            return true;
        }
    }

    return QObject::eventFilter(obj, evt);
}
