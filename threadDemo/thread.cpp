#include "thread.h"
#include <QDebug>

Thread::Thread()
{
    m_i = 0;
    m_buttonState = false;
}

Thread::~Thread()
{

}

void Thread::run()
{
    m_buttonState = true;
    while (1)
    {
        m_mutex.lock();
        m_i++;
        qDebug() << QString("the value of m_i is %1").arg(m_i);
        m_mutex.unlock();
        this->sleep(1);
    }
}

void Thread::threadStart()
{
    this->start();
}

void Thread::threadPause()
{
    qDebug() << QString("pause : %1").arg(m_buttonState);
    m_mutex.lock();
    m_buttonState = false;
    qDebug() << QString("pause");
}

void Thread::threadStop()
{
    this->terminate();
}
void Thread::threadResume()
{
    qDebug() << QString("pause : %1").arg(m_buttonState);
    m_mutex.unlock();
    m_buttonState = true;
    qDebug() << QString("pause");
}

void Thread::threadPR()
{
    if (m_buttonState)
        threadPause();
    else
        threadResume();
}
