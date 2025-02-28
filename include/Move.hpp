#ifndef MOVE_HPP
#define MOVE_HPP

#include <string>
#include <vector>

namespace Move
{
  enum PieceType
  {
    NONE = 0,
    PAWN = 2,
    KNIGHT = 4,
    BISHOP = 8,
    ROOK = 16,
    QUEEN = 32,
    KING = 64
  };

  enum MoveTypes
  {
    CHECK,
    CHECKMATE,
    CAPTURE,
    PROMOTION,
    SHORT_CASTLE,
    LONG_CASTLE,
    EN_PASSANT
  };

  class Move
  {
  public:
    // Type of piece that was moved
    PieceType pieceType = PieceType::NONE;

    // The exact square index where the piece is moving from (if known)
    int from = -1;

    // Disambiguation information (file 0-7 or -1 if not specified)
    int disambiguationFile = -1;

    // Disambiguation information (rank 0-7 or -1 if not specified)
    int disambiguationRank = -1;

    // The square the piece is moving to
    int to = -1;

    // The type of move
    std::vector<MoveTypes> moveTypes;

    bool isValid = true;
    PieceType promotionTo = PieceType::NONE;
    int capturedPiece = -1;

    Move() = default;
    Move(const std::string &move);
    Move(int from, int to, PieceType pieceType, std::vector<MoveTypes> moveTypes);
    Move(int from, int to, PieceType pieceType, std::vector<MoveTypes> moveTypes, PieceType promotionTo);
    Move(bool isValid);
    std::string toString() const;

  private:
    void setPieceType(const std::string &move);
    bool checkAndSetCastle(const std::string &move);
    int getSquareIndex(const std::string &move);
    void handleDisambiguation(const std::string &move, size_t x_pos);
    std::string getDisambiguationString() const;
  };
} // namespace Move

#endif // MOVE_HPP