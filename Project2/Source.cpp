//part2
#include <iostream>
#include <omp.h>
using namespace std;
int main()
{
	//Data Generation
	int a[30][30], mul[30][30], mul1[30][30], mul2[30][30];

	for (int i = 0; i < 30; i++)
		for (int j = 0; j < 30; j++)
		{
			a[i][j] =rand()%100;
		}
	//Data Processing in sections with schedule
#pragma omp parallel sections
	{
		//static
		#pragma omp section
		double start = omp_get_wtime();
		#pragma omp parallel for schedule(static)
		for (int i = 0; i < 30; i++)
			for (int j = 0; j < 30; j++)
			{
				mul[i][j] = 0;
				for (int k = 0; k < 30; k++)
					mul[i][j] += a[i][k] * a[k][j];

			}

		double end = omp_get_wtime();
		double time = (end - start) * 1000000;
		cout << "the time is: \t" << time<<endl;
		//dynamic
		#pragma omp section
		double start1 = omp_get_wtime();
		#pragma omp parallel for schedule(dynamic)
		for (int i = 0; i < 30; i++)
			for (int j = 0; j < 30; j++)
			{
				mul1[i][j] = 0;
				for (int k = 0; k < 30; k++)
					mul1[i][j] += a[i][k] * a[k][j];
			}
		double end1 = omp_get_wtime();
		double time1 = (end1 - start1) * 1000000;
		cout << "the time is: \t" << time1 << endl;
		//guided
		#pragma omp section
		double start2 = omp_get_wtime();
		#pragma omp parallel for schedule(guided)
		for (int i = 0; i < 30; i++)
			for (int j = 0; j < 30; j++)
			{
				mul2[i][j] = 0;
				for (int k = 0; k < 30; k++)
					mul2[i][j] += a[i][k] * a[k][j];
			}
		double end2 = omp_get_wtime();
		double time2 = (end2 - start2) * 1000000;
		cout << "the time is: \t" << time2 << endl;

	}
	int sum1 = 0;
	int sum = 0;
	int sum2 = 0;
	//Data Aggregation with
#pragma omp parallel for reduction(+:sum, sum1, sum2)
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			sum += mul[i][j];
			sum1 += mul[i][j];
			sum2 += mul2[i][j];
		}
	}

	cout << sum << endl;
	cout << sum1 << endl;
	cout << sum2 << endl;

	system("pause");
return 0;
}