#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <deque>
using std::cout;
using std::endl;
using std::cin;
using std::cerr;
using std::ofstream;
using std::ifstream;
using std::vector;
using std::deque;
using std::string;
namespace HexGame{
    enum shape{O,X,DOT};
    enum direction{RIGHT=1,LEFT=2};
    
    class Cell{ // Board cells
            public:
                Cell():row(0),colum(0),shape(2){};
                Cell(const Cell& tmp);
                void operator=(const Cell &temp);
                void set_row(int x){row = x;}
                int get_row() const { return row;}
                void set_colum(int y){colum=y;}
                int get_colum() const { return colum;}
                void set_shape(int temp){shape =temp;} // set shape
                int get_shape() const{ return shape;} // get shape
            private:
                int row;
                int colum;
                int shape;
        };
    class AbstractHex{ // Base Class other  for drived class
        public:
            virtual void setSize(int & tSize)=0;
            virtual void reset()=0;
            virtual void print()=0;
            virtual void readFromFile(char *filename)=0;
            virtual void writeToFile(char *filename)=0;
            virtual Cell play()=0;
            virtual void play(Cell & temp ) =0;
            virtual int operator()(int,int)=0;
            virtual int getSize() =0;
            virtual bool isEnd(int ,int ,int)=0;
            
            bool operator==(AbstractHex &); // no pure becuse drived class compera two obje
            virtual Cell lastMove(AbstractHex &); //no pure becuse drived class compera two obje
            virtual Cell getLastCell()=0;
            virtual void setLastCell(Cell & tmp)=0;
            virtual int numberOfMoves() =0;
            
        private:
            
    };

    class HexVector : public AbstractHex {
        public:
            std::vector <std::vector <Cell>> vecCell; // board cell

            HexVector(int size,Cell tmp):size(size),last(tmp){};
            HexVector():size(5),last(){};
            //HexVector(HexVector& );
            //~HexVector();
            void setSize(int & tSize){size=tSize;}
            int getSize(){return size;}
            void reset(); // redraw boardd 
            void print();
            void playGame(); // start game
            void userUser(); // Play User vs User
            void userPc();  // Play user ve Pc
            Cell play(); //  computer movement
            void movement(Cell & temp,int &move_x,int& move_y,int type);
            void play(Cell & temp); // movement
            int input_fun(); //  input commmit 
            bool isEnd(int move_x,int move_y,int type); // game is end return true
            int convert_let_to_num(const char &letter);  // convert letter to num
            bool recuv_check_O(int x,int y ,int counter,int turn);// game end controll
            bool recuv_check_X(int x,int y ,int counter,int turn); // game end controll
            bool check_board(int tips); // game and controll
            bool check_board_near(); // if computer movement contoll
            void writeToFile(char *filename); // write file
            void readFromFile(char *filename); // read file
            int operator()(int ,int ); // return cell content 
            const char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I','J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'V','W', 'X', 'Y', 'Z'};
            int numberOfMoves();
            Cell getLastCell(){return last;} // helper function
            void setLastCell(Cell & tmp){last=tmp;} // set take last move
            
        private:
            int size;
            char name[20];
            
            Cell last; // take last move content

    };
    // same functions Hexvector class
    class HexArray1D : public AbstractHex {
        public:
            HexArray1D():size(5),last(){};
            HexArray1D(int size,Cell tmp): size(size),last(tmp){};
            HexArray1D(HexArray1D & );
            void operator=(HexArray1D &);
            ~HexArray1D();
            Cell * arrCell=nullptr;
            void setSize(int & tSize){size=tSize;}
            int getSize(){return size;}
            void reset();
            void print();
            void playGame();
            void userUser();
            void userPc();
            int input_fun();
            void movement(Cell & temp,int &move_x,int& move_y,int type);
            void play(Cell & temp);
            int  convert_let_to_num(const char & letter);
            int operator()(int ,int );
            bool check_board(int tips);
            bool recuv_check_O(int x,int y,int counter,int turn);
            bool recuv_check_X(int x,int y,int counter,int turn);
            Cell play();
            void writeToFile(char *filename);
            void readFromFile(char *filename) ; 
            bool isEnd(int move_x,int move_y,int type);
            int numberOfMoves();
            const char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I','J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'V','W', 'X', 'Y', 'Z'};
            Cell getLastCell(){return last;}
            
            void setLastCell(Cell & tmp){last=tmp;}
            
        private:
            int size;
            char name[10];
            
            Cell last;
    };
    // same function HexVector Class
    template<typename T>
    class HexAdapter : public AbstractHex{
        public:
            HexAdapter() :size(5), last() {};
            HexAdapter(int size,Cell last): size(size),last(last){};
            
            T adapCell;
            
            void setSize(int & tSize){size=tSize;}
            int getSize(){return size;}
            void reset();
            void print();
            void playGame();
            void userUser();
            void userPc();
            Cell play();
            void movement(Cell & temp,int &move_x,int& move_y,int type);
            void play(Cell & temp);
            int input_fun();
            int convert_let_to_num(const char &letter);
            bool recuv_check_O(int x,int y ,int counter,int turn);
            bool recuv_check_X(int x,int y ,int counter,int turn);
            bool check_board(int tips);
            bool check_board_near();
            void writeToFile(char *filename);
            void readFromFile(char *filename);
            int operator()(int ,int );
            bool isEnd(int,int ,int );
            int numberOfMoves();
            const char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I','J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'V','W', 'X', 'Y', 'Z'};
            Cell getLastCell(){return last;}
            void setLastCell(Cell & tmp){last=tmp;}
        private:
            int size;
            char name[20];
            
            Cell last;
    };
    class OpenFile{ // control reading and writing file 
        public:
            OpenFile();
            OpenFile(string theMessage): message(theMessage) {} 
            string getMessage() {return message;}
        private :
            string message;        
    };
    class LastMoveError{ // control last move
        public:
            LastMoveError();
            LastMoveError(string theMessage): message(theMessage) {} 
            string getMessage() {return message;}
        private :
            string message;        
    };
    class FalseGame{ // global function control game
         public:
            FalseGame();
            FalseGame(string theMessage): message(theMessage) {} 
            string getMessage() {return message;}
        private :
            string message;        
    };
    

    



}

#endif 
