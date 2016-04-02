#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <boost/algorithm/string.hpp>
#include "Darwin.h"

using namespace std;


Species::Species(string name) : name(name) {}
Species::Species() {}

void Species::addInstruction(string instruction) {
    instructions.push_back(instruction);
}

void Species::print_name(ostream& w) {
    w << name.at(0);
}

bool Species::equal(Species s){
    if (!(name.compare(s.name)))
        return true;
    return false;
}

string Species::curr_inst(int index) {
    return instructions[index];
}

void Species::remove() {
  (*this).name = "\0";
  (*this).instructions.clear();
}

void Creature::parse_inst(int inst_cnt, vector<vector<Creature>> &board, int row, int col) {
    string inst = species.curr_inst(inst_cnt);
    std::vector<std::string> temp_inst;
    boost::split(temp_inst, inst, boost::is_any_of(" "));
    // vector<string> temp_inst = boost::split(inst, ' ');

    string current_inst = temp_inst.front();
    int n_inst = atoi(temp_inst.back().c_str());

    if(!current_inst.compare("hop"))
        hop(board, row, col);
    else if (!current_inst.compare("left"))
        left();
    else if (!current_inst.compare("right"))
        right();
    else if (!current_inst.compare("infect"))
        infect(board, row, col);
    else if (!current_inst.compare("if_empty"))
        if_empty(n_inst, board, row, col);
    else if (!current_inst.compare("if_wall"))
        if_wall(n_inst, board, row, col);
    else if (!current_inst.compare("if_random"))
        if_random(n_inst, board, row, col);
    else if (!current_inst.compare("if_enemy"))
        if_enemy(n_inst, board, row, col);
    else if (!current_inst.compare("go"))
        go(n_inst, board, row, col);
}

bool Creature::is_empty(vector<vector<Creature>> &b, int r, int c) {
    if ((d == 0) && (--c >= 0) && (!b[r][--c].is_creature()))
        return true;
        
    else if ((d == 1) && (--r >= 0) && (!b[--r][c].is_creature()))
        return true;

    else if ((d == 2) && ((unsigned)++c < b[r].size()) && (!b[r][++c].is_creature()))
        return true;
        
    else if ((d == 3) && ((unsigned)++r < b.size()) && (!b[++r][c].is_creature()))
        return true;
    
    else
        return false;
}

void Creature::go(int n, vector<vector<Creature>> &b, int row, int col){
    cnt = n;
    parse_inst(cnt, b, row, col);
}

void Creature::hop(vector<vector<Creature>> &b, int row, int col){
    int r = row;
    int c = col;
    if(is_empty(b, r, c)) {
        if(d == 0){
            b[r][--c] = b[row][col];
            b[row][col].remove();
            
        }else if (d == 1){
            b[--r][c] = b[row][col];
            b[row][col].remove();

        }else if (d == 2){
            b[r][++c] = b[row][col];
            b[row][col].remove();
            
        }else if (d == 3){
            b[++r][c] = b[row][col];
            b[row][col].remove();
        }
    }
}


void Creature::left(){
    if(d)
        --d;
    else
        d = 3;
}

void Creature::right(){
    if(d == 3)
        d = 0;
    else
        ++d;
}

void Creature::infect(vector<vector<Creature>> &b, int r, int c){
    if(!is_empty(b, r, c)) {
        if(d == 0 && !(species.equal(b[r][--c].species))) {
            b[r][c].species = species;
            b[r][c].cnt = 0;
            
        }else if (d == 1 && !(species.equal(b[--r][c].species))) {
            b[r][c].species = species;
            b[r][c].cnt = 0;

        }else if (d == 2 && !(species.equal(b[r][++c].species))) {
            b[r][c].species = species;
            b[r][c].cnt = 0;
            
        }else if (d == 3 && !(species.equal(b[++r][c].species))) {
            b[r][c].species = species;
            b[r][c].cnt = 0;
        }
    }
}

void Creature::if_empty(int n, vector<vector<Creature>> &b, int r, int c){
    if(is_empty(b, r, c))
        go (n, b, r, c); 
    else
        go (++cnt, b, r, c);
}


void Creature::if_wall(int n, vector<vector<Creature>> &b, int row, int col){
  int r = row; 
  int c = col; 
    if(d == 0){
        if ( --c < 0)
            go (n, b, row, col); 
        
    }else if (d == 1){
        if ( --r < 0)
            go (n, b, row, col); 

    }else if (d == 2){
        if ( (unsigned)++c == b[r].size())
            go (n, b, row, col); 
        
    }else if (d == 3){
        if ( (unsigned)++r == b.size())
            go (n, b, row, col); 

    } else {
        go (++cnt, b, row, col);
    }

}

void Creature::if_random(int n, vector<vector<Creature>> &b, int r, int c){
    if(rand()%2)
        go(n, b, r, c);
    else
        go(++cnt, b, r, c);

}

void Creature::if_enemy(int n, vector<vector<Creature>> &b, int row, int col){
    int r = row;
    int c = col;
    if (!is_empty(b, row, col)) {
        if((d == 0) && (!species.equal(b[r][--c].species)))
            go (n, b, row, col);
        else if ((d == 1) && (!species.equal(b[--r][c].species)))
            go (n, b, row, col);

        else if ((d == 2) && (!species.equal(b[r][++c].species)))
            go (n, b, row, col);

        else if ((d == 3) && (!species.equal(b[++r][c].species)))
            go (n, b, row, col);
    } else {
        go (++cnt, b, row, col);
    }
}


Creature::Creature(Species s, Direction direction): species(s), d(direction), cnt(0) {}
Creature::Creature(): species(NULL), d(-1), cnt(0) {}
void Creature::execute_instr(vector<vector<Creature>> &board, int row, int col) {
    parse_inst(cnt, board, row, col);
    ++cnt;
}

void Creature::print_species(ostream& w) {
    species.print_name(w);
}

bool Creature::is_creature() {
    if((*this).d < 0)
      return false;
    return true;
}

void Creature::remove() {
  (*this).d = -1;
  (*this).cnt = 0;
  (*this).species.remove();
}

Darwin::Darwin(int row, int col) {
    board.resize(col, vector<Creature> (row));
}

void Darwin::addCreature(Creature creature, int r, int c) {
    board[r][c] = creature;
}

void Darwin::turn() {
    for(int r = 0; (unsigned)r < board.size(); ++r) {
        for(int c = 0; (unsigned)c < board[r].size(); ++c) {
            if(board[r][c].is_creature()) {
                Creature temp_creat = board[r][c];
                temp_creat.execute_instr(board, r, c);
                // board[temp[0]][temp[1]] = c;
                // board[r][c].remove();
            }
                
        }
    }
}

void Darwin::print(ostream& w) {
    for(int r = 0; (unsigned)r < board.size(); ++r) {
        w << r << " ";
        for(int c = 0; (unsigned)c < board[r].size(); ++c) {
            if(board[r][c].is_creature())
                board[r][c].print_species(w);
            else
                w << ".";
        }
        w << endl;
    }
}
