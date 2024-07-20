/* This program solves a quadratic equation ax^2 + bx + c = 0
   using the quadratic formula and prints the two roots. */

   main() {
    float a = 0.0;
    float b = 0.0;
    float c = 0.0;
    float discriminant = 0.0;
    float root1 = 0.0;
    float root2 = 0.0;

    a = input('Enter coefficient a:');
    b = input('Enter coefficient b:');
    c = input('Enter coefficient c:');
    
    discriminant = b * b - 4 * a * c;
    root1 = (-b + sqrt(discriminant)) / (2 * a);
    root2 = (-b - sqrt(discriminant)) / (2 * a);

    print('Root 1:');
    print(root1);
    print('Root 2:');
    print(root2);
}
