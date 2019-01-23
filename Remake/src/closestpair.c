// Include
#include "closestpair.h"

// Ponto no plano 2D
struct tmpPoint {
    unsigned long id;
    double x;
    double y;
};

// Aloca um vetor de Point e retorna o ponteiro
Point *allocPoint(int n) {
    Point *aux = (Point *) calloc((size_t) n, sizeof(Point));
    return aux;
}

// Guarda informações no ponto
void infoToPoint(Point **P, int pos, unsigned long key, double x, double y) {
    (*P)[pos].id = key;
    (*P)[pos].x = x;
    (*P)[pos].y = y;
}

// Sorting em relação a X
int compareX(const void *a, const void *b) {
    Point *p1 = (Point *) a, *p2 = (Point *) b;
    return (int) (p1->x - p2->x);
}

// Sorting em relação a Y
int compareY(const void *a, const void *b) {
    Point *p1 = (Point *) a, *p2 = (Point *) b;
    return (int) (p1->y - p2->y);
}

// Distancia entre 2 pontos
double dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y)
    );
}

// Forca bruta (pior caso)
double bruteForce(Point *P, int n, unsigned long *um, unsigned long *dois) {
    double min = FLT_MAX;
    int i, j;
    for (i = 0; i < n; ++i) {
        for (j = i + 1; j < n; ++j) {
            if (dist(P[i], P[j]) < min) {
                min = dist(P[i], P[j]);
                *um = P[i].id;
                *dois = P[j].id;
            }
        }
    }
    return min;
}

// Acha o minimo entre dois doubles
double min(double x, double y) {
    return (x < y) ? x : y;
}


// Distancia entre o par mais proximo dentro de dado itnervalo
double stripClosest(Point *strip, int size, double d, unsigned long *um, unsigned long *dois) {
    double min = d;
    int i, j;
    qsort(strip, (size_t) size, sizeof(Point), compareY);
    for (i = 0; i < size; ++i) {
        for (j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j) {
            if (dist(strip[i], strip[j]) < min) {
                min = dist(strip[i], strip[j]);
                *um = strip[i].id;
                *dois = strip[j].id;
            }
        }
    }
    return min;
}

// Função recursiva para encontrar a menos distancia
double closestUtil(Point *P, int n, unsigned long *um, unsigned long *dois) {
    // Forca bruta para n <= 3
    if (n <= 3)
        return bruteForce(P, n, um, dois);

    // Encontrar o meio
    int mid = n / 2;
    Point midPoint = P[mid];

    // Menor a direita e esquerda do meio
    double dl = closestUtil(P, mid, um, dois);
    double dr = closestUtil(P + mid, n - mid, um, dois);

    // Menor das distancias
    double d = min(dl, dr);

    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(P[i].x - midPoint.x) < d) {
            strip[j] = P[i], j++;
        }
    }

    double ret = min(d, stripClosest(strip, j, d, um, dois));
    return ret;
//    return min(d, stripClosest(strip, j, d, um, dois));
}

// Encontra o par mais proximo e retorna a distancia
double closest(Point *P, int n, unsigned long *um, unsigned long *dois) {
    qsort(P, (size_t) n, sizeof(Point), compareX);

    // Use recursive function closestUtil() to find the smallest distance
    return closestUtil(P, n, um, dois);
}

void printPoints(Point *P, int i) {
    printf("\n\nPontos\n\n");
    for (int j = 0; j < i; j++) {
        printf("Key = %lu  X = %lf  Y = %lf\n", P[j].id, P[j].x, P[j].y);
    }
}

void printClosestPoints(Point *P, int i) {
    if (i < 2) {
        return;
    }
    printf("\n\nPontos mais proximos\n\n");
    printf("Key = %lu  X = %lf  Y = %lf\n", P[0].id, P[0].x, P[0].y);
    printf("Key = %lu  X = %lf  Y = %lf\n", P[1].id, P[1].x, P[1].y);
}

// Retorna o id da posicao
unsigned long returnPointKey(Point *P, int i) {
    return P[i].id;
}
