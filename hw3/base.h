
#include <iostream>
#include <fstream>
#include <vector>
#ifndef base
#define base
using namespace std;
enum shape{O,X,DOT};
enum direction{RIGHT=1,LEFT=2};


class Hex{
    public:
        Hex(int s_size);
        Hex();
        static int getTurn(){return turn;};
        static int setTurn(){turn++;};
        void set_board(); //set table every value 2, 2 represent (.) for print
        void print_board(); // print board
        void user_user(); // Game mode
        void user_pc(); // game mode
        bool check_board(int tips); // check the game finish or go on
        int convert_let_to_num(const char letter); // translate letter to number for game board. 
        bool recuv_check_X(int x,int y ,int counter,int turn=0);// check game finish for X
        bool recuv_check_O(int x,int y,int counter,int turn=0 ); // check game finish for O
        void play();// İnteligent computer move.
        int play(char name[20],int type);
        bool check_board_near();// if there are X one side , turn back the other side 
        bool load_game(const char name[],const  bool & tips ); // laod game 
        void save_game(const char name[],const bool & tips); // save game
        void set_size(int input){size=input; } // set size in private member
        int get_size() const {return size;}
        
        void build_board(); // full 
        void playGame();
        
        int get_turn_num()const { return turn_num;}
        int compare(const Hex & other1,const Hex & other2) const;
    private:
        int turn_num=0; // alone class marked cell
        int size;
        static int turn; // all class maeked cell
        const char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I','J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'V','W', 'X', 'Y', 'Z'};
        class Cell{
            public:
                
                
                void set_row(int x){row = x;}
                int get_row() const { return row;}
                void set_colum(int y){colum=y;}
                int get_colum() const { return colum;}
                inline void set_shape(int temp){shape =temp;} // set shape
                inline int get_shape() const{ return shape;} // get shape
                

            private:
                
                int row;
                int colum;
                int shape;

        
        };
    public:
        vector<vector<Cell> > hexCells; // fundamental vector
        vector <Cell> min_hex; //  helper class vector
        Cell berkan; // helper class

        // ı need reserve memory hexcell class so i use min_hex and berkan class.

}; 





#endif

