#ifndef HUSKY_H
#define HUSKY_H

#include <stdio.h>
#include <iostream>

#define dp(fmt, args...) printf("--> %d %s @ %s: " fmt, __LINE__, __FUNCTION__, __FILE__, ##args)

#endif
