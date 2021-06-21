#pragma once

static void errorExit(char* m, int status)
{
    printf("%s\n", m);
    exit(status);
}