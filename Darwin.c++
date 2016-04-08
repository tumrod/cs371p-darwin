#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <boost/algorithm/string.hpp>
#include "Darwin.h"
#include "gtest/gtest.h"
using namespace std;


Species::Species(string name) : name(name) {}
Species::Species() {}

void Species::addInstruction(string instruction) {
    instructions.push_back(instruction);
}

void Species::print_name(ostream& w) {
    if (name.size() > 0)
        w << name.at(0);
    else 
        w << name; 
}

bool Species::operator==(const Species& s) const{
    if ((name.compare(s.name)))
        return false;

    for (int i = 0; (unsigned) i < instructions.size(); ++i) {
        if(instructions[i].compare(s.instructions[i]))
            return false;
    }

    return true;
}

bool Species::operator!=(const Species& s) const{
    return !((*this) == s);
}

void Species::remove() {
  (*this).name = "\0";
  (*this).instructions.clear();
}

void Species::print(ostream& w) {
  w << "name: " << name << endl; 
  for (int i = 0; (unsigned)i < instructions.size(); ++i){
    w << "instruction " << i << " : " << instructions[i] << endl; 
  }
  if (instructions.size() == 0)
    w << "no instructions" << endl; 
}

vector<int> Species::get_action(int &cnt){
    cnt = cnt % instructions.size();  
    string inst = instructions[cnt];

    std::vector<std::string> temp_inst;
    boost::split(temp_inst, inst, boost::is_any_of(" "));

    int n_inst = -1 ;
    string current_inst = temp_inst.front();
    if (temp_inst.size() > 1)
        n_inst = atoi(temp_inst.back().c_str());

    vector<int> act_inst; 

    if(!current_inst.compare("hop"))
        act_inst.push_back(hop); 
    else if (!current_inst.compare("left"))
        act_inst.push_back(lft);  
    else if (!current_inst.compare("right"))
        act_inst.push_back(rit);
    else if (!current_inst.compare("infect"))
        act_inst.push_back(infect);
    else if (!current_inst.compare("if_empty")){
        act_inst.push_back(if_empty);
        act_inst.push_back(n_inst);
    }   
    else if (!current_inst.compare("if_wall")){
        act_inst.push_back(if_wall);
        act_inst.push_back(n_inst);
    }
    else if (!current_inst.compare("if_random")){
        act_inst.push_back(if_random);
        act_inst.push_back(n_inst);
    }
    else if (!current_inst.compare("if_enemy")){
        act_inst.push_back(if_enemy);
        act_inst.push_back(n_inst);
    }
    else if(!current_inst.compare("go")){
        act_inst.push_back(go);
        act_inst.push_back(n_inst);
    }

    return act_inst;  


}

void Creature::do_inst(vector<int> instruction, vector<vector<Creature>> &b, int r, int c){
    int inst = instruction[0]; 
    int n_inst; 
    if ( instruction.size() > 1)
        n_inst = instruction[1];
    switch(inst){
        case hop:
            ex_hop(b, r, c);
            break;  
        case lft:
            ex_left(b, r, c);
            break;
        case rit:
            ex_right(b,r, c);
            break;
        case infect:
            ex_infect(b, r, c);
            break;
        case if_empty:
            ex_if_empty(n_inst, b, r, c);
            break;
        case if_wall:
            ex_if_wall(n_inst, b, r, c);
            break;
        case if_random:
            ex_if_random(n_inst, b, r, c);
            break;
        case if_enemy:
            ex_if_enemy(n_inst, b, r, c);
            break;
        case go:
            ex_go(n_inst, b, r, c);
            break;
    }
} 

bool Creature::is_empty(vector<vector<Creature>> &b, int r, int c) {
    bool wall = is_wall(b, r, c); 
    if ((d == 0) && !wall && (!b[r][(c-1)].is_creature()))
        return true;
        
    else if ((d == 1) && !wall && (!b[(r-1)][c].is_creature()))
        return true;

    else if ((d == 2) && !wall && (!b[r][(c+1)].is_creature()))
        return true;
        
    else if ((d == 3) && !wall && (!b[(r+1)][c].is_creature())) {
        return true;
    }
    else{
        return false;
    }
        
}

bool Creature::is_wall(vector<vector<Creature>> &b, int r, int c) {
    if ((d == 0) && ((c-1) < 0))
        return true;
        
    else if ((d == 1) && ((r-1) < 0))
        return true;

    else if ((d == 2) && ((unsigned)(c+1) >= b[0].size()) )
        return true;
        
    else if ((d == 3) && ((unsigned)(r+1) >= b.size()))
        return true;
    else
        return false;
}

void Creature::ex_go(int n, vector<vector<Creature>> &b, int row, int col){
    cnt = n;
    vector<int> instruction = species.get_action(cnt); 
    do_inst(instruction, b, row, col); 
}

void Creature::ex_hop(vector<vector<Creature>> &b, int row, int col){
    int r = row;
    int c = col;
    ++cnt; 
    if(is_empty(b, r, c)) {
        if(d == 0){
            b[r][--c] = (*this);
            b[row][col].remove();
            
        }else if (d == 1){
            b[--r][c] = (*this);
            b[row][col].remove();
        }else if (d == 2){
            b[r][++c] = (*this);
            b[row][col].remove();
        }else if (d == 3){
            b[++r][c] = (*this);
            b[row][col].remove();
        }

    }else {
        b[row][col]  = (*this); // because it changes the program counter 
    }
}


void Creature::ex_left(vector<vector<Creature>> &b, int row, int col){
    ++cnt; 
    if(d)
        --d;
    else
        d = 3;

    b[row][col] = (*this); 
}

void Creature::ex_right(vector<vector<Creature>> &b, int row, int col){
    ++cnt; 
    if(d == 3)
        d = 0;
    else
        ++d;
    b[row][col] = (*this); 

}

void Creature::ex_infect(vector<vector<Creature>> &b, int row, int col){
    int r = row;
    int c = col; 
    ++cnt;

    if(!is_empty(b, r, c)) {
        if(d == 0 && (species != b[r][--c].species)) {
            b[r][c].species = species;
            b[r][c].cnt = 0;
            
        }else if (d == 1 && (species != b[--r][c].species)) {
            b[r][c].species = species;
            b[r][c].cnt = 0;

        }else if (d == 2 && (species != b[r][++c].species)) {
            b[r][c].species = species;
            b[r][c].cnt = 0;
            
        }else if (d == 3 && (species != b[++r][c].species)) {
            b[r][c].species = species;
            b[r][c].cnt = 0;
        }
        
    }
    b[row][col] = (*this); 
    
}

void Creature::ex_if_empty(int n, vector<vector<Creature>> &b, int r, int c){
    if(is_empty(b, r, c))
        ex_go (n, b, r, c); 
    else
        ex_go (++cnt, b, r, c);
}


void Creature::ex_if_wall(int n, vector<vector<Creature>> &b, int row, int col){
    bool wall = is_wall(b, row, col);
    if(wall)
        ex_go (n, b, row, col);
    else
        ex_go (++cnt, b, row, col);
}

void Creature::ex_if_random(int n, vector<vector<Creature>> &b, int r, int c){
    int ran1 = rand()%2;
    if(ran1) 
        ex_go(n, b, r, c);
    else
        ex_go(++cnt, b, r, c);

}

void Creature::ex_if_enemy(int n, vector<vector<Creature>> &b, int row, int col){
    int r = row;
    int c = col;
    if (!is_empty(b, row, col) && !is_wall(b, row, col)) {
        if((d == 0) && (species != (b[r][--c].species)))
            ex_go (n, b, row, col);
        else if ((d == 1) && (species != (b[--r][c].species)))
            ex_go (n, b, row, col);

        else if ((d == 2) && (species != (b[r][++c].species)))
            ex_go (n, b, row, col);

        else if ((d == 3) && (species != (b[++r][c].species)))
            ex_go (n, b, row, col);
    } else {
        ex_go (++cnt, b, row, col);
    }
}


Creature::Creature(Species s, int direction): species(s), d(direction), cnt(0) {}
Creature::Creature(): d(-1), cnt(0) {}

void Creature::execute_instr(vector<vector<Creature>> &board, int row, int col) {
    vector<int> instruction = species.get_action(cnt);
    do_inst(instruction, board, row, col); 
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

bool Creature::operator==(const Creature& rhs) const {
    if(cnt != rhs.cnt || d != rhs.d || species != rhs.species)
        return false;
    return true;
}

Darwin::Darwin(int row, int col) {
    board.resize(row, vector<Creature> (col, Creature()));
}

void Darwin::addCreature(Creature &creature, int r, int c) {
    if (r < 0 || (unsigned)r >= board.size() || c < 0 || (unsigned)c >= board[0].size())
        throw out_of_range("Out of Range");

    if (board[r][c].is_creature())
        throw std::invalid_argument("Creature already exists"); 

    board[r][c] = creature;
}

void Darwin::turn() {
    vector<vector<Creature>> temp_board;
    temp_board = board;

    for(int r = 0; (unsigned)r < board.size(); ++r) {
        for(int c = 0; (unsigned)c < board[0].size(); ++c) {
            if(board[r][c].is_creature())
                board[r][c].execute_instr(temp_board, r, c);
        }
    }
    board = temp_board;

}

vector<vector<Creature>>::iterator Darwin::begin() {
    return board.begin();
}

const vector<vector<Creature>>::iterator Darwin::begin() const {
    return const_cast<Darwin*>(this)->begin();
}

vector<vector<Creature>>::iterator Darwin::end() {
    return board.end();
}

const vector<vector<Creature>>::iterator Darwin::end() const{
    return const_cast<Darwin*>(this)->end();
}

Creature Darwin::at(int r, int c) {
    if (r < 0 || (unsigned)r >= board.size() || c < 0 || (unsigned)c >= board[0].size())
        throw out_of_range("Out of Range");
    return board[r][c]; 
}

const Creature Darwin::at(int r, int c) const {
    if (r < 0 || (unsigned)r >= board.size() || c < 0 || (unsigned)c >= board[0].size())
        throw out_of_range("Out of Range");
    return board[r][c]; 
}

void Darwin::print(ostream& w) {
    vector<vector<Creature>>::iterator row;
    vector<Creature>::iterator col;

    w << "  "; 
    for(int col = 0; (unsigned)col < board[0].size(); ++col)
        w << col%10;
    w << endl;
    int r = 0;

    for(row = (*this).begin(); row != (*this).end(); ++row) {
        w << r%10 << " ";
        for(col = (*row).begin(); col != (*row).end(); ++col) {
            if((*col).is_creature())
                (*col).print_species(w);
            else
                w << ".";
        }
        w << endl; 
        ++r;
    }
}

void Darwin::simulation(int times, ostream& w, int start, int end, int step) {
    assert(times > 0);
    w << "Turn = 0." << endl;;
    (*this).print(w);
    w << endl;
    bool st = false; 
    if ( start != 0)
        st = true; 

    if ( start == 0 && end == 0) {
        end = times;
        start = 1;        
    }

    for (int i = 1; i <= times; ++i) {
        (*this).turn();
        if (start <= end){
            w << "Turn = " << i << "." << endl;;
            (*this).print(w);
            ++start; 
            w << endl;
        }
        if (st){
            if ( (i % step) == 0){
                 w << "Turn = " << i << "." << endl;;
                (*this).print(w); 
                w << endl;
            }

        }
        
            
    }
}
