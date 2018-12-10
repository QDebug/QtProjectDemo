#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>

class Thread : public QThread
{
public:
    Thread();
    ~Thread();

    void run();

public slots:
    void threadStart();
    void threadPause();
    void threadStop();
    void threadResume();
    void threadPR();

private:
    bool m_buttonState;
    int m_i;
    QMutex m_mutex;
};

#endif // THREAD_H
