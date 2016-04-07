#include "gtest/gtest.h"

#include "Darwin.h"
#include <iostream>
#include <sstream>
#include <string>


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



