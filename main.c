    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define MAX 1005

    void add(char *a, char *b, char *result) {
        int i = strlen(a) - 1;
        int j = strlen(b) - 1;
        int k = 0;
        int carry = 0;
        char temp[MAX * 2];
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0)
                sum += a[i--] - '0';
            if (j >= 0)
                sum += b[j--] - '0';
            temp[k++] = (sum % 10) + '0';
            carry = sum / 10;
        }
        for (int x = 0; x < k; x++)
            result[x] = temp[k - x - 1];
        result[k] = '\0';
    }
    void multiplySimple(char *a, char *b, char *result) {
        int n = strlen(a);
        int m = strlen(b);
        int *num = calloc(n + m, sizeof(int));
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                int mul = (a[i] - '0') * (b[j] - '0');
                int pos1 = i + j;
                int pos2 = i + j + 1;
                int sum = mul + num[pos2];
                num[pos2] = sum % 10;
                num[pos1] += sum / 10;
            }
        }
        int k = 0;
        while (k < n + m - 1 && num[k] == 0)
            k++;
        int pos = 0;
        for (; k < n + m; k++)
            result[pos++] = num[k] + '0';
        result[pos] = '\0';
        free(num);
    }
    void karatsuba(char *x, char *y, char *result) {
        int n = strlen(x);
        int m = strlen(y);
        if (n == 0 || m == 0) {
            strcpy(result, "0");
            return;
        }
        if (n <= 4 || m <= 4) {
            multiplySimple(x, y, result);
            return;
        }
        int size = n > m ? n : m;
        int half = size / 2;
        int xlen = n - half;
        int ylen = m - half;
        char xHigh[MAX], xLow[MAX];
        char yHigh[MAX], yLow[MAX];
        if (xlen > 0) {
            strncpy(xHigh, x, xlen);
            xHigh[xlen] = '\0';
        } else {
            strcpy(xHigh, "0");
        }
        strcpy(xLow, x + xlen);
        if (ylen > 0) {
            strncpy(yHigh, y, ylen);
            yHigh[ylen] = '\0';
        } else {
            strcpy(yHigh, "0");
        }
        strcpy(yLow, y + ylen);
        char z0[MAX * 2];
        char z1[MAX * 2];
        char z2[MAX * 2];
        karatsuba(xLow, yLow, z0);
        karatsuba(xHigh, yHigh, z2);
        char sumX[MAX];
        char sumY[MAX];
        add(xLow, xHigh, sumX);
        add(yLow, yHigh, sumY);

        karatsuba(sumX, sumY, z1);
        multiplySimple(x, y, result);
    }
    int main() {
        char A[MAX];
        char B[MAX];
        char result[MAX * 2];
        printf("A = ");
        scanf("%1000s", A);
        printf("B = ");
        scanf("%1000s", B);
        karatsuba(A, B, result);
        printf("Result = %s\n", result);
        return 0;
    }