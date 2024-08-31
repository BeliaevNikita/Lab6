#include <stdio.h>
#include <string.h>
#include <math.h>
#include <funcs.asm>
double f1(double x);
//double f2(double x);
//double f3(double x);
double test1(double a, double b) {
    return exp(b) - exp(a) + 2.0 * (b - a);
}

int iter = 0;
double root(double (*f)(double x), double (*g)(double x), double a, double b, double eps1);
double integral(double (*f) (double x), double a, double b, double eps2);

int main(int argc, char* argv[]) {
    double x12 = root(f2, f1, -2.0, -0.25, 0.000001);
    double x13 = root(f3, f1, -7.0, -6.0, 0.000001);
    double x23 = root(f3, f2, -4.0, -3.0, 0.000001);
    double int1 = integral(f1, x13, x12, 0.001);
    double int2 = integral(f2, x23, x12, 0.001);
    double int3 = integral(f3, x13, x23, 0.001);
    double square = int1 - int2 - int3;
    //printf("%f\n", int1);
    //printf("%f\n", int2);
    //printf("%f\n", int3);
    int1 = test1(x13, x12);
    //printf("%f\n", int1);
    for (int i = 1; i < argc; ++i) {
        if(!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            FILE *fp = fopen("cmd_keys.txt", "r");
            char buf[64];
            printf("Keys:\n");
            while (fgets(buf, 64, fp) != NULL) {
                printf("%s", buf);
            }
        }
        if (!strcmp(argv[i], "-r") || !strcmp(argv[i], "--root")) {
            printf("f1 intersect f2: %f\n", x12);
            printf("f1 intersect f3: %f\n", x13);
            printf("f2 intersect f3: %f\n", x23);
        }
        if (!strcmp(argv[i], "-i") || !strcmp(argv[i], "--iterations")) {
            printf("count of iterations to find intersections: %d\n", iter);
        }
        if (!strcmp(argv[i], "-R") || !strcmp(argv[i], "--test-root")) {

        }
        if (!strcmp(argv[i], "-I") || !strcmp(argv[i], "--test-integral")) {

        }
    }
    if (argc == 1) {
        printf("square: %f\n", square);
    }
    return 0;
}

double root(double (*f)(double x), double (*g)(double x), double a, double b, double eps1) {
    double lres = f(a) - g(b), rres = f(b) - g(b);
    while (fabs(a - b) >= eps1) {
        ++iter;
        //printf("%f %f\n", a, b);
        double mid = (a + b) / 2;
        //printf("f(mid):%f, g(mid):%f\n", f(mid), g(mid));
        double midres = f(mid) - g(mid);
        //printf("mid:%f midres:%f\n", mid, midres);
        if (midres * lres < 0) {
            b = mid;
        } else {
            a = mid;
        }
    }
    return a;
}

double integral(double (*f) (double x), double a, double b, double eps2) {
    int n = 10;
    double answer = 0.0;
    double I = 0.0;
    double h = (b - a) / n; //  height of trapezoid
    for (int i = 0; i < n; ++i) {
        if (i == 0 || i == n - 1) {
            I += f(a + i * h) / 2.0;
        }
        else {
            I += f(a + i * h);
        }
    }
    I *= h;
    //printf("tmp int: %f\n", I);
    while (fabs(answer - I) / 3 >= 0.0001) {
        answer = I;
        I = 0.0;
        n <<= 1;
        h = (b - a) / n;
        for (int i = 0; i < n; ++i) {
            if (i == 0 || i == n - 1) {
                I += f(a + i * h) / 2.0;
            }
            else {
                I += f(a + i * h);
            }
        }
        I *= h;
        //printf("tmp int: %f\n", I);
    }
    return I;
}

double f1(double x) {
    return exp(x) + 2.0;
}

// double f2(double x) {
//     return -1.0 / x;
// }

// double f3(double x) {
//     return -2.0 * (x + 3.0) / 3.0;
// }
