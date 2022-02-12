#include "Map.h"

Map::~Map()
{
    delete[] tiles;
    tiles = nullptr;
}

Tile& Map::getTile(Vec2<int> pos)
{
    return tiles[(pos.y - topLeft.y) / tileSize * mapWidth + (pos.x - topLeft.x) / tileSize];
}

Tile& Map::getLeftTile(Vec2<int> pos)
{
    return tiles[(pos.y - topLeft.y) / tileSize * mapWidth + (pos.x - topLeft.x - 1 * tileSize) / tileSize ];
}

Tile& Map::getRightTile(Vec2<int> pos)
{
    return tiles[(pos.y - topLeft.y) / tileSize * mapWidth + (pos.x - topLeft.x + 1 * tileSize) / tileSize];
}

Tile& Map::getTopTile(Vec2<int> pos)
{
    return tiles[(pos.y - topLeft.y - 1 * tileSize) / tileSize * mapWidth + (pos.x - topLeft.x) / tileSize];
}

Tile& Map::getBottomTile(Vec2<int> pos)
{
    return tiles[(pos.y - topLeft.y + 1 * tileSize) / tileSize * mapWidth + (pos.x - topLeft.x) / tileSize];
}

Tile& Map::getTileByIndex(int i, int j)
{
    return tiles[i * mapWidth + j];
}

bool Map::wallInfront(Vec2<int> pos, Vec2<int> dir)
{
    Vec2<int> nextTilePos = pos + (dir * tileSize / 2 );
    Tile& nextTile = getTile(nextTilePos);
    return nextTile.checkFlags(Tile::TileState::Wall) > 0;
}

void Map::loadMapFromImage(std::string path)
{
    SDL_Surface* surf = IMG_Load(path.c_str());
    const uint8_t bpp = surf->format->BytesPerPixel;
    
    if (tiles != nullptr) {
        delete[] tiles;
    }

    mapWidth = surf->w;
    mapHeight = surf->h;
    tiles = new Tile[mapWidth * mapHeight];

    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            uint8_t* pPixel = (uint8_t*) surf->pixels + (y * mapWidth + x * bpp);
            uint32_t byteResult = 0;
            switch (bpp)
            {
            case 1:
                byteResult = *pPixel;
                break;
            case 2:
                byteResult = *(uint16_t*)pPixel;
            case 3:
                if (SDL_BYTEORDER == SDL_LIL_ENDIAN)
                    byteResult = pPixel[0] | pPixel[1] << 8 | pPixel[2] << 16;
                else 
                    byteResult = pPixel[0] << 16 | pPixel[1] << 8 | pPixel[2];
            case 4:
                byteResult = *(uint32_t*)pPixel;
            default:
                break;
            }

            SDL_Color color;
            SDL_GetRGB(byteResult, surf->format, &color.r, &color.g, &color.b);


            // Skip Black colored pixel because Black resamble a Wall and Tile default flag is Wall
            if (color.r == 255 && 
                color.g == 255 && 
                color.b == 255) {
                Vec2<int> tilePos = {  x * tileSize, y * tileSize };
                Tile& curTile = getTile(tilePos);
                curTile.setFlags(Tile::TileState::Road);
                curTile.setPosition(tilePos);
                curTile.setSize(tileSize, tileSize);
            }
        }
    }
}

void Map::loadMapFromVector(std::vector<int> mapVector, Animation& coinAnim, int _mapWidth, int _mapHeight)
{
    if (tiles != nullptr) {
        delete[] tiles;
    }
    
    mapWidth = _mapWidth;
    mapHeight = _mapHeight;
    tiles = new Tile[mapWidth * mapHeight];

    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            if (mapVector[y * mapWidth + x] == 0) { //ROAD
                Vec2<int> tilePos = { topLeft.x + x * tileSize, topLeft.y + y * tileSize };
                Tile& curTile = getTile(tilePos);
                curTile.setFlags(Tile::TileState::Road);
                curTile.setPosition(tilePos);
                curTile.setSize(tileSize, tileSize);
            }
            else if (mapVector[y * mapWidth + x] == 1) { //WALL
                Vec2<int> tilePos = { topLeft.x + x * tileSize, topLeft.y + y * tileSize };
                Tile& curTile = getTile(tilePos);
                curTile.setFlags(Tile::TileState::Wall);
                curTile.setPosition(tilePos);
                curTile.setSize(tileSize, tileSize);
            }
            else if (mapVector[y * mapWidth + x] == 2) {
                Vec2<int> tilePos = { topLeft.x + x * tileSize, topLeft.y + y * tileSize };
                Tile& curTile = getTile(tilePos);
                curTile.setFlags(Tile::TileState::Road);
                curTile.setPosition(tilePos);
                curTile.setSize(tileSize, tileSize);
                SDL_Rect colRect = { 8, 8, 8, 8 };
                listOfCoin.emplace_back(curTile.getCenter(), coinAnim, colRect);
            }
            else if (mapVector[y * mapWidth + x] == 5) {
                Vec2<int> tilePos = { topLeft.x + x * tileSize, topLeft.y + y * tileSize };
                Tile& curTile = getTile(tilePos);
                curTile.setFlags(Tile::TileState::Road);
                curTile.setPosition(tilePos);
                curTile.setSize(tileSize, tileSize);
                ghostSpawns[0] = curTile.getCenter();
            }
            else if (mapVector[y * mapWidth + x] == 6) {
                Vec2<int> tilePos = { topLeft.x + x * tileSize, topLeft.y + y * tileSize };
                Tile& curTile = getTile(tilePos);
                curTile.setFlags(Tile::TileState::Road);
                curTile.setPosition(tilePos);
                curTile.setSize(tileSize, tileSize);
                ghostSpawns[1] = curTile.getCenter();
            }
            else if (mapVector[y * mapWidth + x] == 7) {
                Vec2<int> tilePos = { topLeft.x + x * tileSize, topLeft.y + y * tileSize };
                Tile& curTile = getTile(tilePos);
                curTile.setFlags(Tile::TileState::Road);
                curTile.setPosition(tilePos);
                curTile.setSize(tileSize, tileSize);
                ghostSpawns[2] = curTile.getCenter();
            }
            else if (mapVector[y * mapWidth + x] == 8) {
                Vec2<int> tilePos = { topLeft.x + x * tileSize, topLeft.y + y * tileSize };
                Tile& curTile = getTile(tilePos);
                curTile.setFlags(Tile::TileState::Road);
                curTile.setPosition(tilePos);
                curTile.setSize(tileSize, tileSize);
                ghostSpawns[3] = curTile.getCenter();
            }
            else if (mapVector[y * mapWidth + x] == 9) {
                Vec2<int> tilePos = { topLeft.x + x * tileSize, topLeft.y + y * tileSize };
                Tile& curTile = getTile(tilePos);
                curTile.setFlags(Tile::TileState::Road);
                curTile.setPosition(tilePos);
                curTile.setSize(tileSize, tileSize);
                playerSpawn = curTile.getCenter();
            }
            // ADD OOTHER STUFF (COIN, ETC) LATER
        }
    }
}

void Map::draw(Renderer& renderer)
{
    for (int i = 0; i < mapWidth * mapHeight; i++) {
        tiles[i].draw(renderer);
    }
    for (Coin& coin : listOfCoin) {
        if (!coin.isEaten())
            coin.draw(renderer);
    }
}

int Map::getTileSize()
{
    return tileSize;
}

std::vector<Tile> Map::getNeibouringRoads(Vec2<int> pos)
{
    std::vector<Tile> result;

    if (getTopTile(pos).checkFlags(Tile::TileState::Road)) {
        result.push_back(getTopTile(pos));
    }
    if (getRightTile(pos).checkFlags(Tile::TileState::Road)) {
        result.push_back(getRightTile(pos));
    }
    if (getBottomTile(pos).checkFlags(Tile::TileState::Road)) {
        result.push_back(getBottomTile(pos));
    }
    if (getLeftTile(pos).checkFlags(Tile::TileState::Road)) {
        result.push_back(getLeftTile(pos));
    }

    return result;
}
