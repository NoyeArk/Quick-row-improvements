//main.cpp
#include "QuickSort.cpp"

static int cnt[5] = { 0 }; //5个算法对应的排序次数
//待排序的数组
int num[LENGTH], a[5][LENGTH], type[5] = { FIRST ,RANDOM ,AVERAGE ,MEDIAN ,INSERT };
//5个算法每次排序对应的排序时间和排序次数
clock_t startTime[5], endTime[5], wasteTime;
//5个算法对应的平均排序时间和平均排序次数
double averTime[5], averCnt[5];
int ran[6] = { 3,25,56,1,6,9 };

/**
 * \name Init 产生随机数等相关初始化
 * \type void
 */
void Init() {

	for (int i = 0; i < 5; i++) {
		cnt[i] = 0;
		startTime[i] = endTime[i] = 0;
	}
	for (int j = 0; j < LENGTH; j++)
	{
		num[j] = MIN + (rand() + ran[j % 6]) % (MAX - MIN + 1);
	}
	for (int i = 0; i < 5; i++) {
		cnt[i] = 0;
		for (int j = 0; j < LENGTH; j++)
			a[i][j] = num[j];
	}
}

void Menu() {
	cout << endl << "**************快速排序算法改进**************" << endl << endl;
	cout << "\t\t1、随机数法" << endl << endl;
	cout << "\t\t2、三数取中法" << endl << endl;
	cout << "\t\t3、中位数法" << endl << endl;
	cout << "\t\t4、直接插入法" << endl << endl;
	cout << "\t\t5、五种算法对比" << endl << endl;
	cout << "\t\t请输入选择：";

}

void allCompare() {
	for (int j = 0; j < LOOP; j++) {
		printf("第%d次测试\n", j + 1);
		Init();
		for (int i = 0; i < 5; i++) {

			switch (type[i])
			{
			case FIRST:cout << "***********原始***********" << endl; break;
			case RANDOM:cout << endl << "***********随机数为枢轴***********" << endl; break;
			case AVERAGE:cout << endl << "***********三数取中法***********" << endl; break;
			case MEDIAN:cout << endl << "***********中位数为枢轴***********" << endl; break;
			case INSERT:cout << endl << "***********直接插入***********" << endl; break;
			}
			startTime[i] = clock();
			QuickSort(a[i], LENGTH, type[i], i);
			endTime[i] = clock();

			//print(a[i]);
			//得出本次排序所用的时间
			double time = (double)(endTime[i] - startTime[i] - wasteTime) / CLOCKS_PER_SEC;
			cout << "一共进行了" << cnt[i] << "次排序" << "		用时：" << time << "s" << endl;

			averTime[i] += time;
			averCnt[i] += cnt[i];
		}
	}
	for (int i = 0; i < 5; i++) {
		averTime[i] /= LOOP;
		averCnt[i] /= LOOP;
		switch (type[i])
		{
		case FIRST:cout << "原始："; break;
		case RANDOM:cout << "随机数为枢轴："; break;
		case AVERAGE:cout << "三数取中法："; break;
		case MEDIAN:cout << "中位数为枢轴："; break;
		case INSERT:cout << "直接插入："; break;
		}
		cout << averTime[i] << "s";
		cout << "		排序" << averCnt[i] << "次" << endl << endl;
	}
}

void singleSort(int type, int loop) {
	srand((unsigned)time(NULL));

	averTime[0] = averCnt[0] = 0;
	for (int i = 0; i < loop; i++) {
		Init();
		printf("第%d次测试\n", i + 1);
		startTime[0] = clock();
		QuickSort(a[0], LENGTH, type, 0);
		endTime[0] = clock();

		switch (type)
		{
		case FIRST:cout << "原始："; break;
		case RANDOM:cout << "随机数为枢轴："; break;
		case AVERAGE:cout << "三数取中法："; break;
		case MEDIAN:cout << "中位数为枢轴："; break;
		case INSERT:cout << "直接插入："; break;
		}
		double time = (double)(endTime[0] - startTime[0] - wasteTime) / CLOCKS_PER_SEC;
		cout << "用时" << time << "s";
		cout << "		排序" << cnt[0] << "次" << endl << endl;

		averTime[0] += time;
		averCnt[0] += cnt[0];
	}
	averTime[0] /= loop;
	averCnt[0] /= loop;

	cout <<"平均用时" << averTime[0] << "s";
	cout << "		排序" << averCnt[0] << "次" << endl << endl;
}

/**
 * \name main
 * \type int
 * \return 
 */
int main()
{
	int input, loop = 1;
	while (true) {
		Menu();

		cin >> input;
		cout << endl << "\t\t请输入测试次数：";
		cin >> loop;
		switch (input)
		{
		case 1:singleSort(RANDOM, loop); break;
		case 2:singleSort(AVERAGE, loop); break;
		case 3:singleSort(MEDIAN, loop); break;
		case 4:singleSort(INSERT, loop); break;
		case 5:allCompare(); break;
		}
		system("pause");
		system("cls");
	}
	
	return 0;
}
