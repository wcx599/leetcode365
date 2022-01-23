#ifndef _EVAL_H
#define _EVAL_H

/* this horrible macro prints an expression and its value */
#define Eval(x) (printf("%3d: %s == %d\n", __LINE__, #x, (x)))

/* same thing but first argument gives format code */
#define EvalF(format, x) (printf("%3d: %s == %" #format " [%%%s]\n", __LINE__, #x, (x), #format))

#endif /* _EVAL_H */
