#include <mainwindow.h>
#include <custombutton.h>
#include <iostream>
#include <matrix.h>
#include <string>
#include <thread>
#include <chrono>


mainwindow::mainwindow(int one, int two){
        length = one;
        width = two;
}

std::string mainwindow::currenttarget;
std::vector<std::vector<CustomButton*>> mainwindow::hope;
std::vector<std::vector<int>> mainwindow::stored_matrix;
void mainwindow::make(int length, int width,QWidget  *value,std::vector<std::vector<CustomButton*>> targets,std::vector<std::vector<int>> frame){

    QGridLayout *layout = new QGridLayout();
    layout->setHorizontalSpacing(0);
    layout -> setVerticalSpacing(0);
    for (int l = 0; l < length; l ++){
        for ( int w = 0; w <width; w++){
            layout ->addWidget(targets[l][w],l + 1,w);
           std:: string identifier = std::to_string(l) + "/" + std::to_string(w);
            QString resultant = QString::fromStdString(identifier);
            targets[l][w]-> setObjectName(resultant);
            targets[l][w]-> setMinimumSize(35,35);
            targets[l][w] -> setMaximumSize(35,35);
           // targets[l][w] -> setStyleSheet()
            QObject::connect(targets[l][w], SIGNAL(clicked()), this, SLOT(handle()));
            QObject::connect(targets[l][w], SIGNAL(rightClicked()), this, SLOT(rhandle()));
        }
    }
    CustomButton *reset = new CustomButton();
    reset -> setText("New Game");
    reset-> setMinimumSize(70,30);
    reset -> setMaximumSize(70,30);
    QObject::connect(reset, SIGNAL(clicked()),this,SLOT(reset()));
    layout -> addWidget(reset,0 ,width - width / 2 - 1,1,3 );
    hope = targets;
    stored_matrix = frame;
    value->setLayout(layout);

};


void mainwindow::reset(){
       Matrix newgame(length,width);
       std::vector<std::vector<int>> frame = newgame.setup();
       stored_matrix = frame;
       for (int x = 0; x < length; x++){
           for (int y = 0; y < width; y ++){
               CustomButton * storage = hope[x][y];
               storage -> setText("");
               storage -> setEnabled(true);
               std:: string identifier = std::to_string(x) + "/" + std::to_string(y);
               QString resultant = QString::fromStdString(identifier);
               storage -> setObjectName(resultant);
           }
       }
}

void mainwindow::resetl(){
       Matrix newgame(length,width);
       std::vector<std::vector<int>> frame = newgame.setup();
       stored_matrix = frame;
       for (int x = 0; x < length; x++){
           for (int y = 0; y < width; y ++){
               CustomButton * storage = hope[x][y];
               storage -> setText("loser");
               storage -> setEnabled(false);
               std:: string identifier = std::to_string(x) + "/" + std::to_string(y);
               QString resultant = QString::fromStdString(identifier);
               storage -> setObjectName(resultant);
           }
       }
       std::this_thread::sleep_for(std::chrono::milliseconds(200));
       for (int x = 0; x < length; x++){
           for (int y = 0; y < width; y ++){
               CustomButton * storage = hope[x][y];
               storage -> setText("");
               storage -> setEnabled(true);
           }
       }
}
void mainwindow::handle(){
    CustomButton* holder =  (CustomButton *)sender();  //best chance of setting text is here
    QString wow =  holder->objectName();
    std::string usable = wow.toStdString();
    currenttarget = usable;
    std::vector<std::string> positionstring = split(usable,'/');
    int first = atoi(positionstring[0].c_str());
    int second = atoi(positionstring[1].c_str());
    int corosponding = stored_matrix[first][second];
    if (corosponding == 1){
        holder->setText(QString::fromStdString("b"));
        resetl();
    }
    else{
        int tally = checkneighbors(first,second);
        if (tally == 0){
            holder ->setEnabled(false);
            holder -> setText(QString::fromStdString(""));
            holder -> setObjectName(QString::fromStdString("done"));
            clearneighbors(first,second);
        }
        else{
        holder ->setEnabled(false);
        std::string number = std::to_string(tally);
        holder -> setText(QString::fromStdString(number));
        holder -> setObjectName(QString::fromStdString("done"));

        }
    }
    bool gamestate = checkcompletion();
    std::cout << gamestate << "\n";
};

bool mainwindow::checkcompletion(){
    int finalv = 0;
    int amountofb = 0;
    for (int p = 0; p < length;p++){
        for (int w = 0; w < width; w++){
           CustomButton* check = hope[p][w];
           int value = stored_matrix[p][w];
           if (value == 1){
               amountofb += 1;
               continue;
           }
           else{
               QString clep  = check->objectName();
               std::string u = clep.toStdString();
               if (u == "done"){
                   check -> setEnabled(false);
                   finalv += 1;
               }
           }
        }
    }
    int total = length * width;
    int refinedtotal = total - amountofb;
    if (finalv== refinedtotal){
        return true;
    }
    return false;
}
void mainwindow::rhandle(){
    CustomButton* holder = (CustomButton*)sender();
    holder ->setText(QString::fromStdString("F"));
}
/*  og = (1,1) -- > (0,0), (0,1)(0,2) (1,0),(1,2),(2,0),(2,1),(2,2) --> therfore it can be derived that neighbors are equal to -->> (x - 1, y - 1), (x - 1, y),( x - 1, y + 1),(x, y - 1), (x, y + 1),(x + 1, y - 1),(x + 1,y), (x + 1, y + 1)
     [
     [a,a,a,a],
     [a,a,a,a],
     [a,a,a,a],
     [a,a,a,a],

     ]
*/

void mainwindow::clearneighbors(int first,int second){
    int xlist[3] = {first - 1, first, first + 1};
    int ylist[3] = {second - 1, second, second + 1};
    for (int x = 0; x < 3; x++){
        for (int y = 0; y < 3; y ++){
            if (xlist[x] == first && ylist[y] == second){
                continue;
            }
            else{
                if (xlist[x] >= 0 && xlist[x]<= length - 1 && ylist[y] >= 0 && ylist[y] <= width - 1 ){
                    int tally = checkneighbors(xlist[x],ylist[y]);
                    CustomButton *button = hope[xlist[x]][ylist[y]];
                    QString name = button->objectName();
                    std::string realname = name.toStdString();
                    if (realname == "done"){
                        continue;
                    }
                    if (tally == 0){
                        std::string number = "";
                        button ->setEnabled(false);
                        button -> setText(QString::fromStdString(number));
                        button -> setObjectName(QString::fromStdString("done"));
                        clearneighbors(xlist[x],ylist[y]);
                    }
                    else{
                      button ->setEnabled(false);
                      std::string number = std::to_string(tally);
                      button -> setText(QString::fromStdString(number));
                      button -> setObjectName(QString::fromStdString("done"));
                    }
                }
            }
        }
    }

}
int mainwindow::checkneighbors(int first,int second){
    int tally = 0;
    int xlist[3] = {first - 1, first, first + 1};
    int ylist[3] = {second - 1, second, second + 1};
    for (int x = 0; x < 3; x++){
        for (int y = 0; y < 3; y ++){
            if (xlist[x] == first && ylist[y] == second){
                continue;
            }
            else{
                if (xlist[x] >= 0 && xlist[x]<= length - 1 && ylist[y] >= 0 && ylist[y] <= width - 1 ){
                    int resultant = stored_matrix[xlist[x]][ylist[y]];
                    if (resultant == 1){
                        tally = tally + resultant;
                    }
                }
            }
        }
    }
    return tally;
}

std::vector<std::string> mainwindow::split (std::string input, const char delim){
       std::vector<std::string> bank;
       int starting_index;
       bool checker = false;
       for (int i = 0; i < input.length(); i++){
         if (i == 0){
           starting_index = 0;
         }
         if (input[i] == delim ){
           std::string substring = input.substr(starting_index,(i - starting_index));
           bank.push_back(substring);
           starting_index = i + 1;
         }
       }
       std::string last_substring;
       try{
        std::string last_substring = input.substr(starting_index, input.length() - 1);
        checker = true;
       }
       catch(int e){
         std::cout << e;
       }
       if (checker){
         std::string last_substring = input.substr(starting_index, input.length() - 1);
         bank.push_back(last_substring);
       }
       return bank;
    }



