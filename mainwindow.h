#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QWidget>
#include <QGridLayout>
#include <custombutton.h>
#include <QMainWindow>
#include <string>
class mainwindow : public  QMainWindow{
     Q_OBJECT
public:
     int length;
     int width;
     static std::string currenttarget;
     static std::vector<std::vector<CustomButton*>> hope;
     static std::vector<std::vector<int>> stored_matrix;
     mainwindow(int one, int two);
     void  make(int length, int width,QWidget  *value,std::vector<std::vector<CustomButton*>> targets,std::vector<std::vector<int>> frame);
     std::vector<std::string> split (std::string content, const char delim);
     int checkneighbors(int first, int second);
     void clearneighbors(int first, int second);
     bool checkcompletion();
     void resetl();
public slots:
     void handle();
     void rhandle();
     void reset();
};
#endif // MAINWINDOW_H
