#ifndef Darwin_h
#define Darwin_h
enum Direction { west, north, east, south };

class Species {
    private:
        vector<string> instructions;
        string name;

    public:
        Species(string name);
        void addInstruction(string instruction);
        void print_name(ostream& w);
        bool equal(Species s);
        string curr_inst(int index);
};

class Creature {
    private:
        Species species;
        int d;
        int cnt;

        void parse_inst(cnt);
        bool is_empty(vector<vector<Creature>> &b, int r, int c);
        void go(int n);

        void hop(vector<vector<Creature>> &b, int r, int c);
        void left();
        void right();
        void infect(vector<vector<Creature>> &b, int r, int c);
        void if_empty(int n, vector<vector<Creature>> &b, int r, int c);
        void if_wall(int n, vector<vector<Creature>> &b, int r, int c);
        void if_random(int n);
        void if_enemy(int n, vector<vector<Creature>> &b, int r, int c);

    public:
        Creature(Species s, Direction direction);
        void execute_instr(vector<vector<Creature>> &board, int row, int col);
        void print_species(ostream& w);
};

class Darwin {
    private:
        int row;
        int column;
        vector< vector<Creature>> board;
    public:
        Darwin(int row, int col);
        void addCreature(Creature c, int r, int c);
        void turn();
        void print(ostream& w);
};

#endif // Darwin_h