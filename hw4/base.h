
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

        Hex operator--(int); // postfix
        Hex operator-- (); // prefix
        friend  bool operator ==(const Hex & tmpGame1,const Hex & tmpGame2) ;
        friend istream& operator >>(istream& input,Hex &tmpGame);
        friend ofstream& operator <<(ofstream & output,const Hex & tmpGame) ;
        friend ifstream& operator>>(ifstream& input,Hex &tmpGame);
        friend ostream& operator <<(ostream & output,const Hex & tmpGame);
        Hex(int s_size);
        Hex();
        
        static int getTurn(){return turn;};
        static int setTurn(){turn++;};
        void set_board(); //set table every value 2, 2 represent (.) for print
        //void print_board(); // print board
        void user_user(); // Game mode
        void user_pc(); // game mode
        bool check_board(int tips); // check the game finish or go on
        int convert_let_to_num(const char letter); // translate letter to number for game board. 
        bool recuv_check_X(int x,int y ,int counter,int turn=0);// check game finish for X
        bool recuv_check_O(int x,int y,int counter,int turn=0 ); // check game finish for O
        Cell play();// İnteligent computer move.
        void play(Cell & temp); // set move
        bool check_board_near();// if there are X one side , turn back the other side 
        bool load_game(); // laod game 
        void save_game(); // save game
        void set_size(int input){size=input; } // set size in private member
        int get_size() const {return size;}
        
        void build_board(); // full 
        void playGame();
        int input_fun();
        int get_turn_num()const { return turn_num;}
        //int compare(const Hex & other1,const Hex & other2) const; // last compare function
        void undo(const  int& ,const int& ); // save game
        void test_print(); // my test fun for saved game
        void movement(Cell & temp,int & move_x,int & move_y,int type); //
        int turn_check_undo(int move_x,int move_y,int type); // check game 
        int score(int type); // return score

        
        
    private:
        int turn_num=0; // alone class marked cell
        int size;
        static int turn; // all class maeked cell
        const char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I','J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'V','W', 'X', 'Y', 'Z'};
        int *save_row=nullptr; // save movement row
        int  *save_colum=nullptr; // save movement colum
        int back; 
    public:
        Cell **hexCells=nullptr; // fundamental vector
        char name[20];
        char filename[20];
        //vector <Cell> min_hex; //  helper class vector
        //Cell berkan; // helper class

        // ı need reserve memory hexcell class so i use min_hex and berkan class.

        ~Hex();
        

}; 






#endif

