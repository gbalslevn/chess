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

void drawBoard(sf::RenderWindow& window) {
    int boardSize = 10;
    sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            bool isWhite = (row + col) % 2 == 0;
            tile.setFillColor(isWhite ? sf::Color(240, 217, 181) : sf::Color(181, 136, 99));
            tile.setPosition(float(col * TILE_SIZE), float(row * TILE_SIZE));
            if(col == 0 || col == boardSize-1 || row == 0 || row == boardSize-1) {
                tile.setFillColor(sf::Color(0, 0, 10));
            }
            window.draw(tile);
        }
    }
}

int startGui()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess");

    PieceLoader loader(TILE_SIZE, PIECE_ADJUST_X, PIECE_ADJUST_Y); 
    vector<sf::Sprite> &pieces = loader.getPieces();

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
                            int col = int((pos.x + TILE_SIZE / 2) / TILE_SIZE);
                            int row = int((pos.y + TILE_SIZE / 2) / TILE_SIZE);
                            bool validSelection = validateSelection(Field(col - 1, row - 1));
                            if(validSelection) {
                                draggedPiece = &pieces[i];
                                isDragging = true;
                                draggedStartPos = pieces[i].getPosition();
                                dragOffset = mousePos - draggedStartPos;
                            } else {
                                cout << "Cannot select that piece\n";
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
                        int col = int((pos.x + TILE_SIZE / 2) / TILE_SIZE);
                        int row = int((pos.y + TILE_SIZE / 2) / TILE_SIZE);
                        int startCol = int((draggedStartPos.x + TILE_SIZE / 2) / TILE_SIZE);
                        int startRow = int((draggedStartPos.y + TILE_SIZE / 2) / TILE_SIZE);
                        Piece (&board)[8][8] = getBoard();
                        Piece piece = board[startRow-1][startCol-1];
                        cout << piece.name;
                        Field moveTo = Field(col-1, row-1);
                        bool isMoveValid = validateMove(moveTo, piece);
                        if(isMoveValid) {
                            executeMove(moveTo, piece);
                            bool tookOpponentPiece = board[row-1][col-1].name[0] != piece.name[0] && board[row-1][col-1].name != "00";
                            if(tookOpponentPiece) {
                                // Remove opponent piece from board
                            }
                            bool enPassantCapture = false; // make a get to check perhaps? 
                            if(enPassantCapture) {
                                // Remove opponent piece from board
                            }
                            draggedPiece->setPosition(col * TILE_SIZE + PIECE_ADJUST_X, row * TILE_SIZE + PIECE_ADJUST_Y);
                        } else {
                            draggedPiece->setPosition(draggedStartPos);
                        }
                    }
                }
            }
            if (event.type == sf::Event::MouseMoved)
            {
                if(isDragging) {
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

int main() {
    if(false) {
        startConsole();
    } else {
        startGui();
    }
    return 0;
}