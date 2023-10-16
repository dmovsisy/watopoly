#include "board.h"
#include "square.h"
#include "game.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
    // ***** make testing and loaded variables, create game after ******
    if (argc > 4) {
      cout << "Error: Incorrect Number of Arguments" << endl;
      return 1;
    } else { 
        string delim = " ";
        string arg1Flag;
        string arg2Flag;
        string arg3Flag;
        string file = "";
        bool testing = false; 
        bool loading = false;
        
        
        // If 1 argument -> has to be "-testing"
        if (argc == 1) { 
            if (argv[1] == "-testing") {
                testing = true; 
                loading = false;
            } else cout << "Error: Invalid Arguments" << endl; return 1; 

        
        } else if (argc > 1) { 
            if (argc == 2) { // If 2 arguments -> has to be "-load file"
                
                if (argv[1]== "-load") {
                    file = argv[2];
                    
                    testing = false;
                    loading = true;
                } 
               
            
            } else if (argc == 3) { // If 3 arguments -> has to be "-load file" and "-testing"

                if (argv[1] == "-testing" || argv[2] == "-testing") {
                    testing = true; 
                    loading = false;
                    if (argv[1] == "-load"){
                        file = argv[2];
                        
                        testing = false;
                        loading = true;

                    } else if (argv[2] == "-load") {
                        file = argv[3];

                        testing = false;
                        loading = true;
                    }
                }
            }
        }
        Game g = Game{testing, loading};
        ifstream game = ifstream{file};
        if (loading) {
            if (game.is_open()) g.load(game);
            else cout << "Error: unable to open file" << endl; return 1; 
        }
        
        g.play();
    } 
    return 0; 
}
