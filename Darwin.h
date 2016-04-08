#ifndef Darwin_h
#define Darwin_h

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "gtest/gtest.h"

using namespace std;


/*Declaring the enums for direction and instructions*/
enum Direction { west, north, east, south };
enum Instruction { hop, lft, rit, infect, if_empty, if_wall, if_random, if_enemy, go};

/*Declaring Species class which contains the name and instructions for a species*/
class Species {
    friend class SpeciesTest;
    private:
        // holds the name and instructions for species 
        vector<string> instructions;
        string name;
        
    public:
        // -----------
        // Constructor
        // -----------

        /**
         * @param       String name and default 
         */
        Species(string name);
        Species();
        
        // --------------
        // addInstruction
        // --------------

        /**
         * @param       String instruction  
         */ 
        void addInstruction(string instruction);
        // ----------
        // print_name
        // ----------

        /**
         * @param       output stream  
         */ 
        void print_name(ostream& w);

        // ----------
        // operator==
        // ----------

        /**
         * @param      const Species
         * @return       bool   
         */ 
        bool operator==(const Species& s) const;
         // ----------
        // operator!=
        // ----------

        /**
         * @param      const Species
         * @return     bool  
         */ 
        bool operator!=(const Species& s) const;
        // ------
        // remove
        // ------

        /**
         * removes the specie  
         */ 
        void remove();
        // ------
        // print
        // ------

        /**
         * @param      output stream 
         */ 
        void print(ostream& w); 

        // ----------
        // get_action
        // ----------

        /**
         * @param      int& cnt 
         * @return     vector<int>  
         */
        vector<int> get_action(int& cnt);
};

/*Declaring Creature class with its private-public fields and methods*/
class Creature {
    friend class CreatureTest;
    private:
        Species species;
        int d;
        int cnt;
        // ------
        // do_inst
        // -------

        /**
         * @param      vector<int> instruction and  vector<vector<Creature>> &b, int row, int col  
         */
        void do_inst(vector<int> instruction, vector<vector<Creature>> &b, int r, int c); 

        // ----------
        // is_empty
        // ----------

        /**
         * @param      vector<vector<Creature>> &b, int row , int col 
         * @return     bool 
         */ 
        bool is_empty(vector<vector<Creature>> &b, int r, int c);
        // ----------
        // is_wall
        // ----------

        /**
         * @param      takes in board row and col 
         * @return     bool  
         */
        bool is_wall(vector<vector<Creature>> &b, int r, int c);
        // -----
        // ex_go
        // -----

        /**
         * @param      int n, vector<vector<Creature>> &b, int r, int c 
         */
        void ex_go(int n, vector<vector<Creature>> &b, int r, int c);
        
        // -----
        // ex_hop
        // -----

        /**
         * @param      vector<vector<Creature>> &b, int r, int c 
         */
        void ex_hop(vector<vector<Creature>> &b, int r, int c);
        
        // -------
        // ex_left
        // -------

        /**
         * @param      vector<vector<Creature>> &b, int r, int c
         */
        void ex_left(vector<vector<Creature>> &b, int r, int c);

        // -------
        // ex_right
        // -------

        /**
         * @param      vector<vector<Creature>> &b, int r, int c
         */        
        void ex_right(vector<vector<Creature>> &b, int r, int c);
        // -------
        // ex_infect
        // -------

        /**
         * @param      vector<vector<Creature>> &b, int r, int c
         */        
        void ex_infect(vector<vector<Creature>> &b, int r, int c);  

        // -------
        // ex_if_empty
        // -------

        /**
         * @param      int n, vector<vector<Creature>> &b, int r, int c
         */     
        void ex_if_empty(int n, vector<vector<Creature>> &b, int r, int c);

        // -----------
        // ex_if_wall
        // -----------

        /**
         * @param      int n, vector<vector<Creature>> &b, int r, int c
         */     
        void ex_if_wall(int n, vector<vector<Creature>> &b, int r, int c);

        // ------------
        // ex_if_random
        // ------------

        /**
         * @param      int n, vector<vector<Creature>> &b, int r, int c
         */     
        void ex_if_random(int n, vector<vector<Creature>> &b, int r, int c);

        // ------------
        // ex_if_enemy
        // ------------

        /**
         * @param      int n, vector<vector<Creature>> &b, int r, int c
         */     
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
        FRIEND_TEST(CreatureTest, creature_1);
        FRIEND_TEST(CreatureTest, creature_2);
        FRIEND_TEST(CreatureTest, creature_3);
    public:

        // -----------
        // Constructor
        // -----------

        /**
         * @param       Species s, int direction 
         */
        Creature(Species s, int direction);
        Creature();

        // ------------
        // execute_instr
        // ------------

        /**
         * @param      vector<vector<Creature>> &board, int row, int col
         */  
        void execute_instr(vector<vector<Creature>> &board, int row, int col);

        // ------------
        // print_species
        // ------------

        /**
         * @param      ostream& w
         */  
        void print_species(ostream& w);

        // ------------
        // is_creature
        // ------------

        /**
         * @return bool
         */          
        bool is_creature();

        // ------
        // remove
        // ------

        /**
         * remove creature from the board
         */          
        void remove();

        // ----------
        // operator==
        // ----------
        /**
         * @param const Creature
         * @return bool
         */  
        bool operator==(const Creature& rhs) const;
};

/*Declaring Darwin class with its private-public fields and methods*/
class Darwin {
    private:
        int row;
        int column;
        vector< vector<Creature>> board;
        FRIEND_TEST(DarwinTest, darwin_1);
        FRIEND_TEST(DarwinTest, darwin_2);
        FRIEND_TEST(DarwinTest, darwin_3);
    public:

        // -----------
        // Constructor
        // -----------

        /**
         * @param       int row, int col
         */
        Darwin(int row, int col);
        // ------------
        // addCreature
        // ------------

        /**
         * @param      Creature& creature, int r, int c
         */  
        void addCreature(Creature& creature, int r, int c);

        // ----
        // turn
        // ----

        /**
         * execute the turn
         */  
        void turn();

        // -----
        // print
        // -----

        /**
         * @param      ostream& w
         */          
        void print(ostream& w);

        // --
        // at
        // --

        /**
         * @param       int r, int 
         * @return      const Creature
         */          
        const Creature at(int r, int c) const;

        // --
        // at
        // --

        /**
         * @param       int r, int 
         * @return      Creature
         */          
        Creature at(int r, int c);

        // -----
        // begin
        // -----

        /**
         * @return     const vector<vector<Creature>>::iterator
         */          
        const vector<vector<Creature>>::iterator begin() const;

        // -----
        // begin
        // -----

        /**
         * @return     vector<vector<Creature>>::iterator
         */               
        vector<vector<Creature>>::iterator begin();
        // ---
        // end
        // ---

        /**
         * @return     const vector<vector<Creature>>::iterator
         */                 
        const vector<vector<Creature>>::iterator end() const;
        // ---
        // end
        // ---

        /**
         * @return     vector<vector<Creature>>::iterator
         */                 
        vector<vector<Creature>>::iterator end();
        
        // ------------
        // simulation
        // ------------

        /**
         * @param      int times, ostream& w, int start = 0, int end = 0, int step = 1
         */          
        void simulation(int times, ostream& w, int start = 0, int end = 0, int step = 1);
};

#endif // Darwin_h