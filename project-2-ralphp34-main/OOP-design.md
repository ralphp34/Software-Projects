# OOP Design Document

[[UML Diagram Project 2.pdf](https://github.com/cs2113-f21/project-2-ralphp34/files/7600305/UML.Diagram.Project.2.pdf)
]

![](/path/to/UML.ong)

## Overview

In the OOP design we are working around the creatures class within this program. This class is a mother class for all of the creatures that exist in the program. The creatures are mice, cats, and zombie cats. This creature class also depends on two other classes, which are the City class and the GridPoint class.


## Creature Class

This class is a mother class for all of the creatures that exist in the program. The creatures are mice, cats, and zombie cats and they inherit methods and variables in the creature class. This creature class also depends on two other classes, which are the City class and the GridPoint class.


## Mice Class

This class inherits the creature class which encapsulates the varibles and methods but also has specific actions like procreating and dying.

## Cats Class

This class inherits the creature class which encapsulates the varibles and methods but also has specific actions like eating mice and dying.

## Zombie-cats Class

This class inherits the creature class which encapsulates the varibles and methods but also has specific actions like eating mice and cats and dying.

## City 

This class represents the city  in which the creatures live. This class as a method simulate that describes the primary routine of each iteration off the simulation and has two collections that keep the simulation maintained. A list of all the active creatures in the program, and a hashmap that connects the GridPoint.

## GridPoint

This class implements a row/column pair that can be used as a key in a map. All of our classes are depended on it because they are all on a place on the grid.
