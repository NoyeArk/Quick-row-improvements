//QuickSort.cpp
#include <iostream>
#include<queue>
#include<vector>
#include <cassert>
#include <iomanip>
#include <ctime>
using  namespace std;

#define MAX 100 //����������������ֵ
#define MIN 1 //���������������Сֵ
#define LOOP 20 //���ԵĴ���
#define LENGTH 30 //����������ĳ���
#define N 10 //��������Ԫ��С��Nʱ��ȡֱ�Ӳ�������
//������main.cpp�еı���
extern int cnt[];
extern clock_t wasteTime;
extern int a[][LENGTH];

//���ֲ�ͬѡȡ����Ԫ�ص��㷨��ö��ֵ
enum MyEnum
{
	FIRST, RANDOM, AVERAGE, MEDIAN, INSERT
};

/**
 * \name InsertSort ֱ�Ӳ�������
 * \type void
 * \param num ����������
 * \param length ���鳤��
 * \param index ��Ӧ���㷨
 */
void InsertSort(int num[], int length, int index)
{
	cnt[index]++; //�������+1
	int i, j, t;
	for (i = 1; i < length; i++) {
		if (num[i] < num[i - 1]) {
			t = num[i];
			num[i] = num[i - 1];
			for (j = i - 2; j >= 0 && num[j] > t; j--)
				num[j + 1] = num[j];
			num[j + 1] = t;
		}
	}
}

bool compare(int a, int b) { return a < b; }
/**
 * \name median ��λ����
 * \type int
 * \param a ����������
 * \param length ���鳤��
 * \return ��λ������λ�õ��±�
 */
int median(int a[], int length)
{
	int copy[LENGTH];
	std::copy(a, a + length, begin(copy)); //������a����һ��
	sort(copy, copy + length, compare); //������copy��С�����������
	for (int i = 0; i < length; i++)
		if (a[i] == copy[length / 2])
			return i;
}

/**
 * \name average ����ȡ�з�
 * \type int
 * \param num ����������
 * \param length ���鳤��
 * \return �������м�ֵ����λ�õ��±�
 */
int average(int num[], int length) {
	int mid[] = { num[0], num[length - 1], num[length / 2] };
	sort(mid, mid + 3, compare); //��������������ɵ������������
	if (num[0] == mid[1]) return 0;
	else if (num[length - 1] == mid[1]) return length - 1;
	else return length / 2;
}

/**
 * \name print �������Ԫ��ֵ
 * \type void
 * \param num ��ӡ������
 */
void print(int num[]) {
	for (int i = 0; i < LENGTH; i++)
		cout << num[i] << " ";
	cout << endl << endl;
}

/**
 * \name Pivotkey �������Ԫ���±�
 * \type int
 * \param num ����������
 * \param length ���鳤��
 * \param type ȷ��������㷨����
 * \return ��������Ԫ�ص��±�
 */
int Pivotkey(int num[], int length, int type) {
	switch (type)
	{
	case FIRST:return 0; //ԭʼ����-��һ����Ϊ����Ԫ��
	case AVERAGE:return average(num, length); //����ȡ�з�
	case RANDOM: //�������
		srand((unsigned)time(NULL));
		return rand() % length;
	case MEDIAN: return median(num, length); //��λ����
	case INSERT: return 0;
	}
}

/**
 * \name Partition �����������ӱ�ļ�¼��ʹ�����¼��λ��������������λ�á�
 * \type int
 * \param num ����������
 * \param length ���鳤��
 * \param type ȷ��������㷨����
 * \return ��������λ��
 */
int Partition(int num[], int length, int type) {
	clock_t start, end;

	start = clock();
	int index = Pivotkey(num, length, type);
	end = clock();
	wasteTime = end - start; //�����ȷ������Ԫ�����õ�ʱ��
	std::swap(num[index], num[0]); //������Ԫ�ؽ�������һ��

	int pivotkey = num[0];
	int low = 0, high = length - 1;
	while (low < high) { //����������˽�������м�ɨ��
		while (low < high && num[high] >= pivotkey)
			high--;
		if(low < high)
			num[low++] = num[high]; //���������¼С�Ľ������Ͷ�
		while (low < high && num[low] <= pivotkey)
			low++;
		if (low < high)
			num[high--] = num[low]; //���������¼��Ľ������߶�
	}
	if(low != 0)
		num[low] = pivotkey;
	return low; 
}

/**
 * \name QuickSort �ݹ���ʽ�Ŀ��������㷨
 * \type void
 * \param num ����������
 * \param length ���鳤��
 * \param type ȷ��������㷨����
 * \param i ��Ӧ���㷨����
 */
void QuickSort(int num[], int length, int type, int i)
{
	if (length <= 1) return;
	cnt[i]++; //�������+1
	if (type == INSERT) { //����ֱ�Ӳ���
		if (length < N) {
			InsertSort(num, length, i);
			print(a[i]);
			return;
		}
	}
	int k = Partition(num, length, type); //����������һ��Ϊ��
	print(a[i]); //��ӡ����ÿһ���ı仯
	QuickSort(num, k, type, i); //������֮ǰ��Ԫ������
	QuickSort(&num[k + 1], length - k - 1, type, i); //������֮���Ԫ������
}