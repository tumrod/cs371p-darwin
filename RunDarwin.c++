// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2015
// Glenn P. Downing
// -----------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"

// ----
// main
// ----

int main () {
    using namespace std;

    // ----
    // food
    // ----
    /*
     0: left
     1: go 0
    */
    Species f = Species("food");
    f.addInstruction("left");
    f.addInstruction("go 0");
    // f.print(); 

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
    Species h = Species("hopper");
    h.addInstruction("hop");
    h.addInstruction("go 0");
    // h.print(); 

    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */

    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

    // ----------
    // darwin 8x8
    // ----------

    cout << "*** Darwin 8x8 ***" << endl;
    Darwin d = Darwin(8, 8);

    Creature f1 = Creature(f, east);
    d.addCreature(f1, 0, 0);

    Creature h1 = Creature(h, north);
    Creature h2 = Creature(h, east);
    Creature h3 = Creature(h, south);
    Creature h4 = Creature(h, west);
    Creature f2 = Creature(f, north);

    d.addCreature(h1, 3, 3);
    d.addCreature(h2, 3, 4);
    d.addCreature(h3, 4, 4);
    d.addCreature(h4, 4, 3);
    d.addCreature(f1, 7, 7);    

    d.simulation(5, cout);

    /*
    8x8 Darwin
    Food,   facing east,  at (0, 0)
    Hopper, facing north, at (3, 3)
    Hopper, facing east,  at (3, 4)
    Hopper, facing south, at (4, 4)
    Hopper, facing west,  at (4, 3)
    Food,   facing north, at (7, 7)
    Simulate 5 moves.
    Print every grid.
    */

    // ----------
    // darwin 7x9
    // ----------

    cout << "*** Darwin 7x9 ***" << endl;
    srand(0);
    /*
    7x9 Darwin
    Trap,   facing south, at (0, 0)
    Hopper, facing east,  at (3, 2)
    Rover,  facing north, at (5, 4)
    Trap,   facing west,  at (6, 8)
    Simulate 5 moves.
    Print every grid.
    */

    Darwin d2 = Darwin(7, 9);
    Species t = Species("trap");
    t.addInstruction("if_enemy 3");
    t.addInstruction("left");
    t.addInstruction("go 0");
    t.addInstruction("infect");
    t.addInstruction("go 0");
    
    Species r = Species("rover");
    r.addInstruction("if_enemy 9");
    r.addInstruction("if_empty 7");
    r.addInstruction("if_random 5");
    r.addInstruction("left");
    r.addInstruction("go 0");
    r.addInstruction("right");
    r.addInstruction("go 0");
    r.addInstruction("hop");
    r.addInstruction("go 0");
    r.addInstruction("infect");
    r.addInstruction("go 0");

    Creature t21 = Creature(t, south);
    Creature h21 = Creature(h, east);
    Creature r21 = Creature(r, north);
    Creature t22 = Creature(t, west);

    d2.addCreature(t21, 0, 0);
    d2.addCreature(h21, 3, 2);
    d2.addCreature(r21, 5, 4);
    d2.addCreature(t22, 6, 8);

    d2.simulation(5, cout);

    


    cout << "*** Darwin 72x72 without Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: west, north, east, south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    Simulate 1000 moves.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */
    Darwin d3 = Darwin(72, 72);

    int row;
    int col;

    int dir; 

    
    Species s;
    for (int j = 0; j < 4; ++j) {
        if (j == 0)
            s = f;
        else if (j == 1)
            s = h;
        else if (j == 2)
            s = r;
        else if (j == 3)
            s = t; 

        for (int i = 0; i < 10; ++i){
            col = rand()%5184;
            row = col/72;  

            if(col >72)
                col = col%72;
            
            dir = rand()%4;
            Creature f1 = Creature(s, dir);
            d3.addCreature(f1, row, col); 
 

        }
    }

    d3.simulation(1000, cout, 1, 10, 100); 




    // ------------
    // darwin 72x72
    // with best
    // ------------

    cout << "*** Darwin 72x72 with Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: 0:west, 1:north, 2:east, 3:south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    10 Best
    Simulate 1000 moves.
    Best MUST outnumber ALL other species for the bonus pts.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    Darwin d4 = Darwin(72, 72);

    Species best = Species("best"); 
    best.addInstruction("if_empty 5");
    best.addInstruction("if_enemy 3");
    best.addInstruction("if_wall 7");
    best.addInstruction("infect");
    best.addInstruction("go 0");
    best.addInstruction("hop");
    best.addInstruction("go 0");
    best.addInstruction("left");
    best.addInstruction("go 0");
    
  
    for (int j = 0; j < 5; ++j) {
        if (j == 0)
            s = f;
        else if (j == 1)
            s = h;
        else if (j == 2)
            s = r;
        else if (j == 3)
            s = t; 
        else if (j == 4)
            s = best; 

        for (int i = 0; i < 10; ++i){
            col = rand()%5184;
            row = col/72;  

            if(col >72)
                col = col%72;
            
            dir = rand()%4;
            Creature f1 = Creature(s, dir);
            d4.addCreature(f1, row, col); 
 

        }
    }

    d4.simulation(1000, cout, 1, 10, 100); 

    return 0;}
