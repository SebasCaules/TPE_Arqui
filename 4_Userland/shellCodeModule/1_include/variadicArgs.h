#include <stddef.h>
#include <stdint.h>

#define MAX_ARGS 10

typedef enum {
	INT_TYPE = 0,
    HEX_TYPE,
    BIN_TYPE,
    OCT_TYPE,
	FLOAT_TYPE,
	DOUBLE_TYPE,
	CHAR_TYPE,
	STR_TYPE,
} ArgType;

typedef struct {
    ArgType type;
    union {
        int i_val;
        uint64_t u_val;
        double d_val;
        float f_val;
        char c_val;
        char *s_val;
    } value;
} Argument;

typedef struct {
    Argument args[10];  // Adjust size based on max expected arguments
    int count;
} ArgumentList;

void init_argument_list(ArgumentList *list);

void add_int_arg(ArgumentList *list, int value);

void add_double_arg(ArgumentList *list, double value);

void add_float_arg(ArgumentList *list, float value);

void add_char_arg(ArgumentList *list, char value);

void add_string_arg(ArgumentList *list, char *value);

Argument *arg_type(ArgumentList *list, ArgType type);
