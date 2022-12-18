#include <vector>
#include <string>
#include <algorithm>

#include "tictactoe/game_state.h"

// Get final message to display when game is over
std::string GameState::getFinalMessage() const
{
    switch (finalScore) {
        case 1: return "X wins";
        case -1: return "O wins";
        case 0: return "It is a draw";
        default: return "Unknown";
    }
}

// Play the game on the given position
void GameState::playAndChangePlayer(int i, int j) {
    thinking = true;
    if (i >= 0 && i < SIZE && j >= 0 && j < SIZE 
        && getPlay(i, j) == ' ' && !gameStop) {
        setPlay(i, j, currentPlayer);
        togglePlayer();
        checkAndProcessFinalState();

        // If the game is not over and the play mode is HumanVsMachine
        // then play the computer move
        if (!gameStop && playMode == PlayMode::HumanVsMachine) {
            std::pair<int, int> nextMove = getComputerPlay(s);
            setPlay(nextMove.first, nextMove.second, currentPlayer);
            togglePlayer();
            checkAndProcessFinalState();
        }
    }
    thinking = false;
}

char GameState::getPlay(unsigned int i, unsigned int j) const
{
    return s[i][j];
}

char GameState::getPlay(int i, int j) const
{
    if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) {
        return getPlay(static_cast<unsigned int>(i), static_cast<unsigned int>(j));
    } else {
        return ' ';
    }
}
void GameState::togglePlayer()
{
    currentPlayer = (currentPlayer == 'X') ? 'O':'X';
}

void GameState::computerPlayFirst() {
    thinking = true;
    std::pair<int, int> nextMove = getComputerPlay(s);
    setPlay(nextMove.first, nextMove.second, currentPlayer);
    togglePlayer();
    checkAndProcessFinalState();
    thinking = false;
}

void GameState::resetGame()
{
    s = State(SIZE, Row(SIZE, ' '));
    gameStop = false;
    currentPlayer = 'X';
    finalScore = -10;
}

// Check if the game is over and update the final score
void GameState::checkAndProcessFinalState() {
    if (isFinalState(s)) {
        finalScore = getScoreFinalState(s);
        gameStop = true;
    }
}

char GameState::getNextPlayer(State b)
{
    int countX = 0, countO = 0;
    for (unsigned int i = 0; i < SIZE; i++) {
        for (unsigned int j = 0; j < SIZE; j++) {
            if (b[i][j] == 'X') countX++;
            else if (b[i][j] == 'O') countO++;
        }
    }
    if (countX == countO) return 'X';
    else return 'O';
}

GameState::State GameState::play(State b, unsigned int ii, unsigned int jj, char player)
{
    State newState = State(3, Row(3, ' '));
    for (unsigned int i = 0; i < SIZE; i++) {
        for (unsigned int j = 0; j < SIZE; j++) {
            newState[i][j] = b[i][j];
        }
    }
    newState[ii][jj] = player;
    return newState;
}

void GameState::setPlay(unsigned int i, unsigned int j, char player)
{
    s[i][j] = player;
}

void GameState::setPlay(int i, int j, char player)
{
    if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) {
        setPlay(static_cast<unsigned int>(i), static_cast<unsigned int>(j), player);
    }
}

std::pair<unsigned int, unsigned int> GameState::getComputerPlay(State b)
{
    char player = getNextPlayer(b);
    std::pair<int, State> p = getScore(b, player=='X');
    State newState = p.second;
    const unsigned int INVALID = 100;
    for (unsigned int i = 0; i < SIZE; i++) {
        for (unsigned int j = 0; j < SIZE; j++) {
            if (newState[i][j] != b[i][j]) return std::make_pair(i, j);
        }
    }
    return std::make_pair(INVALID, INVALID);
}