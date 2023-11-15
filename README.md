# Fox's Tale
Fox's Tale is a recreation of RapidRoll. It takes inspiration from the classic Nokia game from our childhood, providing a nostalgic experience that resonates with the players. The game stays true to the original concept while adding new dimensions that make it more challenging and engaging. The objective of the game is to control a ball that rolls down through a series of rising platforms while avoiding obstacles and collecting bonuses. The game ends if the ball falls off the bottom of the screen, hits the ceiling, or collides with an obstacle. With improved graphics, animation, and soundtrack, the game provides players with an entertaining gaming experience.

# Demo
Watch here: https://youtu.be/CMADuLaDrM8

# Screenshots
<img src="https://i.ibb.co/dckjMt2/Picture2.png" alt="Picture2" border="0">
<img src="https://i.ibb.co/GkjnmdT/Picture3.png" alt="Picture3" border="0">
<img src="https://i.ibb.co/d0s7SQh/Picture4.png" alt="Picture4" border="0">
<img src="https://i.ibb.co/zhVFhSR/mpv-shot0001.jpg" alt="mpv-shot0001" border="0"> 

## Installation
- ### **Installer**
    You can install the game directly from this [link](https://github.com/orkhasnat/Foxs-Tale/releases/download/v1.01/Setup.exe).
- ### **Manual Compilation**
    Alternatively, you can choose to manually compile the game yourself using the provided source code. To do this, you will need to have the SFML library installed, but don't worry - we have included the version we used in our development process to make it easier for you (Windows Only).
    - #### **For Windows**
        Simply run the powershell script make.ps1.
        ```
        Options:   
        > -h/help - Shows help menu  
        > -c/compile - Compiles the project  
        > -cr - Compiles the project without the roll function (if compilcation arises)
        > clean - Deletes the .o files  
        > cleanall - Deletes the *.o and *.exe files  
        > -a/all - Does all the above except deleting the .exe file  
        ```
        To execute the game, run the Fox's Tale.exe file located in the bin folder. Please note that the -a flag and -e option do not execute properly due to a known issue with loading resources. Additionally, Git may corrupt the symbolic link, resulting in an execution failure. The compiled Fox's Tale.exe file can be found in the ./bin directory.
        
        Note: If you are using PowerShell on Windows and encounter an error message about script execution being disabled, you can enable script execution by opening a PowerShell session as an administrator and running the following command:
        ```Set-ExecutionPolicy RemoteSigned```
        This command sets the execution policy to allow local and remote signed scripts to run on the system. Once you've run this command, you should be able to execute the PowerShell script without any issues.
    - #### **For GNU/Linux**
        To compile the game, you'll need to install the SFML library. Depending on your distribution, you can use your package manager to install the SFML package. For example, on Arch Linux, the package is called ```sfml```, and on Ubuntu/Debian and it's deriavatives, it's ```libsfml-dev```. Once you've installed SFML, open a terminal in the project directory and run the make command. This will compile the game and create the executable in the bin directory. To clean up the object files and the executable, run the ```make clean``` command.
        You can run the ```desktop``` target to create a desktop entry for the game. The entry will be created on the current user's desktop and will include the game name, an icon, and a command to run the executable. Note that the icon file ```icon.ico``` should be present in the root directory of the project for the entry to display correctly.
        
        If you need help with the available commands, run ```make help``` in the terminal. This will display a list of available commands along with a brief description of each command.
        Also this might also work on MacOS but I can't really test that. 


## Features
- **Realistic Physics**: The physics of the game is implemented to provide players with a smooth and responsive gameplay experience, challenging their reflexes and providing an adrenaline rush that makes the game more immersive.
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
- **High Score System**: The high-score system allows players to keep track of their personal best scores and compete with friends, making every playthrough a chance to set a new record.

## Technologies Used
Rapid Roll Advanced was developed using C++ and the SFML (Simple and Fast Multimedia Library) library. The project used various object-oriented programming concepts, including encapsulation, inheritance, polymorphism, function and operator overloading, templates, virtual and abstract functions, enumerations, and exceptions. Also the installation files were made using Inno Setup.

## Feedback and Suggestions
If you have any feedback or suggestions for improvements, please feel free to contact us by sending an email to tasnimulhasnat@iut-dhaka.edu. We are always looking for ways to make the game even better.

### Enjoy the Game!
