#include <stdio.h>
unsigned long long square_digits(unsigned n);

int main() {
    unsigned n;
    n = 100001;
    printf("%llu\n", square_digits(n));
    n = 3456338;
    printf("%llu\n", square_digits(n));
    return 0;
}

unsigned long long square_digits(unsigned n) {
  unsigned long long c = 0, k = 1;
  int count = 0;
  c += (n % 10) * (n % 10) * k;
          if (n % 10 <= 3) {
            count = 2;
        }
  n = n / 10;
  while (n) {
    if (n % 10 <= 3) {
        if (count == 1) {
            k /= 10;
            count = 0;
        }
        if (count == 2)
            k *= 10;
        else
            k *= 100;
        c += (n % 10) * (n % 10) * k;
        count = 1;
    } else {
        if (count == 1) {
            k /= 10;
            count = 0;
        }
        k *=100;
        c += (n % 10) * (n % 10) * k;
    }
    n = n / 10;
  }
    return c;
}
