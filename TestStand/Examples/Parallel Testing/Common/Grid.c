#include <ansi_c.h>
#include <cvirte.h>     /* needed if linking executable in external compiler; harmless otherwise */
#include <userint.h>
#include "tsutil.h"
#include "grid.h"


///////////////////////////////////////////////////////////////

    // returns the size of a grid that can hold the specified number of tiles
void _export _stdcall TileGrid_GetSize(int numTiles, int *xSize, int *ySize)
    {
    *xSize = 1;
    *ySize = 1;
    
    while (*xSize * *ySize < numTiles)
        {
        if (*xSize <= *ySize)
            ++(*xSize);
        else
            ++(*ySize);
        }
    }
    
///////////////////////////////////////////////////////////////

    // returns the coordinates of a specified tile position in the grid
void _export _stdcall TileGrid_GetCoordinates(int tilePosition, int numTiles, int *x, int *y)
    {
    int xSize, ySize;
    
    TileGrid_GetSize(numTiles, &xSize, &ySize);
    
    *y = tilePosition / xSize;
    *x = tilePosition % xSize;
    }
    
/////////////////////////////////////////////

    // tile a panel
void _export _stdcall TileGrid_TilePanel(int panel, int position, int numberOfPositions, Rect *tiledArea, int shrinkToFit)
    {
    int     x, y;                               // grid coordinates
    int     xSize, ySize;                       // size of grid in number of panels in each direction
    int     panelHeight, panelWidth;            // in pixels
    int     frameHeight, frameWidth;            // in pixels
    double  gridHeight, gridWidth;              // in pixels
    int     top, left;                          // in pixels
    double  xScaleFactor = 1.0, yScaleFactor = 1.0; // in case we have to shrink the panels to make them fit on the screen
    int     titleBarHeight = 18;
    int     frameThickness = 4;
    int     panelFrameHeight = 2 * frameThickness + titleBarHeight;
    int     panelFrameWidth = 2 * frameThickness;
    
    TileGrid_GetSize(numberOfPositions, &xSize, &ySize);             // get the grid size
    TileGrid_GetCoordinates(position, numberOfPositions, &x, &y);    // get grid coordinate for this position index
    
    GetPanelAttribute(panel, ATTR_WIDTH, &panelWidth);              // get size of panel client area
    GetPanelAttribute(panel, ATTR_HEIGHT, &panelHeight);
    
    frameHeight = panelHeight + panelFrameHeight;                   // get size of entire panel
    frameWidth = panelWidth + panelFrameWidth;
    
    gridHeight = frameHeight * ySize;                               // get size of entire grid
    gridWidth = frameWidth * xSize;
    
    if (shrinkToFit)                        // if the grid is larger than the screen, we can shrink it
        {
        if (gridHeight > tiledArea->height)
            {
            int yPixelsNeeded = gridHeight - tiledArea->height;
            int scalableYPixels = panelHeight * ySize;  // can't shrink window frame thickness
            
            yScaleFactor = (double)(scalableYPixels - yPixelsNeeded) / scalableYPixels;
            }
    
        if (gridWidth > tiledArea->width)
            {
            int xPixelsNeeded = gridWidth - tiledArea->width;
            int scalableXPixels = panelWidth * xSize;   // can't shrink window frame thickness
            xScaleFactor = (double)(scalableXPixels - xPixelsNeeded) / scalableXPixels;
            }
    
        panelHeight *= yScaleFactor;    // shrink the panel client area just enough to fit all panels on the screen
        panelWidth *= xScaleFactor;
        }

    top = y * (panelHeight + panelFrameHeight) + tiledArea->top;
    left = x * (panelWidth + panelFrameWidth) + tiledArea->left;
    
    top += titleBarHeight + frameThickness; // start the frame at (0,0), not the origin of the client area
    left += frameThickness;
            
    SetPanelAttribute(panel, ATTR_LEFT, left);
    SetPanelAttribute(panel, ATTR_TOP, top);
    SetPanelAttribute(panel, ATTR_WIDTH, panelWidth);
    SetPanelAttribute(panel, ATTR_HEIGHT, panelHeight);
    }
