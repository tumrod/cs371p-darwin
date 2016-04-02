
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "Darwin.h"

using namespace std;

enum Direction { west, north, east, south };

class Species {
    private:
        vector<string> instructions;
        string name;

    public:
        Species(string name) : name(name) {}

        void addInstruction(string instruction) {
            instructions.push_back(instruction);
        }

        void print_name(ostream& w) {
            w << name.at(0);
        }

        bool equal(Species s){
            return strcmp(name, s.name);
        }

        string curr_inst(int index) {
            return instructions[index];
        }

};

class Creature {
    private:
        Species species;
        int d;
        int cnt;

        void parse_inst(cnt) {
            string inst = species.curr_inst[cnt];
            vector<string> temp_inst = split(inst, ' ');

            string current_inst = temp_inst.front();
            int n_inst = atoi(temp_inst.back().c_str());

            if(strcmp(current_inst, "hop"))
                hop(board, row, col);
            else if (strcmp(current_inst, "left"))
                left();
            else if (strcmp(current_inst, "right"))
                right();
            else if (strcmp(current_inst, "infect"))
                infect(board, row, col);
            else if (strcmp(current_inst, "if_empty"))
                if_empty(n_inst, board, row, col);
            else if (strcmp(current_inst, "if_wall"))
                if_wall(n_inst, board, row, col);
            else if (strcmp(current_inst, "if_random"))
                if_random(n_inst);
            else if (strcmp(current_inst, "if_enemy"))
                if_enemy(n_inst, board, row, col);
            else if (strcmp(current_inst, "go"))
                go(n_inst);
        }

        bool is_empty(vector<vector<Creature>> &b, int r, int c) {
            if ((d == 0) && (--c >= 0) && (b[r][--c] == NULL))
                return true;
                
            else if ((d == 1) && (--r >= 0) && (b[--r][c] == NULL))
                return true;

            else if ((d == 2) && (++c < b[r].size()) && (b[r][++c] == NULL))
                return true;
                
            else if ((d == 3) && (++r < b.size()) && (b[++r][c] == NULL))
                return true;
            
            else
                return false;
        }
        
        void go(int n){
            cnt = n;
            parse_inst(cnt);
        }

        void hop(vector<vector<Creature>> &b, int r, int c){
            if(is_empty(b, r, c)) {
                if(d == 0){
                    b[r][--c] = b[r][c];
                    b[r][c] = NULL;
                    
                }else if (d == 1){
                    b[--r][c] = b[r][c];
                    b[r][c] = NULL;

                }else if (d == 2){
                    b[r][++c] = b[r][c];
                    b[r][c] = NULL;
                    
                }else if (d == 3){
                    b[++r][c] = b[r][c];
                    b[r][c] = NULL;
                }
            }
        }


        void left(){
            if(d)
                --d;
            else
                d = 3;
        }

        void right(){
            if(d == 3)
                d = 0;
            else
                ++d;
        }

        void infect(vector<vector<Creature>> &b, int r, int c){
            if(!is_empty(b, r, c)) {
                if(d == 0 && !(species.equal(b[r][--c].species)) {
                    b[r][--c].species = species;
                    b[r][--c].cnt = 0;
                    
                }else if (d == 1 && !(species.equal(b[--r][c].species)){
                    b[--r][c].species = species;
                    b[--r][c].cnt = 0;

                }else if (d == 2 && !(species.equal(b[r][++c].species)){
                    b[r][++c].species = species;
                    b[r][++c].cnt = 0;
                    
                }else if (d == 3 && !(species.equal(b[++r][c].species)){
                    b[++r][c].species = species;
                    b[++r][c].cnt = 0;
                }
            }
        }

        void if_empty(int n, vector<vector<Creature>> &b, int r, int c){
            if(is_empty(b, r, c))
                go (n); 
            else
                go (++cnt);
        }


        void if_wall(int n, vector<vector<Creature>> &b, int r, int c){
            if(d == 0){
                if ( --c < 0)
                    go (n); 
                
            }else if (d == 1){
                if ( --r < 0)
                    go (n); 

            }else if (d == 2){
                if ( ++c == b[r].size())
                    go (n); 
                
            }else if (d == 3){
                if ( ++r == b.size())
                    go (n); 

            } else {
                go (++cnt);
            }

        }

        void if_random(int n){
            if(rand()%2)
                go(n);
            else
                go(++cnt);

        }

        void if_enemy(int n, vector<vector<Creature>> &b, int r, int c){
            if (!is_empty(b, r, c)) {
                if(d == 0) && !(species.equal(b[r][--c].species))
                    go (n);
                else if (d == 1) && !(species.equal(b[--r][c].species))
                    go (n);

                else if (d == 2) && !(species.equal(b[r][++c].species))
                    go (n);

                else if (d == 3) && !(species.equal(b[++r][c].species))
                    go (n);
            } else {
                go (++cnt);
            }
        }

    public:
        Creature(Species s, Direction direction): species(s), d(direction), cnt(0) {}

        void execute_instr(vector<vector<Creature>> &board, int row, int col) {
            parse_inst(cnt);
            ++cnt;
        }

        void print_species(ostream& w) {
            species.print_name(w);
        }

};

class Darwin {
    private:
        int row;
        int column;
        vector<Creature> creature_list;
        vector< vector<Creature>> board;
    public:
        Darwin(int row, int col) {
            board.resize(col, vector<Creature> (row));
        }

        void addCreature(Creature c, int r, int c) {
            board[r][c] = c;
            creature_list.push_back(c);

        }

        void turn() {
            for(int r = 0; r < board.size(); ++r) {
                for(int c = 0; c < r.size(); ++c) {
                    if(board[r][c] != NULL) {
                        Creature temp_creat = board[r][c];
                        int* temp = temp_creat.execute_instr(board, r, c);
                        board[temp[0]][temp[1]] = c;
                        board[r][c] = NULL;
                    }
                        
                }
            }
        }

        void print(ostream& w) {
            for(int r = 0; r < board.size(); ++r) {
                w << r << " ";
                for(int c = 0; c < r.size(); ++c) {
                    if(board[r][c] != NULL)
                        w << board[r][c].print_species(w);
                    else
                        w << ".";
                }
                w << endl;
            }
        }
};