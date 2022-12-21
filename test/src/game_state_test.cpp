#include <gtest/gtest.h>
#include "tictactoe/game_state.h"

class GameStateTest : public ::testing::Test
{
protected:
    // test get final message at the end of the game
    void TestGetFinalMessage() { 
        state.finalScore = 1;
        EXPECT_EQ(state.getFinalMessage(), "X wins");
        state.finalScore = -1;
        EXPECT_EQ(state.getFinalMessage(), "O wins");
        state.finalScore = 0;
        EXPECT_EQ(state.getFinalMessage(), "It is a draw");
        state.finalScore = 2;
        EXPECT_EQ(state.getFinalMessage(), "Unknown");
    }

    // test the initial state of the game
    void TestPlayerTurn() {
        EXPECT_EQ(state.currentPlayer, 'X');
        state.currentPlayer = 'O';
        EXPECT_EQ(state.currentPlayer, 'O');
    }

    // test the initial state of the game
    void TestGameStop() {
        EXPECT_EQ(state.gameStop, false);
        state.gameStop = true;
        EXPECT_EQ(state.gameStop, true);
    }

    // test player turn at the beginning of the game
    void TestPlayAndChangePlayer() {
        state.playAndChangePlayer(0, 0);
        EXPECT_EQ(state.s[0][0], 'X');
        EXPECT_EQ(state.currentPlayer, 'O');
        state.playAndChangePlayer(0, 1);
        EXPECT_EQ(state.s[0][1], 'O');
        EXPECT_EQ(state.currentPlayer, 'X');
    }

    // test terminal state
    void TestCheckAndProcessFinalState() {
        {
            GameState state1;
            state1.s[0][0] = 'X'; state1.s[0][1] = 'X'; state1.s[0][2] = 'X';
            state1.s[1][0] = 'O'; state1.s[1][1] = 'O'; state1.s[1][2] = 'X';
            state1.s[2][0] = ' '; state1.s[2][1] = ' '; state1.s[2][2] = ' ';
            EXPECT_EQ(state1.isFinalState(state1.s), true);
            state1.checkAndProcessFinalState();
            EXPECT_EQ(state1.finalScore, 1);
            EXPECT_EQ(state1.gameStop, true);
        }

        {
            GameState state1;
            state1.s[0][0] = 'X'; state1.s[0][1] = 'X'; state1.s[0][2] = ' ';
            state1.s[1][0] = 'O'; state1.s[1][1] = 'O'; state1.s[1][2] = 'O';
            state1.s[2][0] = 'X'; state1.s[2][1] = ' '; state1.s[2][2] = ' ';
            EXPECT_EQ(state1.isFinalState(state1.s), true);
            state1.checkAndProcessFinalState();
            EXPECT_EQ(state1.finalScore, -1);
            EXPECT_EQ(state1.gameStop, true);
        }

        {
            GameState state1;
            state1.s[0][0] = 'X'; state1.s[0][1] = 'X'; state1.s[0][2] = 'O';
            state1.s[1][0] = 'O'; state1.s[1][1] = 'O'; state1.s[1][2] = 'X';
            state1.s[2][0] = 'X'; state1.s[2][1] = 'O'; state1.s[2][2] = 'X';
            EXPECT_EQ(state1.isFinalState(state1.s), true);
            state1.checkAndProcessFinalState();
            EXPECT_EQ(state1.finalScore, 0);
            EXPECT_EQ(state1.gameStop, true);
        }
    }

    void TestScreen() {
        EXPECT_EQ(state.playScreen, GameState::PlayScreen::PlayModeScreen);
        state.playScreen = GameState::PlayScreen::PlayingScreen;
        EXPECT_EQ(state.playScreen, GameState::PlayScreen::PlayingScreen);
    }
    
    void TestScoreFinalState() {
        {
            GameState state1;
            state.s[0][0] = 'X'; state1.s[0][1] = 'X'; state1.s[0][2] = 'X';
            state.s[1][0] = 'X'; state1.s[1][1] = 'O'; state1.s[1][2] = 'O';
            state.s[2][0] = 'O'; state1.s[2][1] = ' '; state1.s[2][2] = ' ';
            EXPECT_EQ(state1.getScoreFinalState(state1.s), 1);
        }        {
            GameState state1;
            state1.s[0][0] = 'X'; state1.s[0][1] = 'O'; state1.s[0][2] = 'X';
            state1.s[1][0] = 'X'; state1.s[1][1] = 'O'; state1.s[1][2] = 'O';
            state1.s[2][0] = 'X'; state1.s[2][1] = ' '; state1.s[2][2] = ' ';
            EXPECT_EQ(state1.getScoreFinalState(state1.s), 1);
        }
    }

private:
    GameState state;
};

TEST_F(GameStateTest, getFinalMessage) {
    TestGetFinalMessage();
}

TEST_F(GameStateTest, playerTurn) {
    TestPlayerTurn();
}

TEST_F(GameStateTest, gameStop) {
    TestGameStop();
}

TEST_F(GameStateTest, playAndChangePlayer) {
    TestPlayAndChangePlayer();
}

TEST_F(GameStateTest, checkAndProcessFinalState) {
    TestCheckAndProcessFinalState();
}

TEST_F(GameStateTest, screen) {
    TestScreen();
}

TEST_F(GameStateTest, scoreFinalState) {
    TestScoreFinalState();
}