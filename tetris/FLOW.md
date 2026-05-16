# Tetris Game - Complete Flow Documentation

## Table of Contents
1. [Application Startup](#application-startup)
2. [Main Menu Flow](#main-menu-flow)
3. [Game Mode Selection](#game-mode-selection)
4. [Countdown & Game Start](#countdown--game-start)
5. [Gameplay Loop](#gameplay-loop)
6. [Game Over & Score Saving](#game-over--score-saving)
7. [Architecture Overview](#architecture-overview)
8. [Data Flow](#data-flow)

---

## Application Startup

### Entry Point: `main.cpp`

```
START
  ↓
Configure Console (UTF-8, ANSI colors)
  ↓
Initialize Random Seed
  ↓
Load Player Records from db/scores.json
  ↓
Prompt User for Player Name
  ↓
Enter Main Loop
```

**Key Actions:**
1. **Console Setup**
   - Set UTF-8 encoding: `SetConsoleOutputCP(CP_UTF8)`
   - Enable ANSI escape sequences for colors
   - Configure virtual terminal processing

2. **Data Loading**
   - Load all player records from `db/scores.json`
   - If file doesn't exist, start with empty records

3. **Player Identification**
   - Ask user to enter their name
   - Default to "Player" if no name entered

---

## Main Menu Flow

### Menu System: `Menu.cpp`

```
Main Menu
  ├─ PLAY  (selected = 0)
  └─ EXIT  (selected = 1)
```

**User Interaction:**
- **W/S Keys**: Navigate between options
- **ENTER**: Confirm selection

**Flow:**
```
Display Main Menu
  ↓
Wait for Input
  ↓
If PLAY selected → Go to Mode Selection
  ↓
If EXIT selected → Exit Application
```

---

## Game Mode Selection

### Mode Menu: `Menu.cpp`

```
Mode Selection
  ├─ NORMAL     (selected = 0)
  └─ CHALLENGE  (selected = 1)
```

**Mode Differences:**

| Feature | Normal Mode | Challenge Mode |
|---------|-------------|----------------|
| Time Limit | None (unlimited) | 300 seconds (5 minutes) |
| Win Condition | None (play until game over) | Reach 1500 points |
| Timer Display | Elapsed time (counts up) | Remaining time (counts down) |
| Difficulty | Standard | Higher pressure |

**Flow:**
```
Display Mode Menu
  ↓
Wait for Input
  ↓
Store Mode Choice (Normal/Challenge)
  ↓
Proceed to Countdown
```

---

## Countdown & Game Start

### Countdown: `Menu.cpp → showCountdown()`

```
Display "3"
  ↓ (900ms delay)
Display "2"
  ↓ (900ms delay)
Display "1"
  ↓ (900ms delay)
Clear Screen → Start Game
```

**Visual:**
- Large ASCII art numbers (3, 2, 1)
- Yellow color highlight
- Centered on screen

---

## Gameplay Loop

### Main Game Loop: `Game.cpp → run()`

```
┌─────────────────────────────────────┐
│     GAME INITIALIZATION             │
├─────────────────────────────────────┤
│ - Create Board (10x20 grid)        │
│ - Spawn First Piece                 │
│ - Spawn Next Piece                  │
│ - Set Initial Score = 0             │
│ - Set Initial Level = 1             │
│ - Set Gravity Delay = 500ms         │
│ - Record Start Time                 │
└─────────────────────────────────────┘
           ↓
┌─────────────────────────────────────┐
│      GAME LOOP (60 FPS)             │
├─────────────────────────────────────┤
│  1. Handle Input                    │
│  2. Update Game State               │
│  3. Draw Game Screen                │
│  4. Sleep 16ms (60 FPS)             │
│  5. Check Game Over                 │
└─────────────────────────────────────┘
           ↓
     Game Over?
           ↓
┌─────────────────────────────────────┐
│      GAME OVER SEQUENCE             │
├─────────────────────────────────────┤
│ - Save Player Score                 │
│ - Display Game Over Screen          │
│ - Show Leaderboard                  │
│ - Wait for Key Press                │
│ - Return to Main Menu               │
└─────────────────────────────────────┘
```

### 1. Input Handling: `GameInput.cpp`

**Keyboard Controls:**

| Key | Action | Description |
|-----|--------|-------------|
| **A** | Move Left | Move piece one column left |
| **D** | Move Right | Move piece one column right |
| **W** | Rotate | Rotate piece clockwise with wall kicks |
| **S** | Soft Drop | Move piece down one row |
| **SPACE** | Hard Drop | Instantly drop piece to bottom |
| **P** | Pause | Toggle pause state |
| **C** | Controls | Toggle control display panel |
| **Q** | Quit | Exit to main menu |

**Input Flow:**
```
Check Keyboard Buffer (_kbhit)
  ↓
Read Key (_getch)
  ↓
If Q → Set gameOver = true
If P → Toggle paused
If C → Toggle showControls
  ↓
If Not Paused:
  ↓
  Process Movement (A/D/S)
  Process Rotation (W)
  Process Hard Drop (SPACE)
```

### 2. Game Logic: `GameLogic.cpp`

**Gravity System:**
```
Every [gravityDelay] milliseconds:
  ↓
Try Move Piece Down
  ↓
Can Move? → Move Down
  ↓
Cannot Move? → Lock Piece
  ↓
Lock Piece:
  - Add piece to board grid
  - Check for full lines
  - Clear full lines
  - Calculate score
  - Update level
  - Spawn next piece
```

**Scoring System:**
```
Lines Cleared | Points Earned
──────────────┼──────────────
     1        |    100
     2        |    400
     3        |    900
     4        |   1600
```

Formula: `score += lines² × 100`

**Level Progression:**
```
Level = (Score ÷ 500) + 1

Level 1: Gravity Delay = 500ms
Level 2: Gravity Delay = 460ms
Level 3: Gravity Delay = 420ms
...
Level 10+: Gravity Delay = 100ms (minimum)
```

**Rotation System:**
```
Rotate Piece Clockwise
  ↓
Try Position: Original Column
  ↓
Collision? → Try Position: Column + 1
  ↓
Collision? → Try Position: Column - 1
  ↓
Collision? → Cancel Rotation
```

**Piece Spawning:**
```
Move Current Piece → Next Piece
  ↓
Generate New Random Piece → Next Piece
  ↓
Reset Position (top center of board)
  ↓
Check Collision at Spawn
  ↓
Collision? → GAME OVER
```

### 3. Rendering: `GameDraw.cpp`

**Screen Layout:**
```
┌────────────────────┬────────────────┐
│                    │   NEXT:        │
│                    │   [preview]    │
│                    │                │
│   GAME BOARD       │   SCR: 1200    │
│   (10 x 20)        │   LVL: 3       │
│                    │   TMR: 02:45   │
│   [Active Piece]   │                │
│   [Ghost Piece]    │   C:controls   │
│   [Locked Blocks]  │                │
│                    │                │
└────────────────────┴────────────────┘
```

**Rendering Components:**

1. **Board Grid** (10 columns × 20 rows)
   - Locked blocks (colored squares)
   - Active piece (current falling piece)
   - Ghost piece (preview of landing position)

2. **Side Panel**
   - Next piece preview (4×4 grid)
   - Current score
   - Current level
   - Timer (elapsed or remaining)
   - Controls help (toggle with C)

3. **Visual Elements**
   - Box-drawing characters (Unicode)
   - ANSI color codes for pieces
   - Ghost piece (dimmed preview)

**Piece Colors:**
```
Type | Color  | Code
─────┼────────┼─────
  I  | Cyan   | 36
  O  | Yellow | 33
  T  | Purple | 35
  S  | Green  | 32
  Z  | Red    | 31
  J  | Blue   | 34
  L  | Orange | 93
```

### 4. Game Over Conditions

**Normal Mode:**
- Piece cannot spawn (board is full)

**Challenge Mode:**
- Piece cannot spawn (board is full), OR
- Score reaches 1500 (WIN), OR
- Time runs out (LOSE)

---

## Game Over & Score Saving

### End Game Sequence: `GameDraw.cpp → showGameOver()`

```
┌─────────────────────────────────────┐
│         GAME OVER SCREEN            │
├─────────────────────────────────────┤
│                                     │
│   ┌──────────────────────────┐     │
│   │      GAME OVER / WIN     │     │
│   └──────────────────────────┘     │
│                                     │
│   Score : 1200                      │
│   Level : 3                         │
│   Time  : 02:45                     │
│                                     │
│   ─────── LEADERBOARD ──────        │
│                                     │
│   Name        Score  Lvl Mode      │
│   Player1      1500   4  Chal      │
│   Player2      1200   3  Norm      │
│   You          1000   2  Norm      │
│                                     │
│   Press any key to continue...     │
└─────────────────────────────────────┘
```

**Score Saving Flow:**
```
Game Ends
  ↓
Update Player Record:
  - Increment games played
  - Update high score (if better)
  - Update high level (if better)
  - Store last mode played
  ↓
Save to db/scores.json
  ↓
Display Game Over Screen
  ↓
Show Leaderboard (sorted by score)
  ↓
Highlight:
  - Current player (green)
  - Champion (yellow)
  ↓
Wait for Key Press
  ↓
Return to Main Menu
```

### Score Database: `ScoreDB.cpp`

**Data Structure:**
```json
[
  {
    "name": "Player1",
    "games": 5,
    "highScore": 1500,
    "highLevel": 4,
    "lastMode": "Challenge"
  },
  {
    "name": "Player2",
    "games": 3,
    "highScore": 1200,
    "highLevel": 3,
    "lastMode": "Normal"
  }
]
```

**Operations:**
1. **Load Scores**: Read JSON file → Parse → Return vector
2. **Save Scores**: Format vector → Write JSON file
3. **Update Player**: Find/Create record → Update stats → Save
4. **Show Leaderboard**: Sort by score → Display table

---

## Architecture Overview

### Project Structure

```
tetris/
├── Core Layer (Game Logic)
│   ├── Board.cpp/h      → Grid management, collision detection
│   └── Piece.cpp/h      → Piece data, positioning
│
├── Game Layer (Game Engine)
│   ├── Game.cpp/h       → Main game controller
│   ├── GameLogic.cpp/h  → Update logic, scoring, spawning
│   ├── GameInput.cpp/h  → Keyboard input handling
│   ├── GameDraw.cpp/h   → Rendering, game over screen
│   └── GameTime.cpp/h   → Time tracking utilities
│
├── UI Layer (User Interface)
│   ├── Menu.cpp/h       → Menu system, countdown
│   ├── tetris.cpp/h     → Console utilities
│   ├── colors.cpp/h     → ANSI color codes
│   └── piecedata.cpp/h  → Piece shapes, colors
│
├── Database Layer (Persistence)
│   └── ScoreDB.cpp/h    → JSON read/write, leaderboard
│
└── Entry Point
    └── main.cpp         → Application initialization
```

### Component Responsibilities

**Core Components:**
- **Board**: 10×20 grid, collision detection, line clearing
- **Piece**: Shape data, position, type, rotation

**Game Components:**
- **Game**: Main controller, game state, mode settings
- **GameLogic**: Gravity, spawning, scoring, level progression
- **GameInput**: Keyboard handling, movement, rotation
- **GameDraw**: Screen rendering, UI layout
- **GameTime**: Time tracking with clear elapsed/remaining calculations

**UI Components:**
- **Menu**: Main menu, mode selection, countdown
- **tetris**: Console utilities (clear, cursor, centering)
- **colors**: ANSI color code generation
- **piecedata**: Tetromino shapes and metadata

**Database Components:**
- **ScoreDB**: JSON persistence, player records, leaderboard

---

## Data Flow

### Complete Data Flow Diagram

```
┌──────────────┐
│   main.cpp   │
└──────┬───────┘
       │
       ├─→ Load Scores (ScoreDB)
       │   └─→ db/scores.json
       │
       ├─→ Get Player Name
       │
       ├─→ Main Menu (Menu)
       │   └─→ PLAY / EXIT
       │
       ├─→ Mode Menu (Menu)
       │   └─→ NORMAL / CHALLENGE
       │
       ├─→ Countdown (Menu)
       │
       ├─→ Game Loop (Game)
       │   │
       │   ├─→ Input (GameInput)
       │   │   └─→ Keyboard → Piece Movement
       │   │
       │   ├─→ Logic (GameLogic)
       │   │   ├─→ Gravity → Piece Drop
       │   │   ├─→ Collision (Board)
       │   │   ├─→ Lock Piece (Board)
       │   │   ├─→ Clear Lines (Board)
       │   │   ├─→ Update Score
       │   │   └─→ Spawn Next (Piece)
       │   │
       │   └─→ Draw (GameDraw)
       │       ├─→ Board Grid
       │       ├─→ Active Piece
       │       ├─→ Ghost Piece
       │       └─→ Side Panel
       │
       ├─→ Game Over (GameDraw)
       │   ├─→ Update Player (ScoreDB)
       │   │   └─→ Save to db/scores.json
       │   └─→ Show Leaderboard
       │
       └─→ Loop Back to Main Menu
```

### State Transitions

```
[Application Start]
       ↓
[Console Setup]
       ↓
[Load Scores]
       ↓
[Enter Name]
       ↓
┌──────────────┐
│  Main Menu   │ ←──────────────┐
└──────┬───────┘                │
       │                        │
    [PLAY]                      │
       ↓                        │
┌──────────────┐                │
│  Mode Menu   │                │
└──────┬───────┘                │
       │                        │
  [Select Mode]                 │
       ↓                        │
┌──────────────┐                │
│  Countdown   │                │
└──────┬───────┘                │
       │                        │
       ↓                        │
┌──────────────┐                │
│   Gameplay   │                │
│   (Active)   │                │
└──────┬───────┘                │
       │                        │
  [Game Over]                   │
       ↓                        │
┌──────────────┐                │
│  Game Over   │                │
│   Screen     │                │
└──────┬───────┘                │
       │                        │
  [Any Key]                     │
       │                        │
       └────────────────────────┘
```

---

## Key Algorithms

### 1. Collision Detection
```
For each block in piece:
  Calculate absolute position (piece.col + block.x, piece.row + block.y)
  Check if:
    - Out of bounds (< 0 or >= board dimensions)
    - Overlaps with locked block on board
  If any collision → return true
Return false (no collision)
```

### 2. Line Clearing
```
For each row from bottom to top:
  Check if row is full (all 10 columns occupied)
  If full:
    Remove row
    Shift all rows above down by 1
    Add empty row at top
    Increment lines cleared counter
Return total lines cleared
```

### 3. Ghost Piece Calculation
```
Start at current piece position
While no collision:
  Move down one row
Return final row position (before collision)
```

### 4. Wall Kick Rotation
```
Rotate piece shape 90° clockwise
Try positions in order:
  1. Original column
  2. Original column + 1 (right)
  3. Original column - 1 (left)
If any position valid → Apply rotation
Else → Cancel rotation
```

---

## Performance Considerations

- **Frame Rate**: 60 FPS (16ms sleep per frame)
- **Gravity Updates**: Variable (500ms to 100ms based on level)
- **Input Polling**: Non-blocking (_kbhit)
- **Rendering**: Full screen redraw each frame
- **File I/O**: Only on game start/end (not during gameplay)

---

## Future Enhancement Ideas

1. **Gameplay**
   - Hold piece feature
   - T-spin detection and bonus
   - Combo system
   - Multiple difficulty presets

2. **UI/UX**
   - Particle effects on line clear
   - Sound effects and music
   - Customizable controls
   - Color themes

3. **Features**
   - Multiplayer mode
   - Replay system
   - Statistics tracking
   - Achievement system

4. **Technical**
   - Save game state (pause and resume)
   - Configuration file
   - Better error handling
   - Cross-platform support

---

## Conclusion

This Tetris implementation follows a clean, modular architecture with clear separation of concerns:
- **Core** handles game logic
- **Game** manages the game loop
- **UI** handles presentation
- **Database** manages persistence

The flow is intuitive: Menu → Mode → Countdown → Play → Game Over → Repeat

All components work together to create a polished, playable Tetris experience in the Windows console.
