#ifndef BOTBASELINE
#define BOTBASELINE

#include <iostream>
#include <stdlib.h>
#include "config.h"
#include <vector>
#include <time.h>

Point check_win(int board_game[][WIDTH], int player_id);
Point defend(int board_game[][WIDTH], int player_id);
Point attack(int board_game[][WIDTH], int player_id);
Point check_n_tile(int board_game[][WIDTH], int player_id, int n);
Point player_father(int board_game[][WIDTH], int player_id);

// player_id = 1 || -1
Point player_rand(int board_game[][WIDTH], int player_id){
    Point p = player_father(board_game, player_id);
    if(p != Point(-1, -1)) return p;

    int row = HEIGHT/2, col = WIDTH/2;
    while(board_game[row][col] != 0){
        srand (time(NULL));
        row = rand() % HEIGHT;
        col = rand() % WIDTH;
    }

    return Point(row, col);
}

Point player_father(int board_game[][WIDTH], int player_id){
    //Point p = check_win(board_game, player_id);
    //if(p != Point(-1,-1)) return p;

    //p = defend(board_game, player_id);
    //if(p != Point(-1,-1)) return p;

    return attack(board_game, player_id);
}

Point check_win(int board_game[][WIDTH], int player_id){
    return check_n_tile(board_game, player_id, 4);
}

Point defend(int board_game[][WIDTH], int player_id){
    return check_n_tile(board_game, -1*player_id, 3);
}

Point attack(int board_game[][WIDTH], int player_id)
{
    for(int k = 4; k>0; k--){
        Point p = check_n_tile(board_game, player_id, k);
        if(p != Point(-1,-1)) return p;

        p = check_n_tile(board_game, -player_id, k);
        if(p != Point(-1,-1)) return p;
    }

    return Point(-1, -1);
}

Point check_n_tile(int board_game[][WIDTH], int player_id, int n)
{
    int score;
    int temp[HEIGHT][WIDTH];

    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            temp[i][j] = 0;
        }
    }

    score = 0;
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            if(board_game[i][j] == player_id) score++;
            if(score == n && j-score >=0 && board_game[i][j-score] == 0) temp[i][j-score]++;
            if(score == n && board_game[i][j] == 0) temp[i][j]++;
            if(board_game[i][j] != player_id) score = 0;
        }
        score = 0;
    }


    score = 0;
    for(int j=0; j<WIDTH; j++){
        for(int i=0; i<HEIGHT; i++){
            if(board_game[i][j] == player_id) score++;
            if(score == n && i-score >=0 && board_game[i-score][j] == 0) temp[i-score][j]++;
            if(score == n && board_game[i][j] == 0) temp[i][j]++;
            if(board_game[i][j] != player_id) score = 0;
        }
        score = 0;
    }

    score = 0;
    for(int k = 1 - WIDTH; k < HEIGHT; k++){
        for(int i = 0; i<HEIGHT; i++){
            int j = i-k;
            if(0> j || j>=WIDTH) continue;
            if(board_game[i][j] == player_id) score++;
            if(score == n && i-score >=0 && j-score >= 0 && board_game[i-score][j-score] == 0) temp[i-score][j-score]++;
            if(score == n && board_game[i][j] == 0) temp[i][j]++;
            if(board_game[i][j] != player_id) score = 0;
        }
        score = 0;
    }

    score = 0;
    for(int k = 0; k< WIDTH + HEIGHT - 1; k++){
        for(int i = 0; i<HEIGHT; i++){
            int j = k-i;
            if(0> j || j>=WIDTH) continue;
            if(board_game[i][j] == player_id) score++;
            if(score == n && i-score >=0 && j+score >= 0 && board_game[i-score][j+score] == 0) temp[i-score][j+score]++;
            if(score == n && board_game[i][j] == 0) temp[i][j]++;
            if(board_game[i][j] != player_id) score = 0;
        }
        score = 0;
    }

    int row = -1, col = -1;
    for(int i = 0; i<HEIGHT; i++){
        for(int j = 0; j<WIDTH; j++){
            if(temp[i][j] != 0){
                if(row == -1 || temp[row][col] < temp[i][j]) {
                    row = i;
                    col = j;
                }
            }
        }
    }

    if(row == -1) return Point(row, col);

    std::vector<Point> v;
    v.clear();
    for(int i = 0; i<HEIGHT; i++){
        for(int j = 0; j<WIDTH; j++){
            if(temp[row][col] == temp[i][j]) v.push_back(Point(i, j));
        }
    }

    srand (time(NULL));
    int res = rand()%v.size();

    return v[res];
}
#endif //BOT_TEAM_3
