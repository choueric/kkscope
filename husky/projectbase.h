#ifndef PROJECTBASE_H
#define PROJECTBASE_H

#include <QStringList.h>
#include <QDir.h>
#include <QFile.h>
#include <KConfig.h>

#define DEF_IS_KERNEL       false
#define DEF_INV_INDEX       true
#define DEF_NO_COMPRESS     false
#define DEF_SLOW_PATH       false
#define DEF_AC_MIN_CHARS    3
#define DEF_AC_DELAY        500
#define DEF_AC_MAX_ENTRIES  100
#define DEF_TAB_WIDTH       0 /* Use editor's default */
#define DEF_CTAGS_COMMAND   \
	"--regex-c=\"/^[ \\t]*([_a-zA-Z][_a-zA-Z0-9]*):/\\1/l,label/\" " \
	"--regex-c=\"/^[ \\t]*#[ \\t]*include[ \\t]*[\\\"<]" \
	"([_a-zA-Z0-9\\.\\/]*)[\\\">]/\\1/i,include/\" " \
	"--regex-c++=\"/^[ \\t]*#[ \\t]*include[ \\t]*[\\\"<]" \
	"([_a-zA-Z0-9\\.\\/]*)[\\\">]/\\1/i,include/\""

#endif
