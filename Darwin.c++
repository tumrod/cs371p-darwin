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

void Species::print() {
  cout << "name: " << name << endl; 
  for (int i = 0; (unsigned)i < instructions.size(); ++i){
    cout << "instruction " << i << " : " << instructions[i] << endl; 
  }
}

int Species::instruction_size(){
    return instructions.size();
}

void Creature::parse_inst(vector<vector<Creature>> &board, int row, int col) {
    cnt = cnt % species.instruction_size(); 
    string inst = species.curr_inst(cnt);
    // cout << " intrsuction: " << inst << endl; 
    std::vector<std::string> temp_inst;
    boost::split(temp_inst, inst, boost::is_any_of(" "));
    // for(int i = 0; i < temp_inst.size(); ++i){
    //     cout << " i: " << i << " : " << temp_inst[i] << endl; 
    // }
    int n_inst = -1 ;
    string current_inst = temp_inst.front();
    if (temp_inst.size() > 1)
        n_inst = atoi(temp_inst.back().c_str());

    // cout << " current instruction " << current_inst << " : " << n_inst << endl; 


    if(!current_inst.compare("hop")) {
        cout << "in hop" << endl;
        hop(board, row, col);
    }
        
    else if (!current_inst.compare("left"))
        left();
    // else if (!current_inst.compare("right"))
    //     right();
    // else if (!current_inst.compare("infect"))
    //     infect(board, row, col);
    // else if (!current_inst.compare("if_empty"))
    //     if_empty(n_inst, board, row, col);
    // else if (!current_inst.compare("if_wall"))
    //     if_wall(n_inst, board, row, col);
    // else if (!current_inst.compare("if_random"))
    //     if_random(n_inst, board, row, col);
    // else if (!current_inst.compare("if_enemy"))
    //     if_enemy(n_inst, board, row, col);
    // else if (!current_inst.compare("go"))
    //     go(n_inst, board, row, col);
}

bool Creature::is_empty(vector<vector<Creature>> &b, int r, int c) {
    if ((d == 0) && (--c >= 0) && (!b[r][--c].is_creature()))
        return true;
        
    else if ((d == 1) && (--r >= 0) && (!b[--r][c].is_creature()))
        return true;

    else if ((d == 2) && ((unsigned)++c < b[0].size()) && (!b[r][++c].is_creature()))
        return true;
        
    else if ((d == 3) && ((unsigned)++r < b.size()) && (!b[++r][c].is_creature()))
        return true;
    
    else
        return false;
}

void Creature::go(int n, vector<vector<Creature>> &b, int row, int col){
    cnt = n;
    parse_inst(b, row, col);
}

void Creature::hop(vector<vector<Creature>> &b, int row, int col){
    int r = row;
    int c = col;
    // cout << "hopping " << "r " << r << " c " << c << endl;

    if(is_empty(b, r, c)) {

        if(d == 0){
            cout << "d = 0" << endl;
            b[r][--c] = b[row][col];
            b[row][col].remove();
            
        }else if (d == 1){
            cout << "d = 1" << endl;
            b[--r][c] = b[row][col];
            // cout << "copy hopping" << endl;
            b[row][col].remove();
        }else if (d == 2){
            cout << "d = 2" << endl;
            b[r][++c] = b[row][col];
            b[row][col].remove();
            
        }else if (d == 3){
            cout << "d = 3" << endl;
            b[++r][c] = b[row][col];
            b[row][col].remove();
        }

    }
    ++cnt;
    cout << "out of hop" << endl;
}


void Creature::left(){
    // cout << "Executing Left" << endl;
    if(d)
        --d;
    else
        d = 3;
    ++cnt;
}

void Creature::right(){
    if(d == 3)
        d = 0;
    else
        ++d;
    ++cnt;
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
    ++cnt;
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
        if ( (unsigned)++c == b[0].size())
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


Creature::Creature(Species s, Direction direction): species(s), d(direction), cnt(0) {
    cout << "Created Creature " << direction << endl;
    s.print();
}
Creature::Creature(): d(-1), cnt(0) {}
void Creature::execute_instr(vector<vector<Creature>> &board, int row, int col) {
    cout << " In execute_instr creature " << endl;
    parse_inst(board, row, col);
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
    cout << "removing creature" << endl;
  (*this).d = -1;
  (*this).cnt = 0;
  (*this).species.remove();
}

void Creature::print() {
    cout << "species: " << endl;
    species.print();
    cout << "count: " << cnt << endl;
    cout << "direction: " << d << endl;
}

Darwin::Darwin(int row, int col) {
    board.resize(row, vector<Creature> (col, Creature()));
    cout<< "Created Darwin  " << endl; 
    cout << " board size: " << board.size() << " x " << board[0].size() << endl;
}

void Darwin::addCreature(Creature creature, int r, int c) {
    cout << "Adding Creature" << endl;
    board[r][c] = creature;
    board[r][c].print();
}

void Darwin::turn() {
    cout << "Execute Turn" << endl;
    vector<vector<Creature>> temp_board;
    temp_board = board;
    for(int r = 0; (unsigned)r < board.size(); ++r) {
        for(int c = 0; (unsigned)c < board[0].size(); ++c) {
            if(board[r][c].is_creature()) {
                
                
                Creature temp_creat = board[r][c];
                temp_creat.execute_instr(temp_board, r, c);
                // cout << "temp creat status" << endl;
                temp_creat.print();
                // board[temp[0]][temp[1]] = c;
                // board[r][c].remove();
            }
                
        }
    }
    board = temp_board; 
}

void Darwin::print(ostream& w) {
    w << "printing board" << endl;
    w << "  "; 
    for(int col = 0; (unsigned)col < board[0].size(); ++col)
        w << col;
    w << endl;
    for(int r = 0; (unsigned)r < board.size(); ++r) {
        w << r << " ";
        for(int c = 0; (unsigned)c < board[0].size(); ++c) {
            if(board[r][c].is_creature())
                board[r][c].print_species(w);
            else
                w << ".";
        }
        w << endl;
    }
}
