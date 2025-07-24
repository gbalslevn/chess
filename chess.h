#ifndef CHESS_H
#define CHESS_H
using namespace std;

struct Field {
    int col;
    int row;
    Field(int c = -1, int r = -1) : col(c), row(r) {}
};

struct Piece {
    string name;
    Field field;
    string note;
    int value;

    Piece(string n = "00", Field field = Field(), string note = "", int value = 0) : name(n), field(field), note(note), value(value) {}
};

Piece (&getBoard())[8][8];

void startConsole();
bool validateSelection(Field field);
bool validateMove(Field fieldOfMove, Piece piece);
void executeMove(Field moveToField, Piece piece);

#endif