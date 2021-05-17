#include "graphicsdisplay.h"
#include "cell.h"
#include "player.h"
#include <string>

GraphicsDisplay::GraphicsDisplay(std::shared_ptr<player> p1,
    std::shared_ptr<player> p2): p1{p1}, p2{p2}, turn{0} {
    
    link.clear();
    Xw = std::make_shared<Xwindow>(410, 500);

    for (int i = 0; i < 8; ++i ){
        std::map<int,information> arr;
        for (int j = 0; j < 8; j++) {
            arr[j] = information(white);
        }
        link.emplace_back(arr);
    }
}
        

void GraphicsDisplay::notify(Subject<posn, std::shared_ptr<Link>> &whoNotified) {
    int row = whoNotified.getInfo().row;
    int col = whoNotified.getInfo().col;

    if(whoNotified.getState()){ //piece
        link[row][col].colour = cyan;
        link[row][col].name = whoNotified.getState()->get_name();
        link[row][col].player = whoNotified.getState()->get_player();
        link[row][col].type = whoNotified.getState()->get_type();
        link[row][col].strength = whoNotified.getState()->get_strength();
    } else if(whoNotified.get_ability()) { //cell ability
        link[row][col].colour = yellow;
        link[row][col].player = whoNotified.get_ability()->get_player();
    } else if((row==0 || row==7) && (col==3 || col==4)) { //server port
        link[row][col].colour = blue;
    } else { //empty cell
        link[row][col].colour = white;
    }
}


void GraphicsDisplay::display() {
    int y = 50;
    int x = 5;
    int box_size = 50;
    int active = turn+1;

    std::string ablts1 = "Abilities: ";
    std::string ablts2 = "Abilities: ";
    std::vector<char> a1 = p1->get_abilities();
    std::vector<char> a2 = p2->get_abilities();

    std::string data1 = "Downloaded: ";
    std::string data2 = "Downloaded: ";
    data1+=std::to_string(p1->getdata());
    data2+=std::to_string(p2->getdata());
    data1+="D, ";
    data2+="D, ";
    data1+=std::to_string(p1->getvirus());
    data2+=std::to_string(p2->getvirus());
    data1+="V";
    data2+="V";

    Xw->fillRectangle(0,0,410,500,black);

    Xw->drawBigString(140, 30, "PLAYER 1", yellow);
    Xw->drawBigString(140, 495, "PLAYER 2", yellow);

    for(int i = 0; i < 5; ++i) {
        if(a1[i] < 91) {
            ablts1+=a1[i];
        } else {
            ablts1+=" ";
        }
        if(a2[i] < 91) {
            ablts2+=a2[i];
        } else {
            ablts2+=" ";
        }
        if(i != 4) {
            ablts1+=" ";
            ablts2+=" ";
        }
    }

    Xw->drawString(7, 45, data1, yellow);
    Xw->drawString(7, 465, data2, yellow);

    Xw->drawString(280, 45, ablts1, yellow);
    Xw->drawString(280, 465, ablts2, yellow);

    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            if(link[i][j].colour == 5) {
                if((active == link[i][j].player) || 
                    (active == 1 && p2->is_hidden(link[i][j].name) == 0) || 
                    (active == 2 && p1->is_hidden(link[i][j].name) == 0)) {
                    if(link[i][j].type == 'D') {
                        Xw->fillRectangle(x+j*box_size,y+i*box_size,box_size,box_size,green);
                    } else {
                        Xw->fillRectangle(x+j*box_size,y+i*box_size,box_size,box_size,red);
                    }
                    Xw->drawString(x+x+j*box_size, y+(box_size-x)+i*box_size, 
                                    std::to_string(link[i][j].strength));
                } else {
                    Xw->fillRectangle(x+j*box_size,y+i*box_size,box_size,box_size,cyan);
                }
                std::string s;
                s+=link[i][j].name;
                Xw->drawBigString(x+(box_size/3)+j*box_size, y+(2*(box_size/3))+i*box_size, s);
            } else if(link[i][j].colour == yellow) {
                Xw->fillRectangle(x+j*box_size,y+i*box_size,box_size,box_size,yellow);
                Xw->drawBigString(x+(box_size/3)+j*box_size, 
                                  y+(2*(box_size/3))+i*box_size, 
                                  std::to_string(link[i][j].player));
            } else {
                Xw->fillRectangle(x+j*box_size,y+i*box_size,box_size,box_size,link[i][j].colour);
            }
        }
    }

    for(int i = 0; i < 9; ++i) {
        Xw->drawLine(x, y+i*box_size, x+400, y+i*box_size);
        Xw->drawLine(x+i*box_size, y, x+i*box_size, y+400);
    }

    turn+=1;
    turn%=2;
}
