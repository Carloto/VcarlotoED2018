// Modulo main do trabalho

// Include
#include <stdio.h>
#include <stdlib.h>
#include "filehandling.h"
#include "structlib.h"
#include "miscfunctions.h"

// Main
int main(int argc, char *argv[]) {

    fileArguments *FileNames = createInputArguments();
    setInputArguments(&FileNames, argc, argv);
    printInputArguments(FileNames);

    // Free structs
    killInputArguments(FileNames);

    // End main
    return 0;

}
