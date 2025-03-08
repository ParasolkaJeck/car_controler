#pragma once

#include <stdio.h>

#define syslog(__format,...) printf(__format"\t[%d]%s", __VA_ARGS__, __LINE__, "\r\n")

