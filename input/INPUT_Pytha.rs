/* This program calculates the length of the hypotenuse of a right triangle
   given the lengths of the other two sides using the Pythagorean Theorem. */

   main() {
    float a = 0.0;
    float b = 0.0;
    float c = 0.0;

    a = input('Enter the length of side a:');
    b = input('Enter the length of side b:');
    c = sqrt(a * a + b * b);

    print('Length of hypotenuse: ');
    print(c);
}
