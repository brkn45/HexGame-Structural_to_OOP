#include "base.h"
Hex::Hex():size(5),turn_num(0) 
 { } 
 Hex::Hex(int s_start):size(s_start), turn_num(0) 
 { } 

int Hex::turn=0;
//
int main(){
    vector <Hex> game;
    Hex temp;
    bool flag=1;
    int size=0,type=0,game_num=0,totalgame=0; // 
    int i=0,game1=0,game2=0;    
    
    while(1){ // i make a menu. if you want load and save file, you can use upload and save while playing
        cout<<"1-)New game"<<endl;
        cout<<"2-)Chance Game"<<endl;
        cout<<"3-)Compare game"<<endl;
        cout<<"4-)Total Number of marked (non-empty) cells "<<endl;
        cout<<"5-)EXIT"<<endl;
        
        cin>>type;
        if(type==1){
            game.push_back(temp);
            totalgame++;
            game_num=totalgame-1;
            do{
                cout<<"Please Enter Number Larger Than 5"<<endl;
                cin>>size;
                game[game_num].set_size(size);
                
                

                if(size >= 5 )
                    flag=0;
                else
                    cerr<<"Wrong Number"<<endl;   

            }while(flag);
            game[game_num].build_board();
            game[game_num].set_board();
            
            game[game_num].playGame();
            
        }
        else if(type==2){
            cout<<"0 ) return menu"<<endl;
            for(i=0;i<totalgame;i++){
                cout<<i+1<<"th Game"<<endl;
            }
            
            cout<<"Can you select game or come back menu"<<endl;
            cin>>type;
            if(0!=type && type<=totalgame){
                game_num=type-1;
                game[game_num].playGame();
            }
        }
        else if(type==3){
            if(totalgame<2){
                cout<< "You should have enough 2 games. "<<endl;
            }
            else{
                for(i=0;i<totalgame;i++){
                cout<<i+1<<"th Game"<<endl;
            }
                cout<<"Select first game"<<endl;
                cin>>game1;
                cout<<"Select second game"<<endl;
                cin>>game2;
                game1=game1-1;
                game2=game2-1;
                if(game[game1].compare(game[game1],game[game2])==1){
                    cout<<"game1 > game2"<<endl;
                }
                else{
                    cout<<"game1 < game2"<<endl;
                }
                cout<<"game1 marked cells:"<<game[game1].get_turn_num()<<endl;
                cout<<"game2 marked cells:"<<game[game2].get_turn_num()<<endl;
            }

        }
        else if(type==4){
            if(totalgame==0){
                cout<<"You havent active game"<<endl;
            }
            else{
                cout<<"Total Number of marked cells: " <<game[0].getTurn()<<endl;
            }
            
            
        }
        else if(type==5)
            break;
    
    
    }
    


    return 0;
}           

 