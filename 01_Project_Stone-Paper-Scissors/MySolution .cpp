#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enGame { Stone = 1, Paper = 2, Scissors = 3 };

enum enWinner { Player = 1, Computer = 2 };

struct stInfoRounds
{
    short Player = 0;
    short Computer = 0;
    string RoundWinner;
};

struct stInfoOfResultGame
{
    short GameRounds = 0;
    short PlayerWonTimes = 0;
    short ComputerWonTimes = 0;
    short DrawTimes = 0;
    string FinalWinner = "";
};

short ReadRound()
{
    short NumberOfRound = 0;

    do
    {
        cout << "How Many Rounds From 1 to 10 ?\n";
        cin >> NumberOfRound;

    } while (NumberOfRound < 1 || NumberOfRound > 10);

    return NumberOfRound;
}

int RandomNumber(int From, int To)
{
    int RandNum = rand() % (To - From + 1) + From;
    return RandNum;
}

enGame PlayerChoice()
{
    short ChoicePlayer = 0;

    do
    {

        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
        cin >> ChoicePlayer;

    } while (ChoicePlayer < 1 || ChoicePlayer > 3);

    cout << "\n";
    return (enGame)ChoicePlayer;
}

enGame ComputerChoices()
{
    short ChoiceComputer = RandomNumber(1, 3);
    return (enGame)ChoiceComputer;
}

string WhoWinTheRound(enGame PlayerChoice, enGame ComputerChoice)
{

    if (PlayerChoice == ComputerChoice)
    {
        system("color 6F");
        return "Draw";
    }
    if (PlayerChoice == enGame::Paper && ComputerChoice == enGame::Stone)
    {
        system("color 2F");
        return "Player";
    }
    if (PlayerChoice == enGame::Stone && ComputerChoice == enGame::Scissors)
    {
        system("color 2F");
        return "Player";
    }
    if (PlayerChoice == enGame::Scissors && ComputerChoice == enGame::Paper)
    {
        system("color 2F");
        return "Player";
    }
    else
    {
        cout << "\a";
        system("color 4F");
        return "Computer";
    }
}

stInfoRounds AddInfoRound(enGame PlayerChoice, enGame ComputerChoice, string Winner)
{

    stInfoRounds InfoRounds;

    InfoRounds.Player = PlayerChoice;
    InfoRounds.Computer = ComputerChoice;
    InfoRounds.RoundWinner = Winner;

    return InfoRounds;
}

string GetChoiceName(enGame Choice)
{
    switch (Choice)
    {
    case enGame::Stone:
        return "Stone";
    case enGame::Paper:
        return "Paper";
    case enGame::Scissors:
        return "Scissors";
    default:
        return "Unkown";
    }
}

void PrintResultOfRound(enGame PlayerChoice, enGame ComputerChoice, string Winner)
{
    stInfoRounds InfoRounds = AddInfoRound(PlayerChoice, ComputerChoice, Winner);


    cout << "Player1 Choice: " << GetChoiceName(PlayerChoice) << endl;
    cout << "Computer Choice: " << GetChoiceName(ComputerChoice) << endl;
    cout << "Round Winner: " << InfoRounds.RoundWinner << endl;

    cout << "____________________________________\n";
}

void GameOver()
{
    cout << "\n\t\t\t\t_______________________________________________\n";
    cout << "\n\t\t\t\t\t     +++ G a m e O v e r +++\n";
    cout << "\n\t\t\t\t_______________________________________________\n";
}

stInfoOfResultGame PrintFinalResults(stInfoOfResultGame FinalResults)
{

    cout << "\n\t\t\t\t______________ [ Game Results ] _______________\n";
    cout << "\n\t\t\t\t" << "Game Rounds         : " << FinalResults.GameRounds;
    cout << "\n\t\t\t\t" << "Player1 won times   : " << FinalResults.PlayerWonTimes;
    cout << "\n\t\t\t\t" << "Computer won times  : " << FinalResults.ComputerWonTimes;
    cout << "\n\t\t\t\t" << "Draw times          : " << FinalResults.DrawTimes;
    cout << "\n\t\t\t\t" << "Final Winner        : " << FinalResults.FinalWinner;
    cout << "\n\t\t\t\t_______________________________________________\n";

    return FinalResults;
}

bool PlayAgainOrNot()
{
    char choice = 'A';
    short Space = 3;
    cout << "\n\n";


    cout << "\n\t\t\t\t\t Do you want to play Again ? Y/N ? ";
    cout << "\n\n";
    cin >> choice;


    if (choice == 'Y' || choice == 'y')
    {
        system("cls");
        system("color 0F");
        return true;
    }
    return false;
}

void StartGame()
{
    short Number = ReadRound();
    enGame Player, Computer;
    string Winner = "";

    stInfoOfResultGame GameResults;
    GameResults.GameRounds = Number;

    for (int i = 1; i <= Number; i++)
    {
        cout << "\nRound [" << i << "] begins: \n";
        Player = PlayerChoice();
        Computer = ComputerChoices();
        Winner = WhoWinTheRound(Player, Computer);

        if (Winner == "Player")
            GameResults.PlayerWonTimes++;
        else if (Winner == "Computer")
            GameResults.ComputerWonTimes++;
        else
            GameResults.DrawTimes++;

        cout << "\n_____________Round [" << i << "] _____________\n\n";
        PrintResultOfRound(Player, Computer, Winner);
    }

    if (GameResults.PlayerWonTimes == GameResults.ComputerWonTimes)
        GameResults.FinalWinner = "Draw";
    else if (GameResults.PlayerWonTimes > GameResults.ComputerWonTimes)
        GameResults.FinalWinner = "Player";
    else
        GameResults.FinalWinner = "Computer";

    GameOver();
    PrintFinalResults(GameResults);
    cout << "\n\n";
}

int main()
{
    srand((unsigned)time(NULL));

    do
    {
        StartGame();

    } while (PlayAgainOrNot());

    return 0;
}