#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName = "";
};

struct stGameResults
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string FinalWinnerName = "";
};

int RandomNumber(int From, int To)
{
    int RandNum = rand() % (To - From + 1) + From;
    return RandNum;
}

short ReadHowManyRounds()
{
    short GameRounds = 1;

    do
    {
        cout << "How Many Rounds From 1 To 10 ? ";
        cin >> GameRounds;

        cout << "\n";

    } while (GameRounds < 1 || GameRounds > 10);

    return GameRounds;
}

enGameChoice Player1Choice()
{
    short PlayerChoice = 1;

    do
    {

        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
        cin >> PlayerChoice;

    } while (PlayerChoice < 1 || PlayerChoice > 3);

    return enGameChoice(PlayerChoice);
}

enGameChoice GetComputerChoice()
{
    return enGameChoice(RandomNumber(1, 3));
}

string ChoiceName(enGameChoice Choice)
{
    string ArrGameChoices[3] = { "Stone", "Paper", "Scissors" };
    return ArrGameChoices[Choice - 1];
}

string ChoiceWinnerName(enWinner Winner)
{
    string ArrWinnerName[3] = { "Player","Computer","Draw" };
    return ArrWinnerName[Winner - 1];
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
    {
        return enWinner::Draw;
    }
    switch (RoundInfo.ComputerChoice)
    {
    case enGameChoice::Stone:
        if (RoundInfo.Player1Choice == enGameChoice::Paper)
        {
            return enWinner::Player;
        }
        break;
    case enGameChoice::Paper:
        if (RoundInfo.Player1Choice == enGameChoice::Scissors)
        {
            return enWinner::Player;
        }
        break;
    case enGameChoice::Scissors:
        if (RoundInfo.Player1Choice == enGameChoice::Stone)
        {
            return enWinner::Player;
        }
        break;
    }

    return enWinner::Computer;
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player:
        system("color 2F");
        break;

    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;

    default:
        system("color 6F");
        break;
    }
}

void PrintRoundResults(stRoundInfo RoundInfo)
{

    cout << "\n_________ Round [" << RoundInfo.RoundNumber << "] __________\n\n";
    cout << "Player1 Choice   : " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice  : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Winner Name      : [" << RoundInfo.WinnerName << "] \n";
    cout << "______________________________\n" << endl;

    SetWinnerScreenColor(RoundInfo.Winner);
}

string Tabs(short NumberOfTabs)
{
    string T = "";

    for (short i = 1; i < NumberOfTabs; i++)
    {
        T += "\t";
    }

    return T;
}

enWinner WhoWonTheGame(short Player1WonTimes, short ComputerWonTimes)
{
    if (Player1WonTimes > ComputerWonTimes)
        return enWinner::Player;
    else if (ComputerWonTimes > Player1WonTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

stGameResults FillGameResults(short GameRound, short Player1WonTimes, short ComputerWonTimes, short DrawTimes)
{
    stGameResults GameResults;

    GameResults.GameRounds = GameRound;
    GameResults.Player1WinTimes = Player1WonTimes;
    GameResults.ComputerWinTimes = ComputerWonTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WonTimes, ComputerWonTimes);
    GameResults.FinalWinnerName = ChoiceWinnerName(GameResults.GameWinner);

    return GameResults;
}

void ShowGameOverScreen()
{
    cout << Tabs(5) << "_______________________________________________\n\n";
    cout << Tabs(5) << "             +++ G a m e O v e r +++           \n";
    cout << Tabs(5) << "_______________________________________________\n\n";
}

void ShowFinalGameResults(stGameResults GameResults)
{

    cout << Tabs(5) << "_______________ [ Game Results ] ______________\n\n";
    cout << Tabs(5) << " Game Rounds        : " << GameResults.GameRounds << endl;
    cout << Tabs(5) << " Player1 Won Times  : " << GameResults.Player1WinTimes << endl;
    cout << Tabs(5) << " Computer Won Times : " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(5) << " Draw Times         : " << GameResults.DrawTimes << endl;
    cout << Tabs(5) << " Final Winner       : " << GameResults.FinalWinnerName << endl;
    cout << Tabs(5) << "_______________________________________________\n\n";

    this_thread::sleep_for(chrono::seconds(1));

    SetWinnerScreenColor(GameResults.GameWinner);
}

stGameResults PlayGame(short HowManyRound)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRound; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = Player1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = ChoiceWinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player)
            Player1WinTimes++;
        else  if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;


        PrintRoundResults(RoundInfo);
    }
    return FillGameResults(HowManyRound, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

void RestScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        RestScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << endl << Tabs(6) << "Do You Wnat Play Again? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{

    srand((unsigned)time(NULL));
    StartGame();

    return 0;
}