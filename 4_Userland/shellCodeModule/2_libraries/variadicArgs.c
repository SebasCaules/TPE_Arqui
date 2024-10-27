#include <variadicArgs.h>

// Initialize the argument list
void init_argument_list(ArgumentList *list) {
    list->count = 0;
}

Argument *arg_type(ArgumentList *list, ArgType type) {
    for (int i = 0; i < list->count; i++) {
        if (list->args[i].type == type) {
            return &list->args[i];
        }
    }
    return NULL;
}

void start_args_list(ArgumentList *list, const char *fmt, void *arg_ptr) {
    list->count = 0;  // Initialize argument count

    for (int i = 0; fmt[i] != '\0'; i++) {
        if (fmt[i] == '%' && list->count < 10) {  // Ensure within max argument count
            i++;
            switch (fmt[i]) {
                case 'd':  // Integer
                    list->args[list->count].type = INT_TYPE;
                    list->args[list->count].value.i_val = *((int *)arg_ptr);
                    arg_ptr = (void *)((int *)arg_ptr + 1);
                    list->count++;
                    break;
                case 'x':  // Hex integer
                    list->args[list->count].type = HEX_TYPE;
                    list->args[list->count].value.u_val = *((uint64_t *)arg_ptr);
                    arg_ptr = (void *)((uint64_t *)arg_ptr + 1);
                    list->count++;
                    break;
                case 'f':  // Float
                    list->args[list->count].type = FLOAT_TYPE;
                    list->args[list->count].value.f_val = *((float *)arg_ptr);
                    arg_ptr = (void *)((float *)arg_ptr + 1);
                    list->count++;
                    break;
                case 'g':  // Double
                    list->args[list->count].type = DOUBLE_TYPE;
                    list->args[list->count].value.d_val = *((double *)arg_ptr);
                    arg_ptr = (void *)((double *)arg_ptr + 1);
                    list->count++;
                    break;
                case 'c':  // Character
                    list->args[list->count].type = CHAR_TYPE;
                    list->args[list->count].value.c_val = *((char *)arg_ptr);
                    arg_ptr = (void *)((char *)arg_ptr + 1);
                    list->count++;
                    break;
                case 's':  // String
                    list->args[list->count].type = STR_TYPE;
                    list->args[list->count].value.s_val = *((char **)arg_ptr);
                    arg_ptr = (void *)((char **)arg_ptr + 1);
                    list->count++;
                    break;
                default:
                    break;
            }
        }
    }
}

// End function to reset or finalize the argument list
void end_args_list(ArgumentList *list) {
    // For now, this just resets the count; other cleanup could be added as needed
    list->count = 0;
}