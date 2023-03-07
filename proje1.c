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
#include "proje1.h"
#include <time.h>
#include <math.h>

/*

Malloc ile hafızadan belirli bir yer ayırıyorum ama malloc fonksiyonun geriye dönüş tipi void olduğunda float'a cast işlemi yapıyorum.
Floatın bellekte kapladığı yer ile parametre olarak gönderdiğim size değerinin  çarpılmasıyla bellekte size kadarlık float yerini
 hafızada ayırıyorum ve bu ayırdığım alana sonradan değer atayacağım.
*/
float *returnVector(int size)
{
    float *matrix = (float *)malloc(sizeof(float *) * size);
    return matrix;
}
/*
Malloc ile hafızadan satır ve sütun sayısına uygun olarak yer ayırtıyorum.
*/

float **returnMatrix(int row, int col)
{
    float **matris = (float **)malloc(sizeof(float *) * row);
    for (int i = 0; i < row; i++)
    {
        matris[i] = (float *)malloc(sizeof(float *) * col);
    }
    return matris;
}
/* Bu fonksiyonumda 1'den 10'a kadar random sayı üreten ve belirlediğim dizinin eleman
sayısı kadar dizinin ilgili indexini random sayı ile dolduran bir fonksiyon yazdım.Buradaki
seed değerini eğer aynı değeri hep yollarsam aynı değerleri üretecektir. Farklı
değerleri yolladığımda ise farklı değerler üretecektir.
*/
float *vectordoldur(float *dizi, int size, int seed)
{
    int i;
    srand(seed);
    for (i = 0; i < size; i++)
    {
        dizi[i] = 1 + (rand() % 10);
    }
    return dizi;
}
/* 2 boyutlu bir matrisin ilgili eleman sayısı kadar random sayılar ile dolduruyorum.

*/
float **matrixdoldur(float **dizi, int row, int col, int seed)
{
    int i;
    srand(seed);
    for (i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            dizi[i][j] = 1 + (rand() % 10);
        }
    }
    return dizi;
}
/* Bu fonksiyon sayesinde dinamik olarak oluşturduğum matrisin alanını belleğe geri veriyorum.

*/

void freeMatrix(float **mat, int row)
{
    for (int i = 0; i < row; i++)
    {
        free(mat[i]);
    }
    free(mat);
}
/* Bu fonksiyonda tek boyutlu bir vektör yolluyorum ve bu vektörün elemanlarını float tipinde
ortalama adında  bir değişkende tutuyorum ve bu değişkene vektörün ilgili indexindeki
elemanları ekliyorum ve en son ortalamayı vektörün boyutuna bölüyorum.

*/
float mean(float *vec, int size)
{
    float ortalama = 0.0;
    for (int i = 0; i < size; i++)
    {
        ortalama += *(vec + i);
    }
    ortalama /= size;
    return ortalama;
}
/*
Bu fonksiyonumda oluşturduğum mean fonksiyonu ile 2 vektörümünde ortalamasını alıyorum.
float tipinde value adında bir değişken tanımladım. For döngüsü içinde dizimin
index sayısı kadar gezeceğim ve 1.vektörden ilgili vektörün ortalamasını çıkarıyorum.
Aynı işlemi ikinci vektör içinde yapıyorum ve formül gereği bu iki sayıyı çarpıp ortalama
değerime ekliyorum. En son value değerimi size-1'e bölüyorum ve kovaryans değerimi elde
ediyorum.
*/
float covariance(float *vec1, float *vec2, int size)
{
    float covariances = 0;
    float veco1 = mean(vec1, size);
    float veco2 = mean(vec2, size);
    float value = 0;
    for (int i = 0; i < size; i++)
    {
        value += (vec1[i] - veco1) * (vec2[i] - veco2);
    }
    covariances = (value / (size - 1));
    return covariances;
}
/*
Correlation fonksiyonunda oluşturduğum covariance ve mean fonksiyonlarını kullanıyorum.For döngüsü
içinde vektörlerimin boyutu kadar dolaşıyorum.Burada her bir vektörün kendisinden ortalamasını çıkarıyorum ve bu değişkenin
 karesini ilgili değerime ekliyorum. Döngü bittikten sonra xn ve yn değerlerimi size-1'e bölüyorum.
Bu değerlerimin çarpımının karekökünü covarience değerime bölüyorum ve buradan corelasyon değerimi elde ediyorum.
*/

float correlation(float *vec, float *vec2, int size)
{

    float correlations = 0;
    float covariance_c = covariance(vec, vec2, size);
    float veco1 = mean(vec, size);
    float veco2 = mean(vec2, size);
    float xn = 0, yn = 0;
    for (int i = 0; i < size; i++)
    {
        xn += pow(vec[i] - veco1, 2);
        yn += pow(vec2[i] - veco2, 2);
    }

    xn = (xn / (size - 1));
    yn = (yn / (size - 1));
    float multi = xn * yn;
    float sqrt_c = sqrt(multi);
    correlations = covariance_c / sqrt_c;
    return correlations;
}
/* 2 boyutlu matrisimin satır ve sütun sayısına göre iç içe for döngüsünde geziyorum.
Satır ortalamasını bulmak için öncelikle satır sayısı kadar uzunluğu olan  float pointer tipinde
bir değişken üretiyorum. Ort adını verdiğim float tipindeki değişkenime ilgili satırın sütunundaki değerini ekliyorum ve
sütun kısmını gezdiğim ikinci for döngüsü bitince diğer satıra geçmeden önce ilgili satırın
ortalamasını ortalamavectorun ilgili indexine atıyorum ve ort değişkenimi yeni satır indexine
geçerken sıfırlıyorum.
*/
float *rowMeans(float **mat, int row, int col)
{
    float ort;
    float *ortalamavector = returnVector(row);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            ort += mat[i][j];
        }
        *(ortalamavector + i) = ort / col;
        ort = 0;
    }
    return ortalamavector;
}
/* 2 boyutlu matrisimin satır ve sütun sayısına göre iç içe for döngüsünde geziyorum.
Sütun ortalamasını bulmak için öncelikle sütun sayısı kadar uzunluğu olan  float pointer tipinde
bir değişken üretiyorum. Ort adını verdiğim float tipindeki değişkenime ilgili sütunun satırındaki değerini ekliyorum ve
satır kısmını gezdiğim ikinci for döngüsü bitince diğer sütuna geçmeden önce ilgili sütunun
ortalamasını ortalamavectorCol ilgili indexine atıyorum ve ort değişkenimi yeni sütun indexine
geçerken sıfırlıyorum.

*/

float *columnMeans(float **mat, int row, int col)
{
    float ort;
    float *ortalamavectorCol = returnVector(col);

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            ort += mat[j][i];
        }
        *(ortalamavectorCol + i) = ort / row;

        ort = 0;
    }
    return ortalamavectorCol;
}
/*
Öncelikle matrisin transpozunu tutmak için bir dizi oluşturuyorum. Burada satır sayısı col sütun sayısı row uzunluğunda olan kadarlık
bir alanı belleğimde ayırtıyorum. Burada amacım parametre olarak gönderdiğim matrisin satırlarını sütun, sütunlarını ise satır yapıyorum
ve transpoz işlemini yapmış oluyorum.
*/

float **matrixTranspose(float **mat, int row, int col)
{
    float **matrisTranspoz = returnMatrix(col, row);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrisTranspoz[j][i] = mat[i][j];
        }
    }
    return matrisTranspoz;
}
/*Matris çarpımında en önemli olan şey parametre olarak gönderdiğim birinci matrisin col1  değeri ile ikinci matrisin row2 değerinin
 aynı olması gerekmektedir. Aksi takdirde bu matrislerin çarpımı kural gereği mümkün değildir. Bu tarz bir uygunsuzluk durumunda
 fonksiyonumun işlem yapmamasını ve bir uyarı mesajı yollamasını istiyorum. Daha sonra uygun bir şekilde matris çarpım
 işlemini yaptırıyorum.

*/
float **matrixMultiplication(float **mat1, float **mat2, int row1, int col1, int row2, int col2)
{
    if (col1 == row2)
    {
        float sum;
        float **matris = returnMatrix(row1, col2);
        matris = returnMatrix(row1, col2);

        for (int i = 0; i < row1; i++)
        {

            for (int j = 0; j < col2; j++)
            {

                for (int k = 0; k < col1; k++)
                {
                    sum += mat1[i][k] * mat2[k][j];
                }
                matris[i][j] = sum;
                sum = 0;
            }
        }
        return matris;
    }
    else
    {
        printf("Matrisler uygun sartlarda olmadigindan bu islem yapilamaz");
        exit(1);
        return NULL;
    }
}

/*
Öncelikle bu fonksiyonumda sadece 3x3 lük bir matrisin determinantını hesaplayacağım ve Sarrus Kuralı ile
 determinant yapacağımdan dolayı ilk iki satır ve sütundaki elemanları matrisimin sağına eklemek için yeni bir diziye atıyorum.

*/
float determinant(float **matris, int row)
{
    float toplam = 0;
    float *matris_one = returnVector(6);
    float array[3][2];
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < row - 1; j++)
        {
            array[i][j] = matris[i][j];
        }
    }
    /*
    Burada realloc ile her bir satırıma ilgili sütun kadar eleman eklemek için yer açıyorum.
    */
    int col = row + 2;
    for (int h = 0; h < row; h++)
    {
        matris[h] = realloc(matris[h], sizeof(float) * col);
    }

    int b = 0;
    /*
    Burada güncellediğim matrisimin ilgili satırındaki yeni sütunlarına oluşturduğum arraydeki değerleri uygun şekilde ekliyorum.

    */
    for (int i = 0; i < row; i++)
    {
        for (int j = row; j < col; j++)
        {
            *(*(matris + i) + j) = array[i][b];
            b++;
        }
        b = 0;
    }
    /*
    Burada oluşturduğum tek boyutlu vektörün elemanlarını clean foksiyonum sayesinde her bir indexine 1 değerini atıyorum.
    Elde ettiğim örüntüye göre değerlerimi matris_one ekliyorum.
    */

    clean(matris_one, 6);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matris_one[j - i] *= matris[i][j];
        }
    }
    /*
    Sarrus yöntemine göre 3x3 lük bir matriste row sayısı kadar toplanacak eleman geldiğinden bunları toplam değerime atıyorum.
    */
    for (int i = 0; i < row; i++)
    {
        toplam += matris_one[i];
    }
    /*
    Burada tekrar matris_one elemanlarını 1'e eşitleme nedenim yukarı elde ettiğim bazı matris değerlerini tekrardan 1'e eşitleyerek
    çıkarma işlemi için yapılacak örüntüyü oluşturuyorum ve bunu ilgili indexime atıyorum.
    */
    clean(matris_one, 6);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matris_one[i + j + 1] *= matris[i][j];
        }
    }
    /*
Çıkarma işlemi için elde ettiğim değerleri örüntüme uygun olacak şekilde ilgili indexleri toplam değerinden çıkarıyorum ve en son
bu değeri döndürüyorum.

    */
    for (int i = col; i >= row; i--)
    {
        toplam -= matris_one[i];
    }

    return toplam;
}
/*
İlgili vektörün elemanlarını sırayla ekrana yazdırıyorum.
*/
void printVector(float *vec, int N)
{
    int i;
    for (i = 0; i < N; i++)
    {
        printf("%.2f\n", vec[i]);
    }
}
/*
İlgili matrisin elemanlarını sırayla ekrana yazdırıyorum.
*/
void printMatrix(float **mat, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%.2f\t", mat[i][j]);
        }
        printf("\n");
    }
}

/*
İlk olarak matrisimin sütun ortalamasını alıyorum ve yeni bir matris oluşturuyorum.
Mat matrisimin ilgili indexindeki değeri sütunundaki ortalama değerinden çıkartıyorum ve yeni matrisime ekliyorum.
Burada en önemli şey bence matrislerin çarpım sırasıydı.Buna göre cevabım hatalı çıkıyordu bu yüzden ilk olarak transpozunu aldığım
matrisi ve ikinci olarak mat'dan ortalamasını çıkardığım matrisi parametre olarak yolluyorum ve geri dönen matrisi mat3 adını
verdiğim matrisime atıyorum. En son oluşturduğum mat3 matrisinin her bir ilgili satırındaki ve sütunundaki elemanı mat matrisimin
row sayısına bölüyorum ve bu matrisi geri döndürüyorum.

*/
float **covarianceMatrix(float **mat, int row, int col)
{
    float *ort = columnMeans(mat, row, col);
    float **matris = returnMatrix(row, col);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matris[i][j] = ((mat[i][j]) - ort[j]);
        }
    }
    float **dizi2 = matrixTranspose(matris, row, col); // col row
    float **mat3 = matrixMultiplication(dizi2, matris, col, row, row, col);
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < col; j++)
        {
            mat3[i][j] = mat3[i][j] / row;
        }
    }

    return mat3;
}
/* Bu fonksiyon bizden istenen fonksiyonlar arasında yok ama ben determinant fonksiyonumda 2 defa kullandığımdan dolayı
bu fonksiyonu oluşturdum.Bu fonksiyonda ilgili arr vektörümün her bir elemanını 1'e eşitliyorum.

*/
void clean(float *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = 1;
    }
}
