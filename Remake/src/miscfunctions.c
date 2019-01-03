// Include
#include "miscfunctions.h"

// Imprime uma string
void printThis(char *output) {
    if (output != NULL) {
        printf("\n|%s|", output);
    }
}

// Copia uma string
void copyString(char **final, char *aux) {
    size_t len = 0;
    len = strlen(aux);
    freeString(final);
    *final = (char *) calloc(len + 1, sizeof(char));
    //strcpy(*final, aux);
    sprintf(*final, "%s", aux);
}

// Free String
void freeString(char **temp_free) {
    if (*temp_free != NULL) {
        free(*temp_free);
    }
    *temp_free = NULL;
}

// Free double
void freeDouble(double **tmpValue) {
    if (*tmpValue != NULL) {
        free(*tmpValue);
    }
    *tmpValue = NULL;
}

// Free int
void freeInt(int **tmpValue) {
    if (*tmpValue != NULL) {
        free(*tmpValue);
    }
    *tmpValue = NULL;
}

// Remove o primeiro character
void removeFirstChar(char **final) {
    size_t len;
    char *aux;
    len = strlen(*final);
    aux = (char *) calloc(len, sizeof(char));
    for (int i = 1, j = 0; i < len; i++, j++) {
        aux[j] = (*final)[i];
    }

    aux[len - 1] = '\0';
    freeString(final);
    *final = (char *) calloc(len, sizeof(char));
    strcpy(*final, aux);
    freeString(&aux);
}

// Concatena nomes de arquivos
void strcatFileName(char **final, char *before, char **after, char type[50]) {
    freeString(final);
    size_t lenBefore = strlen(before);
//    printf("\n len before = %lu", lenBefore);
    size_t lenAfter = strlen(*after);
//    printf("\n len after = %lu", lenAfter);
    size_t lenType = strlen(type);
//    printf("\n len type = %lu", lenType);

    // Verifica a occorencia de "/"
    if ((before[lenBefore - 1] == '/' && *after[0] != '/') || (before[lenBefore - 1] != '/' && (*after)[0] == '/')) {
        *final = (char *) calloc(lenBefore + lenAfter + lenType + 2, sizeof(char));
        sprintf(*final, "%s%s%s", before, *after, type);
    } else if (before[lenBefore - 1] == '/' && (*after)[0] == '/') {
        removeFirstChar(after);
        *final = (char *) calloc(lenBefore + lenAfter + lenType + 2, sizeof(char));
        sprintf(*final, "%s%s%s", before, *after, type);
    } else if (before[lenBefore - 1] != '/' && (*after)[0] != '/') {
        *final = (char *) calloc(lenBefore + lenAfter + lenType + 3, sizeof(char));
        sprintf(*final, "%s/%s%s", before, *after, type);
    }

}

// Concatena nomes
void strcatName(char **final, char *before, char **after, char type[50]) {
    freeString(final);
    size_t lenBefore = strlen(before);
//    printf("\n len before = %lu", lenBefore);
    size_t lenAfter = strlen(*after);
//    printf("\n len after = %lu", lenAfter);
    size_t lenType = strlen(type);
//    printf("\n len type = %lu", lenType);
    *final = (char *) calloc(lenBefore + lenAfter + lenType + 2, sizeof(char));
    sprintf(*final, "%s%s%s", before, type, *after);

}

// Função de hashing para strings
unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = (hash * 33) + c; /* hash * 33 + c */
    }
    return hash;
}

// Isola o nome de um arquivo
void cutFileName(char **final, char *aux) {
    int i, j;
    size_t len = 0;
    freeString(final);
    len = strlen(aux);
    for (i = (int) len; i > -1; i--) { // Verificar a ocorrencia de / no meio do nome
        if (aux[i] == '/') {
            break;
        }
    }
    if (i == -1) { // Loop no final, não há path
        *final = (char *) calloc(len + 1, sizeof(char));
        i = 0;

        for (j = 0; j < (int) len - 4; j++, i++) {
            (*final)[j] = aux[i];
        }
        (*final)[len - 4] = '\0';
    } else {
        /* O loop não chegou no final, logo, há path */
        len = len - i;
        *final = (char *) calloc(len + 1, sizeof(char));
        i++;
        for (j = 0; j < len - 5; j++, i++) {
            (*final)[j] = aux[i];
        }
        (*final)[len - 5] = '\0';
    }
}

// Conversão para inteiro
int newAtoi(char *aux) {
    char *ptr;
    int newValue = (int) strtol(aux, &ptr, 10);
    return newValue;
}

// Conversão para double
double newAtod(char *aux) {
    char *ptr;
    double newValue = strtod(aux, &ptr);
    return newValue;
}

// Retorna a distancia entre duas coordenadas
double findDistance(double aX, double aY, double bX, double bY) {
    double exp = 2;
    return sqrt(pow(aX - bX, exp) + pow(aY - bY, exp));
}

// Verifica se um ponto é interno a  um circulo
int pointInsideCircle(double pointX, double pointY, double circleX, double circleY, double radius) {
    double distance = findDistance(pointX, pointY, circleX, circleY);
    distance = distance - radius;
    if (distance < 0) { //  O ponto é interno
        return 1;
    }
    return 0; // O ponto não é interno
}

// Verifica se um ponto é interno a  um retangulo
int pointInsideRectangle(double pointX, double pointY, double rectX, double rectY, double width, double height) {
    if (rectX < pointX && (rectX + width) > pointX &&
        rectY < pointY && (rectY + height) > pointY) { //  O ponto é interno
        return 1;
    }
    return 0; // O ponto não é interno
}

// Verifica se dois circulos se sobrepoem
int
overlapCircleCircle(double aX, double aY, double aR, double bX, double bY, double bR, int controle, FILE **outputFile) {
    double distance = findDistance(aX, aY, bX, bY);
    double rectX, rectY, width, height;
    distance = distance - aR - bR;
    if (distance < 0) { // Sobrepõem
        if (controle == 1) { // Imprimir retangulo tracejado
            if (aX - aR <= bX - bR) { // Pega X
                rectX = aX - aR - 1;
            } else {
                rectX = bX - bR - 1;
            }
            if ((bX + bR) > (aX + aR)) { // Pega width
                width = bX - rectX + bR + 1;
            } else {
                width = aX - rectX + aR + 1;
            }
            if (aY - aR <= bY - bR) { // Pega Y
                rectY = aY - aR - 1;
            } else {
                rectY = bY - bR - 1;
            }
            if ((bY + bR) > (aY + aR)) { // Pega height
                height = bY - rectY + bR + 1;
            } else {
                height = aY - rectY + aR + 1;
            }
            printDashRectangle(outputFile, rectX, rectY, width, height);
        }
        return 1;
    }
    return 0; // Não sobrepõem
}

// Verifica se um circulo e um retangulo se sobrepoem
int
overlapCircleRectangle(double aX, double aY, double aR, double bX, double bY, double bWidth, double bHeight,
                       int controle, FILE **outputFile) {
    double distX = fabs(aX - bX - bWidth / 2);
    double distY = fabs(aY - bY - bHeight / 2);
    double rectX, rectY, width, height;
    int validate = 0;
    if (distX < (bWidth / 2 + aR) && distY < (bHeight / 2 + aR)) {
        if (distX <= (bWidth / 2) || distY <= (bHeight / 2)) {
            validate = 1;
        } else {
            distX = distX - bWidth / 2;
            distY = distY - bHeight / 2;
            if (distX * distX + distY * distY <= ((aR) * (aR))) {
                validate = 1;
            }
        }
    }
    if (validate) { // Sobrepõem
        if (controle == 1) { // Imprimir retangulo tracejado
            if ((aX - aR) <= bX) { // Pega x
                rectX = aX - aR - 1;
            } else {
                rectX = bX - 1;
            }
            if ((bX + bWidth) > (aX + aR)) { // Pega width
                width = bX - rectX + bWidth + 1;
            } else {
                width = aX - rectX + aR + 1;
            }
            if ((aY - aR) <= bY) { // Pega y
                rectY = aY - aR - 1;
            } else {
                rectY = bY - 1;
            }
            if ((bY + bHeight) > (aY + aR)) { // Pega height
                height = bY - rectY + bHeight + 1;
            } else {
                height = aY - rectY + aR + 1;
            }
            printDashRectangle(outputFile, rectX, rectY, width, height);
        }
        return 1;
    }
    return 0; // Não sobrepõem
}

// Verifica se dois retangulos se sobrepoem
int
overlapRectangleRectangle(double aX, double aY, double aWidth, double aHeight, double bX, double bY, double bWidth,
                          double bHeight, int controle, FILE **outputFile) {
    double rectX, rectY, width, height;
    if (aX < (bX + bWidth) && (aX + aWidth) > bX &&
        aY < (bY + bHeight) && (aY + aHeight) > bY) { // Sobrepõem
        if (controle == 1) { // Imprimir retangulo tracejado
            if (aX <= bX) { // Pega x
                rectX = aX - 1;
            } else {
                rectX = bX - 1;
            }
            if ((bX + bWidth) > (aX + aWidth)) { // Pega width
                width = bX - rectX + bWidth + 1;
            } else {
                width = aX - rectX + aWidth + 1;
            }
            if (aY <= bY) { // Pega y
                rectY = aY - 1;
            } else {
                rectY = bY - 1;
            }
            if ((bY + bHeight) > (aY + aHeight)) { // Pega height
                height = bY - rectY + bHeight + 1;
            } else {
                height = aY - rectY + aHeight + 1;
            }
            printDashRectangle(outputFile, rectX, rectY, width, height);
        }
        return 1;
    }
    return 0; // Não sobrepõem
}

// Imprime um retangulo tracejado
void printDashRectangle(FILE **outputFile, double rectX, double rectY, double width, double height) {

    fprintf(*outputFile, "\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" \n", rectX, rectY, width, height);
    fprintf(*outputFile, "\t\tstyle=\"stroke: %s;\n\t\t\tstroke-dasharray: 4 1;\n\t\t\tfill: none;\n\t\t\"\n\t/>",
            "black");
    fprintf(*outputFile, "\t<text x=\"%f\" y=\"%f\" fill=\"%s\">Sobrepõe</text>\n", rectX, rectY - 3, "black");
}
