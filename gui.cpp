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
int lastTurn = -1;
bool isGameOver = false;
sf::Vector2f dragOffset;
sf::Vector2f draggedStartPos;
sf::Sprite *draggedPiece = nullptr;
vector<sf::Sprite> pieces;
sf::Text announcementText;
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
    string playerInTurn = getTurn() % 2 == 0 ? "White" : "Black";
    string opponent = getTurn() % 2 != 0 ? "White" : "Black";
    announcementText.setFont(font);
    announcementText.setCharacterSize(18);
    announcementText.setFillColor(sf::Color::White);
    if (isGameOver)
    {
        announcementText.setString(opponent + " won.");
    }
    else
    {
        announcementText.setString(playerInTurn + " to move");
    }
    announcementText.setPosition(32, 32);
    window.draw(announcementText);
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
                            executeMove(moveTo, piece);
                            loader.refreshSpritesFromBoard(getBoard());
                            // draggedPiece->setPosition((col + 1) * TILE_SIZE + PIECE_ADJUST_X, abs(row - 8) * TILE_SIZE + PIECE_ADJUST_Y);
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
        int turn = getTurn();
        if (lastTurn < turn)
        {
            lastTurn = turn;
            if (!isGameInProcess())
            {
                isGameOver = true;
            }
            if (turn % 2 != 0)
            {
                computerMove();
                loader.refreshSpritesFromBoard(getBoard());
            }
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