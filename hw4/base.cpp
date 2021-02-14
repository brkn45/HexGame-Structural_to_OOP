#include "base.h"
bool  operator == (const Hex & tmpGame1,const Hex & tmpGame2){
    return tmpGame1.get_turn_num() == tmpGame2.get_turn_num();
}
ifstream& operator>>(ifstream& input,Hex &tmpGame){
    int tmpSize;
    int i=0,k=0,type;
    input >>tmpSize;
        tmpGame.hexCells=new Hex::Cell*[tmpSize];
        for(i=0;i<tmpSize;i++)
            tmpGame.hexCells[i]=new Hex::Cell[tmpSize];
	    for(i=0;i<tmpSize;i++){
		    for(k=0;k<tmpSize;k++){
			    input>>type;
                tmpGame.hexCells[i][k].set_shape(type);
            }
    
        }
        return input; 
}
ofstream& operator <<(ofstream & output,const Hex & tmpGame) {
    int i=0,k=0;
    output << " "<< tmpGame.get_size() <<endl;
    
	for(i=0;i<tmpGame.get_size();i++){
		for(k=0;k<tmpGame.get_size();k++){
            output<<" "<<tmpGame.hexCells[i][k].get_shape()<<" ";
		}
		output<<endl;
	}
    
    return output;
}
istream& operator >>(istream& input,Hex& tmpGame){
    input>>tmpGame.name;
    
    return input;
    
}
ostream& operator <<(ostream & output,const Hex & tmpGame){
    int i=0,k=0,blank=0;
    output<<endl<<"    ";
    while (blank<tmpGame.get_size()) {
        
        output<<"  "<<tmpGame.alphabet[blank];
        blank++;
    }
    blank=0;
    output<<endl;
    for(i=0;i<tmpGame.get_size();i++){
         
         while(blank < (i+2)){
            output<<" ";
            blank++;
        }
        blank=0;
        output<<" "<<i<<" ";
        for(k=0;k<tmpGame.get_size();k++){
            
            if(tmpGame.hexCells[i][k].get_shape()==2){
                output<<" . ";
            }
            else if(tmpGame.hexCells[i][k].get_shape()==X){
                output<<" X ";
            }
            else if(tmpGame.hexCells[i][k].get_shape()==O){
                output<<" O ";
            }
            
        }
        output<<endl;
    }
    return output;
}
Hex Hex::operator--(int ignoreMe){
    int move_x,move_y;
    turn_num--;
    
    move_y=save_colum[turn_num];
    move_x=save_row[turn_num];
    hexCells[move_x][move_y].set_shape(DOT);
    
    
    //test_print();
    return *this;
    
    
} 
Hex Hex::operator-- (){
    int move_x,move_y;
    turn_num--;
    
    move_y=save_colum[turn_num];
    move_x=save_row[turn_num];
    hexCells[move_x][move_y].set_shape(DOT);
    
    
    //test_print();
    return *this;
} // prefix
/*int Hex::compare(const Hex & other1,const Hex & other2)const{
    return other1.get_turn_num() > other2.get_turn_num();
}*/
void Hex::test_print(){
    int i=0;
    for(i=0;i<turn_num;i++){
        cout<<"row:"<<save_row[i];
        cout<<"  colum:"<<save_colum[i]<<endl;
        
    }

}
void Hex::undo(const int& p_row,const int& p_colum){ // save movement to go to back
    int i=0;
    
    if(turn_num==1){
        save_row=new int[2];
        save_colum=new int[2];
        save_row[0]=p_row;
        save_colum[0]=p_colum;
        return;

    }
    int *tmp_r= new int[turn_num+1];
    int *tmp_c=new int[turn_num+1];
    for(i=0;i<turn_num;i++){
        tmp_r[i]=save_row[i];
        tmp_c[i]=save_colum[i];
    }
    save_row=tmp_r;
    save_colum=tmp_c;
    save_row[turn_num-1]=p_row;
    save_colum[turn_num-1]=p_colum;
    return;
}
void Hex::playGame(){
    int type=0;
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
    hexCells = new Hex::Cell*[size];
    for(int i = 0; i < size; ++i)
        hexCells[i] = new Cell[size];
    
    
    
    
}
/*void  Hex::print_board(){ // print board
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
}*/
void Hex::movement(Cell & temp,int & move_x,int & move_y,int type){ // make movement 
    char letter;
    letter=name[0];
    move_x=atoi(&name[1]);
    move_y=convert_let_to_num(letter);
    temp.set_row(move_x);
    temp.set_colum(move_y);
    temp.set_shape(type);
    return;
}
int Hex::turn_check_undo(int move_x,int move_y,int type){ // turn check and save movement
    int flag;
    Cell tmp;
    turn_num++;
    setTurn();
    
    flag=check_board(type);
    if(flag==1){
        if(type==O){
            cout<<*this;;
            cout<<"Winner is User (O)"<<endl;
            return flag; // function that returns if the game ended.
        }
        else if(type == X){
            cout<<*this;;
            cout<<"Winner is User (X)"<<endl;
            return flag; // function that returns if the game ended.
        }
        
    }
    
    
    
    undo(move_x,move_y);
    return flag;
}
void  Hex::user_pc(){
    int move_x,move_y,i=0,out=1;
    decltype(check_board(X)) flag=0;
    Cell tmp;
    cout<<*this; // print board
    
    while(1){
        do{
            cout<<"Please Enter Number and Letter for O. (write (EXIT) or write  (BACK) ) "<<endl;
             cin>>*this;
             
            if(name[0]=='E' && name[1]=='X' && name[2]=='I' && name[3]=='T'){
                return;
            }
            out=input_fun();
            if(out==2){
                movement(tmp,move_x,move_y,O);
                play(tmp);
            } 
           
            
        }while( out==1);
        
        
        if(out==2){
            flag=turn_check_undo(move_x,move_y,O);
            if(flag==1){
                return;
            }
            tmp=play();         // computer move
            turn_num++;

            setTurn();
            cout<<*this;
            flag=check_board(X);
            if(flag==1){
                cout<<"Winner is Computer(X) "<<endl;
            // function that returns if the game ended.
            return;
            }
            undo(tmp.get_row(),tmp.get_colum());    
        }
        else{
           cout<<*this;
        }  
        out=1;  

    }    
    
}
bool  Hex::load_game(){ // load file fun 
    ifstream file;
	int out=5,shape=0; 
	file.open(name);
	
	if(file.is_open()){
        //cout<<"out:"<<out<<endl;
         file>>*this; // load file overloading
        
        
    file.close();
    cout<<"File "<<name<< "Loaded"<<endl;
    }
    else{
        cerr<< "There arent name "<<name<<"file"<<endl;
        return 1;
    }
    return 1;
}
void  Hex::save_game(){
    ofstream file;
	
	
    file.open(name);
	file<<*this; // ofsream overloading
    //file<<tips;
	file.close();
    cout <<"File"<<name<<" Saved"<<endl;

    
	
}
void Hex::play(Cell & temp){ // play user set Cell
  
    int move_x=0,move_y=0,out=2;

    move_x=temp.get_row();
    move_y=temp.get_colum();        
            
                         
    if(hexCells[move_x][move_y].get_shape()==DOT){
        hexCells[move_x][move_y].set_shape(temp.get_shape());
        out=0;
    }    
   

    return;          
}
Hex::Cell  Hex::play(){ 
    auto i=0,start_x=3,start_y=3;
    decltype(check_board_near()) flag;
    static int move_x, move_y,first;
    flag=check_board_near();
    if(hexCells[start_x][start_y].get_shape()==DOT && flag==0){
        hexCells[start_x][start_y].set_shape(X);
        move_x=start_x;
        move_y=start_y;
        first=1;

        return hexCells[move_x][move_y];
    }
    else if(hexCells[move_x][move_y+1].get_shape()==DOT && flag==0){
        hexCells[move_x][move_y+1].set_shape(X);
        move_y++;
        return hexCells[move_x][move_y];
    }
    else if(hexCells[move_x-1][move_y+1].get_shape()==DOT && flag==0){
        hexCells[move_x-1][move_y+1].set_shape(X);
        move_x--;
        move_y++;
        return hexCells[move_x][move_y];;
    }
    else if(hexCells[move_x+1][move_y].get_shape()==2 && flag==0){
        hexCells[move_x+1][move_y].set_shape(X);
        move_x++;
        return hexCells[move_x][move_y];
    }
    else if(hexCells[move_x-1][move_y].get_shape()==2 && flag==0){
        hexCells[move_x-1][move_y].set_shape(X);
        move_x--;
        return hexCells[move_x][move_y];;
    }
     else if(flag==0){
        for(i=0;i<size;i++){
            if(hexCells[i][move_y].get_shape()==X && hexCells[i+1][move_y].get_shape()==DOT){
                hexCells[i+1][move_y].set_shape(X);
                move_x=i+1;
                return hexCells[move_x][move_y];
            }
            else if(hexCells[i][move_y].get_shape()==X && hexCells[i-1][move_y].get_shape()==DOT){
                hexCells[i-1][move_y].set_shape(X);
                move_x=i-1;
                return hexCells[move_x][move_y];
            }

        }
        
    }
    if(first==1 && flag==1){
        move_x=start_x;
        move_y=start_y;
        first=0;
    }
   
    if(hexCells[move_x][move_y-1].get_shape()==DOT && flag==1){
        hexCells[move_x][move_y-1].set_shape(X);
        move_y--;
        return hexCells[move_x][move_y];
    }
    else if(hexCells[move_x+1][move_y-1].get_shape()==DOT && flag==1){
        hexCells[move_x+1][move_y-1].set_shape(X);
        move_x++;
        move_y--;
        return hexCells[move_x][move_y];

    }
    else if(hexCells[move_x-1][move_y].get_shape()==DOT && flag==1){
        hexCells[move_x-1][move_y].set_shape(X);
        move_x--;
        return hexCells[move_x][move_y];
    }
    else if(hexCells[move_x+1][move_y].get_shape()==DOT && flag==1){
        hexCells[move_x+1][move_y].set_shape(X);
        move_x++;
        return hexCells[move_x][move_y];
    }
    else if(hexCells[move_x-1][move_y+1].get_shape()==2 && flag==1){
        hexCells[move_x-1][move_y+1].set_shape(X);
        move_x--;
        move_y++;
        return hexCells[move_x][move_y];
    }
    else if(hexCells[move_x][move_y+1].get_shape()==2 && flag==1){
        hexCells[move_x][move_y+1].set_shape(X);
        move_y++;
        return hexCells[move_x][move_y];
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
int Hex::input_fun(){
   char letter;
   int move_x,move_y;
    letter=name[0];
    move_x=atoi(&name[1]);
    if((name[0]=='B' || name[0]=='b') && (name[1]=='A' || name[1]=='a') && (name[2]=='C' || name[2]=='c')
         && (name[3]=='K' || name[3]=='k')){
        
        --*this; //  pre and post operator-- overloading
        return 0;
    }
    else if((name[0]=='L' || name[0]=='l') && (name[1]=='O' || name[1]=='o') && (name[2]=='A' || name[2]=='a') &&
    (name[3]=='D' || name[3]=='d')){
        cin>>*this; // input overloading
        load_game();
        cout<<*this;
        return 1;
    }
    else if((name[0]=='S' || name[0]=='s') && (name[1]=='A' || name[1]=='a') && (name[2]=='V' || name[2]=='v') &&
    (name[3]=='E' || name[3]=='e')){
        cin>>*this; // input overloading
        save_game();
        return 1;
    }
    else if(name[0] >=65 && this->get_size()+65 > name[0] && move_x>=0 && move_x <this->get_size() ){
        return 2;
    }
    else{
        return 1;
    }    
}
void  Hex::user_user(){
    int move_x,move_y;
    
    auto flag=0,out=1;
    Cell tmp;
    cout<<*this; // print table screen output overloading
    while(1){
        char letter;
        do{
             
            cout<<"Please Enter Number and Letter for O. (write (EXIT) or write  (BACK) )  "<<endl;
            cin>>*this; // input overloading
            if(name[0]=='E' && name[1]=='X' && name[2]=='I' && name[3]=='T'){
                return;
            }
            out=input_fun();
           
            if(out==2){
                movement(tmp,move_x,move_y,X);
                play(tmp);
            }    
        }while( out==1);
        
        if(out==2){
            flag=turn_check_undo(move_x,move_y,X);
            if(flag==1){
                return;
            }
        }
        
        out=1;
        cout<<*this; // output overloading
        do{
            cout<<"Please Enter Number and Letter for O. (write (EXIT) or write  (BACK) )  "<<endl;
            cin>>*this;
            if(name[0]=='E' && name[1]=='X' && name[2]=='I' && name[3]=='T'){
                return;
            }
            out=input_fun();
            if(out==2){
                movement(tmp,move_x,move_y,O);
                play(tmp);
            } 
        }while( out==1);

        
        if(out==2){
            flag=turn_check_undo(move_x,move_y,O);
            if(flag==1){
                return;
            }
        }
        cout<<*this; // output overloading
        out=1;
            
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
int Hex::score(int type){ // given type return score
    int i=0,j=0,counter=0,big=0;

    if(type==X){    
        for(i=0;i<this->size;i++){
            for(j=0;j<this->size;j++){
                if(this->hexCells[i][j].get_shape()==X)
                    counter++;

            }
            if(big < counter)
                big=counter;
            counter=0;
        }
    }
    else if(type==O){
        for(i=0;i<this->size;i++){
            for(j=0;j<this->size;j++){
                if(this->hexCells[j][i].get_shape()==O)
                    counter++;

            }
            if(big < counter)
                big=counter;
            counter=0;
        }
    }

    return big;
}




