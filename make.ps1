## MakeFile alternative

function compilation{
    echo "........compilling.........."
    g++ -c .\src\*.cpp -I.\include
    echo "..........moving............"
    #Move-Item -Path *.o -Destination .\obj -force
    echo ".........linking............"    
    #g++ -o Play .\obj\*.o main.o -L.\lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
    g++ -o Play .\*.o -L.\lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -mwindows
    mv .\Play.exe .\bin -force
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
            "cleanall" {cleaning ;rm .\bin\Play.exe; Break}
            "execute" {.\bin\Play.exe; Break}
            "-e" {.\bin\Play.exe; Break}
            "all" {
                    compilation;
                    cleaning;
                    .\bin\Play.exe;
                    Break
                    }
            "-a" {
                    compilation;
                    cleaning;
                    .\bin\Play.exe;
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
    "cleanall" {cleaning ;rm .\bin\Play.exe; Break}
    "execute" {.\bin\Play.exe; Break}
    "-e" {.\bin\Play.exe; Break}
    "all" {
        compilation;
        cleaning;
        .\bin\Play.exe;
        Break
    }
    "-a" {
        compilation;
        cleaning;
        .\bin\Play.exe;
        Break
    }
}