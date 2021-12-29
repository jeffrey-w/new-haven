#pragma once

// Records statistics about a Player's VGMap and BuildingHand.
class ScoreBoard {

  public:
    // Constructs a new ScoreBoard object.
    ScoreBoard();
    // Constructs a new ScoreBoard in the same state as the sepcified ScoreBoard.
    ScoreBoard(const ScoreBoard&);
    // Returns the number of villagers recorded by this ScoreBoard.
    int getVillagers() const;
    // Returns the number of built Buildings recorded by this ScoreBoard.
    int getBuilt() const;
    // Returns the number of unbuilt Buildings recorded by this ScoreBoard.
    int getUnbuilt() const;
    // Sets the nubmer of villagers recorded by this ScoreBoard to that specified. Throws an exception if the
    // specified number is negative.
    void setVillagers(int);
    // Sets the nubmer of built Buildings recorded by this ScoreBoard to that specified. Throws an exception if the
    // specified number is negative.
    void setBuilt(int);
    // Sets the nubmer of unbuilt Buildings recorded by this ScoreBoard to that specified. Throws an exception if the
    // specified number is negative.
    void setUnbuilt(int);
    // Sets the number of villagers, built, and unbuilt Buildings recorded by this BuildingFacility to that specified.
    // Throws an exception if the specified numbers are negative.
    void setScores(int, int, int);

    bool operator<(const ScoreBoard&) const;
    bool operator==(const ScoreBoard&) const;

  private:
    int villagers;
    int built;
    int unbuilt;

    int validateScore(int);
};
