/* Галаев Антон
 * 272(1)ПИ
 */

#include <iostream>
#include <ctime>
#include <algorithm>
#include <math.h>
#include <fstream>
#include "library.h"
using namespace std;

//типы функций сортировок с 2 и 3 параметрами
typedef int sort_func2(int*, int);
typedef int sort_func3(int*, int, int);


/*	=========================================================
	Метод для проведения эксперимента
	1 параметр : имя сортировки
	2 параметр : сама функция(типа sort_func2 или sort_func3)
	=========================================================
*/
void sortingExp(char* name, sort_func2 sf) {
	cout << name << " running"  << endl;

	//массивы значений среднего количества операций
	//для 2 типов массивов (худшего и среднего)
	//для 20 размеров массивов
	unsigned long *meansRev = new unsigned long [20];
	unsigned long *meansRand = new unsigned long [20];

	// цикл по длине массива от 10 до 100
	for (int len = 10; len <= 10000; ) {

		cout << "lenght = " << len << " running"  << endl;

		//отсортированный в обратном порядке массив:
		int *reverse = new int[len];
		//заполнение отсортированного в обратном порядке массива
		for (int i = 0; i < len; i++) {
			reverse[i] = len - i;
		}

		// максимальные значения для сортировки подсчетом:
		int cMaxRev = len;
		int cMaxRand = 5;

		// количества разрядов для цифровой сортировки
		int dRev = log10((double)len);
		int dRand = 10;

		// среднее количество операций для массива reverse
		double meanRev = 0;
		// среднее количество операций для массива со случайными значениями
		double meanRand = 0;
		// индекс по длине массива (для массива с конечными счетчиками)
		int index;
		if (len <= 100) { // длины до 100
			index = len / 10 - 1; 
		} else { // длины до 10000
			index = len / 1000 + 9;
		}
		
		// 100 раз выполнить
		for (int i = 0; i < 100; i++) {
			// счетчик операций
			int count;			
			// cортируемый массив
			int *arr = new int[len];

			// ==========================================================
			// Массив обратно отсортированный (или прямо для некоторых сортировок)
			
			// cкопировать значения в сортируемый массив
			copy(reverse, reverse + len, arr);

			// вызов сортировки в зависимости от параметра:
			count = sf(arr, len);				
			//count = sf(arr, 0, len - 1);
			//count = sf(arr, len, cMaxRev);
			//count = sf(arr, len, dRev);

			// установка среднего значения не допуская переполнения
			meanRev = (meanRev * i + (double)count / 1000000) / (i + 1);			

			// ==========================================================
			// Массив со случайными значениями от 0 до 5 (или INT_MAX)

			// заполнить сортируемый массив случайными значениями
			randomArray(arr, len, 0, 5);			

			// вызов сортировки в зависимости от параметров:
			count = sf(arr, len);				
			//count = sf(arr, 0, len - 1);
			//count = sf(arr, len, cMaxRand);
			//count = sf(arr, len, dRand);

			// установка среднего значения не допуская переполнения
			meanRand = (meanRand * i + (double)count / 1000000) / (i + 1);						
		}
		// запоминание средних значений в массивы
		meansRev[index] = meanRev * 1000000;
		meansRand[index] = meanRand * 1000000;

		// итерировать длину:
		if (len < 100) { // длины до 100
			len += 10;
		} else if (len > 100) { // длины от 1000
			len += 1000;
		} else if (len == 100) { // длина 100
			len = 1000;
		}
	}	

	//===========================
	//	Запись значений в файл
	//===========================

	string str = string("count_");
	str.append(name);
	str.append(".txt"); 
	const char *filename = str.c_str();
	ofstream fout(filename);

	fout << name << " обратно отсортированный (худший случай)" << endl;
	for (int i = 0; i < 20; i++) {		
		fout << meansRev[i]<< " ";
	}

	fout << endl << name << " от 0 до 5 (средний случай):" << endl;
	for (int i = 0; i < 20; i++) {		
		fout << meansRand[i] << " ";
	}

	fout.close();
	// очистка памяти
	delete[] meansRev;
	delete[] meansRand;
}

void main() {
	srand(time(0));
	
	//Функции вызова эксперимента для различных сортировок:
	
	// 2 параметра для сортировки
	sortingExp("Bubble", sortBubble);
	sortingExp("BubbleIverson", sortBubbleIverson);
	sortingExp("BubbleIverson_2", sortBubbleIverson_2);
	sortingExp("Insertion", sortInsertion);
	sortingExp("Binary_Insertion", sortBinaryInsertion);
	sortingExp("Pyramid", sortPyramid);
	sortingExp("Shell", sortShell);

	// 3 параметра для сортировки
	//sortingExp("Merge", sortMerge);
	//sortingExp("Quick", sortQuick);
	//sortingExp("Counting", sortCounting);
	//sortingExp("Radix", sortRadix);

	cout << "Done." << endl;	
	system("pause");
}