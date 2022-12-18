#include "tictactoe/game_state.h"

// Check if the game is over
bool GameState::isFinalState(State b)
{
    // check rows
    for (unsigned int i = 0; i < SIZE; i++)
        if (b[i][0] == b[i][1] && b[i][0] == b[i][2] && b[i][0] != ' ') return true;
    // check cols
    for (unsigned int i = 0; i < SIZE; i++)
        if (b[0][i] == b[1][i] && b[0][i] == b[2][i] && b[0][i] != ' ') return true;
    // check diagonals
    if (b[0][0] == b[1][1] && b[0][0] == b[2][2] && b[0][0] != ' ') return true;
    if (b[0][2] == b[1][1] && b[0][2] == b[2][0] && b[0][2] != ' ') return true;
    // check full
    for (unsigned int i = 0; i < SIZE; i++) {
        for (unsigned int j = 0; j < SIZE; j++) {
            if (b[i][j] == ' ') return false;
        }
    }
    return true;
}

// Get the final score
// 1: X wins, -1: O wins, 0: draw
int GameState::getScoreFinalState(State b)
{
    // check rows
    for (unsigned int i = 0; i < SIZE; i++)
        if (b[i][0] == b[i][1] && b[i][0] == b[i][2] && b[i][0] != ' ') 
            return b[i][0] == 'X' ? 1 : -1;
    // check cols
    for (unsigned int i = 0; i < SIZE; i++)
        if (b[0][i] == b[1][i] && b[0][i] == b[2][i] && b[0][i] != ' ')
            return b[0][i] == 'X' ? 1 : -1;
    if (b[0][0] == b[1][1] && b[0][0] == b[2][2] && b[0][0] != ' ')
        return b[0][0] == 'X' ? 1 : -1;
    if (b[0][2] == b[1][1] && b[0][2] == b[2][0] && b[0][2] != ' ')
        return b[0][2] == 'X' ? 1 : -1;;
    return 0;
}

std::vector<GameState::State> GameState::getNextStates(State b)
{
    char nextPlayer = getNextPlayer(b);
    std::vector<State> states;
    for (unsigned int i = 0; i < SIZE; i++) {
        for (unsigned int j = 0; j < SIZE; j++) {
            if (b[i][j] == ' ') {
                State nextState = play(b, i, j, nextPlayer);
                states.push_back(nextState);
            }
        }
    }
    return states;
}

/// @brief Get the score of the state
/// and the best next state
/// @param b the state
/// @param isMax true if the current player is the maximizing player
/// @param alpha MAX best score
/// @param beta MIN best score
/// @return std::pair<int, State> the score and the best next state
std::pair<int, GameState::State> GameState::getScore(State b, bool isMax, int alpha, int beta)
{
    // base case
    if (isFinalState(b)) return make_pair(getScoreFinalState(b), b);

    // get all possible next states
    std::vector<State> states = getNextStates(b);
    
    // store the best score and the best next state
    const int INVALID = -10;
    int bestScore = INVALID;
    State bestState;

    // recursively get the score of the next states
    for (State ns: states) {
        std::pair<int, State> p = getScore(ns, !isMax, alpha, beta);
        int score = p.first;
        // update best score for MAX
        if (isMax) {
            if (bestScore < score || bestScore == INVALID) {
                bestScore = score;
                bestState = ns;
            }
            // prune if bestScore >= best option for MIN
            if (bestScore >= beta) return make_pair(bestScore, bestState);
            alpha = std::max(alpha, bestScore);
        } else { // update best score for MIN
            if (bestScore > score || bestScore == INVALID) {
                bestScore = score;
                bestState = ns;
            }
            // prune if bestScore <= best option for MAX
            if (bestScore <= alpha) return make_pair(bestScore, bestState);
            beta = std::min(beta, bestScore);
        }
    }
    return make_pair(bestScore, bestState);
}
