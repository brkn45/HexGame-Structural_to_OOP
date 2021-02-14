#include <iostream>
#include <fstream>
#ifndef base
#define base
enum shape{O,X,DOT};
enum direction{RIGHT=1,LEFT=2};
//const int  O = 0;  // 0 represent (O), 1 represent (X), 2 Represent (.) 
//const int  X =1;
//const int EMPTY=2;
//const int RIGHT=1;
//const int  LEFT =2;

using namespace std;
void set_board(int board[][12]); //set table every value 2, 2 represent (.) for print
void print_board(const int board[][12],const int size); // print board
void user_user(int board[][12],int size); // Game mode
void user_pc(int board[][12],int size); // game mode
bool check_board(int board[][12],bool tips,int size); // check the game finish or go on
int convert_let_to_num(const char letter,const int size); // translate letter to number for game board. 
bool recuv_check_X(int board[][12],int x,int y, int size ,int counter,int turn=0);// check game finish for X
bool recuv_check_O(int board[][12],int x,int y,int size, int counter,int turn=0 ); // check game finish for O
void computer_move(int board[][12],int size,int start_x,int start_y);// İnteligent computer move.
bool check_board_near(int board[][12],int size);// if there are X one side , turn back the other side 
bool load_game(int board[][12],int & size,const char name[],const  bool & tips ); // laod game 
void save_game(const int board[][12],const int size,const char name[],const bool & tips); // save game

#endif