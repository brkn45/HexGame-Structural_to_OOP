#include "base.h"

void set_board(int board[][12]){ // board fill two
    int i=0,k=0;

    for(i=0;i<12;i++){
        for(k=0;k<12;k++){
            board[i][k]=DOT;
        }
    }
}
void print_board(const int board[][12],const int size){ // print board
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
    decltype(check_board(board,X,size)) flag=0,out=1;
    char name[20],filename[20];
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
            cin>>name;
            if((name[0]=='L' || name[0]=='l') && (name[1]=='O' || name[1]=='o') && (name[2]=='A' || name[2]=='a') &&
            (name[3]=='D' || name[3]=='d')){
                cin>>filename;
                load_game(board,size,filename,O);
                print_board(board,size);
            }
            else if((name[0]=='S' || name[0]=='s') && (name[1]=='A' || name[1]=='a') && (name[2]=='V' || name[2]=='v') &&
            (name[3]=='E' || name[3]=='e')){
                cin>>filename;
                save_game(board,size,filename,O);
            }
            else{
                letter=name[0];
                move_x=name[1] -48; // translate an integer number
                
                if(move_x<size && move_x>=0 && letter>=65 && letter<(65+size) ){
                    move_y=convert_let_to_num(letter,size);
                    if(board[move_x][move_y]==DOT){
                        board[move_x][move_y]= O;
                        out=0;
                    }    
                    else
                        cerr<<"Wrong Entry"<<endl;    
                }
                else
                     cerr<<"Wrong Entry"<<endl;
                }
            
        }while( out);
        out=1;
        
        
        flag=check_board(board,O,size);
        if(flag==1){
            print_board(board,size);
            cout<<"Winner is User (O)"<<endl;
            break;
        }
    }    
    
}
bool load_game(int board[][12],int &size,const char name[],const bool & tips){
    ifstream file;
	int out=5; 
	int i=0,k=0,turn=2;
    
	file.open(name);
	
	if(file.is_open()){
        cout<<"out:"<<out<<endl;
        file >> size;
	    for(i=0;i<12;i++){
		    for(k=0;k<12;k++){
			    file>>board[i][k];
            }
    
        }  
        file>>turn;
        
        return  tips==turn;
    file.close();
    cout<<"File "<<name<< "Loaded"<<endl;
    }
    else{
        cerr<< "There arent name "<<name<<"file"<<endl;
        return 1;
    }
    
}
void save_game(const int board[][12],const int size,const char name[],const bool &tips){
    ofstream file;
	
	int i=0,k=0;
	
	
	file.open(name);
    file << " "<< size <<endl;
    
	for(i=0;i<12;i++){
		for(k=0;k<12;k++){
            file<<" "<<board[i][k]<<" ";
		}
		file<<endl;
	}
    file<<tips;
    file.close();
    cout <<"File"<<name<<" Saved"<<endl;
}
void computer_move(int board[][12],int size,int start_x,int start_y){ 
    auto i=0;
    decltype(check_board_near(board,size)) flag;
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
    char letter,name[20],filename[20];
    auto flag=0,out=1;

    while(1){
        
        do{
            cout<<"Please Enter Number and Letter for X"<<endl;
            cin>>name;
            if((name[0]=='L' || name[0]=='l') && (name[1]=='O' || name[1]=='o') && (name[2]=='A' || name[2]=='a') &&
            (name[3]=='D' || name[3]=='d')){
                cin>>filename;
                out=load_game(board,size,filename,X);
                if(out==1)
                    print_board(board,size);
            }
            else if((name[0]=='S' || name[0]=='s') && (name[1]=='A' || name[1]=='a') && (name[2]=='V' || name[2]=='v') &&
            (name[3]=='E' || name[3]=='e')){
                cin>>filename;
                save_game(board,size,filename,X);
            }
            else{
                letter=name[0];
                move_x=name[1] -48; // translate an integer number
                
                if(move_x<size && move_x>=0 && letter>=65 && letter<(65+size) ){
                    move_y=convert_let_to_num(letter,size);
                    if(board[move_x][move_y]==2){
                        out=0;
                        board[move_x][move_y]= X;
                    }    
                    else
                        cout<<"Wrong Entry"<<endl;    
                }
                else
                     cout<<"Wrong Entry"<<endl;
                }
        }while( out);
        out=1;
        
        print_board(board,size);
        flag=check_board(board,X,size);
        if(flag==1)
            break;
        
        
        do{
            cout<<"Please Enter Number and Letter for O"<<endl;
            cin>>name;
            if((name[0]=='L' || name[0]=='l') && (name[1]=='O' || name[1]=='o') && (name[2]=='A' || name[2]=='a') &&
            (name[3]=='D' || name[3]=='d')){
                cin>>filename;
                out=load_game(board,size,filename,O);
                if(out==1)
                    print_board(board,size);
            }
            else if(  (name[0]=='S' || name[0]=='s') && (name[1]=='A' ||  name[1]=='a') && (name[2]=='V' || name[2]=='v') &&  (name[3]=='E' || name[3]=='e')){
                cin>>filename;
                save_game(board,size,filename,O);
            }
            else{
                letter=name[0];
                move_x=name[1] -48; // translate an integer number
                
                if(move_x<size && move_x>=0 && letter>=65 && letter<(65+size) ){
                    move_y=convert_let_to_num(letter,size);
                    if(board[move_x][move_y]==2){
                        out=0;
                        board[move_x][move_y]= O;
                    }
                    else
                        cout<<"Wrong Entry"<<endl;    
                }
                else
                     cout<<"Wrong Entry"<<endl;
                }

        }while( out);
        out=1;
       
        print_board(board,size);
        flag=check_board(board,O,size);
        if(flag==1)
            break;
    }
}
int convert_let_to_num(const char letter,const int size){
    const char alphabet[] = {'A','B','C','D','E','F','G','H','I','J','K','L'};
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


