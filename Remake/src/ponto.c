#include "ponto.h"

int printed = 0;
char *idi;
char *idj;

void heapsort(ponto *ponto, int n) {
    int i = n / 2, pai, filho, t;
    while (1) {
        if (i > 0) {
            i--;
            t = ponto[i].x;
        } else {
            n--;
            if (n == 0) return;
            t = ponto[n].x;
            ponto[n] = ponto[0];
        }
        pai = i;
        filho = i * 2 + 1;
        while (filho < n) {
            if ((filho + 1 < n) && (ponto[filho + 1].x > ponto[filho].x))
                filho++;
            if (ponto[filho].x > t) {
                ponto[pai] = ponto[filho];
                pai = filho;
                filho = pai * 2 + 1;
            } else {
                break;
            }
        }
        ponto[pai].x = t;
    }
}

void merge(ponto *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    ponto L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i].x <= R[j].x) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        if (L[i].x <= R[j].x) k++;
    }
}

void mergeSort(ponto *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void mergey(ponto *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    ponto L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i].y <= R[j].y) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSorty(ponto *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSorty(arr, l, m);
        mergeSorty(arr, m + 1, r);
        mergey(arr, l, m, r);
    }
}

float Distancia_Pontos(ponto pt1, ponto pt2) {
    float d;
    d = sqrt(pow(pt1.x - pt2.x, 2) + pow(pt1.y - pt2.y, 2));
    return d;
}

float Menor_Float(float n1, float n2) {
    if (n1 < n2) {
        return n1;
    } else {
        return n2;
    }
}

float Distancia_Minima(ponto *pt, int n) {
    float menordist = 3.402 * pow(10, 38);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (Distancia_Pontos(pt[i], pt[j]) < menordist) {
                menordist = Distancia_Pontos(pt[i], pt[j]);
            }
        }
    }
    return menordist;
}

float Menor_Front(ponto *front, int n, float mindist) {
    float min = mindist;
    mergeSorty(front, 0, n - 1);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n && (front[j].y - front[i].y) < min; j++) {
            min = Distancia_Pontos(front[i], front[j]);
            if (Distancia_Pontos(front[i], front[j]) < min) {
            }
        }
    }
    return min;
}


float Mais_Perto(ponto *pt, int n) {
    float menordist;
    if (n <= 3) {
        return Distancia_Minima(pt, n);
    }
    int meio = n / 2;
    float midx = pt[meio].x;
    ponto fronteira[n];
    float menDistDir, menDistEsq;
    menDistEsq = Mais_Perto(pt, meio - 1);
    menDistDir = Mais_Perto(pt + meio, n - meio);
    menordist = Menor_Float(menDistDir, menDistEsq);
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(pt[i].x - midx) < menordist)
            fronteira[j] = pt[i], j++;
    return Menor_Float(menordist, Menor_Front(fronteira, j, menordist));
}

