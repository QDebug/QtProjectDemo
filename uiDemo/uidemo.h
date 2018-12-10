#ifndef UIDEMO_H
#define UIDEMO_H

#include <QDialog>

namespace Ui {
class UiDemo;
}

class UiDemo : public QDialog
{
    Q_OBJECT

public:
    explicit UiDemo(QWidget *parent = 0);
    ~UiDemo();

protected:
   bool eventFilter(QObject *watched, QEvent *event);

private slots:
   void initForm();
   void initStyle();
   void initList();

   void on_btnMin_clicked();
   void on_btnMax_clicked();
   void on_btnClose_clicked();
private:
    Ui::UiDemo *ui;
};

#endif // UIDEMO_H
