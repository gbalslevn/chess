#include <SFML/Graphics.hpp>
#include "chess.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include "PieceLoader.h"
using namespace std;

uint TILE_SIZE = 80;
uint PIECE_ADJUST_X = 8;
uint PIECE_ADJUST_Y = 8;
bool isDragging = false;
sf::Vector2f dragOffset;
sf::Vector2f draggedStartPos;
sf::Sprite *draggedPiece = nullptr;
vector<sf::Sprite> pieces;

sf::Font font;

// Converts a position on the board to the col on the board
int getCol(int posX)
{
    return int((posX + TILE_SIZE / 2) / TILE_SIZE) - 1;
}

// Converts a position on the board to the row on the board
int getRow(int posY)
{
    return abs(8 - int((posY + TILE_SIZE / 2) / TILE_SIZE));
}

void drawBoard(sf::RenderWindow &window)
{
    int boardSize = 10;
    // Create label text
    sf::Text label;
    label.setFont(font);
    label.setCharacterSize(18);
    label.setFillColor(sf::Color::White);
    sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    for (int row = boardSize; row > 0; --row)
    {
        for (int col = 0; col < boardSize; ++col)
        {
            bool isWhite = (row + col) % 2 == 0;
            tile.setFillColor(isWhite ? sf::Color(240, 217, 181) : sf::Color(181, 136, 99));
            tile.setPosition(float(col * TILE_SIZE), float(row * TILE_SIZE));
            if (col == 0 || col == boardSize - 1 || row == 0 || row == boardSize - 1)
            {
                tile.setFillColor(sf::Color(0, 0, 10));
            }
            window.draw(tile);

            // Draw column labels (a-h)
            if ((row == boardSize - 1) && col > 0 && col < 9)
            {
                label.setString(string(1, 'a' + col - 1));
                label.setPosition(col * TILE_SIZE + 32, row * TILE_SIZE + 16);
                window.draw(label);
            }

            // Draw row labels (1-8)
            if (col == 0 && row > 0 && row < 9)
            {
                label.setString(to_string(9 - row));
                label.setPosition(col * TILE_SIZE + 32, row * TILE_SIZE + 32);
                window.draw(label);
            }
        }
    }
}

int startGui()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess");

    PieceLoader loader(TILE_SIZE, PIECE_ADJUST_X, PIECE_ADJUST_Y);
    vector<sf::Sprite> &pieces = loader.getPieces();
    if (!font.loadFromFile("images/font.ttf"))
    {
        // Handle error
    }

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    for (int i = 0; i < pieces.size(); i++)
                    {
                        if (pieces[i].getGlobalBounds().contains(mousePos))
                        {
                            sf::Vector2f pos = pieces[i].getPosition();
                            int col = getCol(pos.x);
                            int row = getRow(pos.y);
                            bool validSelection = validateSelection(Field(col, row));
                            if (validSelection)
                            {
                                draggedPiece = &pieces[i];
                                isDragging = true;
                                draggedStartPos = pieces[i].getPosition();
                                dragOffset = mousePos - draggedStartPos;
                            }
                        }
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (isDragging)
                    {
                        isDragging = false;
                        // Snap to nearest tile
                        sf::Vector2f pos = draggedPiece->getPosition();
                        int col = getCol(pos.x);
                        int row = getRow(pos.y);
                        int startCol = getCol(draggedStartPos.x);
                        int startRow = getRow(draggedStartPos.y);
                        Piece(&board)[8][8] = getBoard();
                        Piece &piece = board[startRow][startCol];
                        Field moveTo = Field(col, row);
                        bool isMoveValid = validateMove(moveTo, piece);
                        if (isMoveValid)
                        {
                            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                            Piece pieceTaken = board[row][col];
                            bool tookOpponentPiece = pieceTaken.name[0] != piece.name[0] && pieceTaken.name != "00";
                            if (tookOpponentPiece)
                            {
                                for (int i = 0; i < pieces.size(); i++)
                                {
                                    if ((pieces[i].getGlobalBounds().contains(mousePos)) && (&pieces[i] != draggedPiece)) 
                                    {
                                        pieces[i].setColor(sf::Color(255, 255, 255, 0)); // Removing from vector created weird bugs
                                        pieces[i].setPosition(0,0);
                                        break;
                                    }
                                }
                            }
                            bool enPassantCapture = false; // make a get to check this?
                            if (enPassantCapture)
                            {
                                // Remove opponent piece from board
                            }
                            executeMove(moveTo, piece);

                            draggedPiece->setPosition((col + 1) * TILE_SIZE + PIECE_ADJUST_X, abs(row - 8) * TILE_SIZE + PIECE_ADJUST_Y);
                        }
                        else
                        {
                            draggedPiece->setPosition(draggedStartPos);
                        }
                    }
                }
            }
            if (event.type == sf::Event::MouseMoved)
            {
                if (isDragging)
                {
                    sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
                    draggedPiece->setPosition(mousePos - dragOffset);
                }
            }
        }
        window.clear(sf::Color::Black);
        drawBoard(window);
        for (int i = 0; i < pieces.size(); i++)
        {
            window.draw(pieces[i]);
        }
        window.display();
    }
    return 0;
}

int main()
{
    if (false)
    {
        startConsole();
    }
    else
    {
        startGui();
    }
    return 0;
}