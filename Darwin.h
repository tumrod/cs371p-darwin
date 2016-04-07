#ifndef Darwin_h
#define Darwin_h

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "gtest/gtest.h"

using namespace std;


enum Direction { west, north, east, south };
enum Instruction { hop, lft, rit, infect, if_empty, if_wall, if_random, if_enemy, go};

class Species {
    friend class SpeciesTest;
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
        void print(ostream& w); 
        vector<int> get_action(int& cnt);
};

class Creature {
    friend class CreatureTest;
    private:
        Species species;
        int d;
        int cnt;
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

        FRIEND_TEST(CreatureTest, do_inst_1);
        FRIEND_TEST(CreatureTest, do_inst_2);
        FRIEND_TEST(CreatureTest, do_inst_3);
        FRIEND_TEST(CreatureTest, is_empty_1);
        FRIEND_TEST(CreatureTest, is_empty_2);
        FRIEND_TEST(CreatureTest, is_empty_3);
        FRIEND_TEST(CreatureTest, is_wall_1);
        FRIEND_TEST(CreatureTest, is_wall_2);
        FRIEND_TEST(CreatureTest, is_wall_3);
        FRIEND_TEST(CreatureTest, ex_go_1);
        FRIEND_TEST(CreatureTest, ex_go_2);   
        FRIEND_TEST(CreatureTest, ex_go_3);   
        FRIEND_TEST(CreatureTest, ex_hop_1);
        FRIEND_TEST(CreatureTest, ex_hop_2);
        FRIEND_TEST(CreatureTest, ex_hop_3);
        FRIEND_TEST(CreatureTest, ex_left_1);
        FRIEND_TEST(CreatureTest, ex_left_2);
        FRIEND_TEST(CreatureTest, ex_left_3);
        FRIEND_TEST(CreatureTest, ex_right_1);
        FRIEND_TEST(CreatureTest, ex_right_2);
        FRIEND_TEST(CreatureTest, ex_right_3);
        FRIEND_TEST(CreatureTest, ex_infect_1);
        FRIEND_TEST(CreatureTest, ex_infect_2);
        FRIEND_TEST(CreatureTest, ex_infect_3);
        FRIEND_TEST(CreatureTest, ex_if_empty_1);
        FRIEND_TEST(CreatureTest, ex_if_empty_2);
        FRIEND_TEST(CreatureTest, ex_if_empty_3);
        FRIEND_TEST(CreatureTest, ex_if_wall_1);
        FRIEND_TEST(CreatureTest, ex_if_wall_2);
        FRIEND_TEST(CreatureTest, ex_if_wall_3);
        FRIEND_TEST(CreatureTest, ex_if_random_1);
        FRIEND_TEST(CreatureTest, ex_if_random_2);
        FRIEND_TEST(CreatureTest, ex_if_random_3);
        FRIEND_TEST(CreatureTest, ex_if_enemy_1);
        FRIEND_TEST(CreatureTest, ex_if_enemy_2);
        FRIEND_TEST(CreatureTest, ex_if_enemy_3);

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
        Creature at(int r, int c);
        vector<vector<Creature>>::iterator begin();
        vector<vector<Creature>>::iterator end();
        void simulation(int times, ostream& w);
};

#endif // Darwin_h