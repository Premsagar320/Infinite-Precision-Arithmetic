int main() {
    LargeInt first("12345");
    LargeInt second(12345);

    cout << "first = " << first << endl;
    cout << "second = " << second << endl;

    if (first == second)
        cout << "first and second are equal!" << endl;
    else
        cout << "first and second are not equal!" << endl;

    LargeInt third("10000");
    LargeInt fourth("100000");
    LargeInt fifth("10000000");

    cout << "third = " << third << endl;
    cout << "fourth = " << fourth << endl;
    cout << "fifth = " << fifth << endl;

    if (third < fourth)
        cout << "third is smaller than fourth!" << endl;

    if (fifth > fourth)
        cout << "fifth is larger than fourth!" << endl;

    first++;
    cout << "first after increment = " << first << endl;

    LargeInt sum = fourth + fifth;
    cout << "fourth + fifth = " << sum << endl;

    LargeInt product = second * third;
    cout << "second * third = " << product << endl;

    cout << "\nFactorials from 0 to 10:" << endl;
    for (int i = 0; i <= 10; ++i) {
        cout << "Factorial of " << i << " = " << LargeInt::factorial(i) << endl;
    }

    return 0;
}

