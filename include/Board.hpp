#ifndef BOARD_HPP
#define BOARD_HPP

#include "Move.hpp"

#include <string>
#include <vector>
#include <utility>

namespace Board
{
  class Board
  {
  public:
    Board();
    ~Board() = default;

    bool makeMove(const Move::Move &move);

    std::vector<Move::Move> getAllValidMoves();

    std::vector<Move::Move> getAllPawnMoves();
    std::vector<Move::Move> getAllKnightMoves();
    std::vector<Move::Move> getAllBishopMoves();
    std::vector<Move::Move> getAllRookMoves();
    std::vector<Move::Move> getAllQueenMoves();
    std::vector<Move::Move> getAllKingMoves();

    Move::Move checkIfAmbiguous(const std::vector<Move::Move> &checkedMoves);

    Move::Move isValidMove(const Move::Move &move);
    std::vector<Move::Move> getValidKnightMoves(const Move::Move &move);
    std::vector<Move::Move> getValidPawnMoves(const Move::Move &move);
    std::vector<Move::Move> getValidBishopMoves(const Move::Move &move);
    std::vector<Move::Move> getValidRookMoves(const Move::Move &move);
    std::vector<Move::Move> getValidQueenMoves(const Move::Move &move);
    std::vector<Move::Move> getValidKingMoves(const Move::Move &move);

    std::pair<bool, Move::Move> checkForPromotion(const Move::Move &move);
    std::pair<bool, Move::Move> checkForEnPassant(const Move::Move &move);

    inline bool isOnLeftBorder(int square);
    inline bool isOnRightBorder(int square);
    inline bool isOnTopBorder(int square);
    inline bool isOnBottomBorder(int square);

    bool makeShortCastle();
    bool makeLongCastle();
    bool makeRegularMove(const Move::Move &move);

    int checkDiagonal(int square, Move::PieceType type, bool isCapture = false, bool reverseColor = false);
    int checkVerticalAndHorizontal(int square, Move::PieceType type, bool isCapture = false, bool reverseColor = false);
    std::vector<int> checkKnightMoves(int square, bool reverseColor = false);
    int checkKingMoves(int square);
    int checkPawnMoves(int square);

    int getSquare(std::string square);
    int isSquareControled(int square);
    bool isInCheck();

    void setToDefault();

    // board[0] = a1

    unsigned long long board[64] = {0};

    bool hasWhiteKingMoved = false;
    bool hasBlackKingMoved = false;
    bool hasWhiteRookAMoved = false;
    bool hasWhiteRookHMoved = false;
    bool hasBlackRookAMoved = false;
    bool hasBlackRookHMoved = false;

    int currentWhiteKingPosition;
    int currentBlackKingPosition;

    bool isWhiteTurn = true;

    std::vector<Move::Move> moveHistory;

    static const int NONE = 0;
    static const int COLOR = 1;
    static const int PAWN = 2;
    static const int KNIGHT = 4;
    static const int BISHOP = 8;
    static const int ROOK = 16;
    static const int QUEEN = 32;
    static const int KING = 64;

    static const int UP = 8;
    static const int DOWN = -8;
    static const int LEFT = -1;
    static const int RIGHT = 1;
    static const int UP_LEFT = 7;
    static const int UP_RIGHT = 9;
    static const int DOWN_LEFT = -9;
    static const int DOWN_RIGHT = -7;
  };
} // namespace Board

#endif // BOARD_HPP