/*
 * BRUNO D. IMFURANKASE M.
 * ID: 2597151
 * DEPARTMENT: SOFTWARE ENGINEERING
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//-------------------This function will generate a random dice number between 1 and 6.

int rollDice(){
    int dice_number=0;
    dice_number=rand() % 6 + 1;
//return the result stored in roll number
    return dice_number;
}



//---------------This function will take the array and round number, and places the token to the first available empty location starting from the left of the board.

void placeCompToken(char** arr,int row,int column,int round_nbr){

    int current_rol=row-round_nbr;
    int current_column=0;
    for(current_column = 0; current_column < column; current_column++){
        //check for the left most empty place
        if(arr[current_rol][current_column]==' '){
            arr[current_rol][current_column]='*';
            printf("My turn -> I placed token to location (%d,%d)\n",(current_rol+1),(current_column+1));
            break;
        }

    }

}

//This function will take the array as a parameter and then ask the user where to place the token.



void placeUserToken(char** arr,int row,int column,int round_nbr){

    int input_row,input_column;
    //getting the location input from the user
    do{
        printf("Your turn -> Enter location to place your token:");
        scanf("(%d,%d)", &input_row,&input_column);
        while((getchar())!='\n');

        //If a user enters a location which is outside the board
        if(input_row>row || input_column>column){
            printf("You cannot place a token outside the board!\n");
        }
            // Player enters location where a token is already
        else if(arr[(input_row-1)][input_column-1]!=' '){
            printf("A token is already placed there!\n");
        }
            //If the user enters a location that doesn't correspond the current round
        else if((input_row+round_nbr)<=row){
            int current_round=(row+1)-round_nbr;
            printf("At this turn you can only place token to row %d!\n",current_round);
        }

        else{
            arr[(input_row-1)][input_column-1]='+';
            break;
        }

    }while(1);
}
//-------------------This function will take the array, round number and score array as parameters, and if there is a possibility to match three tokens, the score of both sides will be updated


void checkMatch(char** board,int row,int column,int round_nbr,int** scoreboard){

    int current_row=(row-round_nbr);
    int current_column;
    int player_count=0;
    int computer_count=0;

    for(current_column=0;current_column<column;current_column++){
        if(board[current_row][current_column]=='+'){
            player_count++;
            computer_count=0;

            //Add one point to score of player once the player_count has reach 3
            if (player_count==3){

                player_count=0;
                scoreboard[0][1]=scoreboard[0][1]+1;
            }
        }
        else if(board[current_row][current_column]=='*'){
            computer_count++;
            player_count=0;
            //Add one point to score of Computer once the computer_count has reach 3
            if (computer_count==3){
                computer_count=0;
                scoreboard[0][0]=scoreboard[0][0]+1;
            }
        }
    }

    printf("Scores [My Yours]: [%d %d]\n",scoreboard[0][0],scoreboard[0][1]);


}
//----------------------This function displays the board on the screen


void displayBoard(char** arr,int row,int column){
    printf("Board:\n");
    printf("  ");
    int current_column;
    for (current_column = 0; current_column < column; current_column++){
        printf("%d ",(current_column+1));
    }
    printf("\n");
    //Going through all the rows and columns to print them on the screen
    int current_row;
    for (current_row = 0; current_row < row; current_row++){
        printf("%d ",(current_row+1));
        for (current_column = 0; current_column < column; current_column++){
            printf("%c ",arr[current_row][ current_column]);
        }
        printf("\n");
    }

}
//Refreshing the board with empty chars and 0 once the user decides to play a new game

void renew_array(char** arr,int** scoreboard){

    int row = 7, column = 6, current_row, current_column;
    int row_score=1,column_score=2,current_row_score, current_column_score;

    for (current_row = 0; current_row < row; current_row++){
        for ( current_column = 0; current_column < column; current_column++){
            arr[current_row][current_column] = ' ';
        }
    }


    for (current_row_score = 0;current_row_score < row_score; current_row_score++){
        for ( current_column_score = 0;current_column_score < column_score; current_column_score++){
            scoreboard[current_row_score ][current_column_score] = 0;
        }
    }

}

//---------------------The main function starts from here and it is also where the empty board will be created

int main(){
    int row = 7, column = 6, current_row;
    //row and columns for the Score board
    int row_score=1,current_row_score;

    int round_nbr=1,count_plays;char user_input;

    //player and computer variable are for holding the rolled dice value
    int player;
    int computer;

    char** g_board = (char**)malloc(row * sizeof(char*));

    int** scoreboard = (int**)malloc(row_score * sizeof(int*));

    //loop through the cols row by row and give it size
    for (current_row = 0; current_row < row; current_row++)
        g_board[current_row] = (char*)malloc(column * sizeof(char));

    for (current_row_score= 0; current_row_score < row_score; current_row_score++)
        scoreboard[current_row_score] = (int*)malloc(column * sizeof(int));
//end of loops
    //call the function to add empty element and 0 to the game board and score card
    renew_array(g_board,scoreboard);



//-----------------The Game starts from here.



    printf("Welcome to the PopThree :)\nLet`s get started!\n\n-----------------------------------------------\n\n");

    srand(time(0));
    while(1){
        renew_array(g_board,scoreboard);
        do{
            player=rollDice();
            computer=rollDice();
        }while(player==computer);

        printf("\nI have rolled the dice and got %d!\n",computer);
        printf("I have rolled the dice for you and you got %d!\n",player);

        //Printing the board
        displayBoard(g_board,row,column);

        //Checking who got the highest dice number from the rolled dice in order to start the game
        if(player>computer){
            //ensuring the players just go for rounds accord to the Game board size
            while(round_nbr<(row+1)){
                printf("------------------Round %d----------------------\n",round_nbr);
                //count_play will keep track of the number of columns to go through.
                count_plays=0;
                while(count_plays<column){
                    //call the function for the user to play
                    placeUserToken(g_board,row,column,round_nbr);
                    displayBoard(g_board,row,column);
                    count_plays++;
                    //call the function for the computer to play
                    placeCompToken(g_board,row,column,round_nbr);
                    displayBoard(g_board,row,column);
                    count_plays++;
                }
                //check the current score and display it
                checkMatch(g_board,row,column,round_nbr,scoreboard);
                round_nbr++;
            }


        }
        else{

            while(round_nbr<(row+1)){
                printf("------------------Round %d----------------------\n",round_nbr);
                count_plays=0;
                while(count_plays<column){
                    //call the function for the computer to play
                    placeCompToken(g_board,row,column,round_nbr);
                    displayBoard(g_board,row,column);
                    count_plays++;
                    //call the function for the user to play
                    placeUserToken(g_board,row,column,round_nbr);
                    displayBoard(g_board,row,column);
                    count_plays++;
                }
                //display the score
                checkMatch(g_board,row,column,round_nbr,scoreboard);
                round_nbr++;
            }

        }

        //Check who won the game. g_board[0][0] is for Computer while g_board[0][1] is for Player
        if(scoreboard[0][0]>scoreboard[0][1]){
            printf("Your Lost!!!\n");
        }
        else if(scoreboard[0][0]<scoreboard[0][1]){
            printf("You won!!!\n");
        }
        else{
            printf("Draw!!!\n");
        }
        printf("------------------End----------------------\n");

        printf("Would you like to play again (Y/N)?");
        scanf("%c",&user_input);
        while((getchar())!='\n');
        //Take input to see if Player still wants to play
        if(user_input=='N'){
            break;
        }
        //if Yes then restart the game
        round_nbr=1;
    }

    //freeing the memory
    for (current_row = 0; current_row < row; current_row++)
        free(g_board[current_row]);



    return 0;
}

