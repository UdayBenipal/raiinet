#include "textdisplay.h"

TextDisplay::TextDisplay() {
  for (int i = 0; i < display.size() ; ++i ){
    display.at(i).clear();
  }
  display.clear();
  for (int i = 0; i < 8; ++i ){
    std::vector<char> cells;
    for (int j = 0; j < 8; j++) {
      if((i == 0 || i == 7) && (j == 3 || j == 4)) {
        cells.emplace_back('S');
      } else {
        cells.emplace_back('.');
      }
    }
    display.emplace_back(cells);
  }
}

void TextDisplay::notify(Subject<posn, std::shared_ptr<Link>> &whoNotified) {
  int row = whoNotified.getInfo().row;
  int col = whoNotified.getInfo().col;
  if(whoNotified.getState()){
    display[row][col] = whoNotified.getState()->get_name();
  } else if(whoNotified.get_ability()) {
    if(whoNotified.get_ability()->get_player() == 1) {
      display[row][col] = 'm';
    } else {
      display[row][col] = 'w';
    }
  } else if((row==0 || row==7) && (col==3 || col==4)) {
    display[row][col] = 'S';
  } else {
      display[row][col] = '.';
  } 
}

TextDisplay::~TextDisplay() {}

//  Ouput Operator
std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
  out << "========" << std::endl;
  for(int i = 0 ; i < 8 ; i++){
    for (int j = 0 ; j < 8 ; j++){
      out << td.display[i][j];
      }
      out << std::endl;
  }
  out << "========" << std::endl;
  return out;
}
