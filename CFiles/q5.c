#include <stdio.h>

int main()
{
    int n;
    printf("Enter the value for n: ");
    scanf("%d", &n);

    for (int i = 0; i <= n; i++)
    {
        int k;
        if (k != 0) printf("Sum: %d\n", k);
        else k = 0;
        if (i == n) break;
        int d = 0;
        printf("Enter your number: ");
        scanf("%d", &d);
        k += d;
    }
    
}
