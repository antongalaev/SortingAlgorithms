/* Галаев Антон
 * 272(1)ПИ
 */

#include <iostream>
using namespace std;

//заполнить массив случайными числами:
void randomArray(int *a, int len, int min, int max);

//вывод массива на экран
void printArray(int *a, int len);

//сортировка пузырьком
int sortBubble(int *a, int len);

//сортировка пузырьком с условием Айверсона
int sortBubbleIverson(int *a, int len);

//сортировка пузырьком с условием Айверсона №2
int sortBubbleIverson_2(int *a, int len);

//сортировка простыми вставками
int sortInsertion(int *a, int len);

//сортировка бинарными вставками
int sortBinaryInsertion(int *a, int len);

//сортировка подсчетом
int sortCounting(int *a, int len, int max);

//получить цифру разряда
int getDigit(int number, int digit, double base);

//получить количество разрядов числа:
int getNumLength(double num, double base);

//цифровая сортировка
int sortRadix(int *a, int len, int d);

//сортировка слиянием
int sortMerge(int* arr, int l, int r);

//быстрая сортировка
int sortQuick(int *arr, int LowInd, int HighInd);

//пирамидальная сортировка
int sortPyramid(int *arr, int len);

// cортировка Шелла
int sortShell(int* arr, int len);