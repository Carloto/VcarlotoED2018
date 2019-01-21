// Include
#include "color.h"

struct tmpColor { // Color
    char *quadStroke;
    char *quadFill;
};

// Aloca e inicializa uma struct Color
Color *allocColor() {
    Color *tmpCol = (Color *) calloc(1, sizeof(Color));
    return tmpCol;
}

// Libera a memoria de uma unica struct Color
void killColor(Color *tmpCol) {
    if (tmpCol != NULL) {
        freeString(&(tmpCol->quadStroke));
        freeString(&(tmpCol->quadFill));
        free(tmpCol);
    }
}

// Adiciona uma nova cor a partir do arquivo lido
void newColorFromFile(Color *colorIndex, char *inputLine, int typeOfData) {
    char *token = strtok(inputLine, " ");// Comando
    if (token == NULL) {
        return;
    }
    // Switch typeOfData
    switch (typeOfData) {
        case 1: // Quadra
            setQuadStrokeColor(colorIndex, strtok(NULL, " "));
            setQuadFillColor(colorIndex, strtok(NULL, " "));
            break;
        default:
            break;
    }
}

// Get quadFill
char *getQuadFillColor(Color *tmpCol) {
    return tmpCol->quadFill;
}

// Get quadStroke
char *getQuadStrokeColor(Color *tmpCol) {
    return tmpCol->quadStroke;
}

// Set quadFill
void setQuadFillColor(Color *tmpCol, char *aux) {
    copyString(&(tmpCol->quadFill), aux);
}

// Set quadStroke
void setQuadStrokeColor(Color *tmpCol, char *aux) {
    copyString(&(tmpCol->quadStroke), aux);
}
