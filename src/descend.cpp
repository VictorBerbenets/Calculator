#include "..//descend.h"

const char* string = NULL;

typedef struct {
    const char func_name[MaxFuncSize];
    int func_id;
} FuncInfo;

enum FUNCTIONS {
    SIN = 0,
    COS = 1,
    TG  = 2,
    CTG = 3,
    SH  = 4,
    CH  = 5,
    TH  = 6,
    CTH = 7,
    ARCSIN = 8,
    ARCCOS = 9,
    ARCTG  = 10,
    ARCCTG = 11,
    EXP    = 12,
    LN     = 13,
};

FuncInfo Functions_[] = {{"sin", SIN}, {"cos", COS}, {"tg", TG}, {"ctg", CTG}, {"sh", SH}, {"ch", CH}, {"th", TH}, {"cth", CTH},
                            {"arcsin", ARCSIN}, {"arccos", ARCCOS}, {"arctg", ARCTG}, {"arcctg", ARCCTG}, {"exp", EXP}, {"ln", LN}};

int main (int argc, char** argv) {
    if (argc > 2) {
        printf("Too many file names, there can be only one:)\n");
        return -1;
    }    

    char* save_alloc_addr = GetData(argv[1]);
    string = save_alloc_addr;

    printf("( %s ) = %lg\n", save_alloc_addr, GetG());

    free(save_alloc_addr);
    return 0;
}

elem_t GetG() {

    SkipSpaces(&string);
    printf("I am GetG, i got such string: <%s>\n", string);
    if(!strlen(string)) {
        printf("String is empty\n");
        exit(EXIT_FAILURE);
    }
    value number = GetE();
    if (*string != '\0') {
        printf("Error: didn't get end simbol <%s>\n", string);
        exit(EXIT_FAILURE);
    }
    if (number.err_flag) {
        PrintError(number.err_flag);
        exit(number.err_flag);
    }
    return number.data;
}

value GetE() {

    SkipSpaces(&string);
    printf("I am GetE, i got such string: <%s>\n", string);

    value number1 = GetT();
    if (number1.err_flag) {
        return number1;
    }
    while (*string == '+' || *string == '-') {
        int save_symb = *string;
        string++;
        printf("Calling GetT, current string: <%s>\n", string);

        value number2 = GetT();
        if (number2.err_flag) {
            return number2;
        }
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

    value number1 = GetS();
    if (number1.err_flag) {
        return number1;
    }
    while (*string == '*' || *string == '/') {

        int save_symb = *string;
        string++;
        printf("Calling GetS, current string: <%s>\n", string);

        value number2 = GetS();
        if (number2.err_flag) {
            return number2;
        }
        if (save_symb == '*') {
            number1.data *= number2.data;
        }
        else {
            if (IsEqual(number2.data, 0)) {
                number1.err_flag = DIVISION_BY_ZERO;
                return number1;
            }
            number1.data /= number2.data;
        }
        SkipSpaces(&string);
    }
    printf("I am GetT, RETURN string: <%s>\n", string);

    return number1;
}

value  GetS() {

    SkipSpaces(&string);
    printf("I am GetS, i got such string: <%s>\n", string);

    value number1 = GetP();
    if (number1.err_flag) {
        return number1;
    }
    
    while (*string == '^') {

        int save_symb = *string;
        string++;
        printf("Calling GetP, current string: <%s>\n", string);

        value number2 = GetP();
        if (number2.err_flag) {
            return number2;
        }
        if (save_symb == '^') {
            number1.data = pow(number1.data, number2.data);
        }

        SkipSpaces(&string);
    }
    printf("I am GetS, RETURN string: <%s>\n", string);

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
            data.err_flag = MISSING_CLOSE_BRACKET;
        }
        else {
            string++;
        }
        SkipSpaces(&string);

        printf("I am GetP, RETURN string: <%s>\n", string);

        return data;
    }
    if (isdigit(*string)) {
        printf("I am GetP,I call GetN, RETURN string: <%s>\n", string);
        return GetN();
    }
    if (isalpha((*string))) {
        printf("I am GetP,I call GetF, RETURN string: <%s>\n", string);

        return GetF();
    }
}

value GetF() {
    char function_name[MaxFuncSize] = {};
    int symbol_counter = 0;
    for( ; isalpha(*string) && symbol_counter < 100; symbol_counter++) {
        function_name[symbol_counter] = *string;
        *string++;
    }
    value data = {};
    if (symbol_counter == MaxFuncSize) {
        data.err_flag = INVALID_FUNCTION_NAME_SIZE;
    }
    int func_id = GetFuncId(function_name);
    if (*string == '(') {
        string++;
        printf("Calling GetE, current string: <%s>\n", string);
        data = GetE();
        if (*string != ')') {
            printf("Close bracket is missed: %s\n", string);
            data.err_flag = MISSING_CLOSE_BRACKET;
        }
        else {
            string++;
        }
        SkipSpaces(&string);
        data.data = CalculateFunc(data.data, func_id);
        printf("I am GetP, RETURN string: <%s>\n", string);
        return data;
    }
    else {
        data.err_flag = INVALID_DATA;
        return  data;
    }
}

value GetN() {

    SkipSpaces(&string);
    printf("I am GetN, i got such string: <%s>\n", string);

    value ret_data   = {};
    int inside_cicle = 0;
    int is_nagative  = 0;

    if (*string == '-') {
        is_nagative = 1;
        string++;
    }
    if (*string == 'P') {
        ret_data.data = M_PI;
        string++;
        SkipSpaces(&string);
        return ret_data;
    }
    while (isdigit(*string)) { 
        inside_cicle  = 1;
        ret_data.data = ret_data.data*10 + (*string - '0');
        string++;
        //if floating point number
        if (*string == '.') {
            int divider = 10;
            string++;
            while(isdigit(*string)) {
                ret_data.data += (*string - '0') / (elem_t)divider;
                divider *= 10;
                string++;
            }
            break;
        }
    } 

    if (is_nagative) {
        ret_data.data *= -1;
    }
    if (!inside_cicle) {
        ret_data.err_flag = UNEXPECTED_SYMBOL;
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

int IsEqual(elem_t num1, elem_t num2) {
    const static elem_t Epsilon = 1e-17;
    return fabs(num1 - num2) <= Epsilon;
}

int GetFuncId(char* func_name) {
    for (int i = 0; i < sizeof(Functions_)/sizeof(Functions_[0]); i++) {
        if (!strcmp(func_name, Functions_[i].func_name)) {
            return Functions_[i].func_id;
        }
    }
    return -1;
}

elem_t CalculateFunc(elem_t value, int func_id) {
    switch(func_id) {
        case SIN:    return sin(value);
        case COS:    return cos(value);
        case TG :    return tan(value);
        case CTG:    return 1/tan(value);
        case ARCSIN: return asin(value);
        case ARCCOS: return acos(value);
        case ARCTG:  return atan(value);
        case ARCCTG: return M_PI/2 + atan(value);
        case SH:     return sinh(value);
        case CH:     return cosh(value);
        case TH:     return tanh(value);
        case CTH:    return 1/tanh(value);
        case EXP:    return exp(value);
        case LN:     return log(value);
        default : printf("Error func calculating\n");
    }
}

void PrintError(int err_id) {
    switch(err_id) {
        case MISSING_CLOSE_BRACKET:      printf("Missing close bracket: <%s>\n", string);                                   break;
        case DIVISION_BY_ZERO:           printf("Trying to divide by '0': <%s>\n", string);                                 break;
        case UNEXPECTED_SYMBOL:          printf("Unexpected symbol: <%s>\n", string);                                       break;
        case INVALID_DATA:               printf("Invalid data: <%s>\n", string);                                            break;
        case INVALID_FUNCTION_NAME_SIZE: printf("Invalid function name size, it must be <= %d: %s\n", MaxFuncSize, string); break;
        default: printf("invalid err_id: %d\n", err_id);
    }
}
