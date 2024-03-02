<h1>Mini Snake Game</h1>

 ### [YouTube Demonstration](https://youtu.be/AOC-wo0NgmU)

<h2>Description</h2>
"Snake" is a classic video game,
where the player controls a snake to pick up food and avoid running into blocks or its own body.
In my Snake Game, there are no "walls" surrounding the playing area,
and whenever the snake goes beyond the boundary,
it will come out of the opposite side.
(for example, if it reaches the rightmost boundary, it will re-emerge from the leftmost one.)
Each time the snake eats a piece of food, its tail grows longer by one segment,
and its speed also increases.
When the snake runs into a roadblock (the dark green blocks),
or a segment of its own body, it dies.

My Snake Game also supports `Undo` after the snake dies.
An Undo command (by pressing `Backspace`) will change the state of the snake back to the last time it eats a piece of food.
Afterwards, the player is able to resume the game by pressing `Enter`,
and five new extra roadblocks will be generated.
Each time the snake dies of running into roadblocks,
the roadblock hit by the snake will be removed after the game resumes.
It is also worth noting that the snake body of a previous state might overlap a newly added roadblock.
Therefore, I will also remove all overlapping roadblocks upon resuming the game.
<br />


<h2>Languages and Utilities Used</h2>

- <b>C++</b> 
- <b>Data structure Algorithm</b>

<h2>Environments Used </h2>

- <b>Windows 10</b> (21H2)

<h2>Playstyle & Guide:</h2>

<p >
Press `Arrow Keys` to control the snake. <br/>
<img src="https://i.imgur.com/oW7H5Or.png" height="80%" width="80%" alt="miniSnkaeGame"/>
<img src="https://i.imgur.com/VGxrSCu.png" height="80%" width="80%" alt="miniSnkaeGame"/>
<br />
<br />
When the snake dies, press `Backspace` to undo.  <br/>
<img src="https://i.imgur.com/jZtrdEe.png" height="80%" width="80%" alt="miniSnkaeGame"/>
<img src="https://i.imgur.com/vjgtMhv.png" width="80%" alt="miniSnkaeGame"/>
<img src="https://i.imgur.com/ZM4Bfuc.png" width="80%" alt="miniSnkaeGame"/>
<br />
<br />
After the Undo command, press `Enter` to resume the game. <br/>
<img src="https://i.imgur.com/3un2M8p.png" height="80%" width="80%" alt="miniSnkaeGame"/>
<br />
<br />
</p>

<!--
 ```diff
- text in red
+ text in green
! text in orange
# text in gray
@@ text in purple (and bold)@@
```
--!>
