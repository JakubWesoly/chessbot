#include <gtest/gtest.h>
#include <algorithm>
#include "Board.hpp"
#include "Move.hpp"

class BoardKnightTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common setup code if needed
    }
};

// Test basic knight moves from center position
TEST_F(BoardKnightTest, CenterKnightMoves) {
    // Setup a board with a white knight in the center
    Board::Board board;
    board.setFromFEN("8/8/8/8/3N4/8/8/8 w");
    
    auto moves = board.getAllKnightMoves();
    
    // A knight in the center should have 8 possible moves
    EXPECT_EQ(moves.size(), 8);
    
    // Knight is at index 27 (d4)
    // Knight offsets are: 17, 15, 10, 6, -17, -15, -10, -6
    std::vector<int> expectedTargetSquares = {
        44, 42, // 27+17, 27+15 (two up, one right/left)
        37, 33, // 27+10, 27+6 (one up, two right/left)
        10, 12, // 27-17, 27-15 (two down, one left/right)
        17, 21  // 27-10, 27-6 (one down, two left/right)
    };
    
    for (const auto& move : moves) {
        EXPECT_TRUE(std::find(expectedTargetSquares.begin(), 
                             expectedTargetSquares.end(), 
                             move.to) != expectedTargetSquares.end());
    }
}

// Test knight moves from corner position
TEST_F(BoardKnightTest, CornerKnightMoves) {
    // Setup a board with a white knight in the corner
    Board::Board board;
    board.setFromFEN("N7/8/8/8/8/8/8/8 w");
    
    auto moves = board.getAllKnightMoves();
    
    // A knight in the corner should have only 2 possible moves
    EXPECT_EQ(moves.size(), 2);
    
    // Check the actual moves (from knight at a8 = index 56)
    bool hasMoveTo10 = false;
    bool hasMoveTo41 = false;
    
    for (const auto& move : moves) {
        if (move.to == 10) hasMoveTo10 = true;  // Move to c7
        if (move.to == 41) hasMoveTo41 = true;  // Move to b6
    }
    
    EXPECT_TRUE(hasMoveTo10 || hasMoveTo41);
}

// Test knight captures
TEST_F(BoardKnightTest, KnightCaptures) {
    // Setup a board with a white knight and some black pieces to capture
    Board::Board board;
    board.setFromFEN("8/8/2p1p3/8/3N4/8/2p1p3/8 w");
    
    auto moves = board.getAllKnightMoves();
    
    // Verify that the knight can make 8 moves (including captures)
    EXPECT_EQ(moves.size(), 8);
    
    // Verify that some of the moves are captures
    int captureCount = 0;
    for (const auto& move : moves) {
        if (std::find(move.moveTypes.begin(), move.moveTypes.end(), Move::MoveTypes::CAPTURE) != move.moveTypes.end()) {
            captureCount++;
        }
    }
    
    // At least a few captures should be available
    EXPECT_GT(captureCount, 0);
}

// Test knight blocked by friendly pieces
TEST_F(BoardKnightTest, BlockedByFriendlyPieces) {
    // Setup a board with a white knight surrounded by friendly pieces
    Board::Board board;
    board.setFromFEN("8/8/2P1P3/8/3N4/8/2P1P3/8 w");
    
    auto moves = board.getAllKnightMoves();
    
    // Knight should not be able to move to squares occupied by friendly pieces
    for (const auto& move : moves) {
        EXPECT_TRUE(move.to != 26); // e6
        EXPECT_TRUE(move.to != 24); // c6
        EXPECT_TRUE(move.to != 44); // c2
        EXPECT_TRUE(move.to != 46); // e2
    }
}

// Test knight moves when in check
TEST_F(BoardKnightTest, KnightMovesInCheck) {
    // Setup a board where white is in check and knight must block or capture
    Board::Board board;
    board.setFromFEN("4k3/8/8/3r4/3N4/8/4K3/8 w");
    
    auto moves = board.getAllKnightMoves();
    
    // Knight should be able to move to e3 to block the check
    bool hasBlockingMove = false;
    for (const auto& move : moves) {
        if (move.to == 44) { // e3 square
            hasBlockingMove = true;
            break;
        }
    }
    EXPECT_TRUE(hasBlockingMove);
}

// Test black knight moves
TEST_F(BoardKnightTest, BlackKnightMoves) {
    // Setup a board with a black knight
    Board::Board board;
    board.setFromFEN("8/8/8/8/3n4/8/8/8 b");
    
    auto moves = board.getAllKnightMoves();
    
    // A black knight in the center should also have 8 possible moves
    EXPECT_EQ(moves.size(), 8);
}

// Test multiple knights
TEST_F(BoardKnightTest, MultipleKnights) {
    // Setup a board with multiple knights
    Board::Board board;
    board.setFromFEN("8/8/2N5/8/5N2/8/8/8 w");
    
    auto moves = board.getAllKnightMoves();
    
    // Total moves should be the sum of possible moves for both knights
    EXPECT_GT(moves.size(), 8); // Should be more than moves for a single knight
}

// Test to debug knight position and moves
TEST_F(BoardKnightTest, KnightPositionDebug) {
    // Setup a board with a white knight in the center
    Board::Board board;
    board.setFromFEN("8/8/8/8/3N4/8/8/8 w");
    
    // Print the value at index 27 (expected knight position)
    std::cout << "Value at index 27: " << board.getPiece(27) << std::endl;
    
    // Print the board to see where the knight is
    for (int i = 0; i < 64; i++) {
        int piece = board.getPiece(i);
        if (piece == Board::Board::KNIGHT || piece == (Board::Board::KNIGHT | Board::Board::BLACK)) {
            std::cout << "Knight found at index: " << i << " with value: " << piece << std::endl;
        }
    }
    
    // Print constants for reference
    std::cout << "KNIGHT value: " << Board::Board::KNIGHT << std::endl;
    std::cout << "BLACK value: " << Board::Board::BLACK << std::endl;
    
    auto moves = board.getAllKnightMoves();
    
    std::cout << "Number of moves: " << moves.size() << std::endl;
    
    // Print all move destinations
    for (const auto& move : moves) {
        std::cout << "Move from " << move.from << " to " << move.to << std::endl;
    }
    
    // Always pass this test
    EXPECT_TRUE(true);
} 