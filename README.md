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

### Compiling / Executing

```
make
./text-game
```

A program feature is the ability to change the game map. A second game map has been provided in the repository named `map2.txt.` To change the maps out:
```
mv map.txt backup.txt
mv map2.txt map.txt
./text-game
```

## C++ / OOP Concepts Implemented

#### Classes & Objects

  A class is used to specify the form of an object and it combines data representation and methods for manipulating that data into one neat package. The data and functions within a class are called members of the class.

  Everything in this program is an object:
  * Game - manages the interaction of the Character, Rooms, Items, and Monster.
  * Character - holds the inventory of Items and Character attributes.
  * Item Room, Locked Room, Monster Room - holds an inventory of Items or Monsters and provides a link to adjacent Spaces.
  * Monster - provides functionality for the combat.

#### Inheritance / Polymorphism
  Inheritance means a class can be derived from more than one classes, which means it can inherit data and functions from multiple base classes.

  In this program, an abstract Space class is established with basic functionality common to all rooms in the realm. Derived from the Space class is the Item Room, Locked Room, and Monster Room. Each of these derived classes have their own specific behavior apart from the common/derived functionality.

  C++ polymorphism means that a call to a member function will cause a different function to be executed depending on the type of object that invokes the function. Once example used in the program is the Space::roomIsLocked() function. The Space class always returns false, but through polymorphism the Locked Room class can return a true or false.

#### Dynamic Memory Allocation
  Because the Realm is created at run-time by reading the map.txt file, the program is not aware in advance how much memory will be needed to store particular information in a defined variable/object, but the size of required memory can be determined at run time. You can allocate memory at run time within the heap for the variable of a given type using a the `new` operator in C++ which returns the address of the space allocated.

  When the need of dynamically allocated memory ceases, you can use the `delete` operator, which de-allocates memory that was previously allocated by `new` operator.

  All Spaces, Characters, and Monsters are allocated dynamically this way. For example, when the Healing Potion Item is drank, it is de-allocated. The rooms are de-allocated when the user exits the game.

#### File Input
  Basic file input is demonstrating using the fstream object. The first use is the Welcome Screen ASCII art. This simply reads each line in the file and prints it to the console.

  The next, and more advanced usage, of file input is the map.txt file. Each character represents a type of Space object. The Game object dynamically creates the specified Space object (Item Room, Locked Room, Monster Room) and pushes them on to a 2-dimensional vector. Further, an Items are allocated and added to the Spaces. Once complete, the program iterates through the 2-dimensional vector and links all adjacent Spaces together by setting pointers to each other. This allows for an endless combination Maps to be created!

#### Vectors

  Vectors are used to dynamically manage the Character's inventory, and the Room's inventory. The program allows the user to drop all their items in one room. The items are pushed on to a vector when dropped.

#### Hash Map
  Instead of using a numerical menu, game commands are based on word commands. For example `north` will attempt to the move the character to the adjacent space to the north. The logic handler for commands is a switch statement. A switch statement allows a variable (user input) to be tested for equality against a list of values. Each value is called a case, and the variable being switched on is checked for each case. But in C++, this variable cannot be a character or a string.

  To solve this, the program uses a Map. Maps are associative containers that store elements formed by a combination of a key value and a mapped value, following a specific order. In a map, the key values are generally used to sort and uniquely identify the elements, while the mapped values store the content associated to this key.

  So commands like `north` and `n` are mapped to the key `1`. Anytime this command is typed, the value `1` is tested for equality in the switch statement.

  One advantage of maps is the time-complexity of searching a map is generally O(log n). So even though, this program has a small command list, the ability to scale larger exists.

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
