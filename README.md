# OOP Console RPG

“Myrddin Emry’s Realm” is a one-player, text-based fantasy game using object-oriented programming concepts. The character, Myrddin Emrys, starts just to the north of Town in the Darkwood Forest. The player can move north, south, east or west depending on the available path through the forest. Myrddin will encounter locked doors, items, healing potions, and eventually a Red Dragon. Myrddin can fight with either his fists or with the use of a longbow to shoot arrows.

The goal of the game is to defeat the one Red Dragon in combat. In order to do this, Myrddin must move through the Realm going from room to room. He must collect the longbow and the wooden key items and add them to your inventory. He likely needs the healing potions, but it is possible to win without them. The key will unlock the door to eventually arrive at the Red Dragon. The weapon will allow you inflict enough damage on the dragon (using your fists will not be enough). The magic healing potion will allow you regenerate your health points to survive through the combat. As soon as you defeat the dragon you will win.

Death is possible either from combat with the Red Dragon or dying of thirst by travelling too much without healing (or contributions from both).

## Getting Started

Download all files to one folder with no subdirectories. A makefile is included that uses the g++ compiler.

### Prerequisites

For linux, you will need the GCC compiler capable of C++11 standard.

```
sudo apt-get update
sudo apt-get install g++
```

### Installing / Executing

```
make
./text-game
```

## Built With

* [Atom](https://ide.atom.io/) - Atom IDE
* [GCC](https://gcc.gnu.org/) - GNU Compiler Collection
* [Valgrind](http://valgrind.org/) - Memory management bug detection

## Authors

* **Robert Jones** - [RobertJonesDev](https://github.com/robertjonesdev)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* The RPG environment was largely adapted from a MUD I frequently played as a teenager in the 90's called MajorMUD.
* The code was adapted from my final project for the class "Introduction to Computer Science II" as part of my Computer Science undergraduate degree.
