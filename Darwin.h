#ifndef Darwin_h
#define Darwin_h

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

enum Direction { west, north, east, south };
enum Instruction { hop, lft, rit, infect, if_empty, if_wall, if_random, if_enemy, go};

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
        void remove();
        void print(); 
        vector<int> get_action(int& cnt);
    


};

class Creature {
    private:
        Species species;
        int d;
        int cnt;

        // void do_action(int action, vector<vector<Creature>> &b, int r, int c);
        // void do_control(int control, int n_inst, vector<vector<Creature>> &b, int r, int c); 
        void do_inst(vector<int> instruction, vector<vector<Creature>> &b, int r, int c);  
        bool is_empty(vector<vector<Creature>> &b, int r, int c);
        bool is_wall(vector<vector<Creature>> &b, int r, int c);
        void ex_go(int n, vector<vector<Creature>> &b, int r, int c);
        void ex_hop(vector<vector<Creature>> &b, int r, int c);
        void ex_left(vector<vector<Creature>> &b, int r, int c);
        void ex_right(vector<vector<Creature>> &b, int r, int c);
        void ex_infect(vector<vector<Creature>> &b, int r, int c);  
        void ex_if_empty(int n, vector<vector<Creature>> &b, int r, int c);
        void ex_if_wall(int n, vector<vector<Creature>> &b, int r, int c);
        void ex_if_random(int n, vector<vector<Creature>> &b, int r, int c);
        void ex_if_enemy(int n, vector<vector<Creature>> &b, int r, int c);

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
        void simulation(int times, ostream& w);
};

#endif // Darwin_h