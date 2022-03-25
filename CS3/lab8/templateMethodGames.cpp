// Games, Template Method example
// Mikhail Nesterenko
// 2/4/2014

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using std::cout; using std::endl; using std::cin;
using std::max;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game{
public:
    Game():playersCount_(0), movesCount_(0), playerWon_(noWinner){}

    // template method
    void playGame(const int playersCount = 0) {
        playersCount_ = playersCount;
        movesCount_ = 0;

        initializeGame();

        for (int i = 0; !endOfGame(); i = (i + 1) % playersCount_ ) {
            makeMove(i);
            if (i == playersCount_ - 1) 
                ++movesCount_;
        }

        printWinner();
    }

    virtual ~Game(){}

protected:
   // primitive operations
   virtual void initializeGame() = 0;
   virtual void makeMove(int player) = 0;
   virtual void printWinner() = 0;
   virtual bool endOfGame() { return playerWon_ != noWinner;} // this is a hook
                   // returns true if winner is decided
   static const int noWinner=-1;

   int playersCount_;
   int movesCount_;
   int playerWon_;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly: public Game {
public:  
   // implementing concrete methods
   void initializeGame(){
      playersCount_ = rand() % numPlayers_ + 1 ; // initialize players
   }

   void makeMove(int player) {
      if (movesCount_ > minMoves_){ 
	 const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Monopoly, player "<< playerWon_<< " won in "
	   << movesCount_<< " moves." << endl;
   }

private:
   static const int numPlayers_ = 8; // max number of players
   static const int minMoves_ = 20; // nobody wins before minMoves_
   static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess: public Game {
public:
   void initializeGame(){
      playersCount_ = numPlayers_; // initalize players
      for(int i=0; i < numPlayers_; ++i) 
	     experience_[i] = rand() % maxExperience_ + 1 ; 
   }

   void makeMove(int player){
      if (movesCount_ > minMoves_){
	 const int chance = (rand() % maxMoves_) / experience_[player];
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Chess, player " << playerWon_ 
	   << " with experience " << experience_[playerWon_]
	   << " won in "<< movesCount_ << " moves over"
	   << " player with experience " << experience_[playerWon_== 0 ? 1:0] 
           << endl;
   }

private:
   static const int numPlayers_ = 2;
   static const int minMoves_ = 2; // nobody wins before minMoves_
   static const int maxMoves_ = 100; // somebody wins before maxMoves_
   static const int maxExperience_ = 3; // player's experience
                              // the higher, the greater probability of winning
   int experience_[numPlayers_]; 
};

class Dice: public Game {
public:
    void initializeGame() override {
        playersCount_ = numPlayers_;
    }

    bool endOfGame() override {
        return ((!rolls_[0] && !rolls_[1]) || movesCount_ == maxMoves_ - 1); // If both pass or we are out of turns
    }

    void makeMove(int player) override {
        int sum = 0;
        int n;
        char r;
        
        cout << (player ? "You" : "Computer") << " rolled: ";
        if (rolls_[player]) { // If the player chose to roll
            for (int i = 0; i < 5; i++) { // Roll the dice
                n = (1 + (rand() % 6));
                cout << n << ' ';
                sum += n; // Add the dice value to the sum
            }
            cout << "= " << sum;
            scores_[player] = max(sum, scores_[player]); // If the sum is bigger than the current score, replace it
        } else {
            cout << "passed";
        }
        cout << ", " << (player ? "your" : "computer's") << " highest score = " << scores_[player] << endl;

        if (player == 0)  { // Computer
            rolls_[player] = rand() % 2; // Might roll again, might not
        } else if (player == 1) {
            do { // Repeat until we get a valid answer
                cout << "Roll again? [y/n] ";
                cin.get(r); // Get the character
                cin.ignore(1, '\n'); // Throw away the newline
            } while (r != 'y' && r != 'n');
            rolls_[player] = r == 'y';
        }
    }

   void printWinner() override {
       cout << "Computer score: " << scores_[0] << ", your score: " << scores_[1] << endl;
       if (scores_[0] < scores_[1]) { // If the players score is higher than the computer's
           cout << "You win!" << endl;
       } else { // Otherwise
           cout << "You lose!" << endl;
       }
   }
private:
    static const int numPlayers_ = 2;
    static const int maxMoves_ = 3;
    int scores_[numPlayers_] = {0, 0};
    bool rolls_[numPlayers_] = {true, true};
};

int main() {
    srand(time(nullptr));

    Game* gp = nullptr;

    /*

    // play chess 10 times
    for (int i = 0; i < 10; ++i){ 
        gp = new Chess;
        gp->playGame(); 
        delete gp;
    }
        

    // play monopoly 5 times
    for (int i = 0; i < 5; ++i){
        gp = new Monopoly;
        gp->playGame(); 
        delete gp;
    }

    */

    gp = new Dice;
    gp->playGame();
    delete gp;
}
