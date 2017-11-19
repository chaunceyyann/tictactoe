#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;
typedef struct tic_tac_toe tic_tac_toe;
struct tic_tac_toe{ 
   tic_tac_toe() {
	   // initialize the board to ' '
	   for (int i = 0; i < 9; i++)
		   board[(int)(i/3)][i%3] = ' ';
       player1 = "\0";
	   player2 = "\0";
       p1sym = '\0';
       p2sym = '\0';
	   mode = 0;
	   end = 0;
    }
	char board[3][3]; 
    string player1; 
    string player2;
    char p1sym;//Player1 symbol
    char p2sym; 
	int mode; // 1 signle player player first, 2 ultron first, 0 for two player. 
	int end; // 1 assigned mean the game end
};
void print_board(tic_tac_toe*);
void initialize_board(tic_tac_toe*);
void swap_player(tic_tac_toe*);
void reset_board(tic_tac_toe*);
int fill_board(tic_tac_toe*,int, int, char);
int is_full(tic_tac_toe*);
int check_for_winner(tic_tac_toe*);
int print_winner_results(tic_tac_toe*, int, int);
void player1_choice(tic_tac_toe*);
void player2_choice(tic_tac_toe*);
void ultron(tic_tac_toe*);
void modechoice(tic_tac_toe*);
int main(){ 
	tic_tac_toe ttt;
	string aga;
	int round = 0;
    srand(time((time_t)NULL));
	initialize_board(&ttt);
	do{
		if (round)
			reset_board(&ttt);
		while (!ttt.end){
			modechoice(&ttt);
		}
		cout << "Would you like to play it again? (q for exit) " ;
		cin >> aga;
		
		round++;
	}
	while (aga != "q");
    return 0;
} 
/****************************************
 * Function : print
 * Description : print everything on the board
 * **************************************/
void print_board(tic_tac_toe *ttt){
    cout    << "-------------" << endl
            << "| " << ttt->board[0][0] << " | " << ttt->board[0][1] << " | " << ttt->board[0][2]
            << " |"<< endl << "-------------" << endl
            << "| " << ttt->board[1][0] << " | " << ttt->board[1][1] << " | " << ttt->board[1][2]
            << " |"<< endl << "-------------" << endl
            << "| " << ttt->board[2][0] << " | " << ttt->board[2][1] << " | " << ttt->board[2][2]
            << " |" << endl << "-------------" << endl;

}
/****************************************
 * Function : initialize_board
 * Description : initialize the name of 
 * the players and players' symbol and mode
 * **************************************/
void initialize_board(tic_tac_toe *ttt){
    string choice;
	string str;

    cout << "Welcome to Tic-tac-toe!" << endl 
		 << "Do you wants to play with Mighty Ultron or two players?" << endl;
	cout << "1 for single game or 2 for two players ";
	getline(cin, choice);
	while(choice != "1" && choice != "2"){
		cout << "Incorrect entry. \nTry again with 1 for single game or 2 for two players \n";
		getline(cin, choice);
	}
	system("CLS");

    if (choice == "2") {
        cout << "What is player1's name?" << endl;
        getline(cin,ttt->player1);
		system("CLS");
        cout << "What is player2's name?" << endl;
        getline(cin,ttt->player2);
		system("CLS");
		ttt->mode = 0;
    }

    else if (choice == "1") {
		cout << "Do you want to move first? (1 for yes/ 2 for no) ";
		getline(cin, str);
		while(str != "1" && str != "2"){
			cout << "Incorrect entry. \nTry again with 1 for move first or 2 for no \n";
			getline(cin, str);
		}
		ttt->mode = atoi(str.c_str());
		system("CLS");

		//Getting the players' name
        if (ttt->mode == 1){
            cout << "What is player's name?" << endl;
            getline(cin,ttt->player1);
			system("CLS");
            ttt->player2 = "Mighty Ultron";
        }
        else if (ttt->mode == 2){
            cout << "What is player's name?" << endl;
            getline(cin,ttt->player2);
			system("CLS");
            ttt->player1 = "Mighty Ultron";
        }
    }
    cout << ttt->player1 << " VS. " << ttt->player2 << endl;
    // character assign
    ttt->p1sym = 'X';
    ttt->p2sym = 'O';
    cout << ttt->player1 <<": What character do you want? ";
	getline(cin, str);
	while(strlen(str.c_str()) != 1){
		cout << "Incorrect entry. \nTry again with single character \n";
		getline(cin,str);
	}
	ttt->p1sym = str[0];
	system("CLS");
    cout << ttt->player2 <<": What character do you want? ";
	getline(cin, str);
	while(strlen(str.c_str()) != 1){
		cout << "Incorrect entry. \nTry again with single character \n";
		getline(cin,str);
	}
	ttt->p2sym = str[0];
	system("CLS");
	do{
		cout << "HOW TO PLAY:\nPut the row first then column, seperate with space or return\n"
			 << "EXAMPLE:\n 2 3\n";
		ttt->board[1][2] = 'X';
		print_board(ttt);
		ttt->board[1][2] = ' ';
		cout << "Again? y/n " ;
		cin >> choice;
		system("CLS");
	}while(choice == "y");
}
/****************************************
 * Function : swao_player
 * Description : swap the players information
 * **************************************/
void swap_player(tic_tac_toe *ttt){
	char temp_sym = ttt->p1sym;
	string temp_name = ttt->player1;
	ttt->p1sym = ttt->p2sym;
	ttt->player1 = ttt->player2;
	ttt->p2sym = temp_sym;
	ttt->player2 = temp_name;
}
/****************************************
 * Function : reset_board
 * Description : set the board full of space
 * set end as 0;
 * **************************************/
void reset_board(tic_tac_toe *ttt){
	string str;
	// initialize the board to ' '
	for (int i = 0; i < 9; i++)
		ttt->board[(int)(i/3)][i%3] = ' ';
	// change the mode for single player
	if (ttt->mode != 0){
		int previous_mode = ttt->mode;
		cout << "Do you want to move first? (1 for yes/ 2 for no) ";
	    cin >> str;
		while(str != "1" && str != "2"){
			cout << "Incorrect entry. \nTry again with 1 for move first or 2 for no \n";
			getline(cin, str);
		}
		ttt->mode = atoi(str.c_str());
		system("CLS");
	    if (ttt->mode != previous_mode){
			swap_player(ttt);
        }
	}
	// for two players
	else {
		cout << "Do you want to swap the order to play? (y/n) ";
		getline(cin, str);
		while(strlen(str.c_str()) != 1){
			cout << "Incorrect entry. \nTry again with y or n \n";
			getline(cin,str);
		}
		if (str == "y")
			swap_player(ttt);
		system("CLS");
	}
	ttt->end = 0;
}
/****************************************
 * Function : fill_board 
 * Description : take the x y fill the board
 * with different mode choice p
 * **************************************/
int fill_board(tic_tac_toe *ttt,int y, int x, char symbol){
	// too big and too small check
    if ( y < 0 || y > 2){
		cout << "Row input is out of bondary" << endl;
		return 0;
	}
    if ( x < 0 || x > 2){
        cout << "Colume input is out of bondary" << endl;
        return 0;
    }
    // fill the players' choice
	if ((ttt->board[y][x] == ' '))
        ttt->board[y][x] = symbol;
    // taken
    else {
        cout << "The place is taken! Make a different choice." << endl;
        return 0;
    }
    return 1;
}
/****************************************
 * Function : is_full
 * Description : return 1 on the board 
 * is full, return 0 on it is not
 * **************************************/
int is_full(tic_tac_toe *ttt){
    for (int i = 0; i < 9; i++){
        if (ttt->board[(int)(i/3)][i%3] == ' ')
            return 0;
    }
    return 1;
}
/****************************************
 * Function : check for winner
 * Description : check winner with three 
 * situation. retruning 0 on no winner, 
 * 1 on winner is player1, 2 on winner is player2
 * **************************************/
int check_for_winner(tic_tac_toe *ttt){
    for (int i = 0; i < 3; i++){
        //check for rows
        if ((ttt->board[i][0] == ttt->board[i][1]) && (ttt->board[i][0] == ttt->board[i][2])){
            if (ttt->board[i][0] == ttt->p1sym)
                return 1;
            else if (ttt->board[i][0] == ttt->p2sym)
                return 2;
        }
        //check for colums
        if ((ttt->board[0][i] == ttt->board[1][i]) && (ttt->board[0][i] == ttt->board[2][i])){
            if (ttt->board[0][i] == ttt->p1sym)
                return 1;
            else if (ttt->board[0][i] == ttt->p2sym)
                return 2;
        }
    }
    //check the slash
    if ((ttt->board[0][0] == ttt->board[1][1]) && (ttt->board[0][0] == ttt->board[2][2])){
        if (ttt->board[0][0] == ttt->p1sym)
            return 1;
        else if (ttt->board[0][0] == ttt->p2sym)
            return 2;
    }
    //check the back slash
    if ((ttt->board[0][2] == ttt->board[1][1]) && (ttt->board[0][2] == ttt->board[2][0])){
        if (ttt->board[0][2] == ttt->p1sym)
            return 1;
        else if (ttt->board[0][2] == ttt->p2sym)
            return 2;
    }
    return 0;
}
/****************************************
 * Function : print_winner_results
 * Description : print the result from 
 * is_full() and check_winner()
 * return 1 on we have a winner, 
 * return 1 on we don't. 
 * **************************************/
int print_winner_results(tic_tac_toe *ttt, int full, int winner){
    if ((full == 1) && (winner == 0)){
		print_board(ttt);
        cout << "Board is full, winner is " << ttt->player2 << "!!!" << endl;
        return 1;
    }
    if (winner == 1){
        print_board(ttt);
		cout << "Winner is " << ttt->player1 << "!!!" << endl;
        return 1;
    }
    else if (winner == 2){
        print_board(ttt);
		cout << "Winner is " << ttt->player2 << "!!!" << endl;
        return 1;
    }
    return 0; 
}
/****************************************
 * Function : player1_choice
 * Description : player1 detemine where to
 * put their symbol
 * **************************************/
void player1_choice(tic_tac_toe *ttt){
    int y, x;
	do {
        print_board(ttt);
        cout    << ttt->player1 <<": Where would you like to put your \""
                << ttt->p1sym << "\" ";
        while( !(cin >> y >> x)){
			cin.clear();
			cin.ignore();
			cout << "Incorrect input. Try with two num between 1 and 3 \n";
		}
        system("CLS");
    }
    while (!fill_board(ttt,y-1,x-1,ttt->p1sym));
    if(print_winner_results(ttt, is_full(ttt), check_for_winner(ttt)) == 1)
        ttt->end = 1;
}
/****************************************
 * Function : player2_choice
 * Description : player2 detemine where to
 * put their symbol
 * **************************************/
void player2_choice(tic_tac_toe *ttt){
    int y, x;
	do {
        print_board(ttt);
        cout    << ttt->player2 <<": Where would you like to put your \""
                << ttt->p2sym << "\" ";
         while( !(cin >> y >> x)){
			cin.clear();
			cin.ignore();
			cout << "Incorrect input. Try with two num between 1 and 3 \n";
		}
        system("CLS");
    }
while (!fill_board(ttt,y-1,x-1,ttt->p2sym));
    if(print_winner_results(ttt, is_full(ttt), check_for_winner(ttt)) == 1)
        ttt->end = 1;
}
/****************************************
 * Function : ultron
 * Description : Ultron's algorithm
 * **************************************/
void ultron(tic_tac_toe *ttt){
    int x = 3, y = 3;
	// determine ultron symbol
	char ultron_symbol,player_symbol;
	if (ttt->mode == 2){
		ultron_symbol = ttt->p1sym;
		player_symbol = ttt->p2sym;
	}
	else if (ttt->mode == 1){
		ultron_symbol = ttt->p2sym;
		player_symbol = ttt->p1sym;
	}
	//check all 9 spots if any player can win by on step.
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if(ttt->board[i][j] == ' '){
                fill_board(ttt,i,j,ultron_symbol);//put ultron sym on i,j
                if (check_for_winner(ttt) != 3-ttt->mode)//ultron does not win
                    ttt->board[i][j] = ' ';
                else{// ultron win within one step
                    print_winner_results(ttt, is_full(ttt), check_for_winner(ttt));
                    ttt->end = 1;
                    return;
                }
                fill_board(ttt,i,j,player_symbol);// put player sym on i,j
                if (check_for_winner(ttt) != ttt->mode){//player does not win
                    ttt->board[i][j] = ' ';
                }
                else {// player win within one step
                    ttt->board[i][j] = ' ';
                    y = i;
                    x = j;
                }
            }
        }
    }
	//if no one can win by one step, ultron will randomly fill the board.
    if(x > 2){
        do{
            x = rand()%3;
            y = rand()%3;
        }
        while (ttt->board[y][x] != ' ');
    }
	
	
    fill_board(ttt,y,x,ultron_symbol);
	system("CLS");
    if(print_winner_results(ttt, is_full(ttt), check_for_winner(ttt)) == 1)
        ttt->end = 1;
}
/****************************************
 * Function : modechoice
 * Description : mode choice determination
 * Mode 0 two players game 1 player move first
 * 2 Ultron move first.
****************************************/
void modechoice(tic_tac_toe *ttt){
    
    if (ttt->mode == 1){
        player1_choice(ttt);
		if(ttt->end == 0)
        	ultron(ttt);
	}
	else if (ttt->mode == 2){
		ultron(ttt);
		if(ttt->end == 0)
			player2_choice(ttt);
	}
	else if (ttt->mode == 0){
		player1_choice(ttt);
		if(ttt->end == 0)
			player2_choice(ttt);
	}
	else
		cout << "Mode is wrong assigned";
}