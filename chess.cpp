#include <iostream>
#include <cctype>
#include <vector>
#include <unordered_map>
#include <map>
using namespace std;

// K=king, q=queen, p=pawn, k=knight, r=rook, b=bishop
// Wq=white queen, Bq=black queen, .... and so on
// 00=empty field

bool gameinprocess = true;
int turn = 0;
int gamemode = 1; // Defaults to local game
int difficulty = 1;

struct Field
{
    int col;
    int row;
    Field(int c = -1, int r = -1) : col(c), row(r) {}

    bool operator==(const Field &other) const
    {
        return col == other.col && row == other.row;
    }

    friend ostream &operator<<(ostream &os, const Field &move)
    {
        os << static_cast<char>(move.col + 'a') << static_cast<char>(move.row + 1 + '0');
        return os;
    }
};

// Consider making a Move struct which keeps track of two fields (from, to) and a Piece. Would make some implementations easier.

struct Piece
{
    string name;
    Field field;
    string note;
    int value;

    Piece(string n = "00", Field field = Field(), string note = "", int value = 0) : name(n), field(field), note(note), value(value) {}

    bool operator==(const Piece &other) const
    {
        return name == other.name &&
               field.col == other.field.col &&
               field.row == other.field.row &&
               note == other.note;
    }

    // Needed to use Piece in a map.
    bool operator<(const Piece &other) const
    {
        if (name != other.name)
            return name < other.name;
        if (field.row != other.field.row)
            return field.row < other.field.row;
        if (field.col != other.field.col)
            return field.col < other.field.col;
        return note < other.note;
    }
};

// Array 0 indexed. a2=row: 1, col: 0
Piece board[8][8] = {
    {Piece("Wr", Field(0, 0), "", 5), Piece("Wk", Field(1, 0), "", 3), Piece("Wb", Field(2, 0), "", 3), Piece("Wq", Field(3, 0), "", 9), Piece("WK", Field(4, 0), "", 10), Piece("Wb", Field(5, 0), "", 3), Piece("Wk", Field(6, 0), "", 3), Piece("Wr", Field(7, 0), "", 5)}, // 0th row (White pieces)
    {Piece("Wp", Field(0, 1), "", 1), Piece("Wp", Field(1, 1), "", 1), Piece("Wp", Field(2, 1), "", 1), Piece("Wp", Field(3, 1), "", 1), Piece("Wp", Field(4, 1), "", 1), Piece("Wp", Field(5, 1), "", 1), Piece("Wp", Field(6, 1), "", 1), Piece("Wp", Field(7, 1), "", 1)},  // 1st row (White pawns)
    {Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece()},                                                                                                                                                                                                  // 2nd row (empty)
    {Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece()},                                                                                                                                                                                                  // 3rd row (empty)
    {Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece()},                                                                                                                                                                                                  // 4th row (empty)
    {Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece()},                                                                                                                                                                                                  // 5rd row (empty)
    {Piece("Bp", Field(0, 6), "", 1), Piece("Bp", Field(1, 6), "", 1), Piece("Bp", Field(2, 6), "", 1), Piece("Bp", Field(3, 6), "", 1), Piece("Bp", Field(4, 6), "", 1), Piece("Bp", Field(5, 6), "", 1), Piece("Bp", Field(6, 6), "", 1), Piece("Bp", Field(7, 6), "", 1)},  // 6th row (Black pawns)
    {Piece("Br", Field(0, 7), "", 5), Piece("Bk", Field(1, 7), "", 3), Piece("Bb", Field(2, 7), "", 3), Piece("Bq", Field(3, 7), "", 9), Piece("BK", Field(4, 7), "", 10), Piece("Bb", Field(5, 7), "", 3), Piece("Bk", Field(6, 7), "", 3), Piece("Br", Field(7, 7), "", 5)}  // 7th row (Black pieces)
};

Piece (&getBoard())[8][8] {
    return board;
}

// Representing an empty field
Piece createEmptyPiece()
{
    return Piece();
}

Piece enPassantPiece; // Store the latest piece which has been done an en passant
Field enPassantMove;
bool whiteCanCastle = true;
bool whiteRookOnHHasMoved = false; // This should be as note on the piece in the future if board contains Piece objects instead of strings
bool whiteRookOnAHasMoved = false;
bool blackCanCastle = true;
bool blackRookOnHHasMoved = false;
bool blackRookOnAHasMoved = false;

void printBoard()
{
    for (int i = 7; i >= 0; i--)
    {
        cout << i + 1 << " ";
        for (int j = 0; j < 8; j++)
        {
            cout << board[i][j].name << " ";
        }
        cout << "\n";
    }
    cout << "  a  b  c  d  e  f  g  h\n";
}

void printBoardBlack()
{ // Board from blacks perspective
    for (int i = 0; i < 8; i++)
    {
        cout << i + 1 << " ";
        for (int j = 7; j >= 0; j--)
        {
            cout << board[i][j].name << " ";
        }
        cout << "\n";
    }
    cout << "  h  g  f  e  d  c  b  a\n";
}

bool validateInput(Field field)
{
    if (field.col < 0 || field.col > 7)
    {
        cout << "Move must start with a letter between a and h\n";
        return false;
    }

    if (field.row < 0 || field.row > 7)
    {
        cout << "Move must end with a number between 1 and 8\n";
        return false;
    }

    return true;
}

// General method for calculating valid moves which are not weird, so not for the pawn or knight
vector<Field> calculateMoves(vector<Field> moves, Piece piece, bool onestep, bool diagonal, bool cardinal)
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
        int currentCol = piece.field.col;
        int currentRow = piece.field.row;
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
            Piece pieceOnCurrentField = board[currentRow][currentCol];
            if (pieceOnCurrentField.name != "00")
            {
                if (piece.name[0] == 'W' && pieceOnCurrentField.name[0] == 'B' || piece.name[0] == 'B' && pieceOnCurrentField.name[0] == 'W')
                {
                    hasRunIntoEnemyPiece = true; // can only run into an enemy piece once (to capture)
                }
                else
                {
                    break; // has run into own piece
                }
            }
            moves.push_back(Field(currentCol, currentRow));
            if (onestep)
            {
                break;
            }
        }
    }
    return moves;
}

// Checks if player has pieces in the way
bool pieceInTheWay(int direction, int steps)
{
    int row = turn % 2 == 0 ? 0 : 7;
    int currentCol = 4;
    bool pieceInTheWay = false;

    for (size_t i = 1; i < steps; i++)
    {
        currentCol += direction;
        if (board[row][currentCol].name != "00")
        {
            pieceInTheWay = true;
            break;
        }
    }
    return pieceInTheWay;
}

// Returns valid moves for the piece.
vector<Field> getValidMoves(Piece piece)
{
    vector<Field> moves;
    int pieceCol = piece.field.col;
    int pieceRow = piece.field.row;
    char pieceType = piece.name[1];

    if (pieceType == 'r') // rook
    {
        moves = calculateMoves(moves, piece, false, false, true);
        // Check for castling
    }
    if (pieceType == 'k') // knight
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
            bool ownPieceBlocks = piece.name[0] == 'W' ? board[row][col].name[0] == 'W' : board[row][col].name[0] == 'B';
            if (col >= 0 && col <= 7 && row >= 0 && row <= 7 && !ownPieceBlocks)
            {
                moves.push_back(Field(col, row));
            }
        }
    }
    if (pieceType == 'b') // bishop
    {
        moves = calculateMoves(moves, piece, false, true, false);
    }
    if (pieceType == 'K') // king
    {
        moves = calculateMoves(moves, piece, true, true, true);
        // Check for castling
        bool canCastle = piece.name[0] == 'W' ? whiteCanCastle : blackCanCastle;

        if (canCastle)
        {
            // Checks castle for the two directions
            bool pieceObstructingKingSide = pieceInTheWay(1, 3);
            bool rookHasBeenMovedKingSide = turn % 2 == 0 ? whiteRookOnHHasMoved : blackRookOnHHasMoved;
            if (!pieceObstructingKingSide && !rookHasBeenMovedKingSide)
            {
                moves.push_back(Field(pieceCol + 2, pieceRow));
            }
            bool pieceObstructingQueenSide = pieceInTheWay(-1, 4);
            bool rookHasBeenMovedQueenSide = turn % 2 == 0 ? whiteRookOnAHasMoved : blackRookOnAHasMoved;
            if (!pieceObstructingQueenSide && !rookHasBeenMovedQueenSide)
            {
                moves.push_back(Field(pieceCol - 2, pieceRow));
            }
        }
        // We allow the king to move to squares where it is under attack even though it cannot by the official rules
        // It should not be able to castle if its in check, AND the player should only be able to move king.
    }
    if (pieceType == 'q') // queen
    {
        moves = calculateMoves(moves, piece, false, true, true);
    }
    if (pieceType == 'p') // Pawn
    {
        int moveDirection = piece.name[0] == 'W' ? 1 : -1;
        int boostRow = piece.name[0] == 'W' ? 1 : 6;
        char opponent = turn % 2 == 0 ? 'B' : 'W';
        Piece pieceInFront = board[pieceRow + moveDirection][pieceCol];
        Piece pieceInFrontFront = board[pieceRow + moveDirection + moveDirection][pieceCol];
        bool aPieceInFront = pieceInFront.name != "00";
        bool aPieceInFrontFront = pieceInFrontFront.name != "00";
        if (pieceRow + moveDirection <= 7 && pieceRow + moveDirection >= 0)
        {
            if (!aPieceInFront)
            {
                moves.push_back(Field(pieceCol, pieceRow + moveDirection));
            }
            if (pieceRow == boostRow && !aPieceInFrontFront)
            {
                moves.push_back(Field(pieceCol, pieceRow + moveDirection + moveDirection));
            }

            // check if able to attack dionaginal
            if (board[pieceRow + moveDirection][pieceCol - 1].name[0] == opponent && pieceCol - 1 >= 0)
            {
                moves.push_back(Field(pieceCol - 1, pieceRow + moveDirection));
            }
            if (board[pieceRow + moveDirection][pieceCol + 1].name[0] == opponent && pieceCol + 1 <= 7)
            {
                moves.push_back(Field(pieceCol + 1, pieceRow + moveDirection));
            }
        }

        // Check if there is a valid en passant move
        if (enPassantPiece.note == "enPassant" + to_string(turn - 1))
        {
            Field move = Field(enPassantPiece.field.col, enPassantPiece.field.row + moveDirection);
            enPassantMove = move;
            moves.push_back(move);
        }
        // Could remove moves which puts oneself in check here. Responsibility is given to validatemove for now. Good thing about that is we only check for a single move instead of running all moves through inCheckAfterMove
    }

    return moves;
}

bool validateSelection(Field field)
{
    bool validInput = validateInput(field);
    if (!validInput)
    {
        return false;
    }
    Piece piece = board[field.row][field.col];
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
    vector<Field> validMoves = getValidMoves(piece);
    if (validMoves.size() == 0)
    {
        cout << field << " does not have any valid moves. Please select another piece. \n"; // - 'a' and - '0' to get correct ASCII representation
        return false;
        // Perhaps check for stalemate here
    }
    return true;
}

// Check if pawn did en passant and adds it as an en passant target if so
void checkEnPassant(Piece piece)
{
    string opponent = turn % 2 == 0 ? "B" : "W";
    bool movedNextToAPawn = piece.field.col - 1 > 0 && board[piece.field.row][piece.field.col - 1].name == opponent + "p" || piece.field.col + 1 < 7 && board[piece.field.row][piece.field.col + 1].name == opponent + "p";
    if (movedNextToAPawn)
    {
        piece.note = "enPassant" + to_string(turn);
        enPassantPiece = piece;
        cout << "en passant...\n";
    }
}

// Checks if the opponent is checked by the provided piece
bool pieceHasCheck(Piece piece, Piece boardState[8][8])
{
    vector<Field> moves = getValidMoves(piece);
    string opponentKing = piece.name[0] == 'W' ? "BK" : "WK";
    for (size_t i = 0; i < moves.size(); ++i)
    {
        if (boardState[moves[i].row][moves[i].col].name == opponentKing)
        {
            return true;
        }
    }
    return false;
}

bool currentPlayerIsChecked(Piece boardCopy[8][8])
{
    char currentPlayer = turn % 2 == 0 ? 'W' : 'B';
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            char player = boardCopy[row][col].name[0];
            if (player == currentPlayer)
            {
                continue;;
            }
            bool pieceIsChecking = pieceHasCheck(boardCopy[row][col], boardCopy);
            if (pieceIsChecking)
            {
                return true;
            }
        }
    }
    // Check if player can make any moves, if not, oponnent has won
    return false;
}

// Checks if the current player will be in check after moving the piece.
bool inCheckAfterMove(Field moveToField, Piece piece)
{
    bool inCheck = false;
    int moveToRow = moveToField.row;
    int moveToCol = moveToField.col;
    Piece boardCopy[8][8];
    memcpy(boardCopy, board, sizeof(board));
    boardCopy[moveToRow][moveToCol] = piece;
    boardCopy[piece.field.row][piece.field.col] = createEmptyPiece();
    piece.field = moveToField;
    if (currentPlayerIsChecked(boardCopy))
    {
        inCheck = true;
    }
    return inCheck;
}

// Checks the move to the provided field using the provided piece is valid
bool validateMove(Field fieldOfMove, Piece piece)
{
    bool validInput = validateInput(fieldOfMove);
    if (!validInput)
    {
        return false;
    }
    vector<Field> validMoves = getValidMoves(piece);
    if (find(validMoves.begin(), validMoves.end(), fieldOfMove) == validMoves.end()) // check if move is not in validmoves
    {
        cout << "sorry, " << fieldOfMove << " is not a valid move, only valid moves are: ";
        for (size_t i = 0; i < validMoves.size(); i++)
        {
            cout << validMoves[i] << ", ";
        }
        cout << "\n";
        return false;
    }
    // Check if player is in check after the move, by doing it, then reverse back
    bool playerInCheckAfterMove = inCheckAfterMove(fieldOfMove, piece);
    if (playerInCheckAfterMove)
    {
        cout << "The move puts you in check...\n";
        return false;
    }

    return true;
}

void executeMove(Field moveToField, Piece piece)
{
    Piece attackedPiece = board[moveToField.row][moveToField.col]; // Maybe rename Piece to Field

    if (attackedPiece.name[1] == 'K')
    {
        gameinprocess = false;
        string winner = turn % 2 == 0 ? "White" : "Black";
        cout << winner << " won! Congratulations.";
        return;
    }

    if (piece.name[1] == 'K')
    {
        if (turn % 2 == 0)
        {
            whiteCanCastle = false;
        }
        else
        {
            blackCanCastle = false;
        }
        bool moveWasCastle = abs(piece.field.col - moveToField.col) == 2;
        string rookName = turn % 2 == 0 ? "Wr" : "Br";
        if (moveWasCastle)
        {
            // Move the rook
            if (piece.field.col - moveToField.col < 0)
            { // Kingside
                board[piece.field.row][piece.field.col + 1].name = rookName;
                board[piece.field.row][7].name = "00";
            }
            else
            { // Queenside
                board[piece.field.row][piece.field.col - 1].name = rookName;
                board[piece.field.row][0].name = "00";
            }
        }
    }
    if (piece.name[1] == 'r')
    {
        if (turn % 2 == 0)
        {
            (moveToField.col == 7 ? whiteRookOnHHasMoved : whiteRookOnAHasMoved) = true;
        }
        else
        {
            (moveToField.col == 7 ? blackRookOnHHasMoved : blackRookOnAHasMoved) = true;
        }
    }

    if (piece.name[1] == 'p')
    {
        bool twoStepMove = abs(moveToField.row - piece.field.row) - 2 == 0; // maybe combine this into the checkEnPassant method
        if (twoStepMove)
        {
            checkEnPassant(attackedPiece);
        }
        if (moveToField == enPassantMove)
        {
            // Take the piece behind the en passant move
            board[enPassantPiece.field.row][enPassantPiece.field.col] = createEmptyPiece();
        }
    }

    Field currentField = piece.field;
    piece.field = moveToField;
    board[moveToField.row][moveToField.col] = piece;
    board[currentField.row][currentField.col] = createEmptyPiece();
    turn++;
}

Piece selectPiece()
{
    string field;
    while (true)
    {
        cout << "Select piece: ";
        cin >> field;
        int row = field[1] - '0' - 1;
        int col = field[0] - 'a';
        bool validInput = validateSelection(Field(col, row));
        if (validInput)
        {
            return board[row][col];
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
    cout << "Move " << piece.name << "(" << "col: " << piece.field.col << "row: " << piece.field.row << ")" << " to: ";
    cin >> move;
    if (move == "back")
    {
        return false;
    }

    int row = move[1] - '0' - 1; // ASCII conversion from string to int between 0-7
    int col = move[0] - 'a';
    Field fieldOfMove = Field(col, row);
    bool validMove = validateMove(fieldOfMove, piece);
    if (validMove)
    {
        executeMove(fieldOfMove, piece);
        return true;
    }
    cout << "Please retype move: \n";
    movePiece(piece);
    return false;
}

vector<Piece> getOwnPiecesWhichCanMove()
{
    char currentPlayer = turn % 2 == 0 ? 'W' : 'B';
    vector<Piece> possiblePieces;
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            Piece piece = board[row][col];
            char player = piece.name[0];
            if (player != currentPlayer)
            {
                continue;
            }
            vector<Field> moves = getValidMoves(piece);
            if (moves.size() > 0)
            {
                possiblePieces.push_back(piece);
            }
        }
    }
    return possiblePieces;
}

void computerMoveRandom()
{
    vector<Piece> possiblePieces = getOwnPiecesWhichCanMove();
    srand(time(0)); // seed for randomness
    int randomNum = rand() % possiblePieces.size();
    Piece randomPiece = possiblePieces[randomNum];
    vector<Field> movesForRandomPiece = getValidMoves(randomPiece);
    randomNum = rand() % movesForRandomPiece.size();
    Field randomMove = movesForRandomPiece[randomNum];
    bool moveSetsItselfInCheck = inCheckAfterMove(randomMove, randomPiece);
    if (!moveSetsItselfInCheck)
    {
        executeMove(randomMove, randomPiece);
        cout << "\nBlack moved " << randomPiece.name << " from " << Field(randomPiece.field.col, randomPiece.field.row) << " to " << randomMove << "\n";
    }
    else
    {
        computerMoveRandom();
    }
}

void computerMoveCleverRandom()
{
    vector<Piece> possiblePieces = getOwnPiecesWhichCanMove();
    map<Piece, Field> bestMoves;
    int highestValuePiece = 0;
    for (int i = 0; i < possiblePieces.size(); i++)
    {
        Piece piece = possiblePieces[i];
        vector<Field> validMoves = getValidMoves(piece);
        for (int i = 0; i < validMoves.size(); i++)
        {
            Field move = validMoves[i];
            Piece attackedPiece = board[move.row][move.col];
            if (attackedPiece.value > highestValuePiece)
            {
                bestMoves.clear();
                highestValuePiece = attackedPiece.value;
            }
            if (attackedPiece.value == highestValuePiece)
            {
                bestMoves[piece] = move;
            }
        }
    }
    srand(time(0)); // seed for randomness
    int randomNum = rand() % bestMoves.size();
    map<Piece, Field>::iterator iterator = bestMoves.begin(); // Here we really should just use a Move struct instead of using a Map.
    advance(iterator, randomNum);                             // Iterate random steps into bestMoves
    Piece randomPiece = iterator->first;
    Field randomMove = iterator->second;
    bool moveSetsItselfInCheck = inCheckAfterMove(randomMove, randomPiece);
    if (!moveSetsItselfInCheck)
    {
        executeMove(randomMove, randomPiece);
        cout << "\nBlack moved " << randomPiece.name << " from " << Field(randomPiece.field.col, randomPiece.field.row) << " to " << randomMove << "\n";
    }
    else
    {
        computerMoveCleverRandom();
    }
}

void computerMove()
{
    switch (difficulty)
    {
    case 1:
        computerMoveRandom();
        break;
    case 2:
        computerMoveCleverRandom();
        break;
    case 3:
        cout << "Selected computermode is not implemented, lol";
        break;
    }
}

void handleTurn()
{
    string move;
    // testMethod();
    if (turn % 2 == 0)
    {
        cout << "\nWhite's turn\n";
        printBoard();
    }
    else
    {
        if (gamemode == 2)
        { // For now computer is always black
            computerMove();
            cout << "\nWhite's turn\n";
            printBoard();
        }
        else
        {
            cout << "\nBlack's turn\n";
            printBoardBlack();
        }
    }
    Piece piece = selectPiece();
    bool succes = movePiece(piece);
    while (!succes)
    {
        Piece piece = selectPiece();
        succes = movePiece(piece);
    }
}

void startConsole()
{
    cout << "Welcome to the game of chess.\n";
    cout << "Press '1' for local game or '2' to play against computer: ";
    cin >> gamemode;
    if (gamemode != 1 && gamemode != 2)
    {
        cout << "Come on, please choose a valid gamemode. Now you have to start over.\n";
        cout << "Game shutting down!\n";
        gameinprocess = false;
    }
    if (gamemode == 2)
    {
        cout << "Select computer difficulty:\n";
        cout << "1. Easy (random moves)\n";
        cout << "2. Medium (greedy moves)\n";
        cout << "3. Hard (future)\n";
        cout << "Enter your choice (1-3): ";
        cin >> difficulty;
        if (difficulty != 1 && difficulty != 2)
        {
            cout << "Selected difficulty has not been implemented. Too bad.\n";
            cout << "Game shutting down!\n";
            gameinprocess = false;
        }
    }
    while (gameinprocess)
    {
        handleTurn();
    }
}