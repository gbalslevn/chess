#include <iostream>
#include <cctype>
#include <vector>
#include <unordered_map>
#include "test.h"
using namespace std;

// K=king, q=queen, p=pawn, k=knight, r=rook, b=bishop
// Wq=white queen, Bq=black queen, .... and so on
// 00=empty field

// Array 0 indexed. a2=row: 1, col: 0
string board[8][8] = {
    {"Wr", "Wk", "Wb", "Wq", "WK", "Wb", "Wk", "Wr"}, // 0th row (White pieces)
    {"Wp", "Wp", "Wp", "Wp", "Wp", "Wp", "Wp", "Wp"}, // 1st row (White pawns)
    {"00", "00", "00", "00", "00", "00", "00", "00"}, // 2nd row (empty)
    {"00", "00", "00", "00", "00", "00", "00", "00"}, // 3rd row (empty)
    {"00", "00", "00", "00", "00", "00", "00", "00"}, // 4th row (empty)
    {"00", "00", "00", "00", "00", "00", "00", "00"}, // 5rd row (empty)
    {"Bp", "Bp", "Bp", "Bp", "Bp", "Bp", "Bp", "Bp"}, // 6th row (Black pawns)
    {"Br", "Bk", "Bb", "Bq", "BK", "Bb", "Bk", "Br"}  // 7th row (Black pieces)
};
bool gameinprocess = true;
int turn = 0;

struct Piece
{
    string name;
    int col;
    int row;
    string note;

    Piece(string n = "", int c = 100, int r = 100, string note = "") : name(n), col(c), row(r), note(note) {}

    bool operator==(const Piece& other) const
    {
        return name == other.name && 
               col == other.col && 
               row == other.row && 
               note == other.note;
    }
};

struct Move
{
    int col;
    int row;
    Move(int c = 100, int r = 100) : col(c), row(r) {}

    bool operator==(const Move &other) const
    { // To be able to compare if two Move structs are equal.
        return col == other.col && row == other.row;
    }

    friend ostream &operator<<(ostream &os, const Move &move)
    {
        os << static_cast<char>(move.col + 'a') << static_cast<char>(move.row + 1 + '0');
        return os;
    }
};

Piece enPassantPiece; // Store the latest piece which has been done an en passant 
Move enPassantMove;
bool whiteCanCastle = true;
bool blackCanCastle = true;
// Forward declarations to handle mutual recursion
void movePiece(string piece, string startPos);
vector<Move> getValidMoves(Piece piece);

void printBoard()
{
    cout << "The board is:\n";
    for (int i = 7; i >= 0; i--)
    {
        cout << i + 1 << " ";
        for (int j = 0; j < 8; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "  a  b  c  d  e  f  g  h\n";
}

void printBoardBlack()
{ // Board from blacks perspective
    cout << "The board is:\n";
    for (int i = 0; i < 8; i++)
    {
        cout << i + 1 << " ";
        for (int j = 7; j >= 0; j--)
        {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "  h  g  f  e  d  c  b  a\n";
}

Piece getPiece(string field)
{
    int row = field[1] - '0' - 1;
    int col = tolower(field[0]) - 'a'; // ASCII conversion to map from char to int. int is needed for coordinates in array.
    return Piece(board[row][col], col, row);
}

bool validateInput(string field)
{
    if (tolower(field[0]) < 'a' || tolower(field[0]) > 'h')
    {
        cout << "Move must start with a letter between a and h\n";
        return false;
    }

    if (field[1] < '1' || field[1] > '8')
    {
        cout << "Move must end with a number between 1 and 8\n";
        return false;
    }

    return true;
}

bool validateSelection(string field)
{
    bool validInput = validateInput(field);
    if (!validInput)
    {
        return false;
    }
    Piece piece = getPiece(field);
    if (piece.name == "00")
    {
        cout << "The field you selected is empty.\n";
        return false;
    }
    if (turn % 2 == 0 && piece.name[0] == 'B' || turn % 2 == 1 && piece.name[0] == 'W')
    {
        cout << "You cannot select an opponent piece.\n";
        return false;
    }
    vector<Move> validMoves = getValidMoves(piece);
    if (validMoves.size() == 0)
    {
        cout << field << " does not have any valid moves. Please select another piece. \n"; // - 'a' and - '0' to get correct ASCII representation
        return false;
        // Perhaps check for stalemate here
    }
    return true;
}

// General method for calculating valid moves which are not weird, so not for the pawn or knight
vector<Move> calculateMoves(vector<Move> moves, int pieceCol, int pieceRow, bool onestep, bool diagonal, bool cardinal)
{
    int direction[8][2] = {
        // {col, row}
        {0, 1},  // up
        {0, -1}, // down
        {1, 0},  // right
        {-1, 0}, // left
        {1, 1},  // Right up
        {1, -1}, // Right down
        {-1, 1}, // Left up
        {-1, -1} // Left down
    };

    int directionsStart = cardinal ? 0 : 4; // Using the directions array, the first 4 is the cardinal directions, then the diagonal.
    int directionsEnd = diagonal ? 8 : 4;
    for (size_t i = directionsStart; i < directionsEnd; i++)
    {
        int currentCol = pieceCol;
        int currentRow = pieceRow;
        bool hasRunIntoEnemyPiece = false;

        while (true)
        {
            currentCol += direction[i][0];
            currentRow += direction[i][1];
            bool isWithinBoard = currentCol >= 0 && currentCol <= 7 && currentRow >= 0 && currentRow <= 7;
            if (!isWithinBoard || hasRunIntoEnemyPiece)
            {
                break;
            }
            string pieceOnField = board[currentRow][currentCol];
            if (pieceOnField != "00")
            {
                if (turn % 2 == 0 && pieceOnField[0] == 'B' || turn % 2 == 1 && pieceOnField[0] == 'W')
                {
                    hasRunIntoEnemyPiece = true; // can only run into an enemy piece once (to capture)
                }
                else
                {
                    break; // has run into own piece
                }
            }
            moves.push_back(Move(currentCol, currentRow));
            if (onestep)
            {
                break;
            }
        }
    }
    return moves;
}

// Make a seperate file for this
vector<Move> getValidMoves(Piece piece)
{
    vector<Move> moves;
    int pieceCol = piece.col;
    int pieceRow = piece.row;

    if (piece.name[1] == 'r') // rook
    {
        moves = calculateMoves(moves, pieceCol, pieceRow, false, false, true);
        // Check for castling
    }
    if (piece.name[1] == 'k') // knight
    {
        int direction[8][2] = {
            // {col, row}
            {1, 2},
            {-1, 2},
            {2, 1},
            {-2, 1},
            {2, -1},
            {-2, -1},
            {1, -2},
            {-1, -2},
        };
        for (size_t i = 0; i < 8; i++)
        {
            int col = pieceCol + direction[i][0];
            int row = pieceRow + direction[i][1];
            if (col >= 0 && col <= 7 && row >= 0 && row <= 7)
            {
                moves.push_back(Move(col, row));
            }
        }
    }
    if (piece.name[1] == 'b') // bishop
    {
        moves = calculateMoves(moves, pieceCol, pieceRow, false, true, false);
    }
    if (piece.name[1] == 'K') // king
    {
        moves = calculateMoves(moves, pieceCol, pieceRow, true, true, true);
        // Check for castling
    }
    if (piece.name[1] == 'q') // queen
    {
        moves = calculateMoves(moves, pieceCol, pieceRow, false, true, true);
    }
    if (piece.name[1] == 'p') // Pawn
    {
        int moveDirection = turn % 2 == 0 ? 1 : -1;
        int boostRow = turn % 2 == 0 ? 1 : 6;
        string pieceInFront = board[pieceRow + moveDirection][pieceCol];
        string pieceInFrontFront = board[pieceRow + moveDirection + moveDirection][pieceCol];
        bool aPieceInFront = pieceInFront != "00";
        bool aPieceInFrontFront = pieceInFront != "00";
        if (pieceRow + moveDirection <= 7 && pieceRow + moveDirection >= 0 && !aPieceInFront)
        {
            moves.push_back(Move(pieceCol, pieceRow + moveDirection));
        }
        if (pieceRow == boostRow)
        {

            if (pieceRow + moveDirection + moveDirection <= 7 && pieceRow + moveDirection + moveDirection >= 0 && !aPieceInFrontFront)
            {
                moves.push_back(Move(pieceCol, pieceRow + moveDirection + moveDirection));
            }
        }

        // Check if there is a valid en passant move
        if (enPassantPiece.note == "enPassant" + to_string(turn - 1))
        {
            Move move = Move(enPassantPiece.col, enPassantPiece.row + moveDirection);
            enPassantMove = move;
            moves.push_back(move); 

        }
    }

    return moves;
}

// Check if pawn did en passant and adds it as an en passant target if so
void checkEnPassant(Piece piece) {
    int oneBack = turn % 2 == 0 ? -1 : 1;
    string opponent = turn % 2 == 0 ? "B" : "W";
    bool movedNextToAPawn = piece.col > 0 && board[piece.row][piece.col - 1] == opponent + "p" || piece.col < 7 && board[piece.row][piece.col + 1] == opponent + "p" ;
    if(movedNextToAPawn) {
        piece.note = "enPassant" + to_string(turn);
        enPassantPiece = piece;
        cout << "en passant...\n";
    }
}

bool validateMove(string field, Piece piece)
{
    bool validInput = validateInput(field);
    if (!validInput)
    {
        return false;
    }
    vector<Move> validMoves = getValidMoves(piece);
    if (find(validMoves.begin(), validMoves.end(), Move(field[0] - 'a', field[1] - '0' - 1)) == validMoves.end()) // check if move is not in validmoves
    {
        cout << "sorry, " << Move(field[0] - 'a', field[1] - '0' - 1) << " is not a valid move, only valid moves are: ";
        for (size_t i = 0; i < validMoves.size(); i++)
        {
            cout << validMoves[i] << ", ";
        }
        cout << "\n";
        return false;
    }
    return true;
}

void executeMove(string move, Piece piece)
{
    int row = move[1] - '0' - 1;
    int col = move[0] - 'a';
    Piece attackedPiece = getPiece(move);

    if (attackedPiece.name[1] == 'K')
    {
        gameinprocess = false;
        string winner = turn % 2 == 0 ? "White" : "Black";
        cout << winner << " won! Congratulations.";
        return;
    }

    if(piece.name[1] == 'p') {
        bool twoStepMove = abs(row - piece.row) - 2 == 0; // maybe combine this into the checkEnPassant method
        if(twoStepMove) {
            checkEnPassant(attackedPiece);
        }
        if(Move(col, row) == enPassantMove) {
            // Take the piece behind the en passant move
            board[enPassantPiece.row][enPassantPiece.col] = "00";
        }
    }

    board[row][col] = piece.name;
    board[piece.row][piece.col] = "00";

}

Piece selectPiece()
{
    string field;
    while (true)
    {
        cout << "Select piece: ";
        cin >> field;
        bool validInput = validateSelection(field);
        if (validInput)
        {
            return getPiece(field);
        }
        else
        {
            cout << "Please retype selection\n";
        }
    }
}

bool movePiece(Piece piece)
{
    string move;
    cout << "Move " << piece.name << "(" << "col: " << piece.col << "row: " << piece.row << ")" << " to: ";
    cin >> move;
    if (move == "back")
    {
        return false;
    }

    bool validMove = validateMove(move, piece);
    if (validMove)
    {
        executeMove(move, piece);
        turn++;
        return true;
    }
    cout << "Please retype move: \n";
    movePiece(piece);
    return false;
}

void handleTurn()
{
    string move;
    //testMethod();
    if (turn % 2 == 0)
    {
        cout << "White's turn\n";
        printBoard();
    }
    else
    {
        cout << "Black's turn\n";
        printBoardBlack();
    }
    Piece piece = selectPiece();
    bool succes = movePiece(piece);
    while (!succes)
    {
        Piece piece = selectPiece();
        succes = movePiece(piece);
    }
}

int main()
{
    while (gameinprocess)
    {
        handleTurn();
    }
    return 0;
}