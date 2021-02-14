#include "base.h"

int main(){
    int board[12][12];
    int size=0;
    auto tips=0;
    auto flag=1;
    do{
        cout<<"Please Enter Size Number Between 6 - 12"<<endl;
        cin>>size;
        if(size <= 12 && size >= 6 )
            flag=0;
        else
            cerr<<"Wrong Number"<<endl;   

    }while(flag);
    
    set_board(board);
    
    print_board(board,size);
    cout<<"please Select game tips"<<endl<<"1)User - user "<<endl<<"2)User - Pc" <<endl;
    cin>>tips;
    if(1==tips)
        user_user(board,size);
    else if(2==tips){
        user_pc(board,size);
    }
    else
        cerr<<"Wrong choice"<<endl;


    return 0;
}           
