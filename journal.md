## What do we need?

---

- Amazing performance for operations that need intense computing
- An algotirhm to determine which move is the best (the brain)
- The bot must know what the position is, so an efficient way to present a chess board is needed
- Input/Output, the bot must read and play moves on an actual board (either taking screenshots and analyzing them or just being connected to a board written from scratch)

In short we need: good performance, an algorithm that determines the best move (the brain), efficient position representation, I/O

## How do we deal with these problems?

---

### Performance

I initially wanted to code this in python, but it would be way to slow to compute all the data, so my weapon of choice for this will be C++ which is blazingly fast. I hope to learn a lot from this project.

### The Brain

This will be the most challenging part of the project as chess is not that simple. Let's break the brain into even smaller problems.
So what the brain has to know is:

- Current position
- The available moves
- Ability to evaluate each move to determine which is the best
- Optimisations to avoid unnessasary calculations
  Doesn't seem like a lot. But in fact it will not be easy.
  The position problem will be discussed further in the next section.
  Then we have the available moves. Ahhh.

#### Available moves

- King - moves 1 square in each direction (horizontal, vertical, diagonal) + CAN CASTLE
- Queen - moves accross the chess board (horizontal, vertical, diagonal), is only limited to the board borders and other pieces
- Rook - moves accross the chess board (horizontal, vertical), is only limited to the board borders and other pieces + CAN CASTLE
- Bishop - moves accross the chess board (diagonal), is only limited to the board borders and other pieces
- Knight - moves in an 'L' shape, can jump over other pieces
- Pawn - can move one or two squares ahead (if hasn't moved yet) takes diagonally 1 square ahead + EN PASSANT + CAN PROMOTE
  So when calculating every possible move we have to watch out for all these rules.
  SPECIAL RULES FOR A MOVE:
- Castling - if king is not in check and an enemy piece does not cover any of the 'castling squares' and neither the king nor the destined rook have moved and there are no pieces in the way, castling is possible
- En Passant - if an enemy pawn has just moved two squares and now stands next to our pawn we can capture that pawn it must be accomplished in the same move
- Promotion - when a white pawn reaches the 8th rank or a black pawn reaches the 1st, it can change into a: knight, bishop, rook, queen
- Check - if a king is attacked by a piece, it must be protected
- Checkmate - if a king has no escape and is in check
- Stalemate - if a king isn't in check and has no escape this must be checked or will produce a number of bugs regarding illegal moves

#### Evaluation

So if we want to evaluate which move is the best we first must know how to evaluate a position and then check the impact of the move on the position.
What is important in a position?

- King's safety
- Material (pieces on the board)
- Piece activity
- Space

this is the order from the most important to the least important at least thats what chess players are used to but we can confront that with a potential evolutionary algorithm

of course we have some quirks over here:

- Checkmating threats
- Combinations
  If we can checkmate the opponent then we dont really have to seek a move that will give us spacial advantage its pretty simple.
  And combinations I honestly dont know about that yet since my algorithm will calculate moves for himself and the opponent so it might not even be a problem.

Now, how can the computer telll all of these values?

- Material - pretty simple (pawn = 1, knights and bishops = 3, rooks = 5, queen = 9 and king is priceless)
- Piece activity - we just look ot how many squares the piece attacks, we can make it better by seeking weaknesses and attacking weak squares. but this will be developed further in the future.
- Space - pretty simple, how far our pawns are and how much space they gather
- King's safety - honestly, i have no clue yet, its not a simple topic and i will come back to it

Seeking checkmates
TODO!
it is another hard topic that i will approach later

The brain will look at a certain depth e.g. 10 moves into the future, it will also have a limitation on time e.g. 10s. After the goal is reached we can ask the bot for the current evaluation and the best move.

#### Optimizations

TODO! NEED TO WORK ON THE ALGORITHM FIRST LOL

### Position Representation

---

My first instinct is to use some kind of bit representation of the board so as to make it as efficient as possible working only on bitwise operators.

So the representation will be this:

square & 1 = color
square & 2 = pawn
square & 4 = knight
square & 8 = bishop
square & 16 = rook
square & 32 = queen
square & 64 = king

so we can just use an 8bit uint to represent a square
if it is equal to 0 then the square is empty
the board will be stored in a 64-long array

some convenience functions like translating a pgn position into our system will be useful aswell

### Input / Output

---

In the beggining we can just assume the bot starts off the default position and we can type in the moves to the console, the bot will print out the best response and the evaluation of the position.

### Prototyped Program Loop

---

- User types in the move
- Move is processed by I/O class and passed to the bot in a make_move() function
- The bot passes it further to the Board class, which actually makes the move
- The board class passes it to the Validator class which checks if the move is valid
- Program class runs evaluate_position() and then runs find_move() on the bot then passes these parameters to be printed out by the Menu class
- Waits for the next move from the user

## Classes

---

### Program

Common ground for all the other classes that lets them comunicate

- static void run() - Runs the program

### Brain

The class for processing moves and evaaluating positions

- float evaluate_position()
- string find_best_move()
- void make_enemy_move(string move)

- Board real_board
- Board testing_board
- bool color

### Board

- Board() - sets to default setup
- void make_move(string move)

- unsigned long long[64] board
- bool has_a1_rook_moved = false
- bool has_a8_rook_moved = false
- bool has_h1_rook_moved = false
- bool has_h8_rook_moved = false
- bool has_white_king_moved = false
- bool has_black_king_moved = false

### Validator

- bool is_valid_move(string move)
- bool does_piece_exist_on_square()
- bool is_valid_move()
- bool is_capture()
- bool is_check()
- bool is_checkmate()

### Menu
