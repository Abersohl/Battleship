# Battleship
Battleship for Cpts 121 at Wsu

Made by Kenneth Eversole



Purpose of project:
Create a game of Battleship that is bettween a human and computer.

Added features:
1. Mouse control 
2. Added a UI that further exemplifies the game of Battleship

Features that need to be worked on:
1. Ai



(AI explaination) 

I am so sorry if this is hard to understand. I tried to create an Ai that would mathmatically attack the human player's ships.
It would do this by adding up the probabilities of all of the ships. Then it would decrement the total probability 
depending on if at that location is a miss. It would then go through and find the top 15 highest probabilites, once found it would randomly
choose from them and fire. If it is a miss repeat previous steps. If it is a hit then it would take that data and enter KILL mode.
In kill mode it take the North, South, East, and West points and uses those to be possible targets, and this is where it currently 
breaks. What is suppose to happen is that it keeps preforming this step till the total hits are zero, I did this because it could hit 
multipleships in this process, what currently happens is that it doesnt add the Dtargets properly and breaks eventually. 


(Ship probabilites)
This is just how many possible ways a ship can be placed into a spot.


(Story about this project)
This project is my first big Computer Science project in which I truly became invested in. I spent over 200+ hours on this project, a lot 
of which was spent learning completly new concepts, an of this example is Windows.h. I know the code may not be pretty, which is something
I plan on fix up over time. This project though, has allow me to prove to myself that if I have an idea I can make it happen. 


If you see anything that could be better feel free to have at it. 
