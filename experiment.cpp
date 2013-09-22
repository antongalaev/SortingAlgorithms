/* √алаев јнтон
 * 272(1)ѕ»
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
	ћетод дл€ проведени€ эксперимента
	1 параметр : им€ сортировки
	2 параметр : сама функци€(типа sort_func2 или sort_func3)
	=========================================================
*/
void sortingExp(char* name, sort_func2 sf) {
	cout << name << " running"  << endl;

	//массивы значений среднего количества операций
	//дл€ 2 типов массивов (худшего и среднего)
	//дл€ 20 размеров массивов
	unsigned long *meansRev = new unsigned long [20];
	unsigned long *meansRand = new unsigned long [20];

	// цикл по длине массива от 10 до 100
	for (int len = 10; len <= 10000; ) {

		cout << "lenght = " << len << " running"  << endl;

		//отсортированный в обратном пор€дке массив:
		int *reverse = new int[len];
		//заполнение отсортированного в обратном пор€дке массива
		for (int i = 0; i < len; i++) {
			reverse[i] = len - i;
		}

		// максимальные значени€ дл€ сортировки подсчетом:
		int cMaxRev = len;
		int cMaxRand = 5;

		// количества разр€дов дл€ цифровой сортировки
		int dRev = log10((double)len);
		int dRand = 10;

		// среднее количество операций дл€ массива reverse
		double meanRev = 0;
		// среднее количество операций дл€ массива со случайными значени€ми
		double meanRand = 0;
		// индекс по длине массива (дл€ массива с конечными счетчиками)
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
			// ћассив обратно отсортированный (или пр€мо дл€ некоторых сортировок)
			
			// cкопировать значени€ в сортируемый массив
			copy(reverse, reverse + len, arr);

			// вызов сортировки в зависимости от параметра:
			count = sf(arr, len);				
			//count = sf(arr, 0, len - 1);
			//count = sf(arr, len, cMaxRev);
			//count = sf(arr, len, dRev);

			// установка среднего значени€ не допуска€ переполнени€
			meanRev = (meanRev * i + (double)count / 1000000) / (i + 1);			

			// ==========================================================
			// ћассив со случайными значени€ми от 0 до 5 (или INT_MAX)

			// заполнить сортируемый массив случайными значени€ми
			randomArray(arr, len, 0, 5);			

			// вызов сортировки в зависимости от параметров:
			count = sf(arr, len);				
			//count = sf(arr, 0, len - 1);
			//count = sf(arr, len, cMaxRand);
			//count = sf(arr, len, dRand);

			// установка среднего значени€ не допуска€ переполнени€
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
	//	«апись значений в файл
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
	// очистка пам€ти
	delete[] meansRev;
	delete[] meansRand;
}

void main() {
	srand(time(0));
	
	//‘ункции вызова эксперимента дл€ различных сортировок:
	
	// 2 параметра дл€ сортировки
	sortingExp("Bubble", sortBubble);
	sortingExp("BubbleIverson", sortBubbleIverson);
	sortingExp("BubbleIverson_2", sortBubbleIverson_2);
	sortingExp("Insertion", sortInsertion);
	sortingExp("Binary_Insertion", sortBinaryInsertion);
	sortingExp("Pyramid", sortPyramid);
	sortingExp("Shell", sortShell);

	// 3 параметра дл€ сортировки
	//sortingExp("Merge", sortMerge);
	//sortingExp("Quick", sortQuick);
	//sortingExp("Counting", sortCounting);
	//sortingExp("Radix", sortRadix);

	cout << "Done." << endl;	
	system("pause");
}