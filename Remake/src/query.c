// Include
#include "query.h"

// Verifica quais estruturas se encontram totalmente dentro da area requisitada
void strucutreInsideRectangle(Cidade *cityIndex, char *linha, FILE **txtOutput, FILE **svgOutput, int action) {
    fprintf(*txtOutput, "%s\n", linha); // Imprime a requisição no txt
    char *token = strtok(linha, " "); // Comando
    double x;
    double y;
    double width;
    double height;
    int i = 0;
    switch (action) {
        case 1: // q?
            x = newAtod(strtok(NULL, " "));
            y = newAtod(strtok(NULL, " "));
            width = newAtod(strtok(NULL, " "));
            height = newAtod(strtok(NULL, " "));
            quadraInsideRectangle(cityIndex, txtOutput, svgOutput, x, y, width, height, 1);
            semafInsideRectangle(cityIndex, txtOutput, svgOutput, x, y, width, height, 1);
            hidInsideRectangle(cityIndex, txtOutput, svgOutput, x, y, width, height, 1);
            torreInsideRectangle(cityIndex, txtOutput, svgOutput, x, y, width, height, 1);
            break;
        case 2: // dq
            x = newAtod(strtok(NULL, " "));
            y = newAtod(strtok(NULL, " "));
            width = newAtod(strtok(NULL, " "));
            height = newAtod(strtok(NULL, " "));
            quadraInsideRectangle(cityIndex, txtOutput, svgOutput, x, y, width, height, 2);
            break;
        case 3: // dle
            token = strtok(NULL, " ");
            x = newAtod(strtok(NULL, " "));
            y = newAtod(strtok(NULL, " "));
            width = newAtod(strtok(NULL, " "));
            height = newAtod(strtok(NULL, " "));
            while (token[i] != '\0') {
                switch (token[i]) {
                    case 's':
                        semafInsideRectangle(cityIndex, txtOutput, svgOutput, x, y, width, height, 2);
                        break;
                    case 'h':
                        hidInsideRectangle(cityIndex, txtOutput, svgOutput, x, y, width, height, 2);
                        break;
                    case 'r':
                        torreInsideRectangle(cityIndex, txtOutput, svgOutput, x, y, width, height, 2);
                        break;
                    default:
                        break;
                }
                i++;
            }
            break;
        default:
            break;
    }
}
