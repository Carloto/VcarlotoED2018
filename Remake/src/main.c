// Modulo main do trabalho

// Include
#include <stdio.h>
#include <stdlib.h>
#include "filehandling.h"
#include "miscfunctions.h"
#include "filehandling.h"
#include "basicshapes.h"
#include "cidade.h"
#include "color.h"
#include "query.h"

// Main
int main(int argc, char *argv[]) {

    // Verificar se entrada de argumentos é nula
    if (argc <= 1) {
        printf("\nNenhum argumento foi encontrado na linha de comando!\n");
        return -1;
    }

    // Obtem os argumentos da linha de comando
    fileArguments *FileNames = createFileArguments();
    setFileArguments(&FileNames, argc, argv);
    printInputArguments(FileNames);

    // Estruturas de Bitnopolis
    BasicShapes *AllBasicShapes = allocBasicShapes();
    Cidade *Bitnopolis = allocCidade(FileNames);
    Color *ColorIndex = allocColor();

    // Variaveis auxiliares
    char *linha = NULL; // Linha lida
    char *tmpLinha = NULL; // Copia para strtok
    unsigned long int hashResult = 0; // Resultado do hash

    // Leitura de .geo
    FILE *GeoInputFile = openFile(getInputGeoFileName(FileNames), "r");
    if (GeoInputFile == NULL) { // Verificar se foi aberto corretamente
        printf("\nFalha na abertura do arquivo!");
        killFileArguments(&FileNames);
        return -1;
    }

    // Cria arquivo de saida svg
    FILE *StandardSvgOutput = openFile(getOutputSvgStandardFileName(FileNames), "w"); // Arquivo de saida svg padrão
    FILE *StandardTxtOutput = openFile(getOutputTxtFileName(FileNames), "w");
    printTagSvg(&StandardSvgOutput, 0); // Inicia header svg

    // Leitura da entrada .geo
    int controle = 1; // Controle permite a execução da leitura, e # muda seu valor para 0

    while (!feof(GeoInputFile) && controle == 1) { // Loop de leitura
        readLine(&linha, &GeoInputFile); // Le uma linha do arquivo de entrada
//        printThis(linha); // Imprime a linha lida
        copyString(&tmpLinha, linha); // Copia a linha lida
        hashResult = hash((unsigned char *) strtok(tmpLinha, " ")); // Extrai o comando
//        printf("\nResultado do hashing : %lu", hashResult);

        switch (hashResult) { // Switch dos comandos lidos
            // T2
            case CMD_NX: // Comando desnecessario nessa implementacao
                break;
            case CMD_A:
                linesFromId(AllBasicShapes, linha, FileNames); // Traça linhas a partir do id
                break;
            case CMD_D:
                distanceBasicShapes(AllBasicShapes, linha, &StandardTxtOutput); // Calcula a distancia entre figuras
                break;
            case CMD_I:
                insideBasicShapes(AllBasicShapes, linha, &StandardTxtOutput); // Verifica se um ponto é interno a figura
                break;
            case CMD_O:
                overlapBasicShapes(AllBasicShapes, linha, &StandardTxtOutput, &StandardSvgOutput); // Sobreposicao
                break;
            case FIG_C:
                newShapeFromFile(AllBasicShapes, linha, 1); // 1 para circulo
                break;
            case FIG_R:
                newShapeFromFile(AllBasicShapes, linha, 2); // 2 para retangulo
                break;
            case CMD_FIM: // Final da leitura
                controle = 0;
                break;
                // T3
            case FIG_Q:
                newCityShapeFromFile(Bitnopolis, linha, ColorIndex, 1); // 1 para quadra
                break;
            case FIG_H:
                newCityShapeFromFile(Bitnopolis, linha, ColorIndex, 2); // 2 para hidrante
                break;
            case FIG_S:
                newCityShapeFromFile(Bitnopolis, linha, ColorIndex, 3); // 3 para semaforo
                break;
            case FIG_T:
                newCityShapeFromFile(Bitnopolis, linha, ColorIndex, 4); // 4 para torre
                break;
            case COR_Q:
                newColorFromFile(ColorIndex, linha, 1);
                break;
            case COR_H:
                newColorFromFile(ColorIndex, linha, 2);
                break;
            case COR_S:
                newColorFromFile(ColorIndex, linha, 3);
                break;
            case COR_T:
                newColorFromFile(ColorIndex, linha, 4);
                break;
            default:
                break;
        }

    }
    fclose(GeoInputFile); // Fecha o arquivo .geo

    printBasicShapesToSvg(AllBasicShapes, &StandardSvgOutput); // Imprime todas as formas no svg
//    printBasicShapes(AllBasicShapes);
    printCityShapesToSvg(Bitnopolis, &StandardSvgOutput); // Imprime as estruturas da cidade no svg
    printCityShapes(Bitnopolis);
    printTagSvg(&StandardSvgOutput, 1); // Finaliza header svg
    fclose(StandardSvgOutput); // Fecha a saida svg padrao

    // Leitura da entrada .qry
    if (getInputQryFileName(FileNames) != NULL) {
        FILE *QryInputFile = openFile(getInputQryFileName(FileNames), "r");
        FILE *SvgQryOutputFile = openFile(getOutputQrySvgName(FileNames), "w");
        printTagSvg(&SvgQryOutputFile, 0); // Inicia header svg
        hashResult = 0; // Resultado do hash

        while (!feof(QryInputFile)) { // Loop de leitura
            readLine(&linha, &QryInputFile); // Le uma linha do arquivo de entrada
            if (linha == NULL){
                break;
            }
            printThis(linha); // Imprime a linha lida
            copyString(&tmpLinha, linha); // Copia a linha lida
            hashResult = hash((unsigned char *) strtok(tmpLinha, " ")); // Extrai o comando
            printf("\nResultado do hashing : %lu", hashResult);

            switch (hashResult) { // Switch dos comandos lidos
                // T3
                case Q_MIN_SEARCH:
                    strucutreInsideRectangle(Bitnopolis, linha, &StandardTxtOutput, &SvgQryOutputFile);
                    break;
                default:
                    break;
            }

        }
        printBasicShapesToSvg(AllBasicShapes, &SvgQryOutputFile); // Imprime todas as formas no svg
        printCityShapesToSvg(Bitnopolis, &SvgQryOutputFile); // Imprime as estruturas da cidade no svg
        printTagSvg(&SvgQryOutputFile, 1); // Finaliza header svg
        fclose(QryInputFile);
        fclose(SvgQryOutputFile);
    }

    // Free structs
    killFileArguments(&FileNames);
    killBasicShapes(&AllBasicShapes);
    killCidade(&Bitnopolis);
    killColor(ColorIndex);
    // Close files
    fclose(StandardTxtOutput);
    // Free aux
    freeString(&linha);
    freeString(&tmpLinha);

    // End main
    return 0;

}
