#include <stdio.h>
#include <stdlib.h>
#include </home/martin/c_practice/ROTx/Header_Files/TerminalColors.h>



int Return_Error(char *error_message, int exit_status) {

    printf("%sError: %s%s\n", Kernel_FORE_RED, Kernel_FORE_WHITE, error_message);

    if (exit_status == 1) {
        abort();
    } else {
        ;
    }

}