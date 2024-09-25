#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char items[MAX];
    int top;
} Stack;

void initStack(Stack* s);
int isFull(Stack* s);
int isEmpty(Stack* s);
void push(Stack* s, char item);
char pop(Stack* s);
char peek(Stack* s);
int precedence(char operator);
int isOperator(char c);
void infixToPostfix(const char* infix, char* postfix);

void initStack(Stack* s) {
    s->top = -1;
}

int isFull(Stack* s) {
    return s->top == MAX - 1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, char item) {
    if (!isFull(s)) {
        s->items[++(s->top)] = item;
    }
}

char pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return '\0';
}

char peek(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    }
    return '\0';
}

int precedence(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

void infixToPostfix(const char* infix, char* postfix) {
    Stack s;
    initStack(&s);
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char current = infix[i];

        if (isalnum(current)) {
            postfix[j++] = current;
        } else if (current == '(') {
            push(&s, current);
        } else if (current == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
            }
            pop(&s);
        } else if (isOperator(current)) {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(current)) {
                postfix[j++] = pop(&s);
            }
            push(&s, current);
        }
    }

    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }
    postfix[j] = '\0';
}

int main() {
    printf("Asmit's(1AY23CS044) Program!\n\n");
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    fgets(infix, MAX, stdin);
    infix[strcspn(infix, "\n")] = 0;

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    return 0;
}
