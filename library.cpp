/* Галаев Антон
 * 272(1)ПИ
 */

#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

//----------------------------------------------
//заполнить массив случайными числами:
void randomArray(int *a, int len, int min, int max) {	
	for (int i = 0; i < len; i++)		
		a[i] = min + rand()%(max - min + 1);
}

//----------------------------------------------
//вывод массива на экран
void printArray(int *a, int len) {
	for (int i = 0; i < len; i++) 
		cout << a[i] << "  ";
		cout << endl << endl;
}

//----------------------------------------------
//функция проверки упорядоченности массива
//параметр ascending = true : сортировка по возрастанию
bool isSorted(int *arr, int len, bool ascending) {
	if (ascending) {
		for (int i = 1; i < len; i++) {
			if (arr[i] < arr[i-1]) return false;
		}
		return true;
	}
	else {
		for (int i = 1; i < len; i++) {
			if (arr[i] > arr[i-1]) return false;
		}
		return true;
	}
}

//----------------------------------------------
//записать массив в файл
void writeArray(int *arr, int len) {
	char *outname = "test.txt";
	ofstream outf(outname);

	outf << len << endl;
	for (int i = 0; i < len; i++) {
		outf << arr[i] << " ";
	}
	outf.close();
}

//----------------------------------------------
//считать массив из файла
int readArray(int *arr) {
    char *inname = "test.txt";
	int len;

	ifstream inf(inname);
	if (!inf) {
		cout << "Error: cannot read the file";
        return -1;
	}
	inf >> len;
	arr = new int[len];	
	for (int i = 0; i < len; i++) {
        if (!(inf >> arr[i]))
			return -1;
	}
	return len;
}

//==============================================
//Сортировки
//==============================================


//----------------------------------------------
//сортировка пузырьком

int sortBubble(int *a, int len) {
	int c = 3;
	for (int i = 0; i < len - 1; i++) {
		c += 4;
		for (int j = 0; j < len - i - 1; j++) {
			c += 4;
			if (a[j] > a[j + 1]) {
				c += 9;
				int temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
			c += 3;
		}
		c += 3;
	}
	return c;
}

//----------------------------------------------
//сортировка пузырьком с условием Айверсона №1
//с верхней границей

int sortBubbleIverson(int *a, int len) {
	int c = 5;
	int bound = len - 1;
	for (int i = 0; i < len - 1; i++) {
		c += 3;
		int t = 0;		
		for (int j = 0; j < bound; j++) {
			c += 4;
			if (a[j] > a[j + 1]) {
				c += 10;
				int temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
				t = j;
			}
			c += 3;
		}
		if (t == 0) {
			c += 1;
			break;
		}
		bound = t;
		c += 5;
	}
	return c;
}

//----------------------------------------------
//сортировка пузырьком с условием Айверсона №2
//с булевой переменной

int sortBubbleIverson_2(int *a, int len) {
	int c = 2;
	for (int i = 0; i < len; i++) {
		c += 5;
		bool mark = true;  //Условие Айверсона
		for (int j = 0; j < len - i - 1; j++) {
			c += 4;
			if (a[j] > a[j+1])
			{
				c += 10;
				mark = false;   //Если найдены элементы, удовлетворяющие условию, изменяем метку
				int temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
			c += 3;
		}
		//Если перестановок не было выходим из цикла
		if (mark) {
			c += 1;
			break; 
		}
		c += 4;
	}
	return c;
}

//----------------------------------------------
//сортировка простыми вставками

int sortInsertion(int *a, int len) {
	int i, j, temp;
	int c = 2;
	for (i = 1; i < len; i++) {
		c += 5;
		temp = a[i]; //перемещаемый элемент
		for (j = i - 1; j >= 0; j--)
		{
			if (a[j] < temp) {
				c += 2;
				break;				
			} else {
				a[j+1] = a[j];	
				c += 6;
			}
			c += 3;
		}
		a[j + 1] = temp;
		c += 6;
	}
	return c;
}

//----------------------------------------------
//сортировка бинарными вставками

int sortBinaryInsertion(int *a, int len) {
	int c, l, r;
	int count = 2;
	for (int i = 1; i < len; i++) {
		l = 0;
		r = i - 1;
		c = (l + r) / 2;
		count += 7;
		while (l != c) {
			if (a[i] > a[c]) l = c;
			else r = c;
			c = (l + r) / 2;
			count += 7;
 		}
		count += 3;
		if (a[i] > a[l]) {			
			if (a[i] > a[r]) {
				count += 5;
				l = r + 1;
			}
			else {
				count += 4;
				l = r;
			}
		}
		count += 4;
		int p = a[i];
		for (int k = i; k > l; k--) {
			count += 7;
			a[k] = a[k-1];
		}
		a[l] = p;	
		count += 5;
	}
	return count;
}

//----------------------------------------------
//сортировка подсчетом

int sortCounting(int *a, int len, int max) {	 
	int *count = new int[max + 1];
	int *result = new int[len];
	//обнуление массива
	for (int i = 0; i <= max; i++) 
		count[i] = 0;
	int c = 7 + (max + 1) * (3 + 2);
	//подсчет количества одинаковых элементов в массиве a
	for (int i = 0; i < len; i++) 
		count[a[i]]++;
	c += 2 + len * (3 + 6);
	//подсчет количества элементов не больше i
	for (int i = 1; i <= max; i++) 
		count[i] += count[i-1];
	c += 2 + max * (3 + 6);
	//расстановка элементов в результирующий массив
	for (int i = len-1; i >= 0; i--) {
		result[count[a[i]]-1] = a[i];
		count[a[i]]--;
	}
	c += 2 + len * (3 + 6 + 6); 
	//обновление исходного массива
	for (int i = 0; i < len; i++) 
		a[i] = result[i];
	c += 2 + len * (3 + 3);
	return c;
}

//----------------------------------------------
//цифровая сортировка

//Цифровая сортировка
int countingSortRadix(int *arr, int size, int k) {
	int base = 16;
    int *B, *C;
    C = new int[base];
    B = new int[size + 1];
	int c = 6;
	//обнуление
    for (int i = 0; i < base; i++) C[i] = 0;
	c += 2 + base * (3 + 2);
    for (int i = 0; i < size; i++){
        int val = arr[i] / k;
        int idx = val % base;
        C[idx]++;
    }
	c += 2 + size * ( 3 + 3 + 2 + 4);
 
    for (int i = 1; i < base; i++) C[i] += C[i - 1];
	c += 2 + (base - 1) * (3 + 6);

    for (int j = size - 1; j >= 0; j--) {
        int val = arr[j] / k;
        int idx = val % base;
        B[C[idx]] = arr[j];
        C[idx]--;
    } 
	c += 2 + size * (3 + 13);
    for (int i = 0; i < size; i++) arr[i] = B[i+1];
	c += 2 + size * (3 + 4);
	return c;
}
 
int sortRadix(int* arr, int len, int d) {
	int c = 2;
    for(int i = 0; i < d; i++) {
        c += 3 + countingSortRadix(arr, len, pow((float) 16, (float) i));
    }
	return c;
}

//----------------------------------------------
//сортировка слиянием

//слияние 2-х частей: от l до с + от c до r
int merge(int* arr, int l, int c, int r) {
	int p1 = l;
    int p2 = c + 1;
    int count = r - l + 1;
	
	int ops = 7;
	if (count <= 1)		
		return ops;
	 
    int *t = new int[count];
	
	ops += 4;
    for (int i = 0; i < count; i++)
    {
		ops += 3;
        if (p1 <= c && p2 <= r)
        {
			ops += 3 + 5;
            if (arr[p1] < arr[p2])
                t[i] = arr[p1++];
            else
                t[i] = arr[p2++];
        }
        else
        {
			ops += 1 + 5;
            if (p1 <= c)
                t[i] = arr[p1++];
            else
                t[i] = arr[p2++];
        }
		ops += 3;
    }
 
    p1 = 0;
	ops += 3;
    for (int i = l; i <= r; i++)
    {
        arr[i] = t[p1++];
		ops += 3 + 5;
    }
    delete[] t;
	ops += 1;
	return ops;
}
//сортировка слиянием
int sortMerge(int* arr, int l, int r) {
	int count = 1;
	if (l < r) {
		count += 3;
		int c = (l + r) / 2;
		count += sortMerge(arr, c + 1, r);
		count += sortMerge(arr, l, c);
		count += merge(arr, l, c, r);
	}
	return count;
}

//----------------------------------------------
//быстрая сортировка
int sortQuick(int *arr, int LowInd, int HighInd)	{
	int i, j;
	int x, temp;
	x = arr[(LowInd + HighInd) / 2];
	i = LowInd;
	j = HighInd;
	int c = 6;
	do	{ 
		c += 2;
		while(arr[i] < x) {
			c += 4;
			i++;
		}
		c += 2;
		while(arr[j] > x) {
			c += 4;
			j--;
		}
		c ++;
		if (i <= j)	{
			c += 11;
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++; j--;
		}
		c ++;
	} while (i <= j);
	
	c += 2;
	if (LowInd < j) c += sortQuick(arr, LowInd, j);
	if (i < HighInd) c += sortQuick(arr, i, HighInd);
	return c;
}


//----------------------------------------------
//пирамидальная сортировка

//индекс левого потомка в бинарном дереве
int Left(int i) {
	return i * 2;
}
//индекс правого потомка в бинарном дереве
int Right(int i) {
	return i * 2 + 1;
}
//восстановить кучу
int Heapify(int *A, int i, int hSize) {
	int largest;
	int L = Left(i + 1) - 1 ;
	int R = Right(i + 1) - 1;
	int c = 10;
	
	if ((L <= hSize) && (A[L] > A[i])) largest = L;
	else largest = i;
	c += 6;

	if ((R <= hSize) && (A[R] > A[largest])) largest = R;
	c += 7;
	if (largest != i) {
		c += 7;
		int temp = A[i];
		A[i] = A[largest];
		A[largest] = temp;
		c += Heapify(A, largest, hSize);
	}	
	return c;
}
//построить кучу
int buildHeap(int *A, int hSize) {
	int c = 2;
	for (int i = hSize / 2; i > -1; i--) {
		c += 3 + Heapify(A, i, hSize);
	}
	return c;
}
//пирамидальная сортировка
int sortPyramid(int *arr, int len) {
	int hSize = len - 1;
	int c = 3 + buildHeap(arr, hSize);
	for (int i = len - 1; i > 0; i--) {
		c += 9;
		int temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;
		hSize--;
		c += 3 + Heapify(arr, 0, hSize);
	}
	return c;
}
// cортировка Шелла
int sortShell(int* arr, int len) {
	int m = 0;
	int count = 1; // счетчик
	// последовательность по формуле Дональда Кнута
	int d[] = { 1, 4, 13, 40, 121, 364, 1096, 3280, 9841, 29524, 88573, 265720, 797161, 2391480};
	count += 15;
	count += 2;
	while (d[m] < len) {
		++ m;
		count += 4;
	}
	count += 3;
	while ( -- m >= 0) {
		int k = d[m];
		count += 2;
		count += 2;
		for (int i = k; i < len; i++) {   
			int j = i;
			int h = arr[i];
			count += 3;
			count += 5;
			while ((j >= k) && (arr[j - k] > h)) {  
				arr[j] = arr[j - k];
				j = j - k;
				count += 11;
			}
			arr[j] = h;
			count += 5;
		}
	}
	return count;
}