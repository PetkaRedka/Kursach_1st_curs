#include <stdio.h>
#include <math.h>
#include <string.h>
#include <locale.h>

typedef struct stack3 {
	double bkvnum;
	char thisbkv;
	struct stack3 *next;
}stackbkv;

typedef struct stack2 {
	char thisznak;
	struct stack2 *next;
} stackchar;

typedef struct stack1 {
	double thisnum;
	struct stack1 *next;
} stack;

double peak(const stack *s) {
	return s->thisnum;
}

char peakchar(const stackchar *s) {
	if (!s) {
		return -1;
	}
	return prior(s->thisznak);
}

int getsize(stack *s) {
	int size = 0;
	while (s) {
		size++;
		s = s->next;
	}
	return size;
}

double found(stackbkv *s, char c) {
	while (s) {
		if (c == s->thisbkv) {
			return (s->bkvnum);
		}
		s = s->next;
	}
	return(-1);
}

char popbkv(stackbkv **s) {
	stackbkv *r;
	r = *s;
	char i = r->thisbkv;
	*s = (*s)->next;
	free(r);
	return i;
}

char popchar(stackchar **s) {
	stackchar *r;
	r = *s;
	char i = r->thisznak;
	*s = (*s)->next;
	free(r);
	return i;
}

void pushbkv(stackbkv **s, char item, double item1) {
	stackbkv *r = malloc(sizeof(stackbkv));
	r->thisbkv = item;
	r->bkvnum = item1;
	r->next = *s;
	*s = r;
}

void pushchar(stackchar **s, char item) {
	stackchar *r = malloc(sizeof(stackchar));
	r->thisznak = item;
	r->next = *s;
	*s = r;
}

double popnum(stack **s) { //снимает
	stack *r;
	r = *s;
	double i = r->thisnum;
	*s = (*s)->next;
	free(r);
	return i;
}

void pushnum(stack **s, double item) { //кладёт
	stack *r = malloc(sizeof(stack));
	r->thisnum = item;
	r->next = *s;
	*s = r;
}

int prior(int); //приоритет
void Input(void);
void math(void);
int oper(char);

stack *s = NULL;
stackchar *s2 = NULL;
stackbkv *s3 = NULL;
char oneChar = 0, stackChar = 0;
double kek1 = 0, kek2 = 0; //число и знак (1 и 2)
char c = 0, d ;
int decel = 0; //режим работы
int zpt = 0;
double bkv4 = 0;
char bkv = 0;
int skobo4ka0 = 0;
char matan[47];
char C = 0;

int main() {
    setlocale(LC_ALL, "russian_russia.1251");
	Input();
	getchar();
}

void Input() {
	printf("Введите сначала пременные и их значения, в конце поставьте ';'  (A = 5);\n");
	printf("Если таких нет, то поставьте просто ';'\n");
	while (c != '\t') {
		d = getchar();
		while (d != '\n') {
			if (((d >= 'A') && (d <= 'Z')) || ((d >= 'a') && (d <= 'z'))) {
				bkv = d;
			}
			if ((kek2 == 1) && (d >= '0') && (d <= '9') && (decel == 0)) {
				bkv4 = 10 * bkv4 + d - '0';
			}
			if (d == '.') {
				decel = 1;
			}
			if ((d >= '0') && (d <= '9') && (decel == 1) && (kek2 == 1)) {
				zpt++;
				bkv4 = bkv4 + (d - '0')*pow(10, -zpt);
			}
			if (d == '=') {
				kek2 = 1;
			}
			if (d == ';') {
				pushbkv(&s3, bkv, bkv4);
				bkv4 = 0;
				decel = 0;
				kek2 = 0;
			}
			d = getchar();
		}
		printf("Введите вашу строку и нажмите 'ENTER'\n");
		c = getchar();
		while (1) {
			int z = 0;
			if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z'))) {
				matan[0] = c;
				c = getchar();
				while (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z'))) {
					z++;
					matan[z] = c;
					c = getchar();
				}
				z++;
				matan[z] = '\0';
				if (strcmp(matan, "sin") == 0) {
					C = 's';
				}
				else if (strcmp(matan, "cos") == 0) {
					C = 'c';
				}
				else if (strcmp(matan, "tg") == 0) {
					C = 't';
				}
				else if (strcmp(matan, "ctg") == 0) {
					C = 'g';
				}
				else if (strcmp(matan, "ln") == 0) {
					C = 'l';
				}
				else {
					if (matan[1] == '\0') {
						printf("Корректно!\n");
						kek1 = found(s3, matan[0]);
					}
					else {
						printf("Не корректное выражение!\n");
						return ;
					}
				}
			}
			if ((c >= '0') && (c <= '9') && (decel == 0)) {
				kek1 = 10 * kek1 + c - '0';
			}
			if ((c >= '0') && (c <= '9') && (decel == 1)) {
				zpt++;
				kek1 = kek1 + (c - '0')*pow(10, -zpt);
			}
			if (c == '.') {
				decel = 1;
			}
			if (oper(c)) {
				pushnum(&s, kek1);
				if ((getsize(s) - skobo4ka0) >= 2) {
					if (prior(c) <= prior(peakchar(s2))) {
						stackChar = popchar(&s2);
						math();
					}
					if (c != '\n') {
						pushchar(&s2, c);
					}
				}
				else {
					pushchar(&s2, c);
				}
				decel = 0;
				kek1 = 0;
			}
			if (c == '\n') {
				pushnum(&s, kek1);
				while (s2) {
					stackChar = popchar(&s2);
					math();
				}
				break;
			}
			if (c == '(') {
				pushchar(&s2, c);
				if (C != 0) {
					pushchar(&s2, C);
					C = 0;
				}
				skobo4ka0 = getsize(s);
			}
			if (c == ')') {
				skobo4ka0 = 0;
				stackChar = popchar(&s2);
				pushnum(&s, kek1);
				decel = 0;
				kek1 = 0;
				while (stackChar != '(') {
					math();
					stackChar = popchar(&s2);
				}
				kek1 = peak(s);
			}
			c = getchar();
		}
        printf("\nВаш ответ: %.3f", peak(s));
		c = getchar();
	}
}

void math() {
	double a = popnum(&s), b=0;
	switch (stackChar) {
	case '+':
		b = popnum(&s);
		b = a + b;
		printf("\nВременно ответ: %.3f\n", b);
		pushnum(&s, b);
		break;
	case '-':
		b = popnum(&s);
		b = b - a;
		printf("\nВременно ответ: %.3f\n", b);
		pushnum(&s, b);
		break;
	case '*':
		b = popnum(&s);
		b = a * b;
		printf("\nВременно ответ: %.3f\n", b);
		pushnum(&s, b);
		break;
	case '/':
		b = popnum(&s);
		b = b / a;
		printf("\nВременно ответ: %.3f\n", b);
		pushnum(&s, b);
		break;
	case '^':
		b = popnum(&s);
		b = pow(b, a);
		printf("\nВременно ответ: %.3f\n", b);
		pushnum(&s, b);
		break;
	case's':
		b = sin(a);
		pushnum(&s, b);
		break;
	case'c':
		b = cos(a);
		pushnum(&s, b);
		break;
	case't':
		b = tan(a);
		pushnum(&s, b);
		break;
	case'g':
		b = 1/tan(a);
		pushnum(&s, b);
		break;
	case'l':
		b = log(a);
		pushnum(&s, b);
		break;
	default:
		;
	}
}

int prior(int c) {
	switch (c) {
	case '+':
		return 1;
	case '-':
		return 1;
	case '*':
		return 2;
	case '/':
		return 2;
	case '^':
		return 2;
	case '\n':
		return 0;
	default:
		;
	}
}

int oper(char c) {
	if ((c == '/') || (c == '+') || (c == '-') || (c == '*') || (c == '^') /*|| (c == '\n')*/) {
		return 1;
	}
	return 0;
}
