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


    // Cria arquivo de saida svg
    FILE *StandardSvgOutput = openFile(getOutputSvgStandardFileName(FileNames), "w"); // Arquivo de saida svg padrão
    FILE *StandardTxtOutput = openFile(getOutputTxtFileName(FileNames), "w");
    printTagSvg(&StandardSvgOutput, 0); // Inicia header svg

    if (getInputGeoFileName(FileNames)!=NULL) {

        // Leitura de .geo
        FILE *GeoInputFile = openFile(getInputGeoFileName(FileNames), "r");
        if (GeoInputFile == NULL) { // Verificar se foi aberto corretamente
            printf("\nFalha na abertura do arquivo!");
            killFileArguments(&FileNames);
            return -1;
        }
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
                    insideBasicShapes(AllBasicShapes, linha,
                                      &StandardTxtOutput); // Verifica se um ponto é interno a figura
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
    } else {
        newCityShapeFromBin(Bitnopolis);
    }

    // Leitura da entrada .ec
    if (getInputEcFileName(FileNames) != NULL) {
        FILE *EcInputFile = openFile(getInputEcFileName(FileNames), "r");
        hashResult = 0; // Resultado do hash

        while (!feof(EcInputFile)) { // Loop de leitura
            readLine(&linha, &EcInputFile); // Le uma linha do arquivo de entrada
            if (linha == NULL) {
                freeString(&linha);
                break;
            }
//            printThis(linha); // Imprime a linha lida
            copyString(&tmpLinha, linha); // Copia a linha lida
            hashResult = hash((unsigned char *) strtok(tmpLinha, " ")); // Extrai o comando
//            printf("\nResultado do hashing : %lu", hashResult);

            switch (hashResult) {
                case EC_E:
                    newCityShapeFromFile(Bitnopolis, linha, ColorIndex, 5); // 5 para estabelecimento
                    break;
                case EC_T:
                    newCityShapeFromFile(Bitnopolis, linha, ColorIndex, 6); // 6 para tipo de estabelecimento
                    break;
                default:
                    break;
            }
        }
        fclose(EcInputFile);
    }

    // Leitura da entrada .pm
    if (getInputPmFileName(FileNames) != NULL) {
        FILE *PmInputFile = openFile(getInputPmFileName(FileNames), "r");
        hashResult = 0; // Resultado do hash

        while (!feof(PmInputFile)) { // Loop de leitura
            readLine(&linha, &PmInputFile); // Le uma linha do arquivo de entrada
            if (linha == NULL) {
                freeString(&linha);
                break;
            }
//            printThis(linha); // Imprime a linha lida
            copyString(&tmpLinha, linha); // Copia a linha lida
            hashResult = hash((unsigned char *) strtok(tmpLinha, " ")); // Extrai o comando
//            printf("\nResultado do hashing : %lu", hashResult);

            switch (hashResult) {
                case PM_P:
                    newCityShapeFromFile(Bitnopolis, linha, ColorIndex, 7); // 7 para pessoa
                    break;
                case PM_M:
                    newCityShapeFromFile(Bitnopolis, linha, ColorIndex, 8); // 8 para moradia
                    break;
                default:
                    break;
            }
        }
        fclose(PmInputFile);
    }

    // Leitura da entrada .via
    if (getInputViaFileName(FileNames) != NULL) {
        FILE *ViaInputFile = openFile(getInputViaFileName(FileNames), "r");
        hashResult = 0; // Resultado do hash

        while (!feof(ViaInputFile)) { // Loop de leitura
            readLine(&linha, &ViaInputFile); // Le uma linha do arquivo de entrada
            if (linha == NULL) {
                freeString(&linha);
                break;
            }
//            printThis(linha); // Imprime a linha lida
            copyString(&tmpLinha, linha); // Copia a linha lida
            hashResult = hash((unsigned char *) strtok(tmpLinha, " ")); // Extrai o comando
//            printf("\nResultado do hashing : %lu", hashResult);
            viasToBin(Bitnopolis, linha);
        }
        readVias(Bitnopolis, &StandardSvgOutput);
        fclose(ViaInputFile);
    }

    printCityShapesToSvg(Bitnopolis, &StandardSvgOutput); // Imprime as estruturas da cidade no svg
//    printCityShapes(Bitnopolis);

    // A PARTIR DAQUI APENAS CONSULTA

    // Leitura da entrada .qry
    if (getInputQryFileName(FileNames) != NULL) {
        FILE *QryInputFile = openFile(getInputQryFileName(FileNames), "r");
        FILE *SvgQryOutputFile = openFile(getOutputQrySvgName(FileNames), "w");
        printTagSvg(&SvgQryOutputFile, 0); // Inicia header svg
        hashResult = 0; // Resultado do hash
        AuxFigura *headAux = NULL; //Figuras auxiliares

        while (!feof(QryInputFile)) { // Loop de leitura
            readLine(&linha, &QryInputFile); // Le uma linha do arquivo de entrada
            if (linha == NULL) {
                freeString(&linha);
                break;
            }
//            printThis(linha); // Imprime a linha lida
            copyString(&tmpLinha, linha); // Copia a linha lida
            hashResult = hash((unsigned char *) strtok(tmpLinha, " ")); // Extrai o comando
//            printf("\nResultado do hashing : %lu", hashResult);

            switch (hashResult) { // Switch dos comandos lidos
                // T3
                case Q_MIN_SEARCH:
                    strucutreInsideRectangle(Bitnopolis, linha, &StandardTxtOutput, &SvgQryOutputFile, 1); // 1 para q?
                    break;
                case Q_SEARCH:
                    structureInsideCircle(Bitnopolis, linha, &StandardTxtOutput, &SvgQryOutputFile, 1); // 1 para Q?
                    break;
                case D_MIN_Q:
                    strucutreInsideRectangle(Bitnopolis, linha, &StandardTxtOutput, &SvgQryOutputFile, 2); // 2 para dq
                    break;
                case D_Q:
                    structureInsideCircle(Bitnopolis, linha, &StandardTxtOutput, &SvgQryOutputFile, 2); // 2 para Dq
                    break;
                case D_MIN_LE:
                    strucutreInsideRectangle(Bitnopolis, linha, &StandardTxtOutput, &SvgQryOutputFile, 3); // 3 para dle
                    break;
                case D_LE:
                    structureInsideCircle(Bitnopolis, linha, &StandardTxtOutput, &SvgQryOutputFile, 3); // 3 para dle
                    break;
                case CC:
                    changeColor(Bitnopolis, linha);
                    break;
                    // T4
                case M_SEARCH:
                    reportMorador(Bitnopolis, linha, &StandardTxtOutput, 1, &headAux);
                    break;
                case MR_SEARCH:
                    reportMoradorRect(Bitnopolis, linha, &StandardTxtOutput);
                    break;
                case DM_SEARCH:
                    reportMorador(Bitnopolis, linha, &StandardTxtOutput, 2, &headAux);
                    break;
                case DE_SEARCH:
                    reportEstab(Bitnopolis, linha, &StandardTxtOutput, 1, &headAux);
                    break;
                case RIP:
                    ripMorador(Bitnopolis, linha, &StandardTxtOutput, &headAux);
                    break;
                case FEC:
                    reportEstab(Bitnopolis, linha, &StandardTxtOutput, 5, &headAux);
                    break;
                case MUD:
                    reportMorador(Bitnopolis, linha, &StandardTxtOutput, 3, &headAux);
                    break;
                case DPR:
                    dpr(Bitnopolis, linha, &StandardTxtOutput, 1, &headAux);
                    break;
                default: // Casos não aceitos por switch
                    // T3
                    if (hashResult == CRD) {
                        reportStructure(Bitnopolis, linha, &StandardTxtOutput);
                    } else if (hashResult == CRB) {
                        closestTorres(Bitnopolis, linha, &StandardTxtOutput);
                    } else if (hashResult == ECQ_SEARCH) {
                        reportEstab(Bitnopolis, linha, &StandardTxtOutput, 2, &headAux);
                    } else if (hashResult == ECR_SEARCH) {
                        reportEstab(Bitnopolis, linha, &StandardTxtOutput, 3, &headAux);
                    } else if (hashResult == TECQ_SEARCH) {
                        reportEstab(Bitnopolis, linha, &StandardTxtOutput, 2, &headAux);
                    } else if (hashResult == TECR_SEARCH) {
                        reportEstab(Bitnopolis, linha, &StandardTxtOutput, 4, &headAux);
                    } else if (hashResult == HMPE_SEARCH) {
                        reportHid(Bitnopolis, linha, &StandardTxtOutput, 1, &headAux);
                    } else if (hashResult == HMP_SEARCH) {
                        reportHid(Bitnopolis, linha, &StandardTxtOutput, 2, &headAux);
                    } else if (hashResult == MUDEC) {
                        reportEstab(Bitnopolis, linha, &StandardTxtOutput, 6, &headAux);
                    } else if (hashResult == M_A_SEARCH) {
                        getRegistradores(Bitnopolis, linha, &StandardTxtOutput, 1);
                    } else if (hashResult == E_SEARCH) {
                        getRegistradores(Bitnopolis, linha, &StandardTxtOutput, 2);
                    } else if (hashResult == G_SEARCH) {
                        getRegistradores(Bitnopolis, linha, &StandardTxtOutput, 3);
                    } else if (hashResult == XY) {
                        getRegistradores(Bitnopolis, linha, &StandardTxtOutput, 4);
                    } else if (hashResult == P_SEARCH) {
                        Best_Caminho(linha, Bitnopolis, &StandardTxtOutput, &StandardSvgOutput);
                    } else if (hashResult == SP) {
                        Best_Direcao_Caminho(linha, Bitnopolis, &StandardTxtOutput, &StandardSvgOutput);
                    } else if (hashResult == AU) {
                        newCityShapeFromFile(Bitnopolis, linha, ColorIndex, 9); // 7 para pessoa
                        break;
                    }

            }
        }
        printBasicShapesToSvg(AllBasicShapes, &SvgQryOutputFile); // Imprime todas as formas no svg
        printCityShapesToSvg(Bitnopolis, &SvgQryOutputFile); // Imprime as estruturas da cidade no svg
        printAuxToSvg(headAux, &SvgQryOutputFile); // Imprime as estruturas auxiliares da cidade no svg
        printTagSvg(&SvgQryOutputFile, 1); // Finaliza header svg
        killAux(&headAux);
        fclose(QryInputFile);
        fclose(SvgQryOutputFile);
    }

// Free structs
    killFileArguments(&FileNames);
    killBasicShapes(&AllBasicShapes);
    killCidade(&Bitnopolis);
    killColor(ColorIndex);
// Close files
    printTagSvg(&StandardSvgOutput, 1); // Finaliza header svg
    fclose(StandardSvgOutput); // Fecha a saida svg padrao
    fclose(StandardTxtOutput);
// Free aux
    freeString(&linha);
    freeString(&tmpLinha);

// End main
    return 0;

}
