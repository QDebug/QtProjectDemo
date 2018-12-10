#ifndef APPINIT_H
#define APPINIT_H

#include <QObject>
#include <QMutex>

class AppInit : public QObject
{
    Q_OBJECT
public:
    explicit AppInit(QObject *parent = 0);

    static AppInit *Instance();
    void start();

protected:
    bool eventFilter(QObject *, QEvent *);

private:
    static AppInit *self;

signals:

public slots:

};

#endif // APPINIT_H
