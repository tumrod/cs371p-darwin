#ifndef Darwin_h
#define Darwin_h
enum Direction { west, north, east, south };

class Species {
    private:
        vector<string> instructions;
        string name;
    public:
        Species(string name);
        addInstruction(string s);
};

class Creature {
    
    private:
        Species species;
        int direction;
        int program_cnt;
    public:
        Creature(Species s, Direction d);
};

class Darwin {
    private:
        int row;
        int column;
        int num_of_creatures = 0;
    public:
        Darwin(int row, int col);
        addCreature(Creature c, int r, int c);

};

#endif // Darwin_h