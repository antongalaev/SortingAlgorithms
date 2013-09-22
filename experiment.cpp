/* ������ �����
 * 272(1)��
 */

#include <iostream>
#include <ctime>
#include <algorithm>
#include <math.h>
#include <fstream>
#include "library.h"
using namespace std;

//���� ������� ���������� � 2 � 3 �����������
typedef int sort_func2(int*, int);
typedef int sort_func3(int*, int, int);


/*	=========================================================
	����� ��� ���������� ������������
	1 �������� : ��� ����������
	2 �������� : ���� �������(���� sort_func2 ��� sort_func3)
	=========================================================
*/
void sortingExp(char* name, sort_func2 sf) {
	cout << name << " running"  << endl;

	//������� �������� �������� ���������� ��������
	//��� 2 ����� �������� (������� � ��������)
	//��� 20 �������� ��������
	unsigned long *meansRev = new unsigned long [20];
	unsigned long *meansRand = new unsigned long [20];

	// ���� �� ����� ������� �� 10 �� 100
	for (int len = 10; len <= 10000; ) {

		cout << "lenght = " << len << " running"  << endl;

		//��������������� � �������� ������� ������:
		int *reverse = new int[len];
		//���������� ���������������� � �������� ������� �������
		for (int i = 0; i < len; i++) {
			reverse[i] = len - i;
		}

		// ������������ �������� ��� ���������� ���������:
		int cMaxRev = len;
		int cMaxRand = 5;

		// ���������� �������� ��� �������� ����������
		int dRev = log10((double)len);
		int dRand = 10;

		// ������� ���������� �������� ��� ������� reverse
		double meanRev = 0;
		// ������� ���������� �������� ��� ������� �� ���������� ����������
		double meanRand = 0;
		// ������ �� ����� ������� (��� ������� � ��������� ����������)
		int index;
		if (len <= 100) { // ����� �� 100
			index = len / 10 - 1; 
		} else { // ����� �� 10000
			index = len / 1000 + 9;
		}
		
		// 100 ��� ���������
		for (int i = 0; i < 100; i++) {
			// ������� ��������
			int count;			
			// c���������� ������
			int *arr = new int[len];

			// ==========================================================
			// ������ ������� ��������������� (��� ����� ��� ��������� ����������)
			
			// c���������� �������� � ����������� ������
			copy(reverse, reverse + len, arr);

			// ����� ���������� � ����������� �� ���������:
			count = sf(arr, len);				
			//count = sf(arr, 0, len - 1);
			//count = sf(arr, len, cMaxRev);
			//count = sf(arr, len, dRev);

			// ��������� �������� �������� �� �������� ������������
			meanRev = (meanRev * i + (double)count / 1000000) / (i + 1);			

			// ==========================================================
			// ������ �� ���������� ���������� �� 0 �� 5 (��� INT_MAX)

			// ��������� ����������� ������ ���������� ����������
			randomArray(arr, len, 0, 5);			

			// ����� ���������� � ����������� �� ����������:
			count = sf(arr, len);				
			//count = sf(arr, 0, len - 1);
			//count = sf(arr, len, cMaxRand);
			//count = sf(arr, len, dRand);

			// ��������� �������� �������� �� �������� ������������
			meanRand = (meanRand * i + (double)count / 1000000) / (i + 1);						
		}
		// ����������� ������� �������� � �������
		meansRev[index] = meanRev * 1000000;
		meansRand[index] = meanRand * 1000000;

		// ����������� �����:
		if (len < 100) { // ����� �� 100
			len += 10;
		} else if (len > 100) { // ����� �� 1000
			len += 1000;
		} else if (len == 100) { // ����� 100
			len = 1000;
		}
	}	

	//===========================
	//	������ �������� � ����
	//===========================

	string str = string("count_");
	str.append(name);
	str.append(".txt"); 
	const char *filename = str.c_str();
	ofstream fout(filename);

	fout << name << " ������� ��������������� (������ ������)" << endl;
	for (int i = 0; i < 20; i++) {		
		fout << meansRev[i]<< " ";
	}

	fout << endl << name << " �� 0 �� 5 (������� ������):" << endl;
	for (int i = 0; i < 20; i++) {		
		fout << meansRand[i] << " ";
	}

	fout.close();
	// ������� ������
	delete[] meansRev;
	delete[] meansRand;
}

void main() {
	srand(time(0));
	
	//������� ������ ������������ ��� ��������� ����������:
	
	// 2 ��������� ��� ����������
	sortingExp("Bubble", sortBubble);
	sortingExp("BubbleIverson", sortBubbleIverson);
	sortingExp("BubbleIverson_2", sortBubbleIverson_2);
	sortingExp("Insertion", sortInsertion);
	sortingExp("Binary_Insertion", sortBinaryInsertion);
	sortingExp("Pyramid", sortPyramid);
	sortingExp("Shell", sortShell);

	// 3 ��������� ��� ����������
	//sortingExp("Merge", sortMerge);
	//sortingExp("Quick", sortQuick);
	//sortingExp("Counting", sortCounting);
	//sortingExp("Radix", sortRadix);

	cout << "Done." << endl;	
	system("pause");
}