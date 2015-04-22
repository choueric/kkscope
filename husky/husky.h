#ifndef HUSKY_H
#define HUSKY_H

#include <stdio.h>
#include <iostream>
#include <QtDebug>

#define dp(fmt, args...) printf("--> %d %s @ %s: " fmt "\n", __LINE__, __FUNCTION__, __FILE__, ##args)

#endif
