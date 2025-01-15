#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define RAND_LEN_MAX 10
#define RAND(x) (rand() % (x))

#define ITER_MAX      3

#define GEN_SPACE     putchar(' ')
#define GEN_LINEBREAK putchar('\n')

/*
  name ::= [a-zA-Z_][a-zA-Z0-9_]*
 */
void gen_name();

/*
  type ::= "int"
         | "float"
         | "char"
 */
void gen_type();

/*
  literal_value ::= [0-9]+
                  | [0-9]+ "." [0-9]+
 */
void gen_literal_value();

/*
  c_program ::= pre_process*
                function_definition*
 */
void gen_program();

/*
  pre_process ::= "#include" "<" name ".h" ">"
                | "#define" name expression
 */
void gen_pre_process();

/*
  function_definition ::= type name (lambda-list) { (expression ";")* }
 */
void gen_function_definition();

/*
  expression ::= name
               | literal_value
               | "(" expression ")"           # reorder computation
               | name "(" expression-list ")" # funcall
               | name "=" expression          # assignment
               | expression ( "+" | "-" | "*" | "/") expression # 2-op

 */
void gen_expression(size_t iter);

// =========== Main Entrance ===========

int main (int argc, char **argv)
{
  if (argc > 2) {
    // print help message if given wrong arg input
    printf("Usage: %s [seed]\n  seed should be random integer\n",
           argv[0]);
    return -1;
  }

  // random seed
  srand(argc == 2 ? atoi(argv[1]) : time(NULL));

  gen_program();

  return 0;
}

// =========== Implementation ===========

void gen_name ()
{
  switch(RAND(3)) {
  case 0: putchar('a' + RAND(26)); break; // a-z lowercase
  case 1: putchar('A' + RAND(26)); break; // A-Z uppercase
  case 2: putchar('_');            break; // _   underline
  default: break;
  }

  size_t star_cnt = RAND(RAND_LEN_MAX);
  for (size_t i = 0; i < star_cnt; i++)
    switch(RAND(4)) {
    case 0: putchar('a' + RAND(26)); break; // a-z lowercase
    case 1: putchar('A' + RAND(26)); break; // A-Z uppercase
    case 2: putchar('0' + RAND(10)); break; // 0-9 numbers
    case 3: putchar('_');            break; // _   underline
    default: break;
    }
}

void gen_type ()
{
  switch(RAND(3)) {
  case 0: printf("int");   break;
  case 1: printf("float"); break;
  case 2: printf("char");  break;
  default: break;
  }
}

void gen_literal_value ()
{
  switch(RAND(3)) {
  case 0:                       // integer
    for (size_t i = RAND(RAND_LEN_MAX); i > 0; i--)
      putchar('0' + RAND(10));
    break;
  case 1:                       // float
    for (size_t i = RAND(RAND_LEN_MAX); i > 0; i--)
      putchar('0' + RAND(10));
    putchar('.');
    for (size_t i = RAND(RAND_LEN_MAX); i > 0; i--)
      putchar('0' + RAND(10));
    break;
  case 2:                       // char
    putchar('\'');
    switch (RAND(3)) {
    case 0: putchar('a' + RAND(26)); break; /* a-z */
    case 1: putchar('A' + RAND(26)); break; /* A-Z */
    case 2:
      putchar('\\');
      switch (RAND(3)) {
      case 0: putchar('n'); break;    /* line break */
      case 1: putchar('t'); break;    /* tab */
      case 2: putchar('b'); break;    /* bell */
      default: break;
      }
    default: break;
    }
    putchar('\'');
    break;
  default: break;
  }
}

void gen_program ()
{
  size_t star_cnt = RAND(RAND_LEN_MAX);
  for (size_t i = 0; i < star_cnt; i++)
    gen_pre_process();

  for (size_t i = RAND(RAND_LEN_MAX); i > 0; i--) {
    gen_function_definition();
    GEN_LINEBREAK;
  }
}

void gen_pre_process ()
{
  switch (RAND(2)) {
  case 0:
    printf("#include");
    GEN_SPACE;
    printf("<"); gen_name(); printf(".h"); printf(">");
    GEN_LINEBREAK;
    break;
  case 1:
    printf("#define");
    GEN_SPACE;
    gen_name();
    GEN_SPACE;
    gen_expression(0);
    GEN_LINEBREAK;
    break;
  default: break;
  }
}

void gen_expression (size_t iter)
{
  if (iter > ITER_MAX) {
    switch (RAND(2)) {
    case 0: // name
      gen_name();
      break;
    case 1: // literal_value
      gen_literal_value();
      break;
    default: break;
    }
    return;
  }

  switch(RAND(6)) {
  case 0: // name
    gen_name();
    break;
  case 1: // literal_value
    gen_literal_value();
    break;
  case 2: // ( expression )
    putchar('(');
    GEN_SPACE;
    gen_expression(iter + 1);
    GEN_SPACE;
    putchar(')');
    break;
  case 3: // funcall
    gen_name();
    GEN_SPACE;
    putchar('(');
    GEN_SPACE;

    // generate lambda-list
    size_t i = RAND(RAND_LEN_MAX);
    for (; i > 1; i--) {
      gen_expression(iter + 1);
      putchar(',');
      GEN_SPACE;
    }
    if (i > 0) gen_expression(iter + 1);

    GEN_SPACE;
    putchar(')');
    break;
  case 4:
    gen_name();
    GEN_SPACE;
    putchar('=');
    GEN_SPACE;
    gen_expression(iter + 1);
    break;
  case 5:
    gen_expression(iter + 1);
    GEN_SPACE;

    switch(RAND(4)) {
    case 0: putchar('+'); break;
    case 1: putchar('-'); break;
    case 2: putchar('*'); break;
    case 3: putchar('/'); break;
    default: break;
    }

    GEN_SPACE;
    gen_expression(iter + 1);
    break;
  default: break;
  }
}

void gen_function_definition ()
{
  gen_type();
  GEN_SPACE;
  gen_name();
  putchar('(');

  // lambda list
  size_t i = RAND(RAND_LEN_MAX);
  for (; i > 1; i--) {
    gen_type();
    GEN_SPACE;
    gen_name();
    putchar(',');
    GEN_SPACE;
  }
  if (i > 0) {
    gen_type();
    GEN_SPACE;
    gen_name();
  }

  putchar(')');

  GEN_LINEBREAK;
  putchar('{');
  GEN_LINEBREAK;
  for (size_t i = RAND(RAND_LEN_MAX); i > 0; i--) {
    gen_expression(0);
    putchar(';');
    GEN_LINEBREAK;
  }
  putchar('}');
}
