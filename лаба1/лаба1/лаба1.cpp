/***************************************************************************************
* Project name  : Topu_methods														   *
* Project type  : win32 console app                                                    *
* File_name     : Lab                                                                  *
* Language      : cpp. MSVS 2013 and above                                             *
* Programmers   : Usupov T.T./Frolov E.V./Pronin I.T.	                               *
***************************************************************************************/

#include"stdafx.h"
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <iomanip>
using namespace std;

/**************************************************************************************/
/*                       П Р О Т О Т И П Ы    Ф У Н К Ц И Й                           */
/**************************************************************************************/

void Dicht(double eps, double l, double a, double b, double &OPTa, int &kolvo_iter, double &OPTb, double(*func)(double));
void Zolotoe(double l, double a, double b, double &OPTa, double &OPTb, int &kolvo_iter, double(*func)(double));
void FIBON(double eps, double l, double a, double b, double &OPTa, int &kolvo_iter, double &OPTb, double(*func)(double));
double F(double x);
double Fib(int i);

/**************************************************************************************/
/*										M A I N		    		                      */
/**************************************************************************************/

int main()
{
	double eps;
	double l;
	double A;
	double B;
	double OpA = 0.;
	double OpB = 0.;
	int iterations = 0;
	int p = 0;

	setlocale(LC_ALL, "RUSSIAN");
	cout << "Введите eps= ";
	cin >> eps;
	cout << "Введите l= ";
	cin >> l;
	if (l <= 2 * eps)
	{
		cout << "Ошибка! ДИХОТОМИИ НЕТ" << endl;
		p = 1;
	}
	cout << "Введите a= ";
	cin >> A;
	cout << "Введите b= ";
	cin >> B;
	if (p != 1)

	{
		cout << "\nМетод ДИХОТОМИЧЕСКОГО ПОИСКА\n";
		Dicht(eps, l, A, B, OpA, iterations, OpB, (*F));
		cout << "Функция посчитана " << iterations << " раз\n";
		cout << "Оптимальный x*= " << (OpB + OpA) / 2 << "\n";
		cout << "Оптимальное значение F(x)= " << F((OpB + OpA) / 2) << "\n";
	}
	cout << "\nМетод ЗОЛОТОГО СЕЧЕНИЯ\n";
	Zolotoe(l, A, B, OpA, OpB, iterations, (*F));
	cout << "Функция посчитана " << iterations << " раз\n";
	cout << "Оптимальный x*= " << (OpB + OpA) / 2 << "\n";
	cout << "Оптимальное значение F(x)= " << F((OpB + OpA) / 2) << "\n";

	cout << "\nМетод ФИБОНАЧЧИ\n";
	FIBON(eps, l, A, B, OpA, iterations, OpB, (*F));
	cout << "Функция посчитана " << iterations << " раз\n";
	cout << "Оптимальный x= " << (OpB + OpA)/2 << "\n";
	cout << "Оптимальное значение F(x)= " << F((OpB + OpA) / 2) << "\n";
	cout << "=================================================" << endl;

	system("pause");
	return 0;
}

/**************************************************************************************/
/*                                 РЕАЛИЗАЦИЯ ФУНКЦИЙ                                 */
/**************************************************************************************/

double F(double x)
{
	double f;
	f = 3*x-pow(x, 3)-1;
	return f;
}

void Dicht(double eps, double l, double a, double b, double &OPTa, int &kolvo_iter, double &OPTb, double(*func)(double))
{
	cout << setw(5) << "K"
		<< setw(10) << "a(k)"
		<< setw(10) << "b(k)"
		<< setw(10) << "lmbd(k)"
		<< setw(10) << "mu(k)"
		<< setw(10) << "F(lmbd(k))"
		<< setw(10) << "F(mu(k))" << endl << endl;
	int k = 1;//счётчик итераций
	double lmbd;
	double mu;
	int j = 0;
	while (b - a >= l)
	{
		cout << setw(5) << k;
		lmbd = (a + b) / 2 - eps;
		mu = (a + b) / 2 + eps;
		cout << setw(10) << setprecision(4) << a
			<< setw(10) << setprecision(4) << b
			<< setw(10) << setprecision(4) << lmbd
			<< setw(10) << setprecision(4) << mu
			<< setw(10) << setprecision(4) << func(lmbd)
			<< setw(10) << setprecision(4) << func(mu)
			<< endl;

		if (func(lmbd) < func(mu))
			b = mu;
		else
			a = lmbd;
		k++;
	}//while

	cout << endl;
	OPTa = a;
	OPTb = b;
	kolvo_iter = (k - 1) * 2 + 1;
}
void Zolotoe(double l, double a, double b, double &OPTa, double &OPTb, int &kolvo_iter, double(*func)(double))
{
	cout << setw(5) << "K"
		<< setw(10) << "a(k)"
		<< setw(10) << "b(k)"
		<< setw(10) << "lmbd(k)"
		<< setw(10) << "mu(k)"
		<< setw(10) << "F(lmbd(k))"
		<< setw(10) << "F(mu(k))" << endl << endl;
	const double al = 0.618;
	int j = 0;
	int k = 1;
	double lmbd = a + (1 - al)*(b - a);
	double mu = a + al * (b - a);

	while (b - a >= l)
	{
		cout << setw(5) << k;
		cout << setw(10) << setprecision(4) << a
			<< setw(10) << setprecision(4) << b
			<< setw(10) << setprecision(4) << lmbd
			<< setw(10) << setprecision(4) << mu
			<< setw(10) << setprecision(4) << func(lmbd)
			<< setw(10) << setprecision(4) << func(mu)
			<< endl;
		
		if (func(lmbd) > func(mu))
		{
			a = lmbd;
			lmbd = mu;
			mu = a + al * (b - a);
		}//if
		else
		{
			b = mu;
			mu = lmbd;
			lmbd = a + (1 - al)*(b - a);
		}//else
		k++;
	}//while

	cout << endl;
	OPTa = a;
	OPTb = b;
	kolvo_iter = k + 1;
}
void FIBON(double eps, double l, double a, double b, double &OPTa, int &kolvo_iter, double &OPTb, double(*func)(double))
{
	cout << setw(5) << "K"
		<< setw(10) << "a(k)"
		<< setw(10) << "b(k)"
		<< setw(10) << "lmbd(k)"
		<< setw(10) << "mu(k)"
		<< setw(10) << "F(lmbd(k))"
		<< setw(10) << "F(mu(k))" << endl;
	int n;
	int j = 0;
	for (n = 0; n < 47; n++)
	{
		if (Fib(n) > abs(b - a) / l)
			break;
	}
	double lmbd = a + (Fib(n - 2) / Fib(n) * abs(b - a));
	double mu = a + (Fib(n - 1) / Fib(n) * abs(b - a));
	int k = 1;
	while (abs(b - a) >= l)
	{
		cout << setw(5) << k;
		cout << setw(10) << setprecision(4) << a
			<< setw(10) << setprecision(4) << b
			<< setw(10) << setprecision(4) << lmbd
			<< setw(10) << setprecision(4) << mu
			<< setw(10) << setprecision(4) << func(lmbd)
			<< setw(10) << setprecision(4) << func(mu)
			<< endl;
		if (func(lmbd) > func(mu))
		{
			a = lmbd;
			lmbd = mu;
			mu = a + (Fib(n - k - 1) / Fib(n - k))*abs(b - a);
			if (k == n - 2)
			{
				mu = lmbd + eps;
				if (func(lmbd) > func(mu))
					a = lmbd;
				else
					b = mu;
			}//if
		}//if
		else
		{
			b = mu;
			mu = lmbd;
			lmbd = a + (Fib(n - k - 2) / Fib(n - k))*abs(b - a);
			if (k == n - 2)
			{
				mu = lmbd + eps;
				if (func(lmbd) > func(mu))
					a = lmbd;
				else
					b = mu;
			}
		}//else
		k++;
	}//while
	 //закрываем таблицу
	cout << endl;
	OPTa = a;
	OPTb = b;
	kolvo_iter = n;
}

double Fib(int i)
{
	if (i<0) return 0;
	if (i == 0) return 0;
	if (i == 1) return 1;
	return Fib(i - 1) + Fib(i - 2);
}
