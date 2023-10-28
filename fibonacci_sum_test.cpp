#include <iostream>

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}

long pisano_length(long m){
    //the first and the second of the pisano period is 0 and 1
    long previous = 0;
    long current = 1;
    long result = 0;

    for (int i = 0; i < m * m; ++i) {
        long tmp = current;
        current = (previous + current) % m;
        previous = tmp;
        //if same with the previous two digit, end the loop, return the length
        if (previous == 0 && current == 1){
            result = i + 1;
            break;
        }
    }
    return result;
}

long fibonacci_sum_fast(long long n) {
    if (n < 0) {
        return 0;
    }

    if (n < 2 )
        return n;

    //get pisano period length for mod 10 first, as p
    long p = pisano_length(10);

    //recursive compute n mod p get the smallest n as new n
    while (n > p) {
        n = n % p;
    }

    if (n < 2 )
        return n;

    //compute fibonacci n module 10, and get the sum
    long previous = 0;
    long current = 1;
    long sum = previous + current;
    for (int i = 0; i < n - 1; ++i) {
        long tmp = current;
        current = previous + current;
        sum += current;
        previous = tmp;
    }

    //std::cout << "sum:" << sum << "\n";

    //return the last digit
    return sum;
}

int compute_from_to (long m, long n) {
    long sumForM = fibonacci_sum_fast(m-1);
    long sumForN = fibonacci_sum_fast(n);

    return (sumForN - sumForM) % 10;
}


int main() {
    long long from, to;
    std::cin >> from >> to;

    std::cout << compute_from_to(from, to) << '\n';
}
