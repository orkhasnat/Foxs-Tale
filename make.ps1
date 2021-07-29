## MakeFile alternative

function compilation{
    echo "........compiling..........."
    g++ -c .\src\*.cpp -I.\include
    echo ".........linking............"    
    g++ -o Play .\*.o -L.\lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
    echo "...........done............."
}

function cleaning{
    echo "........cleaning............"
    rm .\*.o
    echo "...........done............."
}

function Helpmenu{
        echo "Write -c for compilation"
	echo "clean for deleting the .o files, -cl for .o and .exe file"
        echo "And -e to execute the game"
        echo "Or you can pass -a/all for all three (compile,clean,execute)"
}

function RunAgain{
    $param2= Read-Host "Enter the command: "
    switch ($param2){
            "-h" {Helpmenu; Break}
            "help" {Helpmenu; Break}
            "compile" {compilation}
            "-c" {compilation}
            "clean" {cleaning}
            "-cl" {cleaning ;rm Play.exe; Break}
            "execute" {./Play.exe; Break}
            "-e" {./Play.exe; Break}
            "all" {
                    compilation;
                    cleaning;
                    ./Play.exe;
                    Break
                    }
            "-a" {
                    compilation;
                    cleaning;
                    ./Play.exe;
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
    "-cl" {cleaning ;rm Play.exe; Break}
    "execute" {./Play.exe; Break}
    "-e" {./Play.exe; Break}
    "all" {
        compilation;
        cleaning;
        ./Play.exe;
        Break
    }
    "-a" {
        compilation;
        cleaning;
        ./Play.exe;
        Break
    }
}