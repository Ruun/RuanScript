main& {
    data {
        Rs_intg number;  // Define a variable without initialization
    }
    code {
        number = 10;
        print&('The number is: ' + number);
    }
}
