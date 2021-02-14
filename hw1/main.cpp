#include <iostream>
#define O 0  // 0 represent (O), 1 represent (X), 2 Represent (.) 
#define  X 1
#define RIGHT 1
#define LEFT 2
// Oyundaki hamle sayısı kontrol edilecek
using namespace std;
void set_board(int board[][12],int size); //set table every value 2, 2 represent (.) for print
void print_board(int board[][12],int size); // print board
void user_user(int board[][12],int size); // Game mode
void user_pc(int board[][12],int size); // game mode
bool check_board(int board[][12],bool tips,int size); // check the game finish or go on
int convert_let_to_num(char letter,int size); // translate letter to number for game board. 
bool recuv_check_X(int board[][12],int x,int y, int size ,int counter,int turn);// check game finish for X
bool recuv_check_O(int board[][12],int x,int y,int size, int counter,int turn ); // check game finish for O
void computer_move(int board[][12],int size,int start_x,int start_y);// İnteligent computer move.
bool check_board_near(int board[][12],int size);// if there are X one side , turn back the other side 
int main(){
    int board[12][12];
    int size,tips=0;
    bool flag=1;
    do{
        cout<<"Please Enter Size Number Between 6 - 12"<<endl;
        cin>>size;
        if(size <= 12 && size >= 6 )
            flag=0;
        else
            cout<<"Wrong Number"<<endl;   

    }while(flag);
    
    set_board(board,size);
    
    print_board(board,size);
    cout<<"please Select game tips"<<endl<<"1)User - user "<<endl<<"2)User - Pc" <<endl;
    cin>>tips;
    if(1==tips)
        user_user(board,size);
    else if(2==tips){
        user_pc(board,size);
    }
    else
        cout<<"Wrong choice"<<endl;


    return 0;
}           

void set_board(int board[][12],int size){ // board fill two
    int i=0,k=0;

    for(i=0;i<size;i++){
        for(k=0;k<size;k++){
            board[i][k]=2;
        }
    }
}
void print_board(int board[][12],int size){ // print board
    int i=0,k=0,blank=0;
    
    char alphabet[] = {'A','B','C','D','E','F','G','H','I','J','K','L'};
    cout<<endl<<"    ";
    while (blank<size) {
        
        cout<<"  "<<alphabet[blank];
        blank++;
    }
    blank=0;
    cout<<endl;
    for(i=0;i<size;i++){
         
         while(blank < (i+2)){
            cout<<" ";
            blank++;
        }
        blank=0;
        cout<<" "<<i<<" ";
        for(k=0;k<size;k++){
            
            if(board[i][k]==2){
                cout<<" . ";
            }
            else if(board[i][k]==X){
                cout<<" X ";
            }
            else if(board[i][k]==O){
                cout<<" O ";
            }
            
        }
        cout<<endl;
    }
}
void user_pc(int board[][12],int size){
    int move_x,move_y,i=0,rand_x,rand_y;
    char letter;
    bool flag=0,out=1;
   
   rand_x=1;
   rand_y=5;;
    while(1){
        
       
        computer_move(board,size,rand_x,rand_y);
        print_board(board,size);
        flag=check_board(board,X,size);
        if(flag==1){
            cout<<"Winner is Computer(X) "<<endl;
            break;
        }
        
        do{
            cout<<"Please Enter Number and Letter for O"<<endl;
            cin>>letter;
            cin>>move_x;
            if(move_x<size && move_x>=0 && letter>=65 && letter<(65+size) ){
                move_y=convert_let_to_num(letter,size);
                if(board[move_x][move_y]==2)
                    out=0;
                else
                    cout<<"Wrong Entry"<<endl;    
            }
            else
                    cout<<"Wrong Entry"<<endl;
        }while( out);
        out=1;
        board[move_x][move_y]= O;
        
        flag=check_board(board,O,size);
        if(flag==1){
            print_board(board,size);
            cout<<"Winner is User (O)"<<endl;
            break;
        }
    }    
    
}
void computer_move(int board[][12],int size,int start_x,int start_y){ 
    int i=0;
    bool flag;
    static int move_x, move_y,first;
    flag=check_board_near(board,size);
    if(board[start_x][start_y]==2 && flag==0){
        board[start_x][start_y]=X;
        move_x=start_x;
        move_y=start_y;
        first=1;

        return;
    }
    else if(board[move_x][move_y+1]==2 && flag==0){
        board[move_x][move_y+1]=X;
        move_y++;
        return;
    }
    else if(board[move_x-1][move_y+1]==2 && flag==0){
        board[move_x-1][move_y+1]=X;
        move_x--;
        move_y++;
        return;
    }
    else if(board[move_x+1][move_y]==2 && flag==0){
        board[move_x+1][move_y]=X;
        move_x++;
        return;
    }
    else if(board[move_x-1][move_y]==2 && flag==0){
        board[move_x-1][move_y]=X;
        move_x--;
        return;
    }
     else if(flag==0){
        for(i=0;i<size;i++){
            if(board[i][move_y]==X && board[i+1][move_y]==2){
                board[i+1][move_y]=X;
                move_x=i+1;
                break;
            }
            else if(board[i][move_y]==X && board[i-1][move_y]==2){
                board[i-1][move_y]=X;
                move_x=i-1;
                break;
            }

        }
        return;
    }
    if(first==1 && flag==1){
        move_x=start_x;
        move_y=start_y;
        first=0;
    }
   
    if(board[move_x][move_y-1]==2 && flag==1){
        board[move_x][move_y-1]=X;
        move_y--;
        return;
    }
    else if(board[move_x+1][move_y-1]==2 && flag==1){
        board[move_x+1][move_y-1]=X;
        move_x++;
        move_y--;
        return;
    }
    else if(board[move_x-1][move_y]==2 && flag==1){
        board[move_x-1][move_y]=X;
        move_x--;
        return;
    }
    else if(board[move_x+1][move_y]==2 && flag==1){
        board[move_x+1][move_y]=X;
        move_x++;
        return;
    }
    else if(board[move_x-1][move_y+1]==2 && flag==1){
        board[move_x-1][move_y+1]=X;
        move_x--;
        move_y++;
        return;
    }
    else if(board[move_x][move_y+1]==2 && flag==1){
        board[move_x][move_y+1]=X;
        move_y++;
        return;
    }
    
    
}
bool check_board_near(int board[][12],int size){
    int i=0;
    for(i=0;i<size;i++){
        if(board[i][size-1]==X)
            return 1;
    }
    return 0;
}

void user_user(int board[][12],int size){
    int move_x,move_y;
    char letter;
    bool flag=0,out=1;
    while(1){
        cout<<"Please Enter Number and Letter for X"<<endl;
        do{
            cin>>letter;
            cin>>move_x;
            if((move_x<12 && move_x>=0 && letter>=65 && letter<=76)){
                move_y=convert_let_to_num(letter,size);
                if(board[move_x][move_y]==2)
                    out=0;
                else 
                    cout<<"Wrong Enter"<<endl;    
            }
        }while( out);
        out=1;
        board[move_x][move_y]= X;
        print_board(board,size);
        flag=check_board(board,X,size);
        if(flag==1)
            break;
        
        cout<<endl<<"Please Enter Number and Letter for O"<<endl;
        do{
            cin>>letter;
            cin>>move_x; if((move_x<12 && move_x>=0 && letter>=65 && letter<=76)){
                move_y=convert_let_to_num(letter,size);
                if(board[move_x][move_y]==2)
                    out=0;
                else 
                    cout<<"Wrong Enter"<<endl;    
            }

        }while( out);
        out=1;
        board[move_x][move_y]= O;
        print_board(board,size);
        flag=check_board(board,O,size);
        if(flag==1)
            break;
    }
}
int convert_let_to_num(char letter,int size){
    char alphabet[] = {'A','B','C','D','E','F','G','H','I','J','K','L'};
    int i=0;
    for(i=0;i<size;i++){
        if(letter==alphabet[i]){
            return i;
        }
    }
}
bool check_board(int board[][12] ,bool tips,int size){ // if there ara O first line, program find other line recursive
    int i=0, k=0;
    bool flag=0;
    if(tips==O){
        for(k=0;k<size;k++){
            if(board[i][k]==O){
                flag=recuv_check_O(board,i,k,size,0,0); 
            }
        }

    }
    else if(tips==X ){
        for(i=0;i<size;i++){
            if(board[i][k]==X){
                flag=recuv_check_X(board,i,k,size,0,0);
            }
        }
    }
    return flag;    
    
}
bool recuv_check_X(int board[][12],int x,int y, int size ,int counter,int turn){
    bool flag=0;
    if(board[x][y+1]==X && (y+1) < size && flag==0 ){
        flag= recuv_check_X(board,x,y+1,size,counter+1,0);
    }
    if(board[x-1][y+1]==X && (x-1) >= 0 && (y+1) < size && flag == 0){
        flag=  recuv_check_X(board,x-1,y+1,size,counter+1,0);
    }
    if(board[x+1][y]==X  && (x+1) < size  &&flag==0 && turn !=LEFT ){
        flag=  recuv_check_X(board,x+1,y,size,counter,RIGHT);
    }
    if (board[x-1][y] == X && (x-1) >= 0 && flag==0 && turn !=RIGHT  ){
        flag= recuv_check_X(board,x-1,y,size,counter,LEFT);
    }
    if((size-1)==counter || flag==1){
        return 1;
    }
    else 
        return 0;
}
bool recuv_check_O(int board[][12],int x,int y,int size,int counter,int turn ){ // 
    bool flag=0;
    
    if( board[x+1][y]==O && (x+1)<size  &&flag == 0){
        flag =recuv_check_O(board,x+1,y,size,counter +1,0);
    }
    if(board[x+1][y-1]==O && (x+1)< size && (y-1)>= 0 && flag==0 ){
        flag= recuv_check_O(board,x+1,y-1,size,counter +1,0);
    }
    if(board[x][y+1]==O  && (y+1) <size && flag==0  && turn != LEFT){ 
        flag=  recuv_check_O(board,x,y+1,size,counter,RIGHT);
    }
   if (board[x][y-1] == O && (y-1) >=0 && flag==0 && turn !=RIGHT  ){
        flag =recuv_check_O(board,x,y-1,size,counter,LEFT);
    }
    if((size-1)==counter || flag==1){
        return 1;
    }
    else 
        return 0;
}


