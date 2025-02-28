#include "Move.hpp"

#include <algorithm>
#include <iostream>

namespace Move
{
  Move::Move(const std::string &move)
  {
    // Initialize default values
    to = -1;
    pieceType = PieceType::NONE;
    isValid = true;
    promotionTo = PieceType::NONE;
    from = -1;
    capturedPiece = -1;
    disambiguationFile = -1;
    disambiguationRank = -1;
    moveTypes.clear();

    if (move.empty())
    {
      isValid = false;
      return;
    }

    // Check what type of piece is moving
    setPieceType(move);
    
    // Verification Steps
    // 1. Check if the move is a castle move, because it doesn't need further verification
    if (checkAndSetCastle(move))
      return;

    // 2. There is no move, that is shorter than 2 characters
    if (move.size() < 2)
    {
      isValid = false;
      return;
    }

    // 3. Handle disambiguation and captures
    size_t x_pos = move.find('x');
    handleDisambiguation(move, x_pos);

    // 4. If there is a promotion, then add the promotion move type and get the promotion piece
    size_t equals_pos = move.find('=');
    if (equals_pos != std::string::npos)
    {
      moveTypes.push_back(MoveTypes::PROMOTION);
      if (equals_pos + 1 >= move.length()) {
        isValid = false;
        return;
      }
      
      char pawnPromotedTo = move[equals_pos + 1];
      switch (pawnPromotedTo)
      {
      case 'N':
        promotionTo = PieceType::KNIGHT;
        break;
      case 'Q':
        promotionTo = PieceType::QUEEN;
        break;
      case 'B':
        promotionTo = PieceType::BISHOP;
        break;
      case 'R':
        promotionTo = PieceType::ROOK;
        break;
      default:
        isValid = false;
        return;
      }
    }

    // 5. Get where the piece is moving to
      std::string square;
      if (pieceType == PieceType::PAWN)
      {
        // For pawn moves, the destination is either:
        // - The last two characters before '=' for promotions (e.g., "e8=Q")
        // - The characters after 'x' for captures (e.g., "exd5")
        // - The entire move for simple moves (e.g., "e4")
        if (equals_pos != std::string::npos)
        {
          square = move.substr(equals_pos - 2, 2);
        }
        else if (x_pos != std::string::npos)
        {
          square = move.substr(x_pos + 1);
        }
        else
        {
          square = move;
        }
      }
      else
      {
        // For piece moves, the destination is always the last two characters
        square = move.substr(move.length() - 2, 2);
        if(square[0] < 'a' || square[0] > 'h' || square[1] < '1' || square[1] > '8') {
          isValid = false;
          return;
        }
      }
      
      try {
        to = getSquareIndex(square);
      } catch (const std::invalid_argument &e) {
        isValid = false;
        return;
      }
  }

  Move::Move(int from, int to, PieceType pieceType, std::vector<MoveTypes> moveTypes)
  {
    this->from = from;
    this->to = to;
    this->pieceType = pieceType;
    this->moveTypes = moveTypes;
    this->isValid = true;
    this->promotionTo = PieceType::NONE;
    this->capturedPiece = -1;
    this->disambiguationFile = -1;
    this->disambiguationRank = -1;
  }

  Move::Move(int from, int to, PieceType pieceType, std::vector<MoveTypes> moveTypes, PieceType promotionTo)
  {
    this->from = from;
    this->to = to;
    this->pieceType = pieceType;
    this->moveTypes = moveTypes;
    this->isValid = true;
    this->promotionTo = promotionTo;
    this->capturedPiece = -1;
    this->disambiguationFile = -1;
    this->disambiguationRank = -1;
  }

  Move::Move(bool isValid)
  {
    this->isValid = isValid;
    this->from = -1;
    this->to = -1;
    this->pieceType = PieceType::NONE;
    this->promotionTo = PieceType::NONE;
    this->capturedPiece = -1;
    this->disambiguationFile = -1;
    this->disambiguationRank = -1;
    this->moveTypes.clear();
  }

  void Move::setPieceType(const std::string &move)
  {
    if (move.empty())
    {
      isValid = false;      
      return;
    }

    // First check if it's a pawn move
    if (move[0] >= 'a' && move[0] <= 'h')
    {
      pieceType = PieceType::PAWN;
      return;
    }

    // Then check for piece moves
    switch (move[0])
    {
    case 'N':
      pieceType = PieceType::KNIGHT;
      break;
    case 'B':
      pieceType = PieceType::BISHOP;
      break;
    case 'R':
      pieceType = PieceType::ROOK;
      break;
    case 'Q':
      pieceType = PieceType::QUEEN;
      break;
    case 'K':
      pieceType = PieceType::KING;
      break;
    case 'O':  // Handle castling
      pieceType = PieceType::KING;
      break;
    default:
      pieceType = PieceType::NONE;
      isValid = false;
      break;
    }
  }

  bool Move::checkAndSetCastle(const std::string &move)
  {
    if (move.empty())
    {
      return false;
    }
    if (move == "O-O")
    {
      moveTypes.push_back(MoveTypes::SHORT_CASTLE);
      pieceType = PieceType::KING;
      return true;
    }
    else if (move == "O-O-O")
    {
      moveTypes.push_back(MoveTypes::LONG_CASTLE);
      pieceType = PieceType::KING;
      return true;
    }
    return false;
  }

  int Move::getSquareIndex(const std::string &move)
  {
    if (move.empty())
    {
      throw std::invalid_argument("Move is empty");
    }

    if (move.size() != 2) 
    {
      throw std::invalid_argument("Invalid square format: " + move);
    }

    char file = move[0];
    char rank = move[1];

    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
      throw std::invalid_argument("Invalid chess square: " + move);
    }

    // Convert the move to a square index
    // The board is indexed from bottom-left (a1) to top-right (h8)
    // So a1 = 0, b1 = 1, ..., h1 = 7, a2 = 8, etc.
    int file_index = file - 'a';  // 0-7 for a-h
    int rank_index = rank - '1';  // 0-7 for 1-8
    return rank_index * 8 + file_index;
  }

  void Move::handleDisambiguation(const std::string &move, size_t x_pos)
  {
    if (pieceType == PieceType::PAWN)
    {
      // Handle pawn captures with disambiguation (e.g., "exf8=N")
      if (move[0] >= 'a' && move[0] <= 'h' && move.size() > 1 && move[1] == 'x')
      {
        int file = move[0] - 'a';
        disambiguationFile = file;  // Store the from file
        from = file;  // For pawns, from is just the file
        moveTypes.push_back(MoveTypes::CAPTURE);
      }
    }
    else
    {
      // Handle piece disambiguation (e.g., "Nbd7", "R1e4", "Rh1e1")
      size_t start_pos = 1;  // Skip piece letter (N, B, R, Q, K)
      size_t end_pos = x_pos != std::string::npos ? x_pos : move.length() - 2;
      
      if (end_pos > start_pos)
      {
        std::string disambig = move.substr(start_pos, end_pos - start_pos);
        // Could be file (a-h), rank (1-8), or both
        if (disambig.length() == 1)
        {
          if (disambig[0] >= 'a' && disambig[0] <= 'h')
            disambiguationFile = disambig[0] - 'a';  // Store file
          else if (disambig[0] >= '1' && disambig[0] <= '8')
            disambiguationRank = disambig[0] - '1';  // Store rank
        }
        else if (disambig.length() == 2)
        {
          // Both file and rank provided (e.g., "Rh1e1")
          if (disambig[0] >= 'a' && disambig[0] <= 'h' && 
              disambig[1] >= '1' && disambig[1] <= '8')
          {
            int file = disambig[0] - 'a';
            int rank = disambig[1] - '1';
            from = rank * 8 + file;  // Keep the exact square in from
            disambiguationFile = file;
            disambiguationRank = rank;
          }
        }
      }
    }

    // Handle captures for non-pawns
    if (x_pos != std::string::npos && pieceType != PieceType::PAWN)
    {
      moveTypes.push_back(MoveTypes::CAPTURE);
    }
  }

  std::string Move::getDisambiguationString() const
  {
    std::string result = "";
    
    // If we have a full square, use both file and rank
    if (from >= 0 && from < 64) {
      result += (char)('a' + (from % 8));
      result += (char)('1' + (from / 8));
    }
    // Otherwise use file and/or rank disambiguation if available
    else {
      if (disambiguationFile >= 0) {
        result += (char)('a' + disambiguationFile);
      }
      if (disambiguationRank >= 0) {
        result += (char)('1' + disambiguationRank);
      }
    }
    return result;
  }

  std::string Move::toString() const
  {
    if (!isValid) return "";

    std::string result = "";
    
    // Handle castling first
    if (std::find(moveTypes.begin(), moveTypes.end(), MoveTypes::SHORT_CASTLE) != moveTypes.end()) {
      return "O-O";
    }
    if (std::find(moveTypes.begin(), moveTypes.end(), MoveTypes::LONG_CASTLE) != moveTypes.end()) {
      return "O-O-O";
    }

    // Add piece type for non-pawn pieces
    if (pieceType != PieceType::PAWN) {
      switch (pieceType) {
        case PieceType::KNIGHT: result += 'N'; break;
        case PieceType::BISHOP: result += 'B'; break;
        case PieceType::ROOK: result += 'R'; break;
        case PieceType::QUEEN: result += 'Q'; break;
        case PieceType::KING: result += 'K'; break;
        default: break;
      }

      // Add disambiguation
      result += getDisambiguationString();
    } 
    // For pawn captures, add the starting file
    else if (std::find(moveTypes.begin(), moveTypes.end(), MoveTypes::CAPTURE) != moveTypes.end() && from >= 0) {
      result += (char)('a' + from);
    }

    // Add capture symbol
    if (std::find(moveTypes.begin(), moveTypes.end(), MoveTypes::CAPTURE) != moveTypes.end()) {
      result += 'x';
    }

    // Add destination square
    char file = static_cast<char>('a' + (to % 8));
    char rank = static_cast<char>('1' + (to / 8));
    result += file;
    result += rank;

    // Add promotion piece
    if (std::find(moveTypes.begin(), moveTypes.end(), MoveTypes::PROMOTION) != moveTypes.end()) {
      result += '=';
      switch (promotionTo) {
        case PieceType::KNIGHT: result += 'N'; break;
        case PieceType::BISHOP: result += 'B'; break;
        case PieceType::ROOK: result += 'R'; break;
        case PieceType::QUEEN: result += 'Q'; break;
        default: break;
      }
    }

    return result;
  }
}