## MakeFile alternative

function compilation{
    echo "........compilling.........."
    g++ -c .\src\*.cpp -I.\include
    echo "..........moving............"
    #Move-Item -Path *.o -Destination .\obj -force
    echo ".........linking............"    
    #g++ -o RapidRoll .\obj\*.o main.o -L.\lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
    g++ -o RapidRoll .\*.o -L.\lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
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

function RunAgain{
    $param2= Read-Host "Enter the command,sire!!"
    switch ($param2){
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
                    cleaning;
                    .\bin\RapidRoll.exe;
                    Break
                    }
            "-a" {
                    compilation;
                    cleaning;
                    .\bin\RapidRoll.exe;
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
    "clean" {cleaning}
    "cleanall" {cleaning ;rm .\bin\RapidRoll.exe; Break}
    "execute" {.\bin\RapidRoll.exe; Break}
    "-e" {.\bin\RapidRoll.exe; Break}
    "all" {
        compilation;
        cleaning;
        .\bin\RapidRoll.exe;
        Break
    }
    "-a" {
        compilation;
        cleaning;
        .\bin\RapidRoll.exe;
        Break
    }
}