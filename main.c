/**
 * @file Proje2
 * @description Dosya okuma işlemi yapıp bunun sonucunda bazı matematiksel işlemler yapıyorum
 * ve bunları en son bir dosyaya yazdırıyorum.
 * @assignment Proje 2
 * @date 21.12.2022 - 29.12.2022
 * @author Selin Sude ATALI / selinsude.atali@stu.fsm.edu.tr
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proje1.h"
#define N 150
#define M 4
/*
enum yapısı normalde 0'dan başlayarak numaralandırma yaparken ben burada ilk
değerimi 0 yerine 1'den başlatıyorum. Bu yapıyı structın içinde kullanacağım.
Bu şekilde çiçeğimin türü ne ise ona uygun bir şekilde numaralandırma yapacağım.

*/

enum CicekTur
{
    Irissetosa = 1,
    Irisversicolor = 2,
    Irisvirginica = 3
};
/*
Struct yapısı sayesinde birden fazla değişkeni aynı veri tipinde tutuyorum ve
dosyamda var olan çiçeğimin özelliklerini burada tanımlıyorum. Dosyada var olan
id sütununu okumayacağımdan dolayı struct yapısı içinde id tanımlamıyorum.
Son olarak bizden Species sütunun numaralandırma şeklinde olması istendiği için
burada enum yapısını kullanıyorum.
*/
typedef struct
{
    float SepalLengthCm;
    float SepalWidthCm;
    float PetalLengthCm;
    float PetalWidthCm;
    enum CicekTur Species;

} IrisDataType;

/*
Dosyayı fopen ile açıyorum eğer dosyayı bulamazsa ve bir sorun çıkarsa direkt
bitiriyorum. "r" ile read işlemi için bir dosya açıyorum. Bunun sonucunda geri dönüş
olarak bir file pointer döner. Eğer dosyayı açamıyorsa null döneceğinden bu durumda
bir mesaj ile programı bitirmesini istiyorum.


*/
int main()
{
    char species_check[50];
    FILE *file;
    file = fopen("Iris.csv", "r");

    if (file == NULL)
    {
        printf("Dosya aciminda hata.\n");
        return 1;
    }

    IrisDataType flowerArray[150];
    IrisDataType *flowertypes;
    flowertypes = (IrisDataType *)malloc(150 * sizeof(IrisDataType));
    int read = 0;
    int index = 0;
    int id = 0;
    /*
    Burada eğer dosyanın sonuna gelirse okumayı bitirmesi için bir while döngüsü açıyorum ve fscanf ile dosyalarımı okumaya başlıyorum.
    Burada id sütunun IrisDataType türünde oluşturduğum dinamik dizime kaydolmasını istemiyorum.Ben de bunun için int tipinde id adında bir değişkene
    bu değerlerimi atıyorum. Son olarak species bir chara atıyorum. Flowertypes dizimde speciesın enum yapısında bulunmasını istediğim için
    strcmp fonksiyonu sayesinde dosyadan okuduğum species_check değerinin ilgili türlere eşit olup olmama durumunu kontrol ediyorum. Eğer eşit ise
    0 değeri dönüyor ve bunu Species kısmına enum yapısında olacak şekilde ekliyorum. while içindeki koşul sağlandığında dosyamı kapatıyorum.

    */
    while (!feof(file))
    {
        read = fscanf(file,
                      "%d,%f,%f,%f,%f,%s\n",
                      &id,
                      &flowertypes[index].SepalLengthCm,
                      &flowertypes[index].SepalWidthCm,
                      &flowertypes[index].PetalLengthCm,
                      &flowertypes[index].PetalWidthCm,
                      species_check);

        if (strcmp(species_check, "Iris-setosa") == 0)
        {
            flowertypes[index].Species = Irissetosa;
        }
        else if (strcmp(species_check, "Iris-versicolor") == 0)
        {
            flowertypes[index].Species = Irisversicolor;
        }
        else if (strcmp(species_check, "Iris-virginica") == 0)
        {
            flowertypes[index].Species = Irisvirginica;
        }
        index++;
    }
    fclose(file);
    for (int i = 0; i < index; i++)
    {
        printf(" %.2f %.2f %.2f %.2f %d\n",

               flowertypes[i].SepalLengthCm,
               flowertypes[i].SepalWidthCm,
               flowertypes[i].PetalLengthCm,
               flowertypes[i].PetalWidthCm,
               flowertypes[i].Species);
        printf("\n");
    }

    float **matrix1 = returnMatrix(150, 4);

    for (int i = 0; i < 150; i++)
    {
        matrix1[i][0] = flowertypes[i].SepalLengthCm;
        matrix1[i][1] = flowertypes[i].SepalWidthCm;
        matrix1[i][2] = flowertypes[i].PetalLengthCm;
        matrix1[i][3] = flowertypes[i].PetalWidthCm;
    }

    float *sepallengthvec = returnVector(150);
    for (int i = 0; i < 150; i++)
    {
        sepallengthvec[i] = matrix1[i][0];
    }
    float *sepalwidthvec = returnVector(150);
    for (int i = 0; i < 150; i++)
    {
        sepalwidthvec[i] = matrix1[i][1];
    }
    float *petallengthvec = returnVector(150);
    for (int i = 0; i < 150; i++)
    {
        petallengthvec[i] = matrix1[i][2];
    }
    float *petalwidthvec = returnVector(150);
    for (int i = 0; i < 150; i++)
    {
        petalwidthvec[i] = matrix1[i][3];
    }

    // printVector(sepallengthvec, 150);
    // fopen ile yazdırma modunda bir dosya açıyorum.
    FILE *yazdir = fopen("IrisStatistic.txt", "w");
    float sepallength_mean = mean(sepallengthvec, N);
    printf("Sepal length ortalamasi:%.2f \n", sepallength_mean);
    float sepalwidth_mean = mean(sepalwidthvec, N);
    printf("Sepal width ortalamasi:%.2f\n", sepalwidth_mean);
    float petallength_mean = mean(petallengthvec, N);
    printf("Petal length ortalamasi:%.2f \n", petallength_mean);
    float petalwidth_mean = mean(petalwidthvec, N);
    printf("Petal width ortalamasi:%.2f \n", petalwidth_mean);
    fprintf(yazdir, "Sepal Length ortalamasi:%.2f\n", sepallength_mean);
    fprintf(yazdir, "Sepal Width ortalamasi:%.2f\n", sepalwidth_mean);
    fprintf(yazdir, "Petal Length ortalamasi:%.2f\n", petallength_mean);
    fprintf(yazdir, "Petal Width ortalamasi:%.2f\n", petalwidth_mean);
    printf("\n");

    float **korelasyon_matrisi = returnMatrix(4, 4);
    float korsl_sl = correlation(sepallengthvec, sepallengthvec, N);
    korelasyon_matrisi[0][0] = korsl_sl;

    printf("Sepal Length-Sepal Length Korelasyon Degeri:%.2f\n", korsl_sl);
    float korsl_sw = correlation(sepallengthvec, sepalwidthvec, N);
    korelasyon_matrisi[0][1] = korsl_sw;
    printf("Sepal Length-Sepal Width Korelasyon Degeri:%.2f\n", korsl_sw);

    float korsl_pl = correlation(sepallengthvec, petallengthvec, N);
    korelasyon_matrisi[0][2] = korsl_pl;
    printf("Sepal Length-Petal Length Korelasyon Degeri:%.2f\n", korsl_pl);

    float korsl_pw = correlation(sepallengthvec, petalwidthvec, N);
    korelasyon_matrisi[0][3] = korsl_pw;
    printf("Sepal Length-Petal Width Korelasyon Degeri:%.2f\n", korsl_pw);
    korelasyon_matrisi[1][0] = korsl_sw;

    float korsw_sw = correlation(sepalwidthvec, sepalwidthvec, N);
    korelasyon_matrisi[1][1] = korsw_sw;
    printf("Sepal Width-Sepal Width Korelasyon Degeri:%.2f\n", korsw_sw);

    float korsw_pl = correlation(sepalwidthvec, petallengthvec, N);
    korelasyon_matrisi[1][2] = korsw_pl;
    printf("Sepal Width-Petal Length Korelasyon Degeri:%.2f\n", korsw_pl);

    float korsw_pw = correlation(sepalwidthvec, petalwidthvec, N);
    korelasyon_matrisi[1][3] = korsw_pw;
    printf("Sepal Width-Petal Width Korelasyon Degeri:%.2f\n", korsw_pw);
    korelasyon_matrisi[2][0] = korsl_pl;
    korelasyon_matrisi[2][1] = korsw_pl;

    float korpl_pl = correlation(petallengthvec, petallengthvec, N);
    korelasyon_matrisi[2][2] = korpl_pl;
    printf("Petal Length-Petal Length Korelasyon Degeri:%.2f\n", korpl_pl);

    float korpl_pw = correlation(petallengthvec, petalwidthvec, N);
    korelasyon_matrisi[2][3] = korpl_pw;
    printf("Petal Length-Petal Width Korelasyon Degeri:%.2f\n", korpl_pw);
    korelasyon_matrisi[3][0] = korsl_pw;
    korelasyon_matrisi[3][1] = korsw_pw;
    korelasyon_matrisi[3][2] = korpl_pw;

    float korpw_pw = correlation(petalwidthvec, petalwidthvec, N);
    korelasyon_matrisi[3][3] = korpw_pw;
    printf("Petal Width-Petal Width Korelasyon Degeri:%.2f\n", korpw_pw);

    printf("Genel korelasyon matris\n");
    printMatrix(korelasyon_matrisi, 4, 4);
    fprintf(yazdir, "Korelasyon Degerleri:\nSepalLength\tSepalWidth\tPetalLength\tPetalWidth\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            fprintf(yazdir, "%.2f    \t", korelasyon_matrisi[i][j]);
        }
        fprintf(yazdir, "\n");
    }
    float **cov = returnMatrix(4, 4);
    cov = covarianceMatrix(matrix1, 150, 4);
    printf("Kovaryans Matris:\n");
    printMatrix(cov, M, M);
    fprintf(yazdir, "Kovaryans Matris\n");
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
        {
            fprintf(yazdir, "%.2f    \t", cov[i][j]);
        }
        fprintf(yazdir, "\n");
    }
    // printVector(sepallengthvec,150);
    float kovsl_sl = covariance(sepallengthvec, sepallengthvec, N);
    printf("Sepal Length kovaryans: %.5f\n", kovsl_sl);

    float kovsw_sw = covariance(sepalwidthvec, sepalwidthvec, N);
    // printVector(sepalwidthvec,N);
    printf("Sepal Width kovaryans: %.5f\n", kovsw_sw);

    float kovpl_pl = covariance(petallengthvec, petallengthvec, N);
    // printVector(petallengthvec,N);
    printf("Petal Length kovaryans: %.5f\n", kovpl_pl);

    float kovpw_pw = covariance(petalwidthvec, petalwidthvec, N);
    // printVector(petalwidthvec, N);

    printf("Petal Width kovaryans: %.5f\n", kovpw_pw);
    fprintf(yazdir, "Sepal Length varyans: %.5f\n", kovsl_sl);
    fprintf(yazdir, "Sepal Width varyans: %.5f\n", kovsw_sw);
    fprintf(yazdir, "Petal Length varyans: %.5f\n", kovpl_pl);
    fprintf(yazdir, "Petal Width varyans: %.5f\n", kovpw_pw);
   
    fclose(yazdir);
    freeMatrix(korelasyon_matrisi, M);
    return 0;
}
