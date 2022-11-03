# combat_cpp

A simple text-based console game that uses DnD5e rules for combat. This was originally implemented in Python, and now in C++ as my experience grows.
The player chooses their class at the start of the game, and the two enemies are randomly selected for classes.

Classes determine hit die (currently only used in resting), starting weapon, and starting armour.

Possible actions are: Fight, Check Health, Rest, Look Around, and Exit. While fighting, it is only possible to attack or run away.

The game ends when all enemies are defeated, or the user chooses to exit. I hope you enjoy playing this little game! 

## Pre-requisites and Setup

1. Make sure your c++ dev environment is setup
    a. On windows, Visual Studio makes set up very simple (2022 was used in this project)
    b. On Linux/MacOS, be sure to install both `build-essential` and `ninja-build`
    c. Make sure to install CMake version 3.21 or newer
2. Populate submodules with `git submodule update --init`
3. Build with your favorite CMake methods (either GUI or command line)
4. Run tests if you feel like it / are developing
5. Try the game by running `main_game`

## Notices

* Enemy names and any references are meant simply as a tribute to stories I have enjoyed in the past. I will gladly modify as required should anyone have any issues with it
* The majority of rules are based on this source: https://roll20.net/compendium/dnd5e/CategoryIndex%3ARules#content
* It has passed build actions for windows-latest, ubuntu-latest, and macos-latest, however I have only personally tested on windows and ubuntu.
* Please report any bugs you find! Any and all feedback is always welcome as I plan to continue casual improvements of this.
