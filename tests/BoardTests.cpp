#include <gtest/gtest.h>
#include "Board.hpp"
#include "Move.hpp"
#include <Menu.hpp>

class BoardTest : public ::testing::Test {
protected:
    Board::Board board;

    void SetUp() override {
        // Called before each test
        board = Board::Board();
    }
};

// TEST_F(BoardTest, DefaultPositionFEN) {
//     // Test setting up the standard chess starting position
//     const std::string startingFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
//     board.setFromFEN(startingFEN);

//     // Verify white pieces
//     EXPECT_EQ(board.getPiece(0), Board::Board::ROOK);
//     EXPECT_EQ(board.getPiece(1), Board::Board::KNIGHT);
//     EXPECT_EQ(board.getPiece(2), Board::Board::BISHOP);
//     EXPECT_EQ(board.getPiece(3), Board::Board::QUEEN);
//     EXPECT_EQ(board.getPiece(4), Board::Board::KING);
//     EXPECT_EQ(board.getPiece(5), Board::Board::BISHOP);
//     EXPECT_EQ(board.getPiece(6), Board::Board::KNIGHT);
//     EXPECT_EQ(board.getPiece(7), Board::Board::ROOK);

//     // Verify white pawns
//     for(int i = 8; i < 16; i++) {
//         EXPECT_EQ(board.getPiece(i), Board::Board::PAWN);
//     }

//     // Verify empty squares
//     for(int i = 16; i < 48; i++) {
//         EXPECT_EQ(board.getPiece(i), Board::Board::NONE);
//     }

//     // Verify black pawns
//     for(int i = 48; i < 56; i++) {
//         EXPECT_EQ(board.getPiece(i), Board::Board::PAWN | Board::Board::BLACK);
//     }

//     // Verify black pieces
//     EXPECT_EQ(board.getPiece(56), Board::Board::ROOK | Board::Board::BLACK);
//     EXPECT_EQ(board.getPiece(57), Board::Board::KNIGHT | Board::Board::BLACK);
//     EXPECT_EQ(board.getPiece(58), Board::Board::BISHOP | Board::Board::BLACK);
//     EXPECT_EQ(board.getPiece(59), Board::Board::QUEEN | Board::Board::BLACK);
//     EXPECT_EQ(board.getPiece(60), Board::Board::KING | Board::Board::BLACK);
//     EXPECT_EQ(board.getPiece(61), Board::Board::BISHOP | Board::Board::BLACK);
//     EXPECT_EQ(board.getPiece(62), Board::Board::KNIGHT | Board::Board::BLACK);
//     EXPECT_EQ(board.getPiece(63), Board::Board::ROOK | Board::Board::BLACK);
// }

// TEST_F(BoardTest, EmptyBoardFEN) {
//     // Test setting up an empty board
//     const std::string emptyFEN = "8/8/8/8/8/8/8/8";
//     board.setFromFEN(emptyFEN);

//     // Verify all squares are empty
//     for(int i = 0; i < 64; i++) {
//         EXPECT_EQ(board.getPiece(i), Board::Board::NONE);
//     }
// }

// TEST_F(BoardTest, InvalidFENCharacter) {
//     // Test handling of invalid FEN character
//     const std::string invalidFEN = "4k3/8/8/3X4/4p3/8/8/4K3";
    
//     // The function should exit with error message for invalid character
//     EXPECT_THROW(board.setFromFEN(invalidFEN), const char*);
// }

// TEST_F(BoardTest, InvalidFENFormat) {
//     // Test handling of invalid FEN format (too many squares)
//     const std::string invalidFEN = "4k3/8/8/3P5/4p3/8/8/4K3";
    
//     // The function should exit with error message for invalid board position
//     EXPECT_THROW(board.setFromFEN(invalidFEN), const char*);
// } 

TEST_F(BoardTest, PossibleMoves) {
    // Test possible moves for a piece
    std::string startingFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w";
    board.setFromFEN(startingFEN);

    // Test possible moves for white king
    std::vector<Move::Move> moves = board.getAllValidMoves();
    EXPECT_EQ(moves.size(), 20);

    startingFEN = "8/3k4/8/8/8/8/3K4/8 w";
    board.setFromFEN(startingFEN);
    moves = board.getAllValidMoves();
    // List valid moves
    for(auto move : moves) {
        std::cout << move.toString() << std::endl;
    }
    EXPECT_EQ(moves.size(), 6);
}

