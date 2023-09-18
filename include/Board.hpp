#ifndef BOARD_HPP
#define BOARD_HPP

#include "Move.hpp"

#include <string>
#include <vector>
#include <utility>

namespace Board
{
  enum class GameState
  {
    IN_PROGRESS,
    CHECK,
    CHECKMATE,
    STALEMATE,
    THREEFOLD_REPETITION,
    FIFTY_MOVE_RULE,
    INSUFFICIENT_MATERIAL,
    RESIGNATION
  };

  class Board
  {
  public:
    Board();
    ~Board() = default;

    /**
     * @brief Checks if move is correct andif so makes a move given in the param
     *
     * @param move Object of class Move from Move.hpp
     * @return true
     * @return false
     */
    bool makeMove(const Move::Move &move);

    /**
     * @brief Gets the all possible moves that can be made in the current state of the game
     *
     * @return std::vector<Move::Move>
     */
    std::vector<Move::Move> getAllValidMoves();

    /**
     * @brief Helper function for Board::getAllValidMoves, gets all the possible valid pawn moves
     *
     * @return std::vector<Move::Move>
     */
    std::vector<Move::Move> getAllPawnMoves();

    /**
     * @brief Helper function for Board::getAllValidMoves, gets all the possible valid knight moves
     *
     * @return std::vector<Move::Move>
     */
    std::vector<Move::Move> getAllKnightMoves();

    /**
     * @brief Helper function for Board::getAllValidMoves, gets all the possible valid bishop moves
     *
     * @return std::vector<Move::Move>
     */
    std::vector<Move::Move> getAllBishopMoves();

    /**
     * @brief Helper function for Board::getAllValidMoves, gets all the possible valid rook moves
     *
     * @return std::vector<Move::Move>
     */
    std::vector<Move::Move> getAllRookMoves();

    /**
     * @brief Helper function for Board::getAllValidMoves, gets all the possible valid queen moves
     *
     * @return std::vector<Move::Move>
     */
    std::vector<Move::Move> getAllQueenMoves();

    /**
     * @brief Helper function for Board::getAllValidMoves, gets all the possible valid king moves
     *
     * @return std::vector<Move::Move>
     */
    std::vector<Move::Move> getAllKingMoves();

    /**
     * @brief Checks if there are multiple pieces of the same type that can move to the same square, returns Move::Move(false) if no pieces can go to that square or more than one
     *
     * @param checkedMoves Vector of moves to be checked
     * @return Move::Move
     */
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

    std::vector<int> checkDiagonal(int square, Move::PieceType type, bool isCapture = false, bool reverseColor = false);
    std::vector<int> checkVerticalAndHorizontal(int square, Move::PieceType type, bool isCapture = false, bool reverseColor = false);
    std::vector<int> checkKnightMoves(int square, bool reverseColor = false);
    std::vector<int> checkKingMoves(int square);
    int checkIfControledByEnemyKing(int square);
    int checkIfControledByEnemyPawn(int square);
    int checkPawnMoves(int square);

    void setGameState();
    bool isCheckmate();
    bool isCheck();
    bool isStalemate();
    bool isThreefoldRepetition();
    bool isFiftyMoveRule();
    bool isInsufficientMaterial();
    bool isResignation();

    std::vector<std::pair<int, bool>> getDiagonalMoves(int square);
    std::vector<std::pair<int, bool>> getVerticalAndHorizontalMoves(int square);

    bool checkIfCrossesBorder(int square1, int square2);
    bool checkIfFitsInBoard(int square);

    int getSquare(std::string square);
    int isSquareControled(int square);

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

    GameState gameState = GameState::IN_PROGRESS;
    std::pair<std::vector<int>, std::vector<int>> pieceSets;

    int possibleMoves = -1;
    int fiftyMoveRuleCounter = 0;

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