# Fox's Tale
Fox's Tale is a recreation of RapidRoll. It takes inspiration from the classic Nokia game from our childhood, providing a nostalgic experience that resonates with the players. The game stays true to the original concept while adding new dimensions that make it more challenging and engaging. The objective of the game is to control a ball that rolls down through a series of rising platforms while avoiding obstacles and collecting bonuses. The game ends if the ball falls off the bottom of the screen, hits the ceiling, or collides with an obstacle. With improved graphics, animation, and soundtrack, the game provides players with an entertaining gaming experience.

# Demo
Watch here: https://youtu.be/CMADuLaDrM8

# Screenshots
<img src="https://i.ibb.co/dckjMt2/Picture2.png" alt="Picture2" border="0">
<img src="https://i.ibb.co/GkjnmdT/Picture3.png" alt="Picture3" border="0">
<img src="https://i.ibb.co/d0s7SQh/Picture4.png" alt="Picture4" border="0">
<img src="https://i.ibb.co/zhVFhSR/mpv-shot0001.jpg" alt="mpv-shot0001" border="0"> 

## For Windows
Run make.ps1 using powershell.  
Options:   
> -h/help - Shows help menu  
> -c/compile - Compiles the project  
> -cr - Compiles the project without the roll function (if compilcation arises)
> clean - Deletes the .o files  
> cleanall - Deletes the *.o and *.exe files  
> -a/all - Does all the above except deleting the .exe file  
> To execute the game run the executable  

The .exe can be found in ./bin  
The -a flag or -e doesnt execute properly due to failure to load resources.  
Git somehow corrupts the symbolic link thus creates execution failure.  


## Features
- Realistic Physics: The physics of the game is implemented to provide players with a smooth and responsive gameplay experience, challenging their reflexes and providing an adrenaline rush that makes the game more immersive.
- **New Challenges**
    As your score increases, new challenges appear to make the game more difficult and interesting.
    - Moving Platforms: These platforms move both horizontally and vertically.
    - Spikes: These sharp and pointy hazards instantly destroy the ball. Players must plan their movements carefully to navigate around them and avoid losing the game.
    - Bouncy Platforms: These platforms add a fun element to the game by bouncing the ball. However, there is a danger that you may collide with the ceiling.
- **Pickup Items**
    - Coin: This item gives a score bonus.
    - Gem: This item grants an extra life to the player.
    - Boost: This item accelerates the ball. Although it is difficult to control initially, with practice, skilled players can learn to take advantage of its increased velocity.
    - Protection: This item grants temporary invincibility, allowing you to pass through spikes unharmed.
    - Slowdown: This item slows down time, making it easier to navigate through obstacles and spikes. It's a game-changer in the later part of the game.
- High Score System: The high-score system allows players to keep track of their personal best scores and compete with friends, making every playthrough a chance to set a new record.

## Technologies Used
Rapid Roll Advanced was developed using C++ and the SFML (Simple and Fast Multimedia Library) library. The project used various object-oriented programming concepts, including encapsulation, inheritance, polymorphism, function and operator overloading, templates, virtual and abstract functions, enumerations, and exceptions.

## Feedback and Suggestions
If you have any feedback or suggestions for improvements, please feel free to contact us by sending an email to tasnimulhasnat@iut-dhaka.edu. We are always looking for ways to make the game even better.

### Enjoy the Game!
