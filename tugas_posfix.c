#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Struktur Stack
typedef struct {
    int top;
    char items[MAX_SIZE];
} Stack;

// Fungsi untuk inisialisasi stack
void initializeStack(Stack *s) {
    s->top = -1;
}

// Fungsi untuk mengecek apakah stack penuh
int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

// Fungsi untuk mengecek apakah stack kosong
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Fungsi untuk menambahkan elemen ke stack (push)
void push(Stack *s, char value) {
    if (isFull(s)) {
        printf("Stack penuh!\n");
        return;
    }
    s->items[++(s->top)] = value;
}

// Fungsi untuk menghapus elemen dari stack (pop)
char pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack kosong!\n");
        return '\0';
    }
    return s->items[(s->top)--];
}

// Fungsi untuk melihat elemen teratas stack (peek)
char peek(Stack *s) {
    if (isEmpty(s)) {
        return '\0';
    }
    return s->items[s->top];
}

// Fungsi untuk menentukan prioritas operator
int precedence(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// Fungsi untuk mengkonversi infix ke postfix
void infixToPostfix(char *infix, char *postfix) {
    Stack s;
    initializeStack(&s);
    int i, j = 0;

    for (i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isalnum(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            push(&s, ch);
        } else if (ch == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
            }
            pop(&s); // Pop '(' dari stack
        } else {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(ch)) {
                postfix[j++] = pop(&s);
            }
            push(&s, ch);
        }
    }

    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }

    postfix[j] = '\0';
}

// Fungsi untuk mengkonversi postfix ke infix
void postfixToInfix(char *postfix, char *infix) {
    Stack s;
    initializeStack(&s);
    int i, j = 0;

    for (i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        if (isalnum(ch)) {
            char temp[2] = {ch, '\0'};
            push(&s, temp);
        } else {
            char operand2[MAX_SIZE], operand1[MAX_SIZE];
            strcpy(operand2, pop(&s));
            strcpy(operand1, pop(&s));

            char temp[MAX_SIZE];
            sprintf(temp, "(%s%c%s)", operand1, ch, operand2);
            push(&s, temp);
        }
    }

    strcpy(infix, pop(&s));
}

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE], convertedInfix[MAX_SIZE];

    // Contoh konversi infix ke postfix
    printf("Masukkan ekspresi infix: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("Ekspresi postfix: %s\n", postfix);

    // Contoh konversi postfix ke infix
    printf("Masukkan ekspresi postfix: ");
    scanf("%s", postfix);
    postfixToInfix(postfix, convertedInfix);
    printf("Ekspresi infix: %s\n", convertedInfix);

    return 0;
}
