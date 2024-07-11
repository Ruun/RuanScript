# Rs Example: Lexically Correct Program
main() {
    int i = 0;
    float a = 0.0, sum008 = 0.0;
    string text = '';

    a = 1.2;
    sum008 = 7.87050;
    input(a, sum008);

    while (i < 32767 || i == 32767) {
        i = i + 2;
        a = a * (i / 0.5);
        sum008 = sum008 + a - 1;
    };

    if (text == '') {
        text = 'prog' + 'ram';
    } else {
        text = text + 'ram';
    };

    print('\* This is a program -:)-<-<-- \*');
    print(text);

    if (text != 'program' && sum008 == 8.0 || i > 10) {
        print(sum008);
        print();
    };
}
