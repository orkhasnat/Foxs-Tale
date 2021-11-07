## MakeFile alternative

function compilation{
    echo "........compilling.........."
    # remove the -D ROll if the roll func creates problem
    g++ -c .\src\*.cpp -I.\include -D ROLL
    # resource file handling
    windres icon.rc -o icon.o
    echo "..........moving............"
    #Move-Item -Path *.o -Destination .\obj -force
    echo ".........linking............"
    # remove the -D ROll if the roll func creates problem
    g++ -o "Fox's Tale" .\*.o -L.\lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -mwindows -D ROLL
    mv .\"Fox's Tale".exe .\bin -force
    echo "...........done............."
}
function withoutRoll{
    echo "........compilling.........."
    g++ -c .\src\*.cpp -I.\include 
    # resource file handling
    windres icon.rc -o icon.o
    echo "..........moving............"
    #Move-Item -Path *.o -Destination .\obj -force
    echo ".........linking............"
    g++ -o "Fox's Tale" .\*.o -L.\lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -mwindows
    mv .\"Fox's Tale".exe .\bin -force
    echo "...........done............."
}

function cleaning{
    echo "........cleaning.........."
    #rm .\obj\*.o
    rm .\*.o
    echo "...........done............."
}
function cleaningall{
    echo "........cleaning.........."
    rm .\*.o
    rm .\bin\"Fox's Tale".exe
    #rm hscore.savefile
    rm .\bin\data\hscore.savefile
    echo "...........done............."
}

function Helpmenu{
        echo "Write -c for compilation, clean for deleting the .o files and cleanall for .o and .exe file"
        echo "And -e to execute the game"
        echo "Or you can pass -a/all to all three (compile,clean,execute)"
}

function RunAgain{
    $param2= Read-Host "Enter the command,sire!!"
    switch ($param2){
            "-h" {Helpmenu; Break}
            "help" {Helpmenu; Break}
            "compile" {compilation}
            "-c" {compilation}
            "-cr" {withoutRoll}
            "clean" {cleaning}
            "cleanall" {cleaningall; Break}
            "execute" {.\bin\"Fox's Tale".exe; Break}
            "-e" {.\bin\"Fox's Tale".exe; Break}
            "all" {
                    compilation;
                    cleaning;
                    #.\bin\"Fox's Tale".exe;
                    Break
                    }
            "-a" {
                    compilation;
                    cleaning;
                    #.\bin\"Fox's Tale".exe;
                    Break
                }
        }
}

$params =$args[0]

switch ($params){
    "" {Helpmenu; RunAgain; Break}
    "-h" {Helpmenu; Break}
    "help" {Helpmenu; Break}
    "compile" {compilation}
    "-c" {compilation}
    "-cr" {withoutRoll}
    "clean" {cleaning}
    "cleanall" {cleaningall; Break}
    "execute" {.\bin\"Fox's Tale".exe; Break}
    "-e" {.\bin\"Fox's Tale".exe; Break}
    "all" {
        compilation;
        cleaning;
        #.\bin\"Fox's Tale".exe;
        Break
    }
    "-a" {
        compilation;
        cleaning;
        #.\bin\"Fox's Tale".exe;
        Break
    }
}