// Include
#include "query.h"

// Verifica quais estruturas se encontram totalmente dentro da area requisitada
void strucutreInsideRectangle(Cidade *cityIndex, char *linha, FILE **txtOutput, FILE **svgOutput) {
    fprintf(*txtOutput, "%s\n", linha); // Imprime a requisição no txt
    char *token = strtok(linha, " "); // Comando
    double x = newAtod(strtok(NULL, " "));
    double y = newAtod(strtok(NULL, " "));
    double width = newAtod(strtok(NULL, " "));
    double height = newAtod(strtok(NULL, " "));
    quadraInsideRectangle(cityIndex, txtOutput, svgOutput, x, y, width, height);
    semafInsideRectangle(cityIndex,txtOutput,svgOutput, x, y, width, height);
    hidInsideRectangle(cityIndex,txtOutput,svgOutput, x, y, width, height);
    torreInsideRectangle(cityIndex,txtOutput,svgOutput, x, y, width, height);
}
