#include "gtest/gtest.h"

#include "Darwin.h"
#include <iostream>

TEST(DarwinTest, add_creature_1) {
    Darwin d2 = Darwin(7, 9);
    int s = d2.board.size();
    // Species t = Species("trap");
    // t.addInstruction("hop");
    // Creature t1 = Creature(t, south);

    // d2.addCreature(t1, 0, 0);

    //d2.simulation(5, cout);
    
    ASSERT_EQ(s, 7);
}