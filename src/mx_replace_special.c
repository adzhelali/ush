#include "ush.h"

static char *replace_all_escape(char *arg);
// static char *replace_all_special(char *arg);

char *mx_replace_special(char *argument) {
    char *tmp_trim = mx_strtrim(argument);
    char *arg = mx_strnew(ARG_MAX);

    strcpy(arg, tmp_trim);
    arg = replace_all_escape(arg);
    // arg = replace_all_special(arg);
    // printf("arg = %s\n", arg);
    mx_strdel(&tmp_trim);
    return arg;
}

// static char *replace_all_special(char *arg) {
//     arg = mx_replace_env(arg);
//     return arg;
// }

static char *replace_all_escape(char *arg) {
    arg = mx_replace_escape(arg, "\\n", '\x0a', false);
    arg = mx_replace_escape(arg, "\\t", '\x09', false);
    arg = mx_replace_escape(arg, "\\v", '\x0b', false);
    arg = mx_replace_escape(arg, "\\a", '\x07', false);
    arg = mx_replace_escape(arg, "\\\"", '\"', true);
    arg = mx_replace_escape(arg, "\\ ", ' ', true);
    return arg;
}