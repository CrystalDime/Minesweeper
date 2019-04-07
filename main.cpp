#include "mainwindow.h"
#include <custombutton.h>
#include <QApplication>
#include <custombutton.h>
#include <QString>
#include <matrix.h>
#include <string>
using namespace std;
#include <QGridLayout>
#include <vector>
int main(int argc, char *argv[])
{
  QApplication app (argc, argv);
    int length = 20;
    int width = 20;
    mainwindow *guide = new mainwindow(length,width);
    Matrix coolio(length,width);
    std::vector<std::vector<int>> frame = coolio.setup();
    QWidget  *main_window = new QWidget();
   // main_window ->setFixedSize(QSize(length * factor, width * factor));
    std::vector<std::vector<CustomButton*>> targets;
    for (int l = 0; l < length; l++){
        std::vector<CustomButton*> filler;
        for (int w = 0; w < width; w++){
            filler.push_back(new  CustomButton());
        }
        targets.push_back(filler);
    }
    guide->make(length,width,main_window,targets,frame);
    main_window -> setWindowTitle(QString::fromStdString("MineSweeper"));
    main_window->show();
    main_window ->setFixedSize(main_window ->size());
    return app.exec();
}

//important to do list:: style buttons and add file menu to start new game
