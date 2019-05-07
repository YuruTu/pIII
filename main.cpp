#include<iostream>
#include<cmath>

double alpha = 7.7134;
const double   precision = 0.0001;   //定义精度 

using namespace std;
double f(double x)
{
	double m = pow(x, alpha -1)*exp(-x);
	return m;
}
const double c[11] = { 0.0000677106,
-0.0003442342,
0.0015397681,
-0.0024467480,
0.0109736958,
-0.0002109075 ,
0.0742379071 ,
0.0815782188,
0.4118402518 ,
0.4227843370,
1 };

double Gamma(double x) {
	double ret = 1.0;
	while ((x <= 2.0) || (x > 3.0)) {
		if (x > 3) {
			x--;
			ret *= x;
		}
		else if (x <= 2.0) {
			ret/= x;
			x++;
		}
	}
	//cout << "rate:" << ret << endl;
	double f = 0.0;
	for (int i = 0; i < 11; i++) {
		f += c[i] * pow(x - 2, 10 - i);
	}
	ret *= f;
	//cout << ret << endl;
	return ret;
}

int main()
{
	double  left = 0; //左端的值 
	
	double  right = 5.440;   //右端的值 
	double T_n[10];
	int i;
	int step = 100;  //初始化步数
	double stepLength = (right - left) / step; //步长
	double T = f(left) + f(right);   //积分的值 
	for (i = 1; i <= step - 1; i++)
	{
		double x = left + i * stepLength;
		T += 2 * f(x);
	}
	T = stepLength / 2 * T;  //符合梯形公式求解结果
	printf("初始步长得到的积分值:%lf   所分的区间个数：%d\n", T, step);
	//下面改变步长，来细化精度
	double T1 = T + 100;
	double T2 = T;
	double H;      //减小步长后得到的积分值 
	while (fabs(T1 - T2) > precision / 2)
	{
		T1 = T2;
		step = step * 2;
		stepLength = (right - left) / step;
		H = 0;
		for (i = 1; i < step; i++)
		{
			H += 2 * f(left + stepLength * i);
		}
		H = f(left) + f(right) + H;
		H = H * stepLength / 2;
		T2 = (T1 + H) / 2;    //将上次一的积分结果和减小步长后的积分结果求均值 

	}

	
	T = Gamma(alpha);
	
	
	printf("初始步长得到的积分值:%lf   所分的区间个数：%d\n", (1 - T2 / T), step);
}
