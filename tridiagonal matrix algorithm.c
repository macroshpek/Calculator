#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS 
#pragma warning(disable : 4996)
#define num_of_eq num

/**
 * num_of_eq - ����� ��������� (����� �������)
 * nad_diag - ���������, ������� ��� ������� (����������: [0;n-2])
 * glav_diag - ������� ��������� ������� A (����������: [0;n-1])
 * pod_diag - ���������, ������� ��� ������� (����������: [1;n-1])
 * st_y - ������ ����� (�������)
 * roots - �������, ������ x ����� ��������� �����
 */

void progon(int num_of_eq, double* pod_diag, double* glav_diag, double* nad_diag, double* st_y, double* roots) {

    double m;
    for (int i = 1; i < num_of_eq; i++)
    {
        m = pod_diag[i] / glav_diag[i - 1];
        glav_diag[i] = glav_diag[i] - m * nad_diag[i - 1];
        st_y[i] = st_y[i] - m * st_y[i - 1];
    }

    roots[num_of_eq - 1] = st_y[num_of_eq - 1] / glav_diag[num_of_eq - 1];

    for (int i = num_of_eq - 2; i >= 0; i--)
    {
        roots[i] = (st_y[i] - nad_diag[i] * roots[i + 1]) / glav_diag[i];
    }
}

void print_matrix(double** matrix, int code, int num_of_eq) {
    if (code == 1) {
        for (int i = 0; i < num; i++) {
            for (int j = 0; j < num + 1; j++) {
                printf("%.5lf", matrix[i][j]);
            }
            printf("\n");
        }
    }
    else {
        for (int i = 0; i < num; i++) {
            for (int j = 0; j < num; j++) {
                printf("%.5lf", matrix[i][j]);
            }
            printf("\n");
        }
    }
}

int main(void) {
    int num_of_eq;
    scanf("%d", &num_of_eq);
    double** matrix = (double**)malloc(num_of_eq * sizeof(double*)); //��������� ������ ��� �������
    if (!matrix) {
        exit(0);
    }
    for (int i = 0; i < num; i++) {
        matrix[i] = (double*)malloc((num + 1) * sizeof(double));
        if (!matrix[i]) {
            exit(0);
        }
    }
    double* roots = (double*)malloc(num * sizeof(double)); //����� �������
    if (!roots) {
        exit(0);
    }

    double* pod_diag = (double*)calloc(num_of_eq, sizeof(double)); //������ ��� ������������
    double* glav_diag = (double*)calloc(num_of_eq, sizeof(double)); //������ ��� ������� ���������
    double* nad_diag = (double*)calloc(num_of_eq, sizeof(double)); //������ ��� ������������
    double* st_y = (double*)calloc(num_of_eq, sizeof(double)); //������ ��� ������� �������
         
    printf("pod_diag:\n"); //������ ��� ���������
    for (int i = 1; i < num; i++) {
        scanf("%lf", &(pod_diag[i]));
    }
    printf("glav_diag:\n"); //������ ���� ���������
    for (int i = 0; i < num; i++) {
        scanf("%lf", &(glav_diag[i]));
    }
    printf("nad_diag:\n"); //������ ��� ���������
    for (int i = 0; i < num - 1; i++) {
        scanf("%lf", &(nad_diag[i]));
    }
    printf("st_y:\n");
    for (int i = 0; i < num; i++) {
        scanf("%lf", &(st_y[i]));
    }
    progon(num_of_eq, pod_diag, glav_diag, nad_diag, st_y, roots);
    for (int i = 0; i < num; i++) {
        printf("%lf\n", roots[i]);
    }
}