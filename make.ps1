## MakeFile alternative

function compilation{
    echo "........compilling.........."
    g++ -c .\src\*.cpp -I.\include
    g++ -c main.cpp -I.\include
    echo "..........moving............"
    #Move-Item -Path *.o -Destination .\obj -force
    echo ".........linking............"    
    #g++ -o RapidRoll .\obj\*.o main.o -L.\lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
    g++ -o RapidRoll .\*.o main.o -L.\lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
    mv .\RapidRoll.exe .\bin -force
    echo "...........done............."
}

function cleaning{
    echo "........cleaning.........."
    #rm .\obj\*.o
    rm .\*.o
    echo "...........done............."
}

function Helpmenu{
        echo "Write -c for compilation, clean for deleting the .o files and cleanall for .o and .exe file"
        echo "And -e to execute the game"
        echo "Or you can pass -a/all to all three (compile,clean,execute)"
}

$params =$args[0]

switch ($params){
    "" {Helpmenu; Break}
    "-h" {Helpmenu; Break}
    "help" {Helpmenu; Break}
    "compile" {compilation}
    "-c" {compilation}
    "clean" {cleaning}
    "cleanall" {cleaning ;rm .\bin\RapidRoll.exe; Break}
    "execute" {.\bin\RapidRoll.exe; Break}
    "-e" {.\bin\RapidRoll.exe; Break}
    "all" {
        compilation;
        clean;
        .\bin\RapidRoll.exe;
        Break
    }
    "-a" {
        compilation;
        clean;
        .\bin\RapidRoll.exe;
        Break
    }
}