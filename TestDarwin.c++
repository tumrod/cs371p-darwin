#include "gtest/gtest.h"

#include "Darwin.h"
#include <iostream>
#include <sstream>
#include <string>

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
    ASSERT_EQ("", w.str());
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
    ASSERT_EQ("", w.str());
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

TEST(SpeciesTest, NE_1){
    Species f1 = Species("food");
    Species f2 = Species("hop");
    ASSERT_NE(f1, f2);
    
}

TEST(SpeciesTest, NE_2){
    Species f1 = Species();
    Species f2 = Species("hop");
    ASSERT_NE(f1, f2);
}

TEST(SpeciesTest, NE_3){
    Species f1 = Species();
    Species f2 = Species("food");
    ASSERT_NE(f1, f2);
}

TEST(SpeciesTest, EQ_1){
    Species f1 = Species("rover");
    Species f2 = Species("rover");
    ASSERT_EQ(f1, f2);
}

TEST(SpeciesTest, EQ_2){
    Species f1 = Species("food");
    Species f2 = Species("food");
    ASSERT_EQ(f1, f2);
}

TEST(SpeciesTest, EQ_3){
    Species f1 = Species("hopper");
    Species f2 = Species("hopper");
    ASSERT_EQ(f1, f2);
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
TEST(CreatureTest, ex_hop_3){
    vector<vector<Creature>> board(6, vector<Creature>(7)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("icecream"); 
    Creature temp1 = Creature(f1, north);  
    board [4][4] = temp1; 

    Species f2 = Species("gummy");
    Creature temp2 = Creature(f2, west); 
    board [3][4] = temp2;
    
    board[4][4].ex_hop(board, 4, 4);
    ASSERT_TRUE(board[4][4].is_creature());

}
TEST(CreatureTest, ex_left_1){
    vector<vector<Creature>> board(3, vector<Creature>(3)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("rubber"); 
    Creature temp1 = Creature(f1, west);  
    board [1][2] = temp1; 
    ASSERT_EQ(board[1][2].d, 0);
    
    board[1][2].ex_left(board, 1, 2);
    ASSERT_EQ(board[1][2].d, 3);

}
TEST(CreatureTest, ex_left_2){
    vector<vector<Creature>> board(3, vector<Creature>(3)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("paper"); 
    Creature temp1 = Creature(f1, west);  
    board [1][2] = temp1; 
    ASSERT_EQ(board[1][2].d, 0);
    
    board[1][2].ex_left(board, 1, 2);
    ASSERT_EQ(board[1][2].d, 3);
}

TEST(CreatureTest, ex_left_3){
    vector<vector<Creature>> board(5, vector<Creature>(5)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("cross"); 
    Creature temp1 = Creature(f1, south);  
    board [3][3] = temp1; 
    ASSERT_EQ(board[3][3].d, 3);
    
    board[3][3].ex_left(board, 3, 3);
    ASSERT_EQ(board[3][3].d, 2);
}

TEST(CreatureTest, ex_right_1){
    vector<vector<Creature>> board(5, vector<Creature>(5)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("pencil"); 
    Creature temp1 = Creature(f1, south);  
    board [3][3] = temp1; 
    ASSERT_EQ(board[3][3].d, 3);
    
    board[3][3].ex_right(board, 3, 3);
    ASSERT_EQ(board[3][3].d, 0);
}

TEST(CreatureTest, ex_right_2){
    vector<vector<Creature>> board(5, vector<Creature>(5)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("chair"); 
    Creature temp1 = Creature(f1, north);  
    board [1][1] = temp1; 
    ASSERT_EQ(board[1][1].d, 1);
    
    board[1][1].ex_right(board, 1, 1);
    ASSERT_EQ(board[1][1].d, 2);
}

TEST(CreatureTest, ex_right_3){
    vector<vector<Creature>> board(2, vector<Creature>(2)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("blood"); 
    Creature temp1 = Creature(f1, east);  
    board [0][0] = temp1; 
    ASSERT_EQ(board[0][0].d, 2);
    
    board[0][0].ex_right(board, 0, 0);
    ASSERT_EQ(board[0][0].d, 3);
}

TEST(CreatureTest, ex_infect_1){
    vector<vector<Creature>> board(2, vector<Creature>(2)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("food"); 
    Creature temp1 = Creature(f1, east);  
    board [0][0] = temp1; 

    Species f2 = Species("gummy");
    Creature temp2 = Creature(f2, west); 
    board [0][1] = temp2;
    
    
    board[0][0].ex_infect(board, 0, 0);
    ASSERT_EQ(board[0][0].species, board[0][1].species);
}

TEST(CreatureTest, ex_infect_2){
    vector<vector<Creature>> board(4, vector<Creature>(4)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("blood"); 
    Creature temp1 = Creature(f1, east);  
    board [0][0] = temp1; 
    ASSERT_EQ(board[0][0].d, 2);
    
    board[0][0].ex_infect(board, 0, 0);
    ASSERT_EQ(board[0][0].cnt, 1);
}

TEST(CreatureTest, ex_infect_3){
    vector<vector<Creature>> board(2, vector<Creature>(2)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("pencil"); 
    Creature temp1 = Creature(f1, south);  
    board [0][1] = temp1; 

    Species f2 = Species("rover"); 
    Creature temp2 = Creature(f2, east);  
    board [1][1] = temp2; 

    
    board[0][1].ex_infect(board, 0, 1);
    ASSERT_EQ(board[1][1].species, board[0][1].species);
}

TEST(CreatureTest, ex_if_empty_1){
    vector<vector<Creature>> board(2, vector<Creature>(2)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("temp");
    f1.addInstruction("if_empty 1");
    f1.addInstruction("left");
    f1.addInstruction("go 0"); 

    Creature temp1 = Creature(f1, south);  
    board [0][1] = temp1; 
    int n = 1; 
    
    board[0][1].ex_if_empty(n, board, 0, 1);
    ASSERT_EQ(board[0][1].d, 2);
}
TEST(CreatureTest, ex_if_empty_2){
    vector<vector<Creature>> board(3, vector<Creature>(3)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("temp");
    f1.addInstruction("if_empty 1");
    f1.addInstruction("hop");
    f1.addInstruction("go 0"); 

    Creature temp1 = Creature(f1, south);  
    board [0][1] = temp1; 
    int n = 1; 
    
    board[0][1].ex_if_empty(n, board, 0, 1);
    ASSERT_TRUE(board[1][1].is_creature());
}

TEST(CreatureTest, ex_if_empty_3){
    vector<vector<Creature>> board(3, vector<Creature>(3)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("temp");
    f1.addInstruction("if_empty 2");
    f1.addInstruction("left");
    f1.addInstruction("hop");
    f1.addInstruction("go 0"); 

    Creature temp1 = Creature(f1, south); 
    Creature temp2 = Creature(f1, west); 
    board [0][1] = temp1;
    board [1][1] = temp2; 
    int n = 2; 
    
    board[0][1].ex_if_empty(n, board, 0, 1);
    ASSERT_EQ(board[0][1].d, 2);
}

TEST(CreatureTest, ex_if_wall_1){
    vector<vector<Creature>> board(3, vector<Creature>(3)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("temp");
    f1.addInstruction("if_wall 1");
    f1.addInstruction("right");
    f1.addInstruction("hop");
    f1.addInstruction("go 0"); 

    Creature temp1 = Creature(f1, east);  
    board [0][0] = temp1;
    int n = 1; 
    
    board[0][0].ex_if_wall(n, board, 0, 1);
    ASSERT_EQ(board[0][0].d, 3);
}

TEST(CreatureTest, ex_if_wall_2){
    vector<vector<Creature>> board(3, vector<Creature>(3)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("temp");
    f1.addInstruction("if_wall 2");
    f1.addInstruction("hop");
    f1.addInstruction("right");
    f1.addInstruction("go 0"); 

    Creature temp1 = Creature(f1, east);  
    board [1][1] = temp1;
    int n = 2; 
    
    board[1][1].ex_if_wall(n, board, 1, 1);
    ASSERT_TRUE(board[1][2].is_creature());
}

TEST(CreatureTest, ex_if_wall_3){
    vector<vector<Creature>> board(3, vector<Creature>(3)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("temp");
    f1.addInstruction("if_wall 2");
    f1.addInstruction("hop");
    f1.addInstruction("left");
    f1.addInstruction("go 0"); 

    Creature temp1 = Creature(f1, east);  
    board [2][2] = temp1;
    int n = 2; 
    
    board[2][2].ex_if_wall(n, board, 2, 2);
    ASSERT_EQ(board[2][2].d, 1 );

}

TEST(CreatureTest, ex_if_random_1){
    srand(0);
    vector<vector<Creature>> board(3, vector<Creature>(3)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("temp");
    f1.addInstruction("if_random 2");
    f1.addInstruction("hop");
    f1.addInstruction("left");
    f1.addInstruction("go 0"); 

    Creature temp1 = Creature(f1, west);  
    board [2][2] = temp1;
    int n = 2; 
    
    board[2][2].ex_if_random(n, board, 2, 2);
    ASSERT_EQ(board[2][2].d, 3);
}

TEST(CreatureTest, ex_if_random_2){
    srand(0);
    vector<vector<Creature>> board(3, vector<Creature>(3)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("temp");
    f1.addInstruction("if_random 2");
    f1.addInstruction("hop");
    f1.addInstruction("left");
    f1.addInstruction("go 0"); 

    Creature temp1 = Creature(f1, north);  
    board [2][2] = temp1;
    int n = 2; 
    
    board[2][2].ex_if_random(n, board, 2, 2);
    board[2][2].ex_if_random(n, board, 2, 2);
    board[2][2].ex_if_random(n, board, 2, 2);
    ASSERT_EQ(board[2][2].d, 2);
}

TEST(CreatureTest, ex_if_random_3){
    srand(0);
    vector<vector<Creature>> board(3, vector<Creature>(3)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("temp");
    f1.addInstruction("if_random 2");
    f1.addInstruction("hop");
    f1.addInstruction("left");
    f1.addInstruction("go 0"); 

    Creature temp1 = Creature(f1, north);  
    board [2][2] = temp1;
    int n = 2; 
    
    board[2][2].ex_if_random(n, board, 2, 2);
    board[2][2].ex_if_random(n, board, 2, 2);
    board[2][2].ex_if_random(n, board, 2, 2);
    board[2][2].ex_if_random(n, board, 2, 2);

    ASSERT_EQ(board[2][2].d, 1);
}

TEST(CreatureTest, ex_if_enemy_1){
    vector<vector<Creature>> board(4, vector<Creature>(4)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("temp");
    f1.addInstruction("if_enemy 2");
    f1.addInstruction("right");
    f1.addInstruction("left");
    f1.addInstruction("go 0"); 

    Creature temp1 = Creature(f1, north);  
    board [2][2] = temp1;
    Species f2 = Species("enemy");
    Creature temp2 = Creature(f2, east);  
    board [1][2] = temp2;

    
    int n = 2; 
    
    board[2][2].ex_if_enemy(n, board, 2, 2);

    ASSERT_EQ(board[2][2].d, 0);
}

TEST(CreatureTest, ex_if_enemy_2){
    vector<vector<Creature>> board(4, vector<Creature>(4)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("temp");
    f1.addInstruction("if_enemy 2");
    f1.addInstruction("right");
    f1.addInstruction("left");
    f1.addInstruction("go 0"); 

    Creature temp1 = Creature(f1, north);  
    board [2][2] = temp1;

    
    int n = 2; 
    
    board[2][2].ex_if_enemy(n, board, 2, 2);

    ASSERT_EQ(board[2][2].d, 2);
}

TEST(CreatureTest, ex_if_enemy_3){
    vector<vector<Creature>> board(4, vector<Creature>(4)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species f1 = Species("temp");
    f1.addInstruction("if_enemy 2");
    f1.addInstruction("hop");
    f1.addInstruction("left");
    f1.addInstruction("go 0"); 

    Creature temp1 = Creature(f1, north);  
    board [2][2] = temp1;

    
    int n = 2; 
    
    board[2][2].ex_if_enemy(n, board, 2, 2);

    ASSERT_TRUE(board[1][2].is_creature());
}


TEST(CreatureTest, creature_1) {
    Species s = Species();
    Creature h1 = Creature();
    ASSERT_EQ(s, h1.species);
    ASSERT_EQ(-1, h1.d);
    ASSERT_EQ(0, h1.cnt);
}

TEST(CreatureTest, creature_2) {
    Species h = Species("hopper");
    Creature h1 = Creature(h, north);
    ASSERT_EQ(h, h1.species);
    ASSERT_EQ(1, h1.d);
    ASSERT_EQ(0, h1.cnt);
}

TEST(CreatureTest, creature_3) {
    Species f = Species("food");
    Creature f1 = Creature(f, south);
    ASSERT_EQ(f, f1.species);
    ASSERT_EQ(3, f1.d);
    ASSERT_EQ(0, f1.cnt);
}

TEST(CreatureTest, execute_instr_1) {
    vector<vector<Creature>> board(4, vector<Creature>(5)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }

    Species f1 = Species("hop"); 
    f1.addInstruction("hop"); 
    f1.addInstruction("go 0");

    Creature temp1 = Creature(f1, east); 
    board [2][0] = temp1; 

    temp1.execute_instr(board, 2, 0);

    ostringstream w;
    board[2][1].print_species(w);
    ASSERT_EQ("h", w.str());
}

TEST(CreatureTest, execute_instr_2) {
    vector<vector<Creature>> board(4, vector<Creature>(4)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }

    Species t = Species("trap");
    t.addInstruction("if_enemy 3");
    t.addInstruction("left");
    t.addInstruction("go 0");
    t.addInstruction("infect");
    t.addInstruction("go 0");

    Creature temp1 = Creature(t, west); 
    board [3][0] = temp1; 
    
    temp1.execute_instr(board, 3, 0);

    ostringstream w;
    board[3][0].print_species(w);
    ASSERT_EQ("t", w.str());
}

TEST(CreatureTest, execute_instr_3) {
    vector<vector<Creature>> board(8, vector<Creature>(8)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }

    Species h = Species("hopper");
    h.addInstruction("hop");
    h.addInstruction("go 0");

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

    Creature h1 = Creature(h, east);
    Creature r1 = Creature(r, north);

    board[3][3] = h1;
    board[4][4] = r1;  
    
    h1.execute_instr(board, 3, 3);
    r1.execute_instr(board, 4, 4);

    ostringstream w;
    board[3][4].print_species(w);
    ASSERT_EQ("r", w.str());
}

TEST(CreatureTest, print_species_1) {
    Species h = Species("hopper");
    Creature h1 = Creature(h, east);

    ostringstream w;
    h1.print_species(w);
    ASSERT_EQ("h", w.str());
}

TEST(CreatureTest, print_species_2) {
    Species f = Species("food");
    Creature f1 = Creature(f, east);

    ostringstream w;
    f1.print_species(w);
    ASSERT_EQ("f", w.str());
}

TEST(CreatureTest, print_species_3) {
    Creature f1 = Creature();

    ostringstream w;
    f1.print_species(w);
    ASSERT_EQ("", w.str());
}

TEST(CreatureTest, is_creature_1) {
    vector<vector<Creature>> board(8, vector<Creature>(8)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species h = Species("hopper");
    Creature h1 = Creature(h, east);
    board[3][3] = h1;

    ASSERT_TRUE(board[3][3].is_creature());
}

TEST(CreatureTest, is_creature_2) {
    vector<vector<Creature>> board(8, vector<Creature>(8)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }

    ASSERT_FALSE(board[0][0].is_creature());
}

TEST(CreatureTest, is_creature_3) {
    vector<vector<Creature>> board(8, vector<Creature>(8)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species h = Species("hopper");
    h.addInstruction("hop");
    h.addInstruction("go 0");

    Creature h1 = Creature(h, east);
    board[2][2] = h1;

    h1.execute_instr(board, 2, 2);
    ASSERT_FALSE(board[2][2].is_creature());
    ASSERT_TRUE(board[2][3].is_creature());
}

TEST(CreatureTest, remove_1) {
    vector<vector<Creature>> board(8, vector<Creature>(8)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species h = Species("hopper");
    Creature h1 = Creature(h, east);
    board[2][2] = h1;
    ASSERT_TRUE(board[2][2].is_creature());
    board[2][2].remove();
    ASSERT_FALSE(board[2][2].is_creature());
}

TEST(CreatureTest, remove_2) {
    vector<vector<Creature>> board(8, vector<Creature>(8)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    board[0][0].remove();
    ASSERT_EQ(board[0][0], Creature());
}

TEST(CreatureTest, remove_3) {
    vector<vector<Creature>> board(8, vector<Creature>(8)); 
    for ( int i = 0; (unsigned)i < board.size(); ++i){
        for (int c = 0; (unsigned)c < board[0].size(); ++ c)
            board[i][c] = Creature();
    }
    Species h = Species("food");
    Creature h1 = Creature(h, west);
    board[4][4] = h1;
    ASSERT_TRUE(board[4][4].is_creature());
    board[4][4].remove();
    ASSERT_FALSE(board[4][4].is_creature());
}

// ----------
// DarwinTest
// ----------

TEST(DarwinTest, darwin_1) {
    Darwin d = Darwin(10, 10);
    int s = d.board.size();
    ASSERT_EQ(s, 10);
}

TEST(DarwinTest, darwin_2) {
    Darwin d = Darwin(7, 25);
    int r_size = d.board.size();
    int c_size = d.board[0].size();
    ASSERT_EQ(r_size, 7);
    ASSERT_EQ(c_size, 25);

}

TEST(DarwinTest, darwin_3) {
    Darwin d = Darwin(50, 3);
    int r_size = d.board.size();
    int c_size = d.board[0].size();
    ASSERT_EQ(r_size, 50);
    ASSERT_EQ(c_size, 3);
}

TEST(DarwinTest, add_creature_1) {
    Darwin d = Darwin(7, 7);
    Species t = Species("trap");
    Creature t1 = Creature(t, south);
    d.addCreature(t1, 0, 0);
    Creature temp = d.at(0, 0);
    ASSERT_TRUE(temp.is_creature());
    ASSERT_EQ(t1, temp);
}

TEST(DarwinTest, add_creature_2) {
    Darwin d = Darwin(10, 10);
    Species f = Species("food");
    Creature f1 = Creature(f, north);
    d.addCreature(f1, 2, 2);
    Creature temp = d.at(2, 2);
    ASSERT_TRUE(temp.is_creature());
    ASSERT_EQ(f1, temp);
}

TEST(DarwinTest, add_creature_3) {
    Darwin d = Darwin(10, 10);
    Species f = Species("food");
    Creature f1 = Creature(f, north);

    Species h = Species("hopper");
    Creature h1 = Creature(h, east);

    Species r = Species("rover");
    Creature r1 = Creature(r, west);
    Creature r2 = Creature(r, west);
    d.addCreature(f1, 1, 1);
    d.addCreature(h1, 3, 4);
    d.addCreature(r1, 5, 7);

    ASSERT_EQ(d.at(1, 1), f1);
    ASSERT_EQ(d.at(3, 4), h1);
    ASSERT_EQ(d.at(5, 7), r1);

    ASSERT_FALSE(d.at(0, 0).is_creature());

}

TEST(DarwinTest, at_1) {
    Darwin d = Darwin(8, 8);
    Species f = Species("food");
    Creature f1 = Creature(f, north);
    d.addCreature(f1, 1, 1);
    ostringstream w;
    d.at(1, 1).print_species(w);
    ASSERT_EQ("f", w.str());
}

TEST(DarwinTest, at_2) {
    Darwin d = Darwin(8, 8);
    Species f = Species("food");
    Creature f1 = Creature(f, north);
    d.addCreature(f1, 1, 1);
    Species h = Species("hop");
    Creature h1 = Creature(h, south);
    d.addCreature(h1, 3, 5);
    Creature h2 = Creature(h, south);
    d.addCreature(h2, 1, 5);

    ASSERT_EQ(d.at(1, 1), f1);
    ASSERT_EQ(d.at(3, 5), h1);
    ASSERT_EQ(d.at(1, 5), h2);

}

TEST(DarwinTest, at_3) {
    Darwin d = Darwin(8, 8);
    ostringstream w;
    d.at(0, 0).print_species(w);
    ASSERT_EQ("", w.str());
}

TEST(DarwinTest, const_at_1) {
    Darwin d = Darwin(8, 8);
    ostringstream w;
    const Creature result = d.at(0, 0);
    ASSERT_TRUE(true);
}

TEST(DarwinTest, begin_1) {
    Darwin d = Darwin(8, 8);
    Species f = Species("food");
    Creature f1 = Creature(f, north);
    d.addCreature(f1, 0, 0);
    vector<vector<Creature>>::iterator row = d.begin();
    Creature result = *((*row).begin());
    ASSERT_EQ(result, f1);
}

TEST(DarwinTest, begin_2) {
    Darwin d = Darwin(8, 8);
    Species f = Species("food");
    Creature f1 = Creature(f, north);
    d.addCreature(f1, 0, 1);
    vector<vector<Creature>>::iterator row = d.begin();
    vector<Creature>::iterator result = (*row).begin();
    ++result; 
    Creature temp = *result; 
    ASSERT_EQ(temp, f1);
}

TEST(DarwinTest, begin_3) {
    Darwin d = Darwin(2, 2);
    Species f = Species("food");
    Creature f1 = Creature(f, north);
    d.addCreature(f1, 1, 0);
    vector<vector<Creature>>::iterator row = d.begin() + 1;
    Creature result = *((*row).begin());
    ASSERT_EQ(result, f1);
}

TEST(DarwinTest, const_begin_1) {
    Darwin d = Darwin(8, 8);
    Species f = Species("food");
    Creature f1 = Creature(f, north);
    d.addCreature(f1, 0, 0);
    const vector<vector<Creature>>::iterator row = d.begin();
    Creature result = *((*row).begin());
    ASSERT_EQ(result, f1);
}

// TEST(DarwinTest, const_begin_2) {
//     Darwin d = Darwin(8, 8);
//     Species f = Species("food");
//     Creature f1 = Creature(f, north);
//     d.addCreature(f1, 0, 1);
//     const vector<vector<Creature>>::iterator row = d.begin();
//     const vector<Creature>::iterator result = (*row).begin();
//     try {
//         result = result+1;
//         FAIL();
//     }
//     catch (const std::exception& ex) {
//         ASSERT_TRUE(true);
//     }
// }

// TEST(DarwinTest, const_begin_3) {
//     Darwin d = Darwin(2, 2);
//     Species f = Species("food");
//     Creature f1 = Creature(f, north);
//     d.addCreature(f1, 1, 0);
//     vector<vector<Creature>>::iterator row = d.begin() + 1;
//     Creature result = *((*row).begin());
//     ASSERT_EQ(result, f1);
// }

TEST(DarwinTest, end_1) {
    Darwin d = Darwin(8, 8);
    Species h = Species("hopper");
    Creature h1 = Creature(h, south);
    d.addCreature(h1, 7, 7);
    vector<vector<Creature>>::iterator row = d.end() -1 ;
    vector<Creature>::iterator col = (*row).end() -1; 
    Creature result = *(col);
    ASSERT_EQ(result, h1);
}

TEST(DarwinTest, end_2) {
    Darwin d = Darwin(3, 5);
    Species f = Species("food");
    Creature f1 = Creature(f, south);
    d.addCreature(f1, 2, 3);
    vector<vector<Creature>>::iterator row = d.end() -1 ;
    vector<Creature>::iterator col = (*row).end() -2; 
    Creature result = *(col);
    ASSERT_EQ(result, f1);
}

TEST(DarwinTest, end_3) {
    Darwin d = Darwin(10, 10);
    Species h = Species("hopper");
    Creature h1 = Creature(h, south);
    d.addCreature(h1, 9, 0);
    vector<vector<Creature>>::iterator row = d.end() -1 ;
    vector<Creature>::iterator col = (*row).end() -10; 
    Creature result = *(col);
    ASSERT_EQ(result, h1);
}

TEST(DarwinTest, const_end_1) {
    Darwin d = Darwin(8, 8);
    Species h = Species("hopper");
    Creature h1 = Creature(h, south);
    d.addCreature(h1, 7, 7);
    const vector<vector<Creature>>::iterator row = d.end() -1 ;
    const vector<Creature>::iterator col = (*row).end() -1; 
    Creature result = *(col);
    ASSERT_EQ(result, h1);
}

TEST(DarwinTest, turn_1) {
    Darwin d = Darwin(10, 10);
    Species h = Species("hopper");
    h.addInstruction("hop");
    h.addInstruction("go 0");

    Creature h1 = Creature(h, south);
    d.addCreature(h1, 0, 0);

    ASSERT_EQ(d.at(0, 0), h1);
    d.turn();

    ostringstream w;
    d.at(1, 0).print_species(w);
    ASSERT_EQ("h", w.str());
}

TEST(DarwinTest, turn_2) {
    Darwin d = Darwin(10, 10);
    Species h = Species("hopper");
    h.addInstruction("hop");
    h.addInstruction("go 0");

    Creature h1 = Creature(h, south);
    d.addCreature(h1, 0, 0);

    ASSERT_EQ(d.at(0, 0), h1);
    d.turn();

    ostringstream w;
    d.at(1, 0).print_species(w);
    ASSERT_EQ("h", w.str());

    w.str("");
    w.clear();
    d.turn();
    d.at(2, 0).print_species(w);
    ASSERT_EQ("h", w.str());
}


TEST(DarwinTest, turn_3) {
    Darwin d = Darwin(10, 10);
    Species h = Species("hopper");
    h.addInstruction("hop");
    h.addInstruction("go 0");

    Creature h1 = Creature(h, south);
    d.addCreature(h1, 0, 0);

    ASSERT_EQ(d.at(0, 0), h1);
    d.turn();

    ostringstream w;
    d.at(1, 0).print_species(w);
    ASSERT_EQ("h", w.str());

    w.str("");
    w.clear();
    d.turn();
    d.at(2, 0).print_species(w);
    ASSERT_EQ("h", w.str());

    w.str("");
    w.clear();
    d.turn();
    d.at(3, 0).print_species(w);
    ASSERT_EQ("h", w.str());
}

TEST(DarwinTest, print_1) {
    Darwin d = Darwin(8, 8);
    ostringstream w;
    Species f = Species("food");
    f.addInstruction("left");
    f.addInstruction("go 0");

    Species h = Species("hopper");
    h.addInstruction("hop");
    h.addInstruction("go 0");

    Creature f1 = Creature(f, east);
    Creature h1 = Creature(h, north);
    Creature h2 = Creature(h, east);
    Creature h3 = Creature(h, south);
    Creature h4 = Creature(h, west);
    Creature f2 = Creature(f, north);

    d.addCreature(f1, 0, 0); 
    d.addCreature(h1, 3, 3);
    d.addCreature(h2, 3, 4);
    d.addCreature(h3, 4, 4);
    d.addCreature(h4, 4, 3);
    d.addCreature(f2, 7, 7);

    d.turn();
    d.print(w);

    string result = "  01234567\n0 f.......\n1 ........\n2 ...h....\n3 .....h..\n4 ..h.....\n5 ....h...\n6 ........\n7 .......f\n";
    ASSERT_EQ(result, w.str());
}

TEST(DarwinTest, print_2) {
    Darwin d = Darwin(8, 8);
    ostringstream w;
    Species f = Species("food");
    f.addInstruction("left");
    f.addInstruction("go 0");

    Species h = Species("hopper");
    h.addInstruction("hop");
    h.addInstruction("go 0");

    Creature f1 = Creature(f, east);
    Creature h1 = Creature(h, north);
    Creature h2 = Creature(h, east);
    Creature h3 = Creature(h, south);
    Creature h4 = Creature(h, west);
    Creature f2 = Creature(f, north);

    d.addCreature(f1, 0, 0); 
    d.addCreature(h1, 3, 3);
    d.addCreature(h2, 3, 4);
    d.addCreature(h3, 4, 4);
    d.addCreature(h4, 4, 3);
    d.addCreature(f2, 7, 7);

    d.turn();
    d.turn();
    d.turn();

    d.print(w);
    string result = "  01234567\n0 f..h....\n1 ........\n2 ........\n3 .......h\n4 h.......\n5 ........\n6 ........\n7 ....h..f\n";
    ASSERT_EQ(result, w.str());
}

TEST(DarwinTest, print_3) {
    Darwin d = Darwin(15, 15);
    ostringstream w;
    d.print(w);
    string result = "  012345678901234\n0 ...............\n1 ...............\n2 ...............\n3 ...............\n4 ...............\n5 ...............\n6 ...............\n7 ...............\n8 ...............\n9 ...............\n0 ...............\n1 ...............\n2 ...............\n3 ...............\n4 ...............\n";
    ASSERT_EQ(result, w.str());
}

TEST(DarwinTest, simulation_1) {
    Darwin d = Darwin(3, 3);
    ostringstream w;
    d.simulation(1, w);

    string result = "Turn = 0.\n  012\n0 ...\n1 ...\n2 ...\n\nTurn = 1.\n  012\n0 ...\n1 ...\n2 ...\n\n";
    ASSERT_EQ(result, w.str());
}

TEST(DarwinTest, simulation_2) {
    Darwin d = Darwin(8, 8);
    ostringstream w;

    Species f = Species("food");
    f.addInstruction("left");
    f.addInstruction("go 0");

    Species h = Species("hopper");
    h.addInstruction("hop");
    h.addInstruction("go 0");

    Creature f1 = Creature(f, east);
    Creature h1 = Creature(h, north);
    Creature h2 = Creature(h, east);
    Creature h3 = Creature(h, south);
    Creature h4 = Creature(h, west);
    Creature f2 = Creature(f, north);

    d.addCreature(f1, 0, 0); 
    d.addCreature(h1, 3, 3);
    d.addCreature(h2, 3, 4);
    d.addCreature(h3, 4, 4);
    d.addCreature(h4, 4, 3);
    d.addCreature(f2, 7, 7);

    d.simulation(3, w);
    string result = "Turn = 0.\n  01234567\n0 f.......\n1 ........\n2 ........\n3 ...hh...\n4 ...hh...\n5 ........\n6 ........\n7 .......f\n\nTurn = 1.\n  01234567\n0 f.......\n1 ........\n2 ...h....\n3 .....h..\n4 ..h.....\n5 ....h...\n6 ........\n7 .......f\n\nTurn = 2.\n  01234567\n0 f.......\n1 ...h....\n2 ........\n3 ......h.\n4 .h......\n5 ........\n6 ....h...\n7 .......f\n\nTurn = 3.\n  01234567\n0 f..h....\n1 ........\n2 ........\n3 .......h\n4 h.......\n5 ........\n6 ........\n7 ....h..f\n\n";
    ASSERT_EQ(result, w.str());
}

TEST(DarwinTest, simulation_3) {
    Darwin d = Darwin(7, 9);
    ostringstream w;

    Species h = Species("hopper");
    h.addInstruction("hop");
    h.addInstruction("go 0");

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

    Creature t1 = Creature(t, south);
    Creature h1 = Creature(h, east);
    Creature r1 = Creature(r, north);
    Creature t2 = Creature(t, west);

    d.addCreature(t1, 0, 0);
    d.addCreature(h1, 3, 2);
    d.addCreature(r1, 5, 4);
    d.addCreature(t2, 6, 8);

    d.simulation(3, w);
    string result = "Turn = 0.\n  012345678\n0 t........\n1 .........\n2 .........\n3 ..h......\n4 .........\n5 ....r....\n6 ........t\n\nTurn = 1.\n  012345678\n0 t........\n1 .........\n2 .........\n3 ...h.....\n4 ....r....\n5 .........\n6 ........t\n\nTurn = 2.\n  012345678\n0 t........\n1 .........\n2 .........\n3 ....r....\n4 ....r....\n5 .........\n6 ........t\n\nTurn = 3.\n  012345678\n0 t........\n1 .........\n2 .........\n3 ....rr...\n4 .........\n5 .........\n6 ........t\n\n";
    ASSERT_EQ(result, w.str());

}


