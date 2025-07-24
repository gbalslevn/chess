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

struct Piece
{
    sf::Sprite sprite;
    shared_ptr<sf::Texture> texture;
    Piece(string texturePath, float row, float col)
    {
        texture = make_shared<sf::Texture>();
        if (!texture->loadFromFile(texturePath))
        {
            cerr << "Error loading: " << texturePath << "\n";
        }
        else
        {
            cout << "Loaded texture correctly\n";
        }
        texture->setSmooth(true);
        sprite.setTexture(*texture);
        // sprite.setScale(sf::Vector2f(0.5f, 0.5f));
        sprite.setPosition(sf::Vector2f(float(TILE_SIZE) * row, float(TILE_SIZE) * col));
    }
};

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

sf::Sprite *draggedPiece = nullptr;
vector<sf::Sprite> pieces;

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
                            draggedPiece = &pieces[i];
                            isDragging = true;
                            dragOffset = mousePos - pieces[i].getPosition();
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
                        draggedPiece->setPosition(col * TILE_SIZE + PIECE_ADJUST_X, row * TILE_SIZE + PIECE_ADJUST_Y);
                    }
                }
            }
            if (event.type == sf::Event::MouseMoved)
            {
                if(isDragging) {
                    sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
                    draggedPiece->setPosition(mousePos - dragOffset);
                }
                cout << "new mouse x: " << event.mouseMove.x << endl;
                cout << "new mouse y: " << event.mouseMove.y << endl;
            }
        }
        window.clear(sf::Color::Blue);
        drawBoard(window);
        for (int i = 0; i < pieces.size(); i++)
        {
            window.draw(pieces[i]);
        }
        // window.draw(testPiece.sprite);
        // window.draw(testPiece.sprite);
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