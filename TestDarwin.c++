#include "gtest/gtest.h"

#include "Darwin.h"
#include <iostream>
#include <sstream>
#include <string>

// ------------
// SpeciesTest
// ------------

TEST(SpeciesTest, species_1) {
    
    Species f = Species("food");
    ostringstream w;
    f.print_name(w);
    ASSERT_EQ("f", w.str());

}

TEST(SpeciesTest, species_2) {

    Species f = Species();
    ostringstream w;
    f.print_name(w);
    ASSERT_EQ("\n", w.str());
}

TEST(SpeciesTest, species_3) {

    Species f = Species("t");
    ostringstream w;
    f.print_name(w);
    ASSERT_EQ("t", w.str());
}

TEST(SpeciesTest, addInstruction_1){
    Species f = Species("testing");
    f.addInstruction("left"); 
    ostringstream w;
    f.print(w);
    ASSERT_EQ("name: testing\ninstruction 0 : left\n", w.str());
}

TEST(SpeciesTest, addInstruction_2){
    Species f = Species("blood");
    f.addInstruction("infect"); 
    f.addInstruction("hop"); 
    f.addInstruction("go 0"); 
    ostringstream w;
    f.print(w);
    ASSERT_EQ("name: blood\ninstruction 0 : infect\ninstruction 1 : hop\ninstruction 2 : go 0\n", w.str());
    
}

TEST(SpeciesTest, addInstruction_3){
    Species f = Species("hop");
    f.addInstruction("hop"); 
    f.addInstruction("go 0"); 

    ostringstream w;
    f.print(w);
    ASSERT_EQ("name: hop\ninstruction 0 : hop\ninstruction 1 : go 0\n", w.str());
    
}

TEST(SpeciesTest, print_name_1){
    Species f = Species();
    ostringstream w;
    f.print_name(w);
    ASSERT_EQ("\n", w.str());
}

TEST(SpeciesTest, print_name_2){
    Species f = Species("hello from the other side");
    ostringstream w;
    f.print_name(w);
    ASSERT_EQ("h", w.str());
}

TEST(SpeciesTest, print_name_3){
    Species f = Species("aslkfjsdkfjal;sdjfl;kajd;lf");
    ostringstream w;
    f.print_name(w);
    ASSERT_EQ("a", w.str());
}

TEST(SpeciesTest, equal_1){
    Species f1 = Species("food");
    Species f2 = Species("hop");
    ASSERT_FALSE(f1.equal(f2));
    
}

TEST(SpeciesTest, equal_2){
    Species f1 = Species("rover");
    Species f2 = Species("rover");
    ASSERT_TRUE(f1.equal(f2));
}

TEST(SpeciesTest, equal_3){
    Species f1 = Species();
    Species f2 = Species();
    ASSERT_FALSE(f1.equal(f2));
}

TEST(SpeciesTest, remove_1){
    Species f = Species("hop");
    f.addInstruction("hop"); 
    f.addInstruction("go 0"); 
    
    f.remove();
    ostringstream w;
    f.print(w);
    ASSERT_EQ("name: \nno instructions\n", w.str());

}

TEST(SpeciesTest, remove_2){
    Species f = Species("jsalkjfa;");
    f.addInstruction("hop"); 
    f.addInstruction("go 0"); 
    f.addInstruction("right"); 
    f.addInstruction("go 0"); 
    
    f.remove();
    ostringstream w;
    f.print(w);
    ASSERT_EQ("name: \nno instructions\n", w.str());

}

TEST(SpeciesTest, remove_3){
    Species f = Species();
    f.remove();
    ostringstream w;
    f.print(w);
    ASSERT_EQ("name: \nno instructions\n", w.str());
}

TEST(SpeciesTest, print_1){
    Species f = Species();
    ostringstream w;
    f.print(w);
    ASSERT_EQ("name: \nno instructions\n", w.str());
}

TEST(SpeciesTest, print_2){
    Species f = Species("jsalkjfa;");
    ostringstream w;
    f.print(w);
    ASSERT_EQ("name: jsalkjfa;\nno instructions\n", w.str());
}

TEST(SpeciesTest, print_3){
    Species f = Species("work");
    f.addInstruction("right"); 

    ostringstream w;
    f.print(w);
    ASSERT_EQ("name: work\ninstruction 0 : right\n", w.str());
}

TEST(SpeciesTest, get_action_1){
    Species f = Species("food");
    f.addInstruction("left"); 
    f.addInstruction("go 0"); 
    int temp_cnt = 0; 
    vector<int> test = f.get_action(temp_cnt);
    ASSERT_EQ(test.size(), 1); 
    ASSERT_EQ(test[0], 1);
}

TEST(SpeciesTest, get_action_2){
    Species f = Species("blood");
    f.addInstruction("infect");
    f.addInstruction("hop"); 
    f.addInstruction("go 0"); 

    int temp_cnt = 2; 
    vector<int> test = f.get_action(temp_cnt);
    ASSERT_EQ(test.size(), 2); 
    ASSERT_EQ(test[0], 8);
    ASSERT_EQ(test[1], 0);

}

TEST(SpeciesTest, get_action_3){
    Species f = Species("testing");
    f.addInstruction("infect");
    f.addInstruction("hop"); 
    f.addInstruction("right"); 
    f.addInstruction("if_empty 1");
    f.addInstruction("go 0"); 

    int temp_cnt = 8; 
    vector<int> test = f.get_action(temp_cnt);
    ASSERT_EQ(test.size(), 2); 
    ASSERT_EQ(test[0], 4);
    ASSERT_EQ(test[1], 1);
}

// ------------
// CreatureTest
// ------------

TEST(CreatureTest, do_inst_1){
    vector<vector<Creature>> board(4, vector<Creature>(4)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f = Species("hop"); 
    f.addInstruction("hop"); 
    f.addInstruction("go 0");
    Creature temp = Creature(f, east); 
    board [0][0] = temp; 

    vector<int> inst = f.get_action(temp.cnt); 
    ASSERT_FALSE(board[0][1].is_creature());  

    temp.do_inst(inst, board, 0, 0);
    ASSERT_TRUE(board[0][1].is_creature());  


}

TEST(CreatureTest, do_inst_2){
    vector<vector<Creature>> board(5, vector<Creature>(6)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f = Species("blood"); 
    f.addInstruction("right");
    f.addInstruction("hop"); 
    f.addInstruction("go 0");
    Creature temp = Creature(f, north); 
    board [0][0] = temp; 
    vector<int> inst = f.get_action(temp.cnt); 
    temp.do_inst(inst, board, 0, 0);
    inst = f.get_action(temp.cnt); 
    ASSERT_FALSE(board[0][1].is_creature());  

    temp.do_inst(inst, board, 0, 0);
    ASSERT_TRUE(board[0][1].is_creature());  

}

TEST(CreatureTest, do_inst_3){
    vector<vector<Creature>> board(3, vector<Creature>(3)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f = Species("testing");
    f.addInstruction("if_empty 2");
    f.addInstruction("right");
    f.addInstruction("hop"); 
    f.addInstruction("go 0");
    Creature temp = Creature(f, east);
    temp.cnt = 3; 
    board [0][0] = temp;  
    vector<int> inst = f.get_action(temp.cnt);
    ASSERT_FALSE(board[0][1].is_creature());  

    temp.do_inst(inst, board, 0, 0);
    ASSERT_TRUE(board[0][1].is_creature()); 
}

TEST(CreatureTest, is_empty_1){
    vector<vector<Creature>> board(3, vector<Creature>(3)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("hop"); 
    f1.addInstruction("hop"); 
    f1.addInstruction("go 0");
    Creature temp1 = Creature(f1, east); 
    board [0][0] = temp1; 

    Species f2 = Species("testing");
    f2.addInstruction("if_empty 2");
    f2.addInstruction("right");
    f2.addInstruction("hop"); 
    f2.addInstruction("go 0");
    Creature temp2 = Creature(f2, north); 
    board [0][1] = temp2; 
    ASSERT_FALSE(temp1.is_empty(board, 0, 0));
}

TEST(CreatureTest, is_empty_2){
    vector<vector<Creature>> board(4, vector<Creature>(5)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("hello"); 
    Creature temp1 = Creature(f1, north); 
    board [2][3] = temp1; 

    Species f2 = Species("gummy");

    Creature temp2 = Creature(f2, west); 
    board [1][1] = temp2; 
    ASSERT_TRUE(temp1.is_empty(board, 2, 3));
    ASSERT_TRUE(temp2.is_empty(board, 1, 1));

}

TEST(CreatureTest, is_empty_3){
    vector<vector<Creature>> board(5, vector<Creature>(5)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("hello");
    Creature temp1 = Creature(f1, east); 
    board [4][4] = temp1; 

    ASSERT_FALSE(temp1.is_empty(board, 4, 4));
    temp1.d +=1; 
    ASSERT_FALSE(temp1.is_empty(board, 4, 4));


}

TEST(CreatureTest, is_wall_1){
    vector<vector<Creature>> board(3, vector<Creature>(3)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("hop"); 
    Creature temp1 = Creature(f1, east); 
    board [0][0] = temp1; 
    ASSERT_FALSE(temp1.is_wall(board, 0, 0));

}

TEST(CreatureTest, is_wall_2){
    vector<vector<Creature>> board(3, vector<Creature>(3)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("test"); 
    Creature temp1 = Creature(f1, north); 
    board [0][0] = temp1; 
    ASSERT_TRUE(temp1.is_wall(board, 0, 0));
}

TEST(CreatureTest, is_wall_3){
    vector<vector<Creature>> board(2, vector<Creature>(2)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("lol"); 
    Creature temp1 = Creature(f1, south); 
    board [1][1] = temp1; 
    ASSERT_TRUE(temp1.is_wall(board, 1, 1));
}

TEST(CreatureTest, ex_go_1){
    vector<vector<Creature>> board(3, vector<Creature>(3)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("hop"); 
    f1.addInstruction("hop"); 
    f1.addInstruction("go 0");
    Creature temp1 = Creature(f1, east); 
    board [0][0] = temp1; 
    ASSERT_FALSE(board[0][1].is_creature());  

    temp1.ex_go(temp1.cnt, board, 0, 0);
    ASSERT_TRUE(board[0][1].is_creature());  

}

TEST(CreatureTest, ex_go_2){
    vector<vector<Creature>> board(4, vector<Creature>(4)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
 
    Species f = Species("testing");
    f.addInstruction("if_empty 2");
    f.addInstruction("right");
    f.addInstruction("hop"); 
    f.addInstruction("go 0");
    Creature temp = Creature(f, west); 
    temp.cnt = 3; 
    board [3][2] = temp; 
    ASSERT_FALSE(board[3][1].is_creature());  

    temp.ex_go(temp.cnt, board, 3, 2);
    ASSERT_TRUE(board[3][1].is_creature());
}  

TEST(CreatureTest, ex_go_3){
    vector<vector<Creature>> board(3, vector<Creature>(3)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("food"); 
    f1.addInstruction("left"); 
    f1.addInstruction("go 0");
    Creature temp1 = Creature(f1, east);
    temp1.cnt = 1;  
    board [2][2] = temp1; 
    ASSERT_TRUE(board[2][2].d == 2);
    
    temp1.ex_go(temp1.cnt, board, 2, 2);
    ASSERT_TRUE(board[2][2].d == 1);
} 

TEST(CreatureTest, ex_hop_1){
    vector<vector<Creature>> board(3, vector<Creature>(3)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("hop"); 
    f1.addInstruction("hop"); 
    f1.addInstruction("go 0");
    Creature temp1 = Creature(f1, east); 
    board [2][0] = temp1; 
    ASSERT_TRUE(board[2][0].d == 2);
    ASSERT_TRUE(temp1.is_empty(board, 2, 0));
    
    temp1.ex_hop(board, 2, 0);
    ASSERT_TRUE(board[2][1].is_creature());
    ASSERT_FALSE(board[2][0].is_creature());
    

}
TEST(CreatureTest, ex_hop_2){
    vector<vector<Creature>> board(6, vector<Creature>(7)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("blood"); 
    Creature temp1 = Creature(f1, west);  
    board [5][6] = temp1; 
    ASSERT_TRUE(board[5][6].is_empty(board, 5, 6));
    
    board[5][6].ex_hop(board, 5, 6);
    ASSERT_TRUE(board[5][5].is_creature());
    ASSERT_FALSE(board[5][6].is_creature());
    
}
// TEST(CreatureTest, ex_hop_3){

// }
// TEST(CreatureTest, ex_left_1){

// }
// TEST(CreatureTest, ex_left_2){

// }
// TEST(CreatureTest, ex_left_3){

// }
// TEST(CreatureTest, ex_right_1){

// }
// TEST(CreatureTest, ex_right_2){

// }
// TEST(CreatureTest, ex_right_3){

// }
// TEST(CreatureTest, ex_infect_1){

// }
// TEST(CreatureTest, ex_infect_2){

// }
// TEST(CreatureTest, ex_infect_3){

// }

