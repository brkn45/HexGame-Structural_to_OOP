#include "base.h"



using namespace HexGame;
void Cell::operator=(const Cell &temp){
    row=temp.get_row();
    colum=temp.get_colum();
    shape=temp.get_shape();
}
int TrustGame(AbstractHex & game){
   
    int tmp=0;
    if(game.getSize() < 5)
        return false;
    for(int i=0;i<game.getSize();i++){
        for(int k=0;k<game.getSize();k++){
            if(  game(i,k)==X  ){
                tmp++;
            }
            else if( game(i,k)==O){
               tmp++; 
            }
            else if(game(i,k)==DOT){
                tmp++;
            }
            else
                return false;    
        }
    }
    return true;    
}
bool AbstractHex::operator==(AbstractHex &rValue){ // compare 2 game // first compare size than each sell compare
    if(this->getSize()!=rValue.getSize())
        return false;
    else{
      
        for(int i=0;i<rValue.getSize();i++){
            for(int k=0;k<rValue.getSize();k++){
                if((*this)(i,k)!= rValue(i,k))
                    return false;
          }
      }
      return true;
  }    
}
Cell::Cell(const Cell& rCell){
    
    shape=rCell.get_shape();
    row=rCell.get_row();
    colum=rCell.get_colum();
}
/*HexVector::HexVector(HexVector& rVector ){
    size=rVector.getSize();
    last=rVector.getLastCell();
    vecCell.resize(getSize());
    for(int i=0;i<size;i++){
        vecCell[i].resize(size);
    }

    for(int i=0;i<size;i++){
        for(int k=0;k<size;k++){
            vecCell[i][k].set_shape(rVector.vecCell[i][k].get_shape());
        }
    }
}*/
/*HexVector::~HexVector(){
    for(int i=0;i<getSize();i++){
        vecCell[i].clear();
    }
    vecCell.clear();
}*/
int HexVector::operator()(int row ,int colum){
    if(row>getSize() )
        throw(FalseGame("Wrong Row Size"));
    else if( colum > getSize())
        throw(FalseGame("wrong Row Size"));    
    return vecCell[row][colum].get_shape();
}
int HexVector::numberOfMoves(){
    int i=0,k=0,num=0;
    for(i=0;i<getSize();i++){
        for(k=0;k<getSize();k++){
            if((*this)(i,k)!=2)
                num++;
        }
    }
    return num;
}
Cell AbstractHex::lastMove(AbstractHex & container){
    Cell tmp=container.getLastCell();
    int type=tmp.get_shape();
    
    if(type==2)
        throw LastMoveError("No last move");
    else
    {
        return tmp;
    }
    

}
void HexVector::reset(){ // redraw board
    int i=0,k=0;
    vecCell.resize(getSize());
    for(i=0;i<getSize();i++){
        vecCell[i].resize(getSize());
    
    }
    
 

    for(i=0;i<getSize();i++){
        for(k=0;k<getSize();k++){
            vecCell[i][k].set_row(i);
            vecCell[i][k].set_colum(k);
            vecCell[i][k].set_shape(DOT);
        }
    }
    
}
void HexVector::print(){ // print board
    int i=0,k=0,blank=0;
    cout<<endl<<"    ";
    while (blank<getSize()) {
        
        cout<<"  "<<alphabet[blank];
        blank++;
    }
    blank=0;
    cout<<endl;
    for(i=0;i<getSize();i++){
         
         while(blank < (i+2)){
            cout<<" ";
            blank++;
        }
        blank=0;
        cout<<" "<<i<<" ";
        for(k=0;k<getSize();k++){
            
            if((*this)(i,k)==2){ // overload operator()
                cout<<" . ";
            }
            else if((*this)(i,k)==X){  // overload operator()
                cout<<" X ";
            }
            else if((*this)(i,k)==O){  // overload operator()
                cout<<" O ";
            }
            
        }
        cout<<endl;
    }
    
}

void HexVector::playGame(){ // Start game and select size and game type(user -user and user -computer)
    int type=0,theSize;
    do{ cout<<"please Enter Size"<<endl; 
        cin>>theSize;
    }while(theSize<5);
   
    this->setSize(theSize);
    this->reset();
    
    cout<<"please Select game tips"<<endl<<"1)User - user "<<endl<<"2)User - Pc" <<endl;
    cin>>type;
    if(1==type){
        userUser();
    }
    else if(2==type){
        userPc();
    
    }
    else
        cerr<<"Wrong choice"<<endl;
}
void  HexVector::userPc(){ // there are game loop 
    int move_x,move_y,i=0,out=1;
    decltype(check_board(X)) flag=0;
    Cell tmp,tmp1;
    this->print(); // print board
    
    while(1){
        do{
            cout<<"Number of Moves:"<<numberOfMoves()<<endl;
            cout<<"Please Enter Number and Letter for O. (write (EXIT) ) "<<endl;
             cin>>name;
             
            if(name[0]=='E' && name[1]=='X' && name[2]=='I' && name[3]=='T'){
                return;
            }
            out=input_fun();
            if(out==2){
                movement(tmp,move_x,move_y,O);
                play(tmp);
                setLastCell(tmp);
            } 
           
            
        }while( out==1);
        
        
        if(out==2){
            flag=isEnd(move_x,move_y,O);
            if(flag==1){
                return;
            }
            tmp1=play();         // computer move
            setLastCell(tmp1);
            //turn_num++;

            //setTurn();
            this->print();
            flag=check_board(X);
            if(flag==1){
                cout<<"Winner is Computer(X) "<<endl;
            // function that returns if the game ended.
            return;
            }
            //undo(tmp.get_row(),tmp.get_colum());    
        }
        else{
           this->print();
        }  
        out=1;  

    }    
    
}
Cell  HexVector::play(){ 
    auto i=0,start_x=3,start_y=3;
    int flag;
    static int move_x, move_y,first;
    
    flag=check_board_near();
    if(vecCell[start_x][start_y].get_shape()==DOT && flag==0){
        vecCell[start_x][start_y].set_shape(X);
        move_x=start_x;
        move_y=start_y;
        first=1;

        return vecCell[move_x][move_y];
    }
    else if(vecCell[move_x][move_y+1].get_shape()==DOT && flag==0){
        vecCell[move_x][move_y+1].set_shape(X);
        move_y++;
        return vecCell[move_x][move_y];
    }
    else if(vecCell[move_x-1][move_y+1].get_shape()==DOT && flag==0){
        vecCell[move_x-1][move_y+1].set_shape(X);
        move_x--;
        move_y++;
        return vecCell[move_x][move_y];;
    }
    else if(vecCell[move_x+1][move_y].get_shape()==2 && flag==0){
        vecCell[move_x+1][move_y].set_shape(X);
        move_x++;
        return vecCell[move_x][move_y];
    }
    else if(vecCell[move_x-1][move_y].get_shape()==2 && flag==0){
        vecCell[move_x-1][move_y].set_shape(X);
        move_x--;
        return vecCell[move_x][move_y];
    }
     else if(flag==0){
        for(i=0;i<getSize();i++){
            if(vecCell[i][move_y].get_shape()==X && vecCell[i+1][move_y].get_shape()==DOT){
                vecCell[i+1][move_y].set_shape(X);
                move_x=i+1;
                return vecCell[move_x][move_y];
            }
            else if(vecCell[i][move_y].get_shape()==X && vecCell[i-1][move_y].get_shape()==DOT){
                vecCell[i-1][move_y].set_shape(X);
                move_x=i-1;
                return vecCell[move_x][move_y];
            }

        }
        
    }
    if(first==1 && flag==1){
        move_x=start_x;
        move_y=start_y;
        first=0;
    }
   
    if(vecCell[move_x][move_y-1].get_shape()==DOT && flag==1){
        vecCell[move_x][move_y-1].set_shape(X);
        move_y--;
        return vecCell[move_x][move_y];
    }
    else if(vecCell[move_x+1][move_y-1].get_shape()==DOT && flag==1){
        vecCell[move_x+1][move_y-1].set_shape(X);
        move_x++;
        move_y--;
        return vecCell[move_x][move_y];

    }
    else if(vecCell[move_x-1][move_y].get_shape()==DOT && flag==1){
        vecCell[move_x-1][move_y].set_shape(X);
        move_x--;
        return vecCell[move_x][move_y];
    }
    else if(vecCell[move_x+1][move_y].get_shape()==DOT && flag==1){
        vecCell[move_x+1][move_y].set_shape(X);
        move_x++;
        return vecCell[move_x][move_y];
    }
    else if(vecCell[move_x-1][move_y+1].get_shape()==2 && flag==1){
        vecCell[move_x-1][move_y+1].set_shape(X);
        move_x--;
        move_y++;
        return vecCell[move_x][move_y];
    }
    else if(vecCell[move_x][move_y+1].get_shape()==2 && flag==1){
        vecCell[move_x][move_y+1].set_shape(X);
        move_y++;
        return vecCell[move_x][move_y];
    }
    
    
}
bool  HexVector::check_board_near(){
    int i=0;
    for(i=0;i<getSize();i++){
        if(vecCell[i][getSize()-1].get_shape()==X)
            return 1;
    }
    return 0;
}    
void HexVector::userUser(){ // there are game loop
    int move_x,move_y;
    
    int flag=0,out=1;
    Cell tmp;
    print(); // print table screen output overloading
    while(1){
        char letter;
        do{
            cout<<"Number of Moves:"<<numberOfMoves()<<endl; 
            cout<<"Please Enter Number and Letter for O. (write (EXIT)  )  "<<endl;
            cin>>name; // input overloading
            if(name[0]=='E' && name[1]=='X' && name[2]=='I' && name[3]=='T'){
                return;
            }
            out=input_fun();
           
            if(out==2){
                movement(tmp,move_x,move_y,X);
                play(tmp);
                setLastCell(tmp); // for last move
            }    
        }while( out==1);
        
        if(out==2){
            flag=isEnd(move_x,move_y,X);
            if(flag==1){
                return;
            }
        }
        
        out=1;
        print(); // output overloading
        do{
            cout<<"Please Enter Number and Letter for O. (write (EXIT) )  "<<endl;
            cin>>name;
            if(name[0]=='E' && name[1]=='X' && name[2]=='I' && name[3]=='T'){
                return;
            }
            out=input_fun();
            if(out==2){
                movement(tmp,move_x,move_y,O);
                play(tmp);
                setLastCell(tmp); // for lastmove
            } 
        }while( out==1);

        
        if(out==2){
            flag=isEnd(move_x,move_y,O);
            if(flag==1){
                return;
            }
        }
        this->print(); // output overloading
        out=1;
            
    }
}

void HexVector::movement(Cell & temp,int &move_x,int& move_y,int type){ // make movement 
    char letter;
    letter=name[0];
    move_x=atoi(&name[1]);
    move_y=convert_let_to_num(letter);
    temp.set_row(move_x);
    temp.set_colum(move_y);
    temp.set_shape(type);
    return;
}
int  HexVector::convert_let_to_num(const char & letter){ // convert to letter to number
   
    int i=0;
    for(i=0;i<getSize();i++){
        if(letter==alphabet[i]){
            return i;
        }
    }
}
int HexVector::input_fun(){
    char letter,theFilename[20];
   int move_x,move_y;
    letter=name[0];
    move_x=atoi(&name[1]);
    if((name[0]=='B' || name[0]=='b') && (name[1]=='A' || name[1]=='a') && (name[2]=='C' || name[2]=='c')
         && (name[3]=='K' || name[3]=='k')){
        
        //--*this; //  pre and post operator-- overloading
        return 0;
    }
    else if((name[0]=='L' || name[0]=='l') && (name[1]=='O' || name[1]=='o') && (name[2]=='A' || name[2]=='a') &&
    (name[3]=='D' || name[3]=='d')){
        cin>>theFilename; // input overloading
        this->readFromFile(theFilename);
        print();
        return 1;
    }
    else if((name[0]=='S' || name[0]=='s') && (name[1]=='A' || name[1]=='a') && (name[2]=='V' || name[2]=='v') &&
    (name[3]=='E' || name[3]=='e')){
        cin>>theFilename;
        writeToFile(theFilename);
        return 1;
    }
    else if(name[0] >=65 && this->getSize()+65 > name[0] && move_x>=0 && move_x <this->getSize() ){
        return 2;
    }
    else{
        return 1;
    }    
}
void HexVector::play(Cell & temp){ // user movement save board
    int move_x=0,move_y=0,out=2;

    move_x=temp.get_row();
    move_y=temp.get_colum();        
            
                         
    if(vecCell[move_x][move_y].get_shape()==DOT){
        vecCell[move_x][move_y].set_shape(temp.get_shape());
        out=0;
    }    
   

    return;
}

bool HexVector::isEnd(int move_x,int move_y,int type){ // turn check and save movement
    int flag;
    Cell tmp;
    //turn_num++;
    //setTurn();
    
    flag=check_board(type);
    if(flag==1){
        if(type==O){
            print();
            cout<<"Winner is User (O)"<<endl;
            return flag; // function that returns if the game ended.
        }
        else if(type == X){
            print();
            cout<<"Winner is User (X)"<<endl;
            return flag; // function that returns if the game ended.
        }
    }
    //undo(move_x,move_y);
    return flag;
}
bool  HexVector::check_board(int tips){ // if there ara O first line, program find other line recursive
    int i=0, k=0;
    bool flag=0;
    if(tips==O){
        for(k=0;k<getSize();k++){
            if(vecCell[i][k].get_shape()==O){
                flag=recuv_check_O(i,k,0,0);  
            }
        }

    }
    else if(tips==X ){
        for(i=0;i<getSize();i++){
            if(vecCell[i][k].get_shape()==X){
                flag=recuv_check_X(i,k,0,0);
            }
        }
    }
    return flag;    
    
}
bool HexVector::recuv_check_X(int x,int y ,int counter,int turn){
    bool flag=0;
    if((y+1) < getSize() && flag==0){
        if(vecCell[x][y+1].get_shape()==X   ){
            flag= recuv_check_X(x,y+1,counter+1,0);
        }
    }
    
    if((x-1) >= 0 && (y+1) < getSize() && flag == 0){
        if(vecCell[x-1][y+1].get_shape()==X ){
            flag=  recuv_check_X(x-1,y+1,counter+1,0);
        }
    }
    if((x+1) < getSize()  &&flag==0 && turn !=LEFT ){
        if(vecCell[x+1][y].get_shape()==X  ){
            flag=  recuv_check_X(x+1,y,counter,RIGHT);
        }
    }
    if((x-1) >= 0 && flag==0 && turn !=RIGHT){
        if (vecCell[x-1][y].get_shape() == X   ){
            flag= recuv_check_X(x-1,y,counter,LEFT);
        }
    }
    
    

    if((getSize()-1)==counter || flag==1){
        return 1;
    }
    else 
        return 0;
}
bool  HexVector::recuv_check_O(int x,int y,int counter,int turn ){ // 
    bool flag=0;
    if((x+1)<getSize()  &&flag == 0){
        if( vecCell[x+1][y].get_shape()==O ){
            flag =recuv_check_O(x+1,y,counter +1,0);
        }
    }
    if( (x+1)< getSize() && (y-1)>= 0 && flag==0 ){
        if(vecCell[x+1][y-1].get_shape()==O ){
            flag= recuv_check_O(x+1,y-1,counter +1,0);
        }
    }
    if( (y+1) <getSize() && flag==0  && turn != LEFT){
        if(vecCell[x][y+1].get_shape()==O  ){ 
            flag=  recuv_check_O(x,y+1,counter,RIGHT);
        }
    }
    if((y-1) >=0 && flag==0 && turn !=RIGHT ){
        if (vecCell[x][y-1].get_shape() == O  ){
            flag =recuv_check_O(x,y-1,counter,LEFT);
    }
    }
    
    if((getSize()-1)==counter || flag==1){
        return 1;
    }
    else 
        return 0;
}

void HexVector::writeToFile(char *filename){ // write file
    ofstream file;
	
	int i=0,k=0;
	file.open(filename);
    if(!(file.is_open()))
        throw OpenFile("File wasnt open");

    file << " "<< getSize() <<endl;
    
	for(i=0;i<getSize();i++){
		for(k=0;k<getSize();k++){
            file<<" "<<(*this)(i,k)<<" ";
		}
		file<<endl;
	}
    //file<<tips;
    file.close();
    cout <<"File"<<name<<" Saved"<<endl;
}
void HexVector::readFromFile(char *filename){// read file
    ifstream file;
	int out=5,shape=0; 
	int i=0,k=0,turn=2,tmpSize;
    
	file.open(filename);
	
	if(file.is_open()){
        //cout<<"out:"<<out<<endl;
        file >>tmpSize;
        setSize(tmpSize);
        reset();
        
	    for(i=0;i<getSize();i++){
		    for(k=0;k<getSize();k++){
			    file>>shape;
                vecCell[i][k].set_shape(shape);
            }
    
        }
        if(!TrustGame(*this)){
               throw(FalseGame("Wrong Game"));
        }
        //file>>turn;
        
        return ;
    file.close();
    cout<<"File "<<name<< "Loaded"<<endl;
    }
    else{
        throw OpenFile("file wasnt open");
    }
}
void HexArray1D::operator=(HexArray1D & tmp){ 
    size=tmp.getSize();
    last=tmp.getLastCell();
    
    for(int i=0;i<size;i++){
        arrCell[i].set_shape(tmp.arrCell[i].get_shape());
    }    
    
}
int HexArray1D::operator()(int row,int colum ){
    int index=row*getSize() + colum;
    return arrCell[index].get_shape();
}
HexArray1D::HexArray1D(HexArray1D & tmp ){
    size=tmp.getSize();
    last=tmp.getLastCell();
    
    arrCell =(Cell*)malloc(sizeof(Cell)*size*size);
    for(int i=0;i<size;i++){
        arrCell[i].set_shape(tmp.arrCell->get_shape());
    }    
}
HexArray1D::~HexArray1D(){
    delete [] arrCell;
    arrCell=nullptr;
}
int HexArray1D::numberOfMoves(){
    int i=0,num=0;
    for(i=0;i<getSize();i++){
        if(arrCell[i].get_shape()!=2)
            num++;
    }
    return num;
}
void HexArray1D::reset(){
    int i=0;
    arrCell =(Cell*)malloc(sizeof(Cell)*getSize()*getSize());
    for(i=0;i<getSize()*getSize();i++){
        arrCell[i].set_shape(DOT);
        arrCell[i].set_row(i);
        
        
    }
}

void HexArray1D::print(){
    int i=0,k=0,blank=0;
    cout<<endl<<"    ";
    while (blank<getSize()) {
        
        cout<<"  "<<alphabet[blank];
        blank++;
    }
    blank=0;
    cout<<endl;
    for(i=0;i<getSize();i++){
         
         while(blank < (i+2)){
            cout<<" ";
            blank++;
        }
        blank=0;
        cout<<" "<<i<<" ";
        for(k=0;k<getSize();k++){
            
            if((*this)(i,k)==2){ // overload operator()
                cout<<" . ";
            }
            else if((*this)(i,k)==X){  // overload operator()
                cout<<" X ";
            }
            else if((*this)(i,k)==O){  // overload operator()
                cout<<" O ";
            }
            
        }
        cout<<endl;
    }
    
    
}

void HexArray1D::playGame(){
    int type=0,theSize=0;

    do{ cout<<"please Enter Size"<<endl; 
        cin>>theSize;
    }while(theSize<5);
   
    this->setSize(theSize);
    this->reset();

    cout<<"please Select game tips"<<endl<<"1)User - user "<<endl<<"2)User - Pc" <<endl;
    cin>>type;
    if(1==type){
        userUser();
    }
    else if(2==type){
        userPc();
    
    }
    else
        cerr<<"Wrong choice"<<endl;
}
void HexArray1D::userPc(){
    int move_x,move_y,i=0,out=1;
    int flag=0;
    Cell tmp;
    this->print(); // print board
    
    while(1){
        do{
            cout<<"Number of Moves:"<<numberOfMoves()<<endl;
            cout<<"Please Enter Number and Letter for O. (write (EXIT)  ) "<<endl;
             cin>>name;
             
            if(name[0]=='E' && name[1]=='X' && name[2]=='I' && name[3]=='T'){
                return;
            }
            out=input_fun();
            if(out==2){
                movement(tmp,move_x,move_y,O);
                play(tmp);
                setLastCell(tmp);
            } 
           
            
        }while( out==1);
        
        
        if(out==2){
            flag=isEnd(move_x,move_y,O);
            if(flag==1){
                return;
            }
            tmp=play();         // computer move
            setLastCell(tmp);
            //turn_num++;

            //setTurn();
            this->print();
            flag=isEnd(move_x,move_y,X);
            if(flag==1){
                cout<<"Winner is Computer(X) "<<endl;
            // function that returns if the game ended.
            return;
            }
            //undo(tmp.get_row(),tmp.get_colum());    
        }
        else{
           this->print();
        }  
        out=1;  

    } 
}
void HexArray1D::userUser(){
    int move_x,move_y;
    
    int flag=0,out=1;
    Cell tmp;
    this->print(); // print table screen output overloading
    while(1){
        char letter;
        do{
            cout<<"Number of Moves:"<<numberOfMoves()<<endl; 
            cout<<"Please Enter Number and Letter for O. (write (EXIT)  )  "<<endl;
            cin>>name; // input overloading
            if(name[0]=='E' && name[1]=='X' && name[2]=='I' && name[3]=='T'){
                return;
            }
            out=this->input_fun();
           
            if(out==2){
                movement(tmp,move_x,move_y,X);
                play(tmp);
                setLastCell(tmp);
            }    
        }while( out==1);
        
        if(out==2){
            flag=isEnd(move_x,move_y,X);
            if(flag==1){
                return;
            }
        }
        
        out=1;
        print(); 
        do{
            cout<<"Number of Moves:"<<numberOfMoves()<<endl;
            cout<<"Please Enter Number and Letter for O. (write (EXIT) )  "<<endl;
            cin>>name;
            if(name[0]=='E' && name[1]=='X' && name[2]=='I' && name[3]=='T'){
                return;
            }
            out=input_fun();
            if(out==2){
                movement(tmp,move_x,move_y,O);
                play(tmp);
                setLastCell(tmp);
            } 
        }while( out==1);

        
        if(out==2){
            flag=isEnd(move_x,move_y,O);
            if(flag==1){
                return;
            }
        }
        this->print(); 
        out=1;
            
    }

}

int HexArray1D::input_fun(){
    char letter ,theFilename[20];
   int move_x,move_y;
    letter=name[0];
    
    move_x=atoi(&name[1]);
    if((name[0]=='B' || name[0]=='b') && (name[1]=='A' || name[1]=='a') && (name[2]=='C' || name[2]=='c')
         && (name[3]=='K' || name[3]=='k')){
        
        //--*this; //  pre and post operator-- overloading
        return 0;
    }
    else if((name[0]=='L' || name[0]=='l') && (name[1]=='O' || name[1]=='o') && 
    (name[2]=='A' || name[2]=='a') && (name[3]=='D' || name[3]=='d')){
        cin>>theFilename; // input overloading
        
        this->readFromFile(theFilename);
        print();
        return 1;
    }
    else if((name[0]=='S' || name[0]=='s') && (name[1]=='A' || name[1]=='a') && (name[2]=='V' || name[2]=='v') &&
    (name[3]=='E' || name[3]=='e')){
        cin>>theFilename;
        writeToFile(theFilename);
        return 1;
    }
    else if(name[0] >=65 && this->getSize()+65 > name[0] && move_x>=0 && move_x <this->getSize() ){
        return 2;
    }
    else{
        return 1;
    }    
}

void HexArray1D::movement(Cell & temp,int &move_x,int& move_y,int type){ // make movement 
    char letter;
    letter=name[0];
    move_x=atoi(&name[1]);
    move_y=convert_let_to_num(letter);
    temp.set_row(move_x);
    temp.set_colum(move_y);
    temp.set_shape(type);
    return;
}
void HexArray1D::play(Cell & temp){
    int move_x=0,move_y=0,out=2;
    int index;
    move_x=temp.get_row();
    move_y=temp.get_colum();        
            
    index=move_x*getSize()+move_y;                     
    if(arrCell[index].get_shape()==DOT){
        arrCell[index].set_shape(temp.get_shape());
        
    }    
   

    return;
}

int  HexArray1D::convert_let_to_num(const char & letter){
   
    int i=0;
    for(i=0;i<getSize();i++){
        if(letter==alphabet[i]){
            return i;
        }
    }
}
bool HexArray1D::isEnd(int move_x,int move_y,int type){ // turn check and save movement
    int flag,num=0,i=0;
    
    //turn_num++;
    //setTurn();
     
    flag=check_board(type);
    if(flag==1){
        if(type==O){
            print();
            cout<<"Winner is User (O)"<<endl;
            return flag; // function that returns if the game ended.
        }
        else if(type == X){
            print();
            cout<<"Winner is User (X)"<<endl;
            return flag; // function that returns if the game ended.
        }
    }
    //undo(move_x,move_y);
    return flag;
}
bool  HexArray1D::check_board(int tips){ // if there ara O first line, program find other line recursive
    int i=0, k=0;
    bool flag=0;
    
    if(tips==O){
        for(k=0;k<getSize();k++){
            
            if(arrCell[k].get_shape()==O){
                flag=recuv_check_O(i,k,0,0);  
            }
        }

    }
    else if(tips==X ){
        for(i=0;i<getSize();i++){

            if(arrCell[k].get_shape()==X){
                flag=recuv_check_X(i,k,0,0);
            }
        }
    }
    return flag;    
    
}
bool HexArray1D::recuv_check_X(int x,int y ,int counter,int turn){
    bool flag=0;
    int index=x*getSize() +y;
    if((y+1) < getSize() && flag==0){
        
        if(arrCell[index+1].get_shape()==X   ){
            flag= recuv_check_X(x,y+1,counter+1,0);
        }
    }
    
    if((x-1) >= 0 && (y+1) < getSize() && flag == 0){
        
        if(arrCell[index-getSize()+1].get_shape()==X ){
            flag=  recuv_check_X(x-1,y+1,counter+1,0);
        }
    }
    if((x+1) < getSize()  &&flag==0 && turn !=LEFT ){
        
        if(arrCell[index+getSize()].get_shape()==X  ){
            flag=  recuv_check_X(x+1,y,counter,RIGHT);
        }
    }
    if((x-1) >= 0 && flag==0 && turn !=RIGHT){
    
        if (arrCell[index-getSize()].get_shape() == X   ){
            flag= recuv_check_X(x-1,y,counter,LEFT);
        }
    }
    
    

    if((getSize()-1)==counter || flag==1){
        return 1;
    }
    else 
        return 0;
}
bool  HexArray1D::recuv_check_O(int x,int y,int counter,int turn ){ // 
    bool flag=0;
    int index=x*getSize()+y;
    if((x+1)<getSize()  &&flag == 0){
        
        if( arrCell[index+getSize()].get_shape()==O ){
            flag =recuv_check_O(x+1,y,counter +1,0);
        }
    }
    if( (x+1)< getSize() && (y-1)>= 0 && flag==0 ){
        if(arrCell[index+getSize()-1].get_shape()==O ){
            flag= recuv_check_O(x+1,y-1,counter +1,0);
        }
    }
    if( (y+1) <getSize() && flag==0  && turn != LEFT){
        if(arrCell[index+1].get_shape()==O  ){ 
            flag=  recuv_check_O(x,y+1,counter,RIGHT);
        }
    }
    if((y-1) >=0 && flag==0 && turn !=RIGHT ){
        if (arrCell[index-1].get_shape() == O  ){
            flag =recuv_check_O(x,y-1,counter,LEFT);
    }
    }
    
    if((getSize()-1)==counter || flag==1){
        return 1;
    }
    else 
        return 0;
}

Cell HexArray1D::play(){
     auto i=0,start=2;
    int flag=0;
    
    static int move,first;
    //flag=check_board_near();
    if(arrCell[start].get_shape()==DOT && flag==0){
        arrCell[start].set_shape(X);
        move=start;
        first=1;

        return arrCell[move];
    }
    else if(arrCell[move+1].get_shape()==DOT && flag==0){
        arrCell[move+1].set_shape(X);
        move++;
        return arrCell[move];
    }
    else if(arrCell[move+getSize()+1].get_shape()==DOT && flag==0){
        arrCell[move+getSize()+1].set_shape(X);
        
        move=move+getSize()+1;
        return arrCell[move];
    }
    else if(arrCell[move+1].get_shape()==2 && flag==0){
        arrCell[move+getSize()].set_shape(X);
        move=move+getSize();
        return arrCell[move];
    }
    else if(arrCell[move-getSize()].get_shape()==2 && flag==0){
        arrCell[move-getSize()].set_shape(X);
        move=move-getSize();
        return arrCell[move];
    }
}

void HexArray1D::writeToFile(char *filename){
    ofstream file;
	
	int i=0,k=0;
	
	
	file.open(filename);
    if(!(file.is_open())) // file open control
        throw OpenFile("File wasnt open");
    file << " "<< getSize() <<endl;
    
	for(i=0;i<getSize();i++){
		for(k=0;k<getSize();k++){
            file<<" "<<(*this)(i,k)<<" ";
		}
		file<<endl;
	}
    //file<<tips;
    file.close();
    cout <<"File"<<name<<" Saved"<<endl;

}

void HexArray1D::readFromFile(char *filename){
    ifstream file;
    file.open(filename);
    if(!(file.is_open()))
        throw OpenFile("File wasnt open");
    int i=0,shape=0,blank,tmpSize;
    file>>tmpSize;
    setSize(tmpSize);
    reset();
    for(i=0;i<getSize()*getSize();i++){
        if(i%getSize()==0)
            file>>blank;
        file>>shape;
        arrCell[i].set_shape(shape);
    }
    if(!TrustGame(*this)){
        throw(FalseGame("Wrong Game"));
    }
}



