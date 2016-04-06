#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
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
    w << name.at(0);
}

bool Species::equal(Species s){
    if (!(name.compare(s.name)))
        return true;
    return false;
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

vector<int> Species::get_action(int &cnt){
    // should parse the insturctions and return the action number 
    cnt = cnt % instructions.size();  
    // cout << "count " << cnt << endl; 
    string inst = instructions[cnt];
    // cout << " intrsuction: " << inst << endl; 
    std::vector<std::string> temp_inst;
    boost::split(temp_inst, inst, boost::is_any_of(" "));

    int n_inst = -1 ;
    string current_inst = temp_inst.front();
    if (temp_inst.size() > 1)
        n_inst = atoi(temp_inst.back().c_str());

    // cout << " current instruction " << current_inst << " : " << n_inst << endl; 
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

// void Creature::do_action(int action, vector<vector<Creature>> &b, int r, int c){
//     if(action == 0) 
//         hop(b, r, c);    
//     else if (action == 1)
//          left(b, r, c);
//     else if (action == 2)
//         right(b,r, c);
//     else if (action == 3)
//         infect(b, r, c);
// }
// void Creature::do_control(int control, int n_inst, vector<vector<Creature>> &board, int row, int col){

//     if (control == 0)
//         if_empty(n_inst, board, row, col);
//     else if (control == 1)
//         if_wall(n_inst, board, row, col);
//     else if (control == 2)
//         if_random(n_inst, board, row, col);
//     else if (control == 3)
//         if_enemy(n_inst, board, row, col);
//     else if (control == 4){
//         // cout << "in go if" << endl;

//         go(n_inst, board, row, col);
//     }

// } 

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
    // cout << "direction in is_empty " << d << endl;
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
        
    else if ((d == 3) && ((unsigned)(r+1) >= b.size())) {
        return true;
    }
    else{
        return false;
    }
}

void Creature::ex_go(int n, vector<vector<Creature>> &b, int row, int col){
    cnt = n;
    vector<int> instruction = species.get_action(cnt); 
    do_inst(instruction, b, row, col); 

    // parse_inst(b, row, col);
}

void Creature::ex_hop(vector<vector<Creature>> &b, int row, int col){
    int r = row;
    int c = col;
    ++cnt; 
    if(is_empty(b, r, c)) {
        if(d == 0){
            // cout << "d = 0" << endl;
            // b[r][--c] = b[row][col];
            b[r][--c] = (*this);

            b[row][col].remove();
            
        }else if (d == 1){
            // cout << "d = 1" << endl;
            
            b[--r][c] = (*this);

            // b[--r][c] = b[row][col];
            b[row][col].remove();
        }else if (d == 2){
            // cout << "d = 2" << endl;
            // b[r][++c] = b[row][col];
            b[r][++c] = (*this);

            b[row][col].remove();
            
        }else if (d == 3){
            // cout << "d = 3" << endl;
            // b[++r][c] = b[row][col];
            b[++r][c] = (*this);

            b[row][col].remove();
        }

    }else {
        b[row][col]  = (*this); // because it changes the program counter 
    }
    // cout << "out of hop" << endl;
}


void Creature::ex_left(vector<vector<Creature>> &b, int row, int col){
    // cout << "Executing Left" << endl;
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
    // (*this).print();
    // cout << "\tin infect()" << endl;
    int r = row;
    int c = col; 
    ++cnt;

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
    // (*this).print();
    // cout <<"\tin if_enemy()" << endl;
    int r = row;
    int c = col;
    if (!is_empty(b, row, col) && !is_wall(b, row, col)) {
        // cout << "is_enemy() should not be here!" << endl; 
        if((d == 0) && (!species.equal(b[r][--c].species)))
            ex_go (n, b, row, col);
        else if ((d == 1) && (!species.equal(b[--r][c].species)))
            ex_go (n, b, row, col);

        else if ((d == 2) && (!species.equal(b[r][++c].species)))
            ex_go (n, b, row, col);

        else if ((d == 3) && (!species.equal(b[++r][c].species)))
            ex_go (n, b, row, col);
    } else {
        ex_go (++cnt, b, row, col);
    }
}


Creature::Creature(Species s, Direction direction): species(s), d(direction), cnt(0) {
    // cout << "Created Creature " << direction << endl;
    // s.print();
}
Creature::Creature(): d(-1), cnt(0) {}

void Creature::execute_instr(vector<vector<Creature>> &board, int row, int col) {
    // cout << " In execute_instr creature " << endl;
    // cout << " count before executing turn " << cnt << endl; 
    vector<int> instruction = species.get_action(cnt);
    do_inst(instruction, board, row, col); 

    // if (instruction.size() > 1)
    //     do_control(instruction[0], instruction[1], board, row, col); 
    // else 
    //     do_action(instruction[0], board, row, col); 

    // parse_inst(board, row, col);
    // cout << " out execute_instr creature " << endl;

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
    // cout << "removing creature" << endl;
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
    // cout<< "Created Darwin  " << endl; 
    // cout << " board size: " << board.size() << " x " << board[0].size() << endl;
}

void Darwin::addCreature(Creature &creature, int r, int c) {
    // cout << "Adding Creature" << endl;
    if (r < 0 || (unsigned)r >= board.size() || c < 0 || (unsigned)c >= board[0].size())
        throw out_of_range("Out of Range");

    board[r][c] = creature;
    // board[r][c].print();
}

void Darwin::turn() {
    // cout << "Execute Turn" << endl;
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

vector<vector<Creature>>::iterator Darwin::end() {
    return board.end();
}

Creature Darwin::at(int r, int c) {
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

void Darwin::simulation(int times, ostream& w) {
    assert(times > 0);
    w << "Turn = 0." << endl;;
    (*this).print(w);
    w << endl;

    for (int i = 1; i <= times; ++i) {
        w << "Turn = " << i << "." << endl;;
        (*this).turn();
        (*this).print(w);
        w << endl;
    }
}
