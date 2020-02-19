#include "ush.h"

int mx_exec(t_process *process, char *filename, char **argv, char **env) {
    t_list **list = mx_get_list_procs();
    int retval = 0;

    mx_disable_canon();
    process->command = mx_arr_to_str(argv);
    process->status = posix_spawn(&process->pid, filename,
                         &process->actions, &process->attrs, argv, env);
    if (waitpid(process->pid, &process->status, WUNTRACED) != -1) {
        if (MX_WIFSTOPPED(process->status)) {
            mx_push_back(list, process);
        }
    }
    if (waitpid(process->pid, &process->status, WUNTRACED) != -1)
        if (WIFSTOPPED(process->status))
            mx_push_back(list, process);
    if (retval != 126)
        retval = MX_WEXITSTATUS(process->status);
    mx_enable_canon();
    return retval;
}
