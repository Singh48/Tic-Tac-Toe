#include <iostream>
#include <string>
#include <algorithm>
#include <limits.h>
#include <ctype.h>
#include <vector>

using namespace std;

class Game
{
    private:
    char cmp = 'X';
    char usr = 'O';
    char emt = '-';
    int INF = (int)1e9;
    struct moves
    {
        int x;
        int y;
    };
    
    vector<string> board = vector<string>(3, "---");
    void printBoard()
    {
        for (int i=0; i<3; i++)
        {
            cout << "\t";
            for (int j=0; j<3; j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
        //for (auto s: board) cout << s << endl;
        cout << "*******************************\n";
    }

    void debug()
    {
        board[0][0] = cmp;
        board[1][0] = usr;
        board[1][1] = usr;
        board[2][0] = cmp;
        board[2][2] = cmp;
    }

    public:
    Game(int c)
    {
        //for (int i=0; i<3; i++) board.push_back("---");
        if (c)
        { 
            board[0][0] = cmp;
            //debug();
            cout << "Computer's Turn: \n";
            printBoard();
            c = 0;
        }
        
        playChance(c);
    }

    void playChance(int c)
    {
        int score = 0;
        moves* mv = new moves();
        int i, j;
        while (1)
        {
            score = evaluate();
            if (score == 10)
            {
                cout << "--- Computer Wins ---\nGame Over\n";
                break;
            }
            else if (score == -10)
            {
                cout << "--- Human Wins ---\nGame Over\n";
                break;
            }
            else if (!movesLeft())
            {
                cout << "--- Nobody Wins ---\nGame Over\n";
                break;
            }
            //cout << "========\n";
            //printBoard();
            if (c)
            {
                mv = minimax(1);
                board[mv->x][mv->y] = cmp;
                cout << "Computer's Turn: \n";
                printBoard();
                c = 0;
            }
            else
            {
                cout << "Your Turn: \n";
                cout << "Enter row and column: ";
                cin >> i >> j;
                board[i][j] = usr;
                printBoard();
                c = 1;
            }
        }
    }

    int evaluate()
    {
        for (int i=0; i<3; i++)
        {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            {
                if (board[i][0] == cmp) return 10;
                else if (board[i][0] == usr) return -10;
            }
        }

         for (int i=0; i<3; i++)
        {
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            {
                if (board[0][i] == cmp) return 10;
                else if (board[0][i] == usr) return -10;
            }
        }

        if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        {
            if (board[1][1] == cmp) return 10;
            else if (board[1][1] == usr) return -10;
        }

        if (board[2][0] == board[1][1] && board[1][1] == board[2][0])
        {
            if (board[1][1] == cmp) return 10;
            else if (board[1][1] == usr) return -10;
        }

        return 0;
    }

    bool movesLeft()
    {
        for (int i=0; i<3; i++)
        {
            for (int j=0; j<3; j++)
                if (board[i][j] == emt) return true;
        }
        return false;
    }

    moves* minimax(int isMax)//, int alpha, int b)
    {
        //cout << "minimax : \n";
        moves* mv = new moves();
        if (isMax)
        {
            int score;
            int max_score = INT_MIN;
            for (int i=0; i<3; i++)
            {
                for (int j=0; j<3; j++)
                {
                    if (board[i][j] == emt)
                    {
                        board[i][j] = cmp;
                        score = minimizer();
                        if (score > max_score)
                        {
                            max_score = score;
                            mv->x = i;
                            mv->y = j;
                        }
                        board[i][j] = emt;
                        //cout << i << " " << j << endl;
                    }
                }
            }
        }
        return mv;
    }

    int minimizer()
    {
        //cout << "\tminimizer\n";
        int score = evaluate();
        if (score != 0)
        { 
            //cout << "\tevaluate = " << score << endl;
            return score;
        }
        else if (!movesLeft())
        {
            //cout << "\tno moves left\n"; 
            return score;
        }

        int min_score = INT_MAX;
        for (int i=0; i<3; i++)
        {
            for (int j=0; j<3; j++)
            {
                if (board[i][j] == emt)
                {
                    board[i][j] = usr;
                    score = maximizer();
                    if (score < min_score)
                    {
                        min_score = score;
                    }
                    board[i][j] = emt;
                }
            }
        }
        //cout << "\tmin_score = " << min_score << endl;
        return min_score;
    }

    int maximizer()
    {
        //cout << "\tmaximizer\n";
        int score = evaluate();
        if (score != 0)
        { 
            //cout << "\t evaluate = " << score << endl;
            return score;
        }
        else if (!movesLeft())
        {
            //cout << "\t no moves left\n"; 
            return score;
        }

        int max_score = INT_MIN;
        for (int i=0; i<3; i++)
        {
            for (int j=0; j<3; j++)
            {
                if (board[i][j] == emt)
                {
                    board[i][j] = cmp;
                    score = minimizer();
                    if (score > max_score)
                    {
                        max_score = score;
                    }
                    board[i][j] = emt;
                }
            }
        }
        //cout << "\t max_score = " << max_score << endl;
        return max_score;
    }
};

int main ()
{
    cout << "---- Tic-Tac-Toe ----\n";
    cout << "\n Do you want first Chance (y/n) : ";
    char cmd;
    cin >> cmd;
    int computer=1;// human=0;
    if (toupper(cmd) == 'Y') computer = 0;    
    Game newGame(computer);
}