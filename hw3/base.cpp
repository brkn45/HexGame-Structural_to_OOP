#include "base.h"


int Hex::compare(const Hex & other1,const Hex & other2)const{
    return other1.get_turn_num() > other2.get_turn_num();
}
void Hex::playGame(){
    int type=0;
    
    
            //game[game_num].print_board();
    cout<<"please Select game tips"<<endl<<"1)User - user "<<endl<<"2)User - Pc" <<endl;
    cin>>type;
    if(1==type)
        user_user();
        
    else if(2==type){
        user_pc();
    }
    else
        cerr<<"Wrong choice"<<endl;
}
void Hex::set_board(){ // board fill two
    int i=0,k=0;

    for(i=0;i<size;i++){
        for(k=0;k<size;k++){
            hexCells[i][k].set_row(i);
            hexCells[i][k].set_colum(k);
            hexCells[i][k].set_shape(DOT);
        }
    }
}
void Hex::build_board(){
    int i=0,k=0;
    for(i=0;i<size;i++){
        for(k=0;k<size;k++){
        min_hex.push_back(berkan);
     }
    hexCells.push_back(min_hex);
    }
    
    
    
    
}
void  Hex::print_board(){ // print board
    int i=0,k=0,blank=0;
    
    
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
            
            if(hexCells[i][k].get_shape()==2){
                cout<<" . ";
            }
            else if(hexCells[i][k].get_shape()==X){
                cout<<" X ";
            }
            else if(hexCells[i][k].get_shape()==O){
                cout<<" O ";
            }
            
        }
        cout<<endl;
    }
}
void  Hex::user_pc(){
    int move_x,move_y,i=0;
    char letter;
    decltype(check_board(X)) flag=0,out=1;
    char name[20],filename[20];
    print_board();
    while(1){
        do{
            cout<<"Please Enter Number and Letter for O. (write EXIT to return menu ) "<<endl;

            cin>>name;
            if(name[0]=='E' && name[1]=='X' && name[2]=='I' && name[3]=='T'){
                return;
            }
           out =play(name,O);
            
        }while( out);
        out=1;
        turn_num++;
        setTurn();
        
        flag=check_board(O);
        if(flag==1){
            print_board();
            cout<<"Winner is User (O)"<<endl;
            return; // function that returns if the game ended.
        }
        play();
        turn_num++;
        setTurn();
        print_board();
        flag=check_board(X);
        if(flag==1){
            cout<<"Winner is Computer(X) "<<endl;
            return; // function that returns if the game ended.
        }


    }    
    
}
bool  Hex::load_game(const char name[],const bool & tips){
    ifstream file;
	int out=5,shape=0; 
	int i=0,k=0,turn=2;
    
	file.open(name);
	
	if(file.is_open()){
        //cout<<"out:"<<out<<endl;
        file >>size;
        
	    for(i=0;i<size;i++){
		    for(k=0;k<size;k++){
			    file>>shape;
                hexCells[i][k].set_shape(shape);
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
void  Hex::save_game(const char name[],const bool &tips){
    ofstream file;
	
	int i=0,k=0;
	
	
	file.open(name);
    file << " "<< size <<endl;
    
	for(i=0;i<size;i++){
		for(k=0;k<size;k++){
            file<<" "<<hexCells[i][k].get_shape()<<" ";
		}
		file<<endl;
	}
    file<<tips;
    file.close();
    cout <<"File"<<name<<" Saved"<<endl;
}
int Hex::play(char name[20],int type){
     char filename[20],letter;
     int move_x=0,move_y=0,out=2;
            if((name[0]=='L' || name[0]=='l') && (name[1]=='O' || name[1]=='o') && (name[2]=='A' || name[2]=='a') &&
            (name[3]=='D' || name[3]=='d')){
                cin>>filename;
                load_game(filename,type);
                print_board();
            }
            else if((name[0]=='S' || name[0]=='s') && (name[1]=='A' || name[1]=='a') && (name[2]=='V' || name[2]=='v') &&
            (name[3]=='E' || name[3]=='e')){
                cin>>filename;
                save_game(filename,type);
            }
            else{
                letter=name[0];
                move_x=atoi(&name[1]); // translate an integer number
                
                if( move_x>=0 && move_x < size && letter>=65 && letter<(65+size) ){
                    move_y=convert_let_to_num(letter);
                    if(hexCells[move_x][move_y].get_shape()==DOT){
                        hexCells[move_x][move_y].set_shape(type);
                        out=0;
                        
                    }    
                    else
                        cerr<<"Wrong Entry"<<endl;    
                }
                else
                     cerr<<"Wrong Entry"<<endl;
                }
               
      return out;          
}
void  Hex::play(){ 
    auto i=0,start_x=3,start_y=3;
    decltype(check_board_near()) flag;
    static int move_x, move_y,first;
    flag=check_board_near();
    if(hexCells[start_x][start_y].get_shape()==DOT && flag==0){
        hexCells[start_x][start_y].set_shape(X);
        move_x=start_x;
        move_y=start_y;
        first=1;

        return;
    }
    else if(hexCells[move_x][move_y+1].get_shape()==DOT && flag==0){
        hexCells[move_x][move_y+1].set_shape(X);
        move_y++;
        return;
    }
    else if(hexCells[move_x-1][move_y+1].get_shape()==DOT && flag==0){
        hexCells[move_x-1][move_y+1].set_shape(X);
        move_x--;
        move_y++;
        return;
    }
    else if(hexCells[move_x+1][move_y].get_shape()==2 && flag==0){
        hexCells[move_x+1][move_y].set_shape(X);
        move_x++;
        return;
    }
    else if(hexCells[move_x-1][move_y].get_shape()==2 && flag==0){
        hexCells[move_x-1][move_y].set_shape(X);
        move_x--;
        return;
    }
     else if(flag==0){
        for(i=0;i<size;i++){
            if(hexCells[i][move_y].get_shape()==X && hexCells[i+1][move_y].get_shape()==DOT){
                hexCells[i+1][move_y].set_shape(X);
                move_x=i+1;
                break;
            }
            else if(hexCells[i][move_y].get_shape()==X && hexCells[i-1][move_y].get_shape()==DOT){
                hexCells[i-1][move_y].set_shape(X);
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
   
    if(hexCells[move_x][move_y-1].get_shape()==DOT && flag==1){
        hexCells[move_x][move_y-1].set_shape(X);
        move_y--;
        return;
    }
    else if(hexCells[move_x+1][move_y-1].get_shape()==DOT && flag==1){
        hexCells[move_x+1][move_y-1].set_shape(X);
        move_x++;
        move_y--;
        return;

    }
    else if(hexCells[move_x-1][move_y].get_shape()==DOT && flag==1){
        hexCells[move_x-1][move_y].set_shape(X);
        move_x--;
        return;
    }
    else if(hexCells[move_x+1][move_y].get_shape()==DOT && flag==1){
        hexCells[move_x+1][move_y].set_shape(X);
        move_x++;
        return;
    }
    else if(hexCells[move_x-1][move_y+1].get_shape()==2 && flag==1){
        hexCells[move_x-1][move_y+1].set_shape(X);
        move_x--;
        move_y++;
        return;
    }
    else if(hexCells[move_x][move_y+1].get_shape()==2 && flag==1){
        hexCells[move_x][move_y+1].set_shape(X);
        move_y++;
        return;
    }
    
    
}
bool  Hex::check_board_near(){
    int i=0;
    for(i=0;i<size;i++){
        if(hexCells[i][size-1].get_shape()==X)
            return 1;
    }
    return 0;
}

void  Hex::user_user(){
    int move_x,move_y;
    char letter,name[20],filename[20];
    auto flag=0,out=1;
    print_board();
    while(1){
        
        do{
            cout<<"Please Enter Number and Letter for X. (write EXIT to return menu ) "<<endl;

            cin>>name;
            if(name[0]=='E' && name[1]=='X' && name[2]=='I' && name[3]=='T'){
                return;
            }
            
            out=play(name,X);
        }while( out);
        out=1;
        
        turn_num++;
        setTurn();
        print_board();
        flag=check_board(X); 
        if(flag==1){
            cout<<"Game winner is X"<<endl;
            return; // function that returns if the game ended.
        }
            
        
        
        do{
            cout<<"Please Enter Number and Letter for O. (write EXIT to return menu ) "<<endl;

            cin>>name;
            if(name[0]=='E' && name[1]=='X' && name[2]=='I' && name[3]=='T'){
                return;
            }
            
            out=play(name,O);
        }while( out);
        out=1;
        turn_num++;
        setTurn();
        print_board();
        flag=check_board(O);
        if(flag==1){
            cout<<"Game winner is O"<<endl;
            return; // function that returns if the game ended.
        }
            
    }
}
int  Hex::convert_let_to_num(const char letter){
   
    int i=0;
    for(i=0;i<size;i++){
        if(letter==alphabet[i]){
            return i;
        }
    }
}
bool  Hex::check_board(int tips){ // if there ara O first line, program find other line recursive
    int i=0, k=0;
    bool flag=0;
    if(tips==O){
        for(k=0;k<size;k++){
            if(hexCells[i][k].get_shape()==O){
                flag=recuv_check_O(i,k,0,0);  
            }
        }

    }
    else if(tips==X ){
        for(i=0;i<size;i++){
            if(hexCells[i][k].get_shape()==X){
                flag=recuv_check_X(i,k,0,0);
            }
        }
    }
    return flag;    
    
}
bool Hex::recuv_check_X(int x,int y ,int counter,int turn){
    bool flag=0;
    if((y+1) < size && flag==0){
        if(hexCells[x][y+1].get_shape()==X   ){
            flag= recuv_check_X(x,y+1,counter+1,0);
        }
    }
    
    if((x-1) >= 0 && (y+1) < size && flag == 0){
        if(hexCells[x-1][y+1].get_shape()==X ){
            flag=  recuv_check_X(x-1,y+1,counter+1,0);
        }
    }
    if((x+1) < size  &&flag==0 && turn !=LEFT ){
        if(hexCells[x+1][y].get_shape()==X  ){
            flag=  recuv_check_X(x+1,y,counter,RIGHT);
        }
    }
    if((x-1) >= 0 && flag==0 && turn !=RIGHT){
        if (hexCells[x-1][y].get_shape() == X   ){
            flag= recuv_check_X(x-1,y,counter,LEFT);
        }
    }
    
    

    if((size-1)==counter || flag==1){
        return 1;
    }
    else 
        return 0;
}
bool  Hex::recuv_check_O(int x,int y,int counter,int turn ){ // 
    bool flag=0;
    if((x+1)<size  &&flag == 0){
        if( hexCells[x+1][y].get_shape()==O ){
            flag =recuv_check_O(x+1,y,counter +1,0);
        }
    }
    if( (x+1)< size && (y-1)>= 0 && flag==0 ){
        if(hexCells[x+1][y-1].get_shape()==O ){
            flag= recuv_check_O(x+1,y-1,counter +1,0);
        }
    }
    if( (y+1) <size && flag==0  && turn != LEFT){
        if(hexCells[x][y+1].get_shape()==O  ){ 
            flag=  recuv_check_O(x,y+1,counter,RIGHT);
        }
    }
    if((y-1) >=0 && flag==0 && turn !=RIGHT ){
        if (hexCells[x][y-1].get_shape() == O  ){
            flag =recuv_check_O(x,y-1,counter,LEFT);
    }
    }
    
    if((size-1)==counter || flag==1){
        return 1;
    }
    else 
        return 0;
}


