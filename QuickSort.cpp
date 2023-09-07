//QuickSort.cpp
#include <iostream>
#include<queue>
#include<vector>
#include <cassert>
#include <iomanip>
#include <ctime>
using  namespace std;

#define MAX 100 //产生的随机数的最大值
#define MIN 1 //产生的随机数的最小值
#define LOOP 20 //测试的次数
#define LENGTH 30 //待排序数组的长度
#define N 10 //当区间内元素小于N时采取直接插入排序
//声明在main.cpp中的变量
extern int cnt[];
extern clock_t wasteTime;
extern int a[][LENGTH];

//五种不同选取枢轴元素的算法的枚举值
enum MyEnum
{
	FIRST, RANDOM, AVERAGE, MEDIAN, INSERT
};

/**
 * \name InsertSort 直接插入排序
 * \type void
 * \param num 待排序数组
 * \param length 数组长度
 * \param index 对应的算法
 */
void InsertSort(int num[], int length, int index)
{
	cnt[index]++; //排序次数+1
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
 * \name median 中位数法
 * \type int
 * \param a 待排序数组
 * \param length 数组长度
 * \return 中位数所在位置的下标
 */
int median(int a[], int length)
{
	int copy[LENGTH];
	std::copy(a, a + length, begin(copy)); //将数组a拷贝一份
	sort(copy, copy + length, compare); //对数组copy从小到大进行排序
	for (int i = 0; i < length; i++)
		if (a[i] == copy[length / 2])
			return i;
}

/**
 * \name average 三数取中法
 * \type int
 * \param num 待排序数组
 * \param length 数组长度
 * \return 三个数中间值所在位置的下标
 */
int average(int num[], int length) {
	int mid[] = { num[0], num[length - 1], num[length / 2] };
	sort(mid, mid + 3, compare); //对由这三个数组成的数组进行排序
	if (num[0] == mid[1]) return 0;
	else if (num[length - 1] == mid[1]) return length - 1;
	else return length / 2;
}

/**
 * \name print 输出数组元素值
 * \type void
 * \param num 打印的数组
 */
void print(int num[]) {
	for (int i = 0; i < LENGTH; i++)
		cout << num[i] << " ";
	cout << endl << endl;
}

/**
 * \name Pivotkey 求枢轴的元素下标
 * \type int
 * \param num 待排序数组
 * \param length 数组长度
 * \param type 确定枢轴的算法类型
 * \return 返回枢轴元素的下标
 */
int Pivotkey(int num[], int length, int type) {
	switch (type)
	{
	case FIRST:return 0; //原始方法-第一个作为枢轴元素
	case AVERAGE:return average(num, length); //三数取中法
	case RANDOM: //随机数法
		srand((unsigned)time(NULL));
		return rand() % length;
	case MEDIAN: return median(num, length); //中位数法
	case INSERT: return 0;
	}
}

/**
 * \name Partition 交换数组中子表的记录，使枢轴记录到位，并返回其所在位置。
 * \type int
 * \param num 待排序数组
 * \param length 数组长度
 * \param type 确定枢轴的算法类型
 * \return 枢轴所在位置
 */
int Partition(int num[], int length, int type) {
	clock_t start, end;

	start = clock();
	int index = Pivotkey(num, length, type);
	end = clock();
	wasteTime = end - start; //计算出确定枢轴元素所用的时间
	std::swap(num[index], num[0]); //将枢轴元素交换到第一个

	int pivotkey = num[0];
	int low = 0, high = length - 1;
	while (low < high) { //从数组的两端交替地向中间扫描
		while (low < high && num[high] >= pivotkey)
			high--;
		if(low < high)
			num[low++] = num[high]; //将比枢轴记录小的交换到低端
		while (low < high && num[low] <= pivotkey)
			low++;
		if (low < high)
			num[high--] = num[low]; //将比枢轴记录大的交换到高端
	}
	if(low != 0)
		num[low] = pivotkey;
	return low; 
}

/**
 * \name QuickSort 递归形式的快速排序算法
 * \type void
 * \param num 待排序数组
 * \param length 数组长度
 * \param type 确定枢轴的算法类型
 * \param i 对应的算法类型
 */
void QuickSort(int num[], int length, int type, int i)
{
	if (length <= 1) return;
	cnt[i]++; //排序次数+1
	if (type == INSERT) { //采用直接插入
		if (length < N) {
			InsertSort(num, length, i);
			print(a[i]);
			return;
		}
	}
	int k = Partition(num, length, type); //将待排数组一分为二
	print(a[i]); //打印数组每一步的变化
	QuickSort(num, k, type, i); //对枢轴之前的元素排序
	QuickSort(&num[k + 1], length - k - 1, type, i); //对枢轴之后的元素排序
}