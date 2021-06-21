#pragma once

static void errorExit(const char* m, int status)
{
    printf("%s\n", m);
    exit(status);
}