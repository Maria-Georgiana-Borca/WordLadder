# Word Ladder Puzzle Game

## Overview

The Word Ladder game, an invention by Lewis Carroll, is a challenging word puzzle where players transform a starting word into a target word by changing one letter at a time. Each intermediate step must also form a valid word. This project implements the game using various C++ Standard Library containers and a custom graph data structure.

## Features

- **Automatic Mode:** Automatically displays the steps from the starting to the target word.
- **Playing Mode:** Allows the player to manually attempt the transformation, with hints available upon request.
- **Analytics Module:** Tracks and displays statistics from past games.

### Menu Options

- **Automatic Mode:** Enter the starting and target words.
- **Playing Mode:** The game will randomly choose words of a specified length.
- **View Statistics:** Enter a username to view game statistics.

## Game Rules

- Each transformation must change only one letter and result in a valid word.
- The word length for transformations is consistent throughout a game session.

## Hints

- Use hints sparingly to learn about possible next steps in the transformation process.
- Hints will highlight which letter to change next.

## Data Management

- Game data is saved to a file named after the user (`username.csv`).
- Each game session records:
  - Starting and target words
  - Date and time of the game
  - Number of hints used
  - Words used in the transformation
  - Number of moves and the optimal number of moves
