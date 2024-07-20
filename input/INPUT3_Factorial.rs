/* RuanScript Example: Testing numbers (factorial) - single line comment*/
// another comment

main() {

    int i = 1;
    int n = 0;
    int f = 1;

    n = input('Write a number: ');

    while (i <= n) {
        f = f * i;
        i = i + 1;
    };

    print('Factorial: ');
    print(f);
}
