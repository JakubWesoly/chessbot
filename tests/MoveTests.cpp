#include <gtest/gtest.h>
#include "Move.hpp"
#include <iostream>

class MoveTest : public ::testing::Test {
protected:
    // Helper function to check if a move has a specific move type
    bool hasMoveType(const Move::Move& move, Move::MoveTypes type) {
        return std::find(move.moveTypes.begin(), move.moveTypes.end(), type) != move.moveTypes.end();
    }
};

TEST_F(MoveTest, BasicPieceMoves) {
    // Test basic piece moves
    Move::Move knight_move(std::string("Nf3"));
    EXPECT_EQ(knight_move.pieceType, Move::PieceType::KNIGHT);
    EXPECT_EQ(knight_move.to, 21); // f3 = (2 * 8 + 5)
    EXPECT_TRUE(knight_move.isValid);
    EXPECT_EQ(knight_move.toString(), std::string("Nf3"));

    Move::Move bishop_move(std::string("Bd4"));
    EXPECT_EQ(bishop_move.pieceType, Move::PieceType::BISHOP);
    EXPECT_EQ(bishop_move.to, 27); // d4 = (3 * 8 + 3)
    EXPECT_TRUE(bishop_move.isValid);
    EXPECT_EQ(bishop_move.toString(), std::string("Bd4"));

    Move::Move queen_move(std::string("Qe4"));
    EXPECT_EQ(queen_move.pieceType, Move::PieceType::QUEEN);
    EXPECT_EQ(queen_move.to, 28); // e4 = (3 * 8 + 4)
    EXPECT_TRUE(queen_move.isValid);
    EXPECT_EQ(queen_move.toString(), std::string("Qe4"));

    Move::Move king_move(std::string("Ke2"));
    EXPECT_EQ(king_move.pieceType, Move::PieceType::KING);
    EXPECT_EQ(king_move.to, 12); // e2 = (1 * 8 + 4)
    EXPECT_TRUE(king_move.isValid);
    EXPECT_EQ(king_move.toString(), std::string("Ke2"));
}

TEST_F(MoveTest, PawnMoves) {
    // Test basic pawn moves
    Move::Move pawn_move(std::string("e4"));
    EXPECT_EQ(pawn_move.pieceType, Move::PieceType::PAWN);
    EXPECT_EQ(pawn_move.to, 28); // e4 = (3 * 8 + 4)
    EXPECT_TRUE(pawn_move.isValid);
    EXPECT_EQ(pawn_move.toString(), std::string("e4"));

    // Test pawn captures
    Move::Move pawn_capture(std::string("exd5"));
    EXPECT_EQ(pawn_capture.pieceType, Move::PieceType::PAWN);
    EXPECT_EQ(pawn_capture.to, 35); // d5 = (4 * 8 + 3)
    EXPECT_EQ(pawn_capture.from, 4); // e-file = 4
    EXPECT_TRUE(hasMoveType(pawn_capture, Move::MoveTypes::CAPTURE));
    EXPECT_TRUE(pawn_capture.isValid);
    EXPECT_EQ(pawn_capture.toString(), std::string("exd5"));

    // Test edge file pawn captures
    Move::Move pawn_capture_edge(std::string("axb6"));
    EXPECT_EQ(pawn_capture_edge.pieceType, Move::PieceType::PAWN);
    EXPECT_EQ(pawn_capture_edge.from, 0); // a-file = 0
    EXPECT_TRUE(hasMoveType(pawn_capture_edge, Move::MoveTypes::CAPTURE));
    EXPECT_TRUE(pawn_capture_edge.isValid);
    EXPECT_EQ(pawn_capture_edge.toString(), std::string("axb6"));

    Move::Move pawn_capture_edge2(std::string("hxg6"));
    EXPECT_EQ(pawn_capture_edge2.pieceType, Move::PieceType::PAWN);
    EXPECT_EQ(pawn_capture_edge2.from, 7); // h-file = 7
    EXPECT_TRUE(hasMoveType(pawn_capture_edge2, Move::MoveTypes::CAPTURE));
    EXPECT_TRUE(pawn_capture_edge2.isValid);
    EXPECT_EQ(pawn_capture_edge2.toString(), std::string("hxg6"));
}

TEST_F(MoveTest, CastlingMoves) {
    // Test kingside castle
    Move::Move kingside_castle(std::string("O-O"));
    EXPECT_EQ(kingside_castle.pieceType, Move::PieceType::KING);
    EXPECT_TRUE(hasMoveType(kingside_castle, Move::MoveTypes::SHORT_CASTLE));
    EXPECT_TRUE(kingside_castle.isValid);
    EXPECT_EQ(kingside_castle.toString(), std::string("O-O"));

    // Test queenside castle
    Move::Move queenside_castle(std::string("O-O-O"));
    EXPECT_EQ(queenside_castle.pieceType, Move::PieceType::KING);
    EXPECT_TRUE(hasMoveType(queenside_castle, Move::MoveTypes::LONG_CASTLE));
    EXPECT_TRUE(queenside_castle.isValid);
    EXPECT_EQ(queenside_castle.toString(), std::string("O-O-O"));
}

TEST_F(MoveTest, PawnPromotions) {
    // Test all possible promotion pieces
    std::vector<std::pair<std::string, Move::PieceType>> promotions = {
        {std::string("e8=Q"), Move::PieceType::QUEEN},
        {std::string("e8=R"), Move::PieceType::ROOK},
        {std::string("e8=B"), Move::PieceType::BISHOP},
        {std::string("e8=N"), Move::PieceType::KNIGHT}
    };

    for (const auto& [moveStr, promoPiece] : promotions) {
        Move::Move promotion(moveStr);
        EXPECT_EQ(promotion.pieceType, Move::PieceType::PAWN);
        EXPECT_EQ(promotion.to, 60); // e8 = (7 * 8 + 4)
        EXPECT_EQ(promotion.promotionTo, promoPiece);
        EXPECT_TRUE(hasMoveType(promotion, Move::MoveTypes::PROMOTION));
        EXPECT_TRUE(promotion.isValid);
        EXPECT_EQ(promotion.toString(), std::string(moveStr));
    }

    // Test promotion with capture
    Move::Move capture_promotion(std::string("exf8=N"));
    EXPECT_EQ(capture_promotion.pieceType, Move::PieceType::PAWN);
    EXPECT_EQ(capture_promotion.to, 61); // f8 = (7 * 8 + 5)
    EXPECT_EQ(capture_promotion.from, 4); // e-file = 4
    EXPECT_EQ(capture_promotion.promotionTo, Move::PieceType::KNIGHT);
    EXPECT_TRUE(hasMoveType(capture_promotion, Move::MoveTypes::PROMOTION));
    EXPECT_TRUE(hasMoveType(capture_promotion, Move::MoveTypes::CAPTURE));
    EXPECT_TRUE(capture_promotion.isValid);
    EXPECT_EQ(capture_promotion.toString(), std::string("exf8=N"));
}

TEST_F(MoveTest, PieceCaptures) {
    // Test captures for all piece types
    std::vector<std::string> captures = {
        "Nxe4", "Bxd5", "Rxh8", "Qxf7", "Kxe2"
    };

    for (const auto& moveStr : captures) {
        Move::Move capture(moveStr);
        EXPECT_TRUE(hasMoveType(capture, Move::MoveTypes::CAPTURE));
        EXPECT_TRUE(capture.isValid);
        EXPECT_EQ(capture.toString(), std::string(moveStr));
    }
}

TEST_F(MoveTest, PieceDisambiguation) {
    // Test file disambiguation
    Move::Move file_disambig(std::string("Nbd7"));
    EXPECT_EQ(file_disambig.pieceType, Move::PieceType::KNIGHT);
    EXPECT_EQ(file_disambig.disambiguationFile, 1); // b-file = 1
    EXPECT_EQ(file_disambig.disambiguationRank, -1); // no rank disambiguation
    EXPECT_TRUE(file_disambig.isValid);
    EXPECT_EQ(file_disambig.toString(), std::string("Nbd7"));

    // Test rank disambiguation
    Move::Move rank_disambig(std::string("R1e4"));
    EXPECT_EQ(rank_disambig.pieceType, Move::PieceType::ROOK);
    EXPECT_EQ(rank_disambig.disambiguationFile, -1); // no file disambiguation
    EXPECT_EQ(rank_disambig.disambiguationRank, 0); // rank 1 = 0
    EXPECT_TRUE(rank_disambig.isValid);
    EXPECT_EQ(rank_disambig.toString(), std::string("R1e4"));

    // Test full square disambiguation
    Move::Move full_disambig(std::string("Qh4e1"));
    EXPECT_EQ(full_disambig.pieceType, Move::PieceType::QUEEN);
    EXPECT_EQ(full_disambig.from, 31); // h4 = (3 * 8 + 7)
    EXPECT_EQ(full_disambig.disambiguationFile, 7); // h-file = 7
    EXPECT_EQ(full_disambig.disambiguationRank, 3); // rank 4 = 3
    EXPECT_TRUE(full_disambig.isValid);
    EXPECT_EQ(full_disambig.toString(), std::string("Qh4e1"));

    // Test disambiguation with capture
    Move::Move disambig_capture(std::string("Rdxd4"));
    EXPECT_EQ(disambig_capture.pieceType, Move::PieceType::ROOK);
    EXPECT_EQ(disambig_capture.disambiguationFile, 3); // d-file = 3
    EXPECT_EQ(disambig_capture.disambiguationRank, -1); // no rank disambiguation
    EXPECT_TRUE(hasMoveType(disambig_capture, Move::MoveTypes::CAPTURE));
    EXPECT_TRUE(disambig_capture.isValid);
    EXPECT_EQ(disambig_capture.toString(), std::string("Rdxd4"));
}

TEST_F(MoveTest, InvalidMoves) {
    // Test invalid piece type
    Move::Move invalid_piece(std::string("Xx4"));
    EXPECT_EQ(invalid_piece.pieceType, Move::PieceType::NONE);
    EXPECT_FALSE(invalid_piece.isValid);
    EXPECT_EQ(invalid_piece.toString(), std::string(""));

    // Test invalid promotion piece
    Move::Move invalid_promotion(std::string("e8=X"));
    EXPECT_FALSE(invalid_promotion.isValid);
    EXPECT_EQ(invalid_promotion.toString(), std::string(""));

    // Test empty move
    Move::Move empty_move(std::string(""));
    EXPECT_FALSE(empty_move.isValid);
    EXPECT_EQ(empty_move.toString(), std::string(""));

    // Test invalid squares
    std::vector<std::string> invalid_squares = {
        "Nx9", "Ni1", "Na0", "Nh9", "e9", "i4"
    };

    for (const auto& moveStr : invalid_squares) {
        Move::Move invalid_square(moveStr);
        EXPECT_FALSE(invalid_square.isValid);
        EXPECT_EQ(invalid_square.toString(), std::string(""));
    }

    // Test malformed promotions
    std::vector<std::string> invalid_promotions = {
        "e8=", "e8=P", "e8Q", "exf8="
    };

    for (const auto& moveStr : invalid_promotions) {
        Move::Move invalid_promo(moveStr);
        EXPECT_FALSE(invalid_promo.isValid);
        EXPECT_EQ(invalid_promo.toString(), std::string(""));
    }

    // Test malformed castling
    std::vector<std::string> invalid_castling = {
        "O", "O-O-O-O", "0-0", "o-o"
    };

    for (const auto& moveStr : invalid_castling) {
        Move::Move invalid_castle(moveStr);
        EXPECT_FALSE(invalid_castle.isValid);
        EXPECT_EQ(invalid_castle.toString(), std::string(""));
    }
}

TEST_F(MoveTest, ConstructorVariants) {
    // Test constructor with from, to, piece type, and move types
    std::vector<Move::MoveTypes> moveTypes = {Move::MoveTypes::CAPTURE};
    Move::Move basic_move(12, 28, Move::PieceType::KNIGHT, moveTypes);
    EXPECT_EQ(basic_move.from, 12);
    EXPECT_EQ(basic_move.to, 28);
    EXPECT_EQ(basic_move.pieceType, Move::PieceType::KNIGHT);
    EXPECT_TRUE(hasMoveType(basic_move, Move::MoveTypes::CAPTURE));
    EXPECT_TRUE(basic_move.isValid);

    // Test constructor with promotion
    std::vector<Move::MoveTypes> promoTypes = {Move::MoveTypes::PROMOTION};
    Move::Move promo_move(52, 60, Move::PieceType::PAWN, promoTypes, Move::PieceType::QUEEN);
    EXPECT_EQ(promo_move.from, 52);
    EXPECT_EQ(promo_move.to, 60);
    EXPECT_EQ(promo_move.pieceType, Move::PieceType::PAWN);
    EXPECT_EQ(promo_move.promotionTo, Move::PieceType::QUEEN);
    EXPECT_TRUE(hasMoveType(promo_move, Move::MoveTypes::PROMOTION));
    EXPECT_TRUE(promo_move.isValid);

    // Test constructor with isValid flag
    Move::Move invalid_move(false);
    EXPECT_FALSE(invalid_move.isValid);
    EXPECT_EQ(invalid_move.from, -1);
    EXPECT_EQ(invalid_move.to, -1);
    EXPECT_EQ(invalid_move.pieceType, Move::PieceType::NONE);
    EXPECT_EQ(invalid_move.promotionTo, Move::PieceType::NONE);
    EXPECT_EQ(invalid_move.capturedPiece, -1);
    EXPECT_TRUE(invalid_move.moveTypes.empty());
}

