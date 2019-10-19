

Lab3 3rd Yr Automatic Maze game

LAB BRIEF: 
Lab 3 2d Life Your name and student number must be at the top of every file.
You cannot use or anything else except char ,ints and an array of chars..
All code must be consistently indented and variables given appropriate names.
You must upload the code to blackboard before Wednesday30th October @ 11 am even if not all the parts are completed. You will be 
unable to upload any code after that time. If no code is uploaded, you get Zero for the lab. If you don’t demo the code you get 
Zero for the lab!
You must both demo the lab and upload the code to get a mark.
The demo is after the deadline.
Lab Book Diary
You must also show your lab book, when demoing the code. The lab book shows your work as you do it and illustrates your approach to 
solving the problems below. The lab book is worth 15%.
When you are demoing the lab, you will be asked questions about the code. Use lab 3 Example Code from blackboard as a starting point.
Components:

1: The Maze 
The maze is stored as an array of chars . ‘0’ for a ground and ‘1’ for a wall. Use the sample program as a starting point.The 
user enters a key to update the maze and redraw it.

2:The Walkers 
Each walker is represented by an ‘2’ in the array.
At the start of each game the walkers are randomly placed in the ground(anything that’s not a wall). The walkers cannot be placed on a 
maze position that already contains a plant or another walker. With each update the walker randomly chooses a direction to move (it can 
move in any of the 8 adjoining maze positions). If there isn't a wall in its way it will move into the next maze position. If it cannot 
move it tries another direction until it can move. If you have tried all directions and it still can’t move it just stay where it is. 
After a walker has moved it must return the previous position to a ‘0’ for ground.
If the walker hits a plant ( see below) the plant will be removed from the 2D Life.

3: The Plants
The plant is represented by a char from ‘a’ to ‘y’ in the array. The plants are randomly placed on the maze and they just stay in 
one spot. At each update the plant counts back one at a time from ‘y’ down to ‘a’..e.g. y, x,v,....a. When it reaches ‘a’ 
it cycles back to ‘y’ . The plant only updates it’s value only if it can’t ‘see’ a walker . A plant can see a walker if there 
is a walker in the same row or the same column,and if there is not a wall between it and the walker.

4: Wander forever 
Life is over when all the plants are gone, only walkers wandering the maze forever. Instead of printing the Maze, print 
“Life Simulation Complete”.

Bonus: Have a look at conway's game of life (https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) and grow the plants in a similar way.
