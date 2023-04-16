#include "..//descend.h"

const char* string = "52 * 10   + 5 *(90 +11 - 1)+  25";

int main () {

    printf("%lg\n", GetG());
    return 0;
}

elem_t GetG() {

    SkipSpaces(&string);
    printf("I am GetG, i got such string: <%s>\n", string);

    value number = GetE();
    if (*string != '\0') {
        printf("Error: didn't get end simbol <%s>\n", string);
        exit(EXIT_FAILURE);
    }
    return number.data;
}

value GetE() {

    SkipSpaces(&string);
    printf("I am GetE, i got such string: <%s>\n", string);

    value number1 = GetT();
    while (*string == '+' || *string == '-') {
        int save_symb = *string;
        string++;
        printf("Calling GetT, current string: <%s>\n", string);

        value number2 = GetT();
        if (save_symb == '+') {
            number1.data += number2.data;
        }
        else {
            number1.data -= number2.data;
        }
    }
    printf("I am GetE, RETURN string: <%s>\n", string);

    return number1;
}

value GetT( ) {

    SkipSpaces(&string);
    printf("I am GetT, i got such string: <%s>\n", string);

    value number1 = GetP();

    while (*string == '*' || *string == '/') {

        int save_symb = *string;
        string++;
        printf("Calling GetP, current string: <%s>\n", string);

        value number2 = GetP();

        if (save_symb == '*') {
            number1.data *= number2.data;
        }
        else {
            number1.data /= number2.data;
        }
        SkipSpaces(&string);


    }
    printf("I am GetT, RETURN string: <%s>\n", string);

    return number1;
}

value GetP() {

    SkipSpaces(&string);
    printf("I am GetP, i got such string: <%s>\n", string);
    if (*string == '(') {
        string++;
        printf("Calling GetE, current string: <%s>\n", string);
        value data = GetE();
        if (*string != ')') {
            printf("Close bracket is missed: %s\n", string);
            data.err_flag = 1;
        }
        else {
            string++;
        }
        SkipSpaces(&string);

        printf("I am GetP, RETURN string: <%s>\n", string);

        return data;
    }
    printf("I am GetP, RETURN string: <%s>\n", string);
    return GetN();
}

value GetN() {

    SkipSpaces(&string);
    printf("I am GetN, i got such string: <%s>\n", string);

    value ret_data   = {};
    int inside_cicle = 0;
    while ('0' <= *string && *string <= '9') {
        inside_cicle  = 1;
        ret_data.data = ret_data.data*10 + (*string - '0');
        string++;
    } 

    if (!inside_cicle) {
        ret_data.err_flag = 1;
    }
    SkipSpaces(&string);

    printf("I am GetN, i RETURN such string: <%s>\n", string);
    printf("ret value by GetN = %lg\n", ret_data.data);

    return ret_data;
}

void SkipSpaces(const char** string) {
    printf("String in SkipSpaces before: <%s>\n", *string);
    while (*string && isspace(**string)) {
        (*string)++;
    }
    printf("String in SkipSpaces after: <%s>\n", *string);

}
