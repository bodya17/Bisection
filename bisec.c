#include <stdio.h>
#include <math.h>

#define BCK  "\x1B[0m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"

using namespace std;

// Функція з варіанту 13
double f(double x)
{
    return	x * log10(x + 1) - 0.5;
    // return x * x * x - x;
}

int main()
{
	double a     // початок відрізка
        , b      // кінець відрізка
	    , c      // середина між a і b
	    , eps;   // точність

	int n = 0;   // кількість ітерацій
	printf("Введіть початок відрізка: ");
	scanf("%lf", &a);

	printf("Введіть кінець відрізка: ");
	scanf("%lf", &b);

	double fa = f(a);
	double fb = f(b);

	if ( fa * fb > 0 ) {
		printf("%s", "На кінцях інтервала функція повинна змінювати знак, бо алгоритм не спрацює!\n");
		printf("f(%g) = %s%g\t%sf(%g) = %s%g%s\n", a, RED, fa, BCK, b, RED, fb, BCK);

		do {
			printf("Введіть початок відрізка: ");
			scanf("%lf", &a);

			printf("Введіть кінець відрізка: ");
			scanf("%lf", &b);
		} while ( f(a) * f(b) > 0);
	}

	printf("Введіть точність: ");
	scanf("%lf", &eps);

	/* Опис алгоритму */
	// 1. Перевірити чи на кінцях інтервалу функція приймає протилежні за знаком значення,
	// 		якщо так то переходимо до наступного кроку інакше просимо ввести інші значення a i b
	// 2. Порахувати с, середину інтервала [a, b], c = 0.5 * (a + b).
	// 3. Порахувати значення функції у точці с
	// 4. Якщо умова збіжності виконується (тобто a-b < eps, або f(c) < eps)
	//		тоді завершити програму з виводом результатів
	// 5. Перевірити знак f(c) і продовжувати алгоритм з інтервалом на якому є корінь
	//		[a, c], якшо f(a)*f(c) < 0 або з ітервалом [c, b], якщо f(b)*f(c) < 0

	double fc; // значення функції в середній точці інтервала [a, b]

	printf("%sТабуляція:\n%s%-9s%-9s%-9s%-9s%-9s\n", GRN, RED, "#", "a", "b", "c", "f(c)");


	do {
		n++;
		c = (a + b) / 2;

		fc = f(c); // значення функції в точці c, де с = 0.5 * (a + b)

		printf("%s%-9d%-9g%-9g%-9g%-9g\n", BCK, n, a, b, c, fc);

		if ( f(b) * fc < 0 )
			a = c;
		else
			b = c;

	} while ( fabs(b - a) > eps && fabs(fc) > eps);

	printf("%sКорінь: %s%g\n", GRN, RED, c);
	printf("%sКількість ітерацій: %s%d\n\n", GRN, RED, n);

	return 0;
}
