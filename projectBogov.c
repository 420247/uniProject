#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <math.h>
int getchar(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
 }


/* в данной программе x - строки, y - столбцы*/
void menu(void); // меню
 
int get_int(); // получить INT
 
float get_float(); // получить FLOAT
 
float* get_matrix(int x, int y); // получить матрицу
 
void show_matrix(float * pt, int x, int y); // показ матрицы
 
float* add_matrix(float * m1, float * m2, int x, int y); /* функция
сложения, создает новую матрицу и возвращает указатель на нее*/
 
float* div_matrix(float * m1, float * m2, int x, int y); // вычитание
 
void transpose(float * m, int x, int y); // транспонирование
 
void pow_matrix(float *, int, int, float); // ввозведение в степень
 
int main()
{
    
  
    
    int choice;
    menu();
    while (choice = get_int())
    {
        switch (choice)
        {
            case 1 :
                {
                    printf("СЛОЖЕНИЕ\n");
                    printf("Укажите размер матриц:\nстроки  >> ");
                    int x, y;
                    x = get_int();
                    printf("столбцы >> ");
                    y = get_int();
                    
                    /* заполняем 2 матрицы */
                    printf("\nМАТРИЦА 1\n");
                    float * pm1 = get_matrix(x, y);
                    printf("\nМАТРИЦА 2\n");
                    float * pm2 = get_matrix(x, y);
                    
                    /* вывели получившиеся матрицы */
                    printf("\nМАТРИЦА 1\n");
                    show_matrix(pm1, x, y);
                    printf("\nМАТРИЦА 2\n");
                    show_matrix(pm2, x, y);
                    
                    /* вызываем функцию сложения и выводим результат*/
                    float * sum_m = add_matrix(pm1, pm2, x, y);
                    printf("\nРЕЗУЛЬТАТ СЛОЖЕНИЯ\n");
                    show_matrix(sum_m, x, y);
                    
                    /* освобождаем память (или так нельзя делать?)*/
                    free(pm1);
                    free(pm2);
                    free(sum_m);
                    
                    break;
                }
            case 2 :
                {
                    printf("\nВЫЧИТАНИЕ\n");
                    printf("Укажите размер матриц:\nстроки  >> ");
                    int x, y;
                    x = get_int();
                    printf("столбцы >> ");
                    y = get_int();
                    
                    /* заполняем 2 матрицы */
                    printf("\nМАТРИЦА 1 - уменьшаемое\n");
                    float * pm1 = get_matrix(x, y);
                    printf("\nМАТРИЦА 2 - вычитаемое\n");
                    float * pm2 = get_matrix(x, y);
                    
                    /* вывели получившиеся матрицы */
                    printf("\nМАТРИЦА 1\n");
                    show_matrix(pm1, x, y);
                    printf("\nМАТРИЦА 2\n");
                    show_matrix(pm2, x, y);
                    
                    /* вызываем функцию вычитания и выводим результат*/
                    float * div_m = div_matrix(pm1, pm2, x, y);
                    printf("\nРЕЗУЛЬТАТ ВЫЧИТАНИЯ\n");
                    show_matrix(div_m, x, y);
                    
                    /* освобождаем память (или так нельзя делать?)*/
                    free(pm1);
                    free(pm2);
                    free(div_m);
                    
                    break;
                }
            case 3 :
                {
                    printf("\nТРАНСПОНИРОВАНИЕ МАТРИЦЫ\n");
                    printf("Укажите размер матрицы:\nстроки  >> ");
                    int x, y;
                    x = get_int();
                    printf("столбцы >> ");
                    y = get_int();
                    
                    /* заполняем матрицу */
                    printf("\nМАТРИЦА 1 - уменьшаемое\n");
                    float * pm = get_matrix(x, y);
                    show_matrix(pm, x, y);
                    
                    /* транспонируем отображаем */
                    transpose(pm, x, y);
                    printf("\nРЕЗУЛЬТАТ ТРАНСПОНИРОАНИЯ\n");
                    show_matrix(pm, x, y);
                    
                    free(pm);
                    
                    break;
                }
            case 4 :
                {
                    printf("\nВОЗВЕДЕНИЕ МАТРИЦЫ В СТЕПЕНЬ\n");
                    printf("Укажите размер матрицы:\nстроки  >> ");
                    int x, y;
                    x = get_int();
                    printf("столбцы >> ");
                    y = get_int();
                    
                    /* заполняем матрицу */
                    printf("\nМАТРИЦА 1 - уменьшаемое\n");
                    float * pm = get_matrix(x, y);
                    show_matrix(pm, x, y);
                    
                    printf("\nВ какую степень будем возводить?\n >>");
                    float pw;
                    pw = get_float();
                    pow_matrix(pm, x, y, pw);
                    printf("\nРЕЗУЛЬТАТ ВОЗВЕДЕНИЯ МАТРИЦЫ В СТЕПЕНЬ %.2f\n", pw);
                    show_matrix(pm, x, y);
                    
                    free(pm);
                    
                    break;
                }
            default : printf("Ошибочка, такого варианта нет.\n");
        }
    menu(); 
    }
    printf("Досвидули!\n");
        
    return 0;
}
// меню
void menu(void)
{
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("Выберите действие, либо 0 для выхода:\n");
    printf("1) сложение матриц\t\t2) вычитание матриц\n");
    printf("3) транспонирование матрицы\t"
        "4) возведение матрицы в степень\n");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}
// получить INT
int get_int()
{
    int n;
    while (scanf("%d", &n) != 1)
    {
        printf("Некорректные данные. Повторите ввод:\n");
        while (getchar() != '\n')
            continue;
    }
    return n;
}
 
float get_float() // получить FLOAT
{
    float n;
    while (scanf("%f", &n) != 1)
    {
        printf("Некорректные данные. Повторите ввод:\n");
        while (getchar() != '\n')
            continue;
    }
    return n;
}
 
float* get_matrix(int x, int y) // получить матрицу
{
    float *pd;
    pd = (float *) malloc(x * y * sizeof (float));
    printf("Заполним матрицу\n");
    
    for (int i = 0; i < x; i++)
    {
        printf("Строка %d:\n", i+1);
        for (int k = 0; k < y; k++)
        {
            printf("#%d: ", k+1);
            *(pd + i*y + k) = get_float();
        }
    }
    return pd;
}
// вывод матрицы на экран
void show_matrix(float * pt, int x, int y)
{
    for (int i = 0; i < x; i++)
    {
        for (int k = 0; k < y; k++)
            printf("%.2f\t", *(pt + i*y + k));
        printf("\n");
    }
}
// сложение матриц
float* add_matrix(float * m1, float * m2, int x, int y)
{
    float * sum = (float*) malloc(x * y * sizeof (float));
    
    for (int i = 0; i < x; i++)
        for (int k = 0; k < y; k++)
            *(sum + i*y + k) = *(m1 + i*y + k) + *(m2 + i*y + k);   
    return sum;
}
// вычитание матриц
float* div_matrix(float * m1, float * m2, int x, int y)
{
    float * sum = (float*) malloc(x * y * sizeof (float));
    
    for (int i = 0; i < x; i++)
        for (int k = 0; k < y; k++)
            *(sum + i*y + k) = *(m1 + i*y + k) - *(m2 + i*y + k);   
    return sum;
}
// транспонирование
void transpose(float * m, int x, int y)
{
    for (int i = 0; i < x; i++)
        for (int k = i; k < (y > x ? x : y); k++)
        {
            float temp;
            temp = *(m + i*y + k);
            *(m + i*y + k) = *(m + k*y + i);
            *(m + k*y + i) = temp;
        }
}
// возведение матрицы в степень
void pow_matrix(float * m, int x, int y, float pw)
{
    for (int i = 0; i < x; i++)
        for (int k = 0; k < y; k++)
            *(m + i*y + k) = pow(*(m + i*y + k), pw);
}