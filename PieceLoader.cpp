#include "PieceLoader.h"
#include <iostream>
using namespace std;

// This class is neccesary for mainting the textures and not destroying them. Each piece needs to be loaded individually and each texture needs to be stored in its own variable to not be destroyed.
// A better solution might exist, but from my trials i found this solution to be neccesary. 

PieceLoader::PieceLoader(int tileSize, int pieceAdjustX, int pieceAdjustY) : TILE_SIZE(tileSize), PIECE_ADJUST_X(pieceAdjustX), PIECE_ADJUST_Y(pieceAdjustY)
{
    loadTextures();
    createSprites();
}

bool PieceLoader::loadTexture(string &path, sf::Texture &texture)
{
    if (!texture.loadFromFile(path))
    {
        cerr << "Error loading: " << path << "\n";
        return false;
    }
    texture.setSmooth(true);
    return true;
}

void PieceLoader::loadTextures()
{
    vector<string> texturePaths = {
        "images/white-rook.png", "images/white-knight.png", "images/white-bishop.png",
        "images/white-queen.png", "images/white-king.png", "images/white-pawn.png",
        "images/black-rook.png", "images/black-knight.png", "images/black-bishop.png",
        "images/black-queen.png", "images/black-king.png", "images/black-pawn.png"};

    for (auto &path : texturePaths)
    {
        sf::Texture tex;
        if (loadTexture(path, tex))
        {
            textures.push_back(move(tex));
        }
    }
}

void PieceLoader::createSprites()
{
    auto addPiece = [&](int texIndex, int col, int row)
    {
        sf::Sprite sprite;
        sprite.setTexture(textures[texIndex]);
        sprite.setScale(0.5f, 0.5f);
        sprite.setPosition(float(TILE_SIZE) * col + PIECE_ADJUST_X, float(TILE_SIZE) * row + PIECE_ADJUST_Y);
        pieces.push_back(sprite);
    };

    // White major pieces (row 1)
    addPiece(0, 1, 1);
    addPiece(0, 8, 1); // Rooks
    addPiece(1, 2, 1);
    addPiece(1, 7, 1); // Knights
    addPiece(2, 3, 1);
    addPiece(2, 6, 1); // Bishops
    addPiece(3, 4, 1); // Queen
    addPiece(4, 5, 1); // King

    // White pawns (row 2)
    for (int i = 1; i <= 8; ++i)
        addPiece(5, i, 2);

    // Black major pieces (row 8)
    addPiece(6, 1, 8);
    addPiece(6, 8, 8); // Rooks
    addPiece(7, 2, 8);
    addPiece(7, 7, 8); // Knights
    addPiece(8, 3, 8);
    addPiece(8, 6, 8);  // Bishops
    addPiece(9, 4, 8);  // Queen
    addPiece(10, 5, 8); // King

    // Black pawns (row 7)
    for (int i = 1; i <= 8; ++i)
        addPiece(11, i, 7);
}

vector<sf::Sprite> &PieceLoader::getPieces()
{
    return pieces;
}
