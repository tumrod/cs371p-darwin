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
        if_random(n_inst);
    else if (!current_inst.compare("if_enemy"))
        if_enemy(n_inst, board, row, col);
    else if (!current_inst.compare("go"))
        go(n_inst);
}

bool Creature::is_empty(vector<vector<Creature>> &b, int r, int c) {
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

void Creature::go(int n){
    cnt = n;
    parse_inst(cnt, );
}

void Creature::hop(vector<vector<Creature>> &b, int r, int c){
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
            b[r][--c].species = species;
            b[r][--c].cnt = 0;
            
        }else if (d == 1 && !(species.equal(b[--r][c].species))) {
            b[--r][c].species = species;
            b[--r][c].cnt = 0;

        }else if (d == 2 && !(species.equal(b[r][++c].species))) {
            b[r][++c].species = species;
            b[r][++c].cnt = 0;
            
        }else if (d == 3 && !(species.equal(b[++r][c].species))) {
            b[++r][c].species = species;
            b[++r][c].cnt = 0;
        }
    }
}

void Creature::if_empty(int n, vector<vector<Creature>> &b, int r, int c){
    if(is_empty(b, r, c))
        go (n); 
    else
        go (++cnt);
}


void Creature::if_wall(int n, vector<vector<Creature>> &b, int r, int c){
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

void Creature::if_random(int n){
    if(rand()%2)
        go(n);
    else
        go(++cnt);

}

void Creature::if_enemy(int n, vector<vector<Creature>> &b, int r, int c){
    if (!is_empty(b, r, c)) {
        if((d == 0) && (!species.equal(b[r][--c].species)))
            go (n);
        else if ((d == 1) && (!species.equal(b[--r][c].species)))
            go (n);

        else if ((d == 2) && (!species.equal(b[r][++c].species)))
            go (n);

        else if ((d == 3) && (!species.equal(b[++r][c].species)))
            go (n);
    } else {
        go (++cnt);
    }
}


Creature::Creature(Species s, Direction direction): species(s), d(direction), cnt(0) {}
Creature::Creature(): cnt(0) {}
void Creature::execute_instr(vector<vector<Creature>> &board, int row, int col) {
    parse_inst(cnt, board, row, col);
    ++cnt;
}

void Creature::print_species(ostream& w) {
    species.print_name(w);
}

Darwin::Darwin(int row, int col) {
    board.resize(col, vector<Creature> (row));
}

void Darwin::addCreature(Creature creature, int r, int c) {
    board[r][c] = creature;
    creature_list.push_back(creature);
}

void Darwin::turn() {
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

void Darwin::print(ostream& w) {
    for(int r = 0; r < board.size(); ++r) {
        w << r << " ";
        for(int c = 0; c < r.size(); ++c) {
            if(board[r][c] != NULL)
                board[r][c].print_species(w);
            else
                w << ".";
        }
        w << endl;
    }
}
