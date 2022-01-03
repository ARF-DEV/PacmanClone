#include "Map.h"

Tile& Map::getTile(Vec2<int> pos)
{
    return tiles[pos.getY() * mapWidth + pos.getX()];
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
                Tile& curTile = getTile({ x, y });
                curTile.setFlags(Tile::TileState::Road);
                curTile.setPosition({ x * tileWidth, y * tileHeight });
                curTile.setSize(tileWidth, tileHeight);
            }
        }
    }
}

void Map::loadMapFromVector(std::vector<int> mapVector, int _mapWidth, int _mapHeight)
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
                Tile& curTile = getTile({ x, y });
                curTile.setFlags(Tile::TileState::Road);
                curTile.setPosition({ x * tileWidth, y * tileHeight });
                curTile.setSize(tileWidth, tileHeight);
            }
            else if (mapVector[y * mapWidth + x] == 1) { //WALL
                Tile& curTile = getTile({ x, y });
                curTile.setFlags(Tile::TileState::Wall);
                curTile.setPosition({ x * tileWidth, y * tileHeight });
                curTile.setSize(tileWidth, tileHeight);
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
}
