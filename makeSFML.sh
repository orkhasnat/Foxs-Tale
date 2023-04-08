#!/bin/bash

homeDir=$(dirname "$(realpath "$0")")
srcDir="$homeDir/src"
includeDir="$homeDir/include"
libDir="$homeDir/lib"
binDir="$homeDir/bin"

function help {
  cat <<EOF
Usage: makeSFML.sh [options]

Options:
  -h, --help        Show this help message and exit
  -c, --compile     Compile the project
  -cl, --clean      Clean the project (delete object files and shortcut)
  -a, --all         Compile the project and create a shortcut to the executable
EOF
}

function compile {
    echo "Compiling..."
    if [[ ! -d "$binDir" ]]; then
        mkdir "$binDir"
    fi
    for file in "$srcDir"/*.cpp; do
        g++ -c "$file" -I"$includeDir" -o "$binDir/$(basename "${file%.cpp}.o")"
    done
    echo "Done!"
    
    echo "Linking..."
    linkerOptions=()
    while IFS= read -r linker || [ -n "$linker" ]; do
        linkerOptions+=("-l$linker")
    done < "$homeDir/linkers.txt"
    g++ -o "$binDir/Play" "$binDir/"*.o "-L$libDir" "${linkerOptions[@]}"
    echo "Done!"
    
    createShortcut
}

function createShortcut {
  echo "Creating shortcut..."
  shortcutPath="$homeDir/Play.desktop"
  targetPath="$binDir/Play"
  echo -e "[Desktop Entry]\nType=Application\nName=Play\nExec=$targetPath\nPath=$binDir\nTerminal=false" > "$shortcutPath"
  chmod +x "$shortcutPath"
  echo "Done!"
}

function clean {
  echo "Cleaning..."
  if [[ -n "$(find "$binDir" -name '*.o' -print -quit)" ]]; then
    rm -rf "$binDir"/*.o
  fi
  echo "Done!"
}

function cleanExe {
  echo "Deleting executable and shortcut..."
  if [[ -e "$binDir/Play" ]]; then
    rm -f "$binDir/Play"
  fi
  if [[ -e "$homeDir/Play.desktop" ]]; then
    rm -f "$homeDir/Play.desktop"
  fi
  echo "Done!"
}

if [[ $# -eq 0 ]]; then
  help
else
  case "$1" in
    -h|--help)
      help
      ;;
    -cl|--clean)
      clean
      cleanExe
      ;;
    -c|--compile)
      compile
      ;;
    -a|--all)
      clean
      cleanExe
      compile
      clean
      ;;
    *)
      help
      ;;
  esac
fi