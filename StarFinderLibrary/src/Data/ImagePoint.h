#pragma once

struct ImagePoint {
    int redValue{0};
    int greenValue{0};
    int blueValue{0};
    int starSetNumber{-1};

    void setValue(int red, int green, int blue) {
        redValue = red;
        greenValue = green;
        blueValue = blue;
    }

    void upateSetNumber(int setNumber) {
        starSetNumber = setNumber;
    }
};
