/* ������ �����
 * 272(1)��
 */

#include <iostream>
using namespace std;

//��������� ������ ���������� �������:
void randomArray(int *a, int len, int min, int max);

//����� ������� �� �����
void printArray(int *a, int len);

//���������� ���������
int sortBubble(int *a, int len);

//���������� ��������� � �������� ���������
int sortBubbleIverson(int *a, int len);

//���������� ��������� � �������� ��������� �2
int sortBubbleIverson_2(int *a, int len);

//���������� �������� ���������
int sortInsertion(int *a, int len);

//���������� ��������� ���������
int sortBinaryInsertion(int *a, int len);

//���������� ���������
int sortCounting(int *a, int len, int max);

//�������� ����� �������
int getDigit(int number, int digit, double base);

//�������� ���������� �������� �����:
int getNumLength(double num, double base);

//�������� ����������
int sortRadix(int *a, int len, int d);

//���������� ��������
int sortMerge(int* arr, int l, int r);

//������� ����������
int sortQuick(int *arr, int LowInd, int HighInd);

//������������� ����������
int sortPyramid(int *arr, int len);

// c��������� �����
int sortShell(int* arr, int len);