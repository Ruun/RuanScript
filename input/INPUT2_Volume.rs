/* RuanScript Example: Volume of a sphere*/
//single line comment

main()
{
    float PI = 3.14;
    float r = 0.0;
    float Vol = 0.0;
   
    r = input('Enter the radius:');
    Vol = 4.0 / 3.0 * PI * (r * r * r);
   
    print(Vol);
}
