/**
 * @file Proje2
 * @description Dosya okuma işlemi yapıp bunun sonucunda bazı matematiksel işlemler yapıyorum 
 * ve bunları en son bir dosyaya yazdırıyorum.
 * @assignment Proje 2
 * @date 21.12.2022 - 29.12.2022
 * @author Selin Sude ATALI / selinsude.atali@stu.fsm.edu.tr
 */

#ifndef MATRIXLIB_H
#define MATRIXLIB_H

float *returnVector(int size);
float **returnMatrix(int row, int col);
void freeMatrix(float **mat, int row);
float mean(float *vec, int size);
float correlation(float *vec, float *vec2, int size);
float covariance(float *vec1, float *vec2, int size);
float **matrixMultiplication(float **mat1, float **mat2, int row1, int col1, int row2, int col2);
float **matrixTranspose(float **mat, int row, int col);
float *rowMeans(float **mat, int row, int col);
float *columnMeans(float **mat, int row, int col);
float **covarianceMatrix(float **mat, int row, int col);
float determinant(float **mat, int row);
void printVector(float *vec, int N);
void printMatrix(float **mat, int row, int col);
float *vectordoldur(float *dizi, int size, int seed);
float **matrixdoldur(float **dizi, int row, int col, int seed);
void clean(float *arr, int size);
#endif