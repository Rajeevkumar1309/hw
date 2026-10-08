#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>

typedef struct timespec Time;

Time start(){
    Time x;
    timespec_get(&x, TIME_UTC);
    return x;
}
Time end(){
    Time x;
    timespec_get(&x, TIME_UTC);
    return x;
}
double diff(Time start, Time end){
    return (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec) / 1e9;
}

long int Hn(int n);
long int Ln(int n);

long int Hn(int n){
    if(n==0) return 1;
    return 2*Hn(n-1) + Ln(n-1);
}

long int Ln(int n){
    if(n==0) return 0;
    return Hn(n-1) + Ln(n-1);
}

void func3(int n, long int *H, long int *L){
    if(n==0){
        *H = 1;
        *L = 0;
        return;
    }
    long int h_prev, l_prev;
    func3(n-1, &h_prev, &l_prev);
    *H = 2*h_prev + l_prev;
    *L = h_prev + l_prev;
}

long int *a(int n){
    long int *arr = (long int *)malloc(2 * sizeof(long int));
    func3(n, &arr[0], &arr[1]);
    return arr;
}

long int *b(int n){
    long int *arr = (long int *)malloc(2 * sizeof(long int));

    arr[0] = round(((5.0 + sqrt(5.0)) / 10.0) * pow((3.0 - sqrt(5.0)) / 2.0, n+1) + ((5.0 - sqrt(5.0)) / 10.0) * pow((3.0 + sqrt(5.0)) / 2.0, n+1));
    arr[1] = round(((-5.0 - 3.0 * sqrt(5.0)) / 10.0) * pow((3.0 - sqrt(5.0)) / 2.0, n+1) + ((-5.0 + 3.0* sqrt(5.0)) / 10.0) * pow((3.0 + sqrt(5.0)) / 2.0, n+1));
    return arr;
}

typedef struct{
    long int m[2][2];
} Matrix;

Matrix multiply(Matrix x, Matrix y){
    Matrix res;
    res.m[0][0] = x.m[0][0]*y.m[0][0] + x.m[0][1]*y.m[1][0];
    res.m[0][1] = x.m[0][0]*y.m[0][1] + x.m[0][1]*y.m[1][1];
    res.m[1][0] = x.m[1][0]*y.m[0][0] + x.m[1][1]*y.m[1][0];
    res.m[1][1] = x.m[1][0]*y.m[0][1] + x.m[1][1]*y.m[1][1];
    return res;
}

Matrix matpow(Matrix base, int n){
    Matrix result;
    result.m[0][0] = 1;
    result.m[0][1] = 0;
    result.m[1][0] = 0;
    result.m[1][1] = 1;

    while(n > 0){
        if(n % 2 == 1){
            result = multiply(result, base);
        }
        base = multiply(base, base);
        n = n / 2;
    }
    return result;
}

long int *c(int n){
    long int *arr = (long int *)malloc(2 * sizeof(long int));
    if(n == 0){
        arr[0] = 1;
        arr[1] = 0;
        return arr;
    }
    Matrix M;
    M.m[0][0] = 2;
    M.m[0][1] = 1;
    M.m[1][0] = 1;
    M.m[1][1] = 1;

    Matrix result = matpow(M, n);
    arr[0] = result.m[0][0];
    arr[1] = result.m[1][0];
    return arr;
}

int main(){
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    Time start_time, end_time;
    long int *result;

    start_time = start();
    long int hval = Hn(n);
    end_time = end();
    printf("H(%d) = %ld\n", n, hval);
    printf("Execution time: %f seconds of part 1\n\n", diff(start_time, end_time));

    start_time = start();
    long int lval = Ln(n);
    end_time = end();
    printf("L(%d) = %ld\n", n, lval);
    printf("Execution time: %f seconds of part 2\n\n", diff(start_time, end_time));

    start_time = start();
    result = a(n);
    end_time = end();
    printf("H(%d) = %ld, L(%d) = %ld\n", n, result[0], n, result[1]);
    printf("Execution time: %f seconds of part 3\n\n", diff(start_time, end_time));
    free(result);

    start_time = start();
    result = b(n);
    end_time = end();
    printf("H(%d) = %ld, L(%d) = %ld\n", n, result[0], n, result[1]);
    printf("Execution time: %f seconds of part 4\n\n", diff(start_time, end_time));
    free(result);

    start_time = start();
    result = c(n);
    end_time = end();
    printf("H(%d) = %ld, L(%d) = %ld\n", n, result[0], n, result[1]);
    printf("Execution time: %f seconds of part 5\n\n", diff(start_time, end_time));
    free(result);

    return 0;
}