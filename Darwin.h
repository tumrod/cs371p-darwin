#ifndef Darwin_h
#define Darwin_h

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

enum Direction { west, north, east, south };
enum Action { hop, lft, rit, infect};
enum Control { empty, wall, ran, enemy, go};

class Species {
    private:
        vector<string> instructions;
        string name;

        
    public:
        Species(string name);
        Species();
        void addInstruction(string instruction);
        void print_name(ostream& w);
        bool equal(Species s);
        string curr_inst(int index);
        void remove();
        void print(); 
        int instruction_size(); 
        vector<int> get_action(int& cnt);
    


};

class Creature {
    private:
        Species species;
        int d;
        int cnt;

        void do_action(int action, vector<vector<Creature>> &b, int r, int c);
        void do_control(int control, int n_inst, vector<vector<Creature>> &b, int r, int c); 
        void parse_inst(vector<vector<Creature>> &b, int r, int c);
        void do_inst(vector<int> instruction, vector<vector<Creature>> &b, int r, int c);  
        bool is_empty(vector<vector<Creature>> &b, int r, int c);
        void go(int n, vector<vector<Creature>> &b, int r, int c);
        void hop(vector<vector<Creature>> &b, int r, int c);
        void left(vector<vector<Creature>> &b, int r, int c);
        void right(vector<vector<Creature>> &b, int r, int c);
        void infect(vector<vector<Creature>> &b, int r, int c);  
        void if_empty(int n, vector<vector<Creature>> &b, int r, int c);
        void if_wall(int n, vector<vector<Creature>> &b, int r, int c);
        void if_random(int n, vector<vector<Creature>> &b, int r, int c);
        void if_enemy(int n, vector<vector<Creature>> &b, int r, int c);

    public:
        Creature(Species s, Direction direction);
        Creature();
        void execute_instr(vector<vector<Creature>> &board, int row, int col);
        void print_species(ostream& w);
        bool is_creature();
        void remove();
        void print();
};

class Darwin {
    private:
        int row;
        int column;
        vector< vector<Creature>> board;
    public:
        Darwin(int row, int col);
        void addCreature(Creature& creature, int r, int c);
        void turn();
        void print(ostream& w);
};

#endif // Darwin_h