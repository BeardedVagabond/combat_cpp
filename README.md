# combat_cpp

A simple text-based console game that uses DnD5e rules for combat. This was originally implemented in Python, and now in C++ as my experience grows.
The player chooses their class at the start of the game, and the two enemies are randomly selected for classes.

Classes determine hit die (currently only used in resting), starting weapon, and starting armour.

Possible actions are: Fight, Check Health, Rest, Look Around, and Exit. While fighting, it is only possible to attack or run away.

The game ends when all enemies are defeated, or the user chooses to exit. I hope you enjoy playing this little game! 

Want to try it out? All you need to do is clone, configure + build with CMake, and run exampleMain :D 
It has passed build actions for windows-latest, ubuntu-latest, and macos-latest, however I have only personally tested on windows and ubuntu (in WSL for now).

Last but not least, please report any bugs you find! Any and all feedback is always welcome as I plan to continue casual improvements of this.

Note: Enemy names and any references are meant simply as a tribute to stories I have enjoyed in the past. I will gladly modify as required should anyone have any issues with it

Note: The majority of rules are based on this source: https://roll20.net/compendium/dnd5e/CategoryIndex%3ARules#content
