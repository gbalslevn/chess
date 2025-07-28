#ifndef PIECE_LOADER_H
#define PIECE_LOADER_H

#include "chess.h"
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;

class PieceLoader {
public:
    PieceLoader(int tileSize, int pieceAdjustX, int pieceAdjustY);
    vector<sf::Sprite>& getPieces();
    void refreshSpritesFromBoard(Piece board[8][8]);

private:
    void loadTextures();
    void createSprites();
    int getTextureIndex(string name);
    void addPiece(int texIndex, int col, int row);

    int TILE_SIZE;
    int PIECE_ADJUST_X;
    int PIECE_ADJUST_Y;
    vector<sf::Texture> textures;
    vector<sf::Sprite> pieces;

    bool loadTexture(string& path, sf::Texture& texture);
};

#endif
