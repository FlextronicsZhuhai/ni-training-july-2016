#ifndef _GRID_HEADER_
#define _GRID_HEADER_

void _stdcall TileGrid_GetSize(int numTiles, int *xSize, int *ySize);
void _stdcall TileGrid_GetCoordinates(int tilePosition, int numTiles, int *x, int *y);
void _stdcall TileGrid_TilePanel(int panel, int tilePosition, int numTiles, Rect *tiledArea, int shrinkToFit);

#endif // _GRID_HEADER_
