#pragma once

struct StarPoint {
    int redValue{ 0 };
    int greenValue{ 0 };
    int blueValue{ 0 };
    
    int x{ 0 };
    int y{ y };

    StarPoint(int red, int green, int blue, int xVal, int yVal) {
        redValue = red;
        greenValue = green;
        blueValue = blue;
        x = xVal;
        y = yVal;
    }
};