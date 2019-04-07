#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H
#include <QPushButton>
#include <QMouseEvent>

class CustomButton : public QPushButton{
        Q_OBJECT
public:
    explicit CustomButton(QWidget *parent = 0);
private slots:
    void mousePressEvent(QMouseEvent *e);
 signals:
    void clicked();
    void rightClicked();
 public slots:
};

#endif // CUSTOMBUTTON_H
