// Include
#include "color.h"

struct tmpColor { // Color
    char *quadStroke;
    char *quadFill;
    char *hidStroke;
    char *hidFill;
    char *semafStroke;
    char *semafFill;
    char *torreStroke;
    char *torreFill;
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
        freeString(&(tmpCol->hidStroke));
        freeString(&(tmpCol->hidFill));
        freeString(&(tmpCol->semafStroke));
        freeString(&(tmpCol->semafFill));
        freeString(&(tmpCol->torreStroke));
        freeString(&(tmpCol->torreFill));
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
        case 2: // Hidrante
            setHidStrokeColor(colorIndex, strtok(NULL, " "));
            setHidFillColor(colorIndex, strtok(NULL, " "));
            break;
        case 3: // Semaforo
            setSemafStrokeColor(colorIndex, strtok(NULL, " "));
            setSemafFillColor(colorIndex, strtok(NULL, " "));
            break;
        case 4: // Torre
            setTorStrokeColor(colorIndex, strtok(NULL, " "));
            setTorFillColor(colorIndex, strtok(NULL, " "));
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

// Get hidFill
char *getHidFillColor(Color *tmpCol) {
    return tmpCol->hidFill;
}

// Get hidStroke
char *getHidStrokeColor(Color *tmpCol) {
    return tmpCol->hidStroke;
}

// Set hidFill
void setHidFillColor(Color *tmpCol, char *aux) {
    copyString(&(tmpCol->hidFill), aux);
}

// Set hidStroke
void setHidStrokeColor(Color *tmpCol, char *aux) {
    copyString(&(tmpCol->hidStroke), aux);
}

// Get semafFill
char *getSemafFillColor(Color *tmpCol) {
    return tmpCol->semafFill;
}

// Get semafStroke
char *getSemafStrokeColor(Color *tmpCol) {
    return tmpCol->semafStroke;
}

// Set semafFill
void setSemafFillColor(Color *tmpCol, char *aux) {
    copyString(&(tmpCol->semafFill), aux);
}

// Set semafStroke
void setSemafStrokeColor(Color *tmpCol, char *aux) {
    copyString(&(tmpCol->semafStroke), aux);
}

// Get torreFill
char *getTorFillColor(Color *tmpCol) {
    return tmpCol->torreFill;
}

// Get torreStroke
char *getTorStrokeColor(Color *tmpCol) {
    return tmpCol->torreStroke;
}

// Set torreFill
void setTorFillColor(Color *tmpCol, char *aux) {
    copyString(&(tmpCol->torreFill), aux);
}

// Set torreStroke
void setTorStrokeColor(Color *tmpCol, char *aux) {
    copyString(&(tmpCol->torreStroke), aux);
}
