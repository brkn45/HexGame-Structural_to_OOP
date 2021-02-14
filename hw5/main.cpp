#include "base.h"
#include "template.cpp"


using namespace HexGame;
int TrustGame(AbstractHex & game);
int main(){  // 4 option diffrient games
    int size=8,menu=0,totalGame=0,theSize=0 ,exit=0; 
    HexAdapter<deque<deque<Cell>>> gameStlDeque;
    HexAdapter<vector<vector<Cell>>> gameStlVector;
    HexArray1D gameArray;
    HexVector gameVector;

    try
    {
        do{
            cout<<"1-)New Game"<<endl;
            cout<<"2-)Compare Came"<<endl;
            cout<<"3-)Game Controll"<<endl;
            cout<<"4-)Last Move"<<endl;
            cout<<"5-)EXIT"<<endl;
            
            //cout<<"5-) Compare Score"<<endl; // new feature
            

            cin>>menu;

            if(menu==1){
                cout<<"1-HexVector Game"<<endl;
                cout<<"2-HexArray1D Game"<<endl;
                cout<<"3-HexAdapter deque Game"<<endl;
                cout<<"4-HexAdapter vector Game"<<endl;
                cin>>menu;
                if(menu==1){
                    totalGame++;
                    gameVector.playGame();

                }
                else if(menu ==2){
                    totalGame++;
                    gameArray.playGame();

                }
                else if(menu==3){
                    totalGame++;
                    gameStlDeque.playGame();


                }
                else if(menu ==4){
                    totalGame++;
                    gameStlVector.playGame();

                }
            }
            else if(menu==2){ // game compare
                cout<<"1)HexVector - HexArray1D"<<endl;
                cout<<"2)HexVector - HexAdapterVector"<<endl;
                cout<<"3)HexArray1D- HexAdapterDeque "<<endl;
                cout<<"Compare Game "<<endl;
                cin>>menu;
                if(menu==1){
                    if(gameVector==gameArray)
                        cout<<"Equal 2 game"<<endl;
                    else
                        cout<<"game is diffirent"<<endl;    
                }
                else if(menu==2){
                    if(gameVector==gameStlVector)
                        cout<<"Equal 2 game"<<endl;
                    else
                        cout<<"game is diffirent"<<endl;    
                }
                else if(menu==3){
                    if(gameArray==gameStlDeque)
                        cout<<"Equal 2 game"<<endl;
                    else
                        cout<<"game is diffirent"<<endl;    
                }      
                

            }
            else if(menu==3){ // Game controll
                cout<<"1-HexVector Game"<<endl;
                cout<<"2-HexArray1D Game"<<endl;
                cout<<"3-HexAdapter deque Game"<<endl;
                cout<<"4-HexAdapter vector Game"<<endl;
                cin>>menu;
                if(menu==1){
                    if(TrustGame(gameVector)){
                        cout<<"Geme is True"<<endl;

                    }
                    else
                        throw(FalseGame("Game is wrong"));
                }
                else if(menu==2){
                    if(TrustGame(gameArray)){
                        cout<<"Geme is True"<<endl;

                    }
                    else
                        throw(FalseGame("Game is wrong"));
                }
                else if(menu==3){
                    if(TrustGame(gameStlDeque)){
                        cout<<"Geme is True"<<endl;

                    }
                    else
                        throw(FalseGame("Game is wrong"));
                }
                else if(menu==4){
                    if(TrustGame(gameStlVector)){
                        cout<<"Geme is True"<<endl;

                    }
                    else
                        throw(FalseGame("Game is wrong"));
                }
            }
            else if(menu ==4){ // Last Movement
                cout<<"1-HexVector Game"<<endl;
                cout<<"2-HexArray1D Game"<<endl;
                cout<<"3-HexAdapter deque Game"<<endl;
                cout<<"4-HexAdapter vector Game"<<endl;
                cin>>menu;
                if(menu==1){
                    cout<<"row: "<<gameVector.lastMove(gameVector).get_row()<<endl;
                    cout<<"colum: "<<gameVector.lastMove(gameVector).get_colum()<<endl;
                }
                else if(menu==2){
                    cout<<"row: "<<gameArray.lastMove(gameArray).get_row()<<endl;
                    cout<<"colum: "<<gameArray.lastMove(gameArray).get_colum()<<endl;
                }
                else if(menu==3){
                    cout<<"row: "<<gameStlDeque.lastMove(gameStlDeque).get_row()<<endl;
                    cout<<"colum: "<<gameStlDeque.lastMove(gameStlDeque).get_colum()<<endl;
                }
                else if(menu==4){
                    cout<<"row: "<<gameStlVector.lastMove(gameStlVector).get_row()<<endl;
                    cout<<"colum: "<<gameStlVector.lastMove(gameStlVector).get_colum()<<endl;
                }

               
            }
            else if(menu==5){
                 exit=1;
            }
        }while(exit!=1);

        
    }
    catch(OpenFile errFile) // if file dont open 
    {
        std::cerr << errFile.getMessage() <<'\n';
    }
    catch(LastMoveError errLast){  // if last move there arent
        std::cerr << errLast.getMessage() <<'\n';
    }
    catch(FalseGame errGame){ // if global function detect is error  
        std::cerr<<errGame.getMessage()<<endl;
    }
    
   
    

}