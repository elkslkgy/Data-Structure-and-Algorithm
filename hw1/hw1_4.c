#include <stdio.h>
#include <string.h>
 
void read(char line[], char stack[], int* invalid);
int priority(char calculate);
void push(int stack_count[], int *top, int number);
int pop(int stack_count[], int *top);    
 
int main()
{
    long long int num;
    scanf("%lld", &num);
    char line[100001], stack[200002];
    int stack_count[100001];
    int i, j;
    int length, valid;
    int* invalid = &valid;
    for (i = 0; i < num; i++) {
        valid = 0;
        scanf("%s", line);
        length = strlen(line);
        if (line[length - 1] == '+' || line[length - 1] == '-' || line[length - 1] == '*' || line[length - 1] == '(') {
            printf("invalid\n");
            continue;
        }
        if (line[0] == '+' || line[0] == '-' || line[0] == '*' || line[0] == ')') {
            printf("invalid\n");
            continue;
        }
        read(line, stack, invalid);
        if (valid) {
            printf("invalid\n");
            continue;
        }
        long long int a_num;
        long long int a, b;
        long long int c;
        int top_point = 0;
        int *top = &top_point;
        int keylong = strlen(stack);
        for (j = 0; j < keylong; j++) {
            if (stack[j] == '*') {
                a = pop(stack_count, top);
                b = pop(stack_count, top);
                c = a * b;
                if (c >= 1000000007) {
                    c %= 1000000007;
                }
                push(stack_count, top, c);
            }
            else if (stack[j] == '+') {
                a = pop(stack_count, top);
                b = pop(stack_count, top);
                c = a + b;
                if (c >= 1000000007) {
                    c %= 1000000007;
                }
                push(stack_count, top, c);
            }
            else if (stack[j] == '-') {
                a = pop(stack_count, top);
                b = pop(stack_count, top);
                c = b - a;
                while (c < 0) {
                    c += 1000000007;
                }
                push(stack_count, top, c);
            }
            else {
                while (stack[j] != 'e') {
                    a_num = a_num * 10 + (stack[j] - 48);
                    j++;
                    if (a_num >= 1000000007) {
                        a_num %= 1000000007;
                    }
                }
                push(stack_count, top, a_num);
                a_num = 0;
            }
        }
        printf("%d\n", stack_count[0]);
    }
    return 0;
}
 
void read(char line[], char stack[], int* invalid) {
    int line_order, stack_order = 0, top = 0;
    char temp[100001] = {'\0'};
    for (line_order = 0; line[line_order] != '\0'; line_order++) {
        if (line[line_order] == '0') {
            line[line_order] = 'z';
        }
        switch (line[line_order]) {
           case '(':
               if (line[line_order + 1] == ')' || line[line_order + 1] == '+' || line[line_order + 1] == '-' || line[line_order + 1] == '*') {
                   *invalid = 1;
                   return;
               }
               if (line[line_order - 1] <= '9' && line[line_order - 1] >= '0') {
                    *invalid = 1;
                   return;
               }
               temp[top] = line[line_order];
               top++;
               break;
           case '*': case '+': case '-':
               if (line[line_order + 1] == '*' || line[line_order + 1] == '+' || line[line_order + 1] == '-') {
                   *invalid = 1;
                   return;
               }
               if (line[line_order - 1] >= 48 && line[line_order - 1] <= 57) {
                   stack[stack_order] = 'e';
                   stack_order++;
               }
               while (priority(temp[top - 1]) >= priority(line[line_order])) {
                   stack[stack_order] = temp[top - 1];
                   stack_order++;
                   top--;
               }
               temp[top] = line[line_order];
               top++;
               break;
           case ')':
               if (line[line_order - 1] >= 48 && line[line_order - 1] <= 57) {
                   stack[stack_order] = 'e';
                   stack_order++;
               }
               if ((line[line_order + 1] >= '0' && line[line_order + 1] <= '9') || line[line_order + 1] == '(' || line[line_order - 1] == '+'||line[line_order - 1] == '-'||line[line_order - 1] == '*') {
                   *invalid = 1;
                   return;
               }
               while (temp[top - 1] != '(' && top - 1 >= 0) {
                   stack[stack_order] = temp[top - 1];
                   stack_order++;
                   top--;
               }
               if (temp[top - 1] != '(' && top - 1 < 0) {
                   *invalid = 1;
                   return;
               }
               top--;
               break;
           default:
                if (line[line_order + 1] == '(') {
                    *invalid = 1;
                    return;
                }
                if (line[line_order] == 'z') {
                    line[line_order] = '0';
                    if ((line[line_order + 1] >= '0' && line[line_order + 1] <= '9') && !(line[line_order - 1] >= '0' && line[line_order - 1] <= '9')) {
                        *invalid = 1;
                        return;
                    }
                }
               stack[stack_order] = line[line_order];
               stack_order++;
               if (line[line_order + 1] == '\0') {
                       stack[stack_order] = 'e';
                       stack_order++;
               }
       }
    }
    while (top != 0) {
        if (temp[top - 1] == '(') {
            *invalid = 1;
            return;
        }
        stack[stack_order] = temp[top - 1];
        stack_order++;
        top--;
    }
    stack[stack_order] = 'e';
    stack[stack_order + 1] = '\0';
    return;
}
 
int priority(char calculate) {
    switch (calculate) {
        case '*':
            return 2;
        case '+': case '-':
            return 1;
    }
    return 0;
}
 
void push(int stack_count[], int *top, int number) {
    stack_count[*top] = number;
    (*top)++;
    return;
}
 
int pop(int stack_count[], int *top) {
    int result;
    result = stack_count[*top - 1];
    (*top)--;
    return result;
}