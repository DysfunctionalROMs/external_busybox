/* vi: set sw=4 ts=4: */
/*
 * Busybox main internal header file
 *
 * Licensed under the GPL v2 or later, see the file LICENSE in this tarball.
 */
#ifndef	_BB_INTERNAL_H_
#define	_BB_INTERNAL_H_    1

#include "libbb.h"

/* order matters: used as index into "install_dir[]" in appletlib.c */
typedef enum bb_install_loc_t {
	_BB_DIR_ROOT = 0,
	_BB_DIR_BIN,
	_BB_DIR_SBIN,
	_BB_DIR_USR_BIN,
	_BB_DIR_USR_SBIN
} bb_install_loc_t;

typedef enum bb_suid_t {
	_BB_SUID_NEVER = 0,
	_BB_SUID_MAYBE,
	_BB_SUID_ALWAYS
} bb_suid_t;


/* Defined in appletlib.c (by including generated applet_tables.h) */
/* Keep in sync with applets/applet_tables.c! */
extern const char applet_names[];
extern int (*const applet_mains[])(int argc, char **argv);

#if ENABLE_FEATURE_INSTALLER || ENABLE_FEATURE_PREFER_APPLETS
extern const uint32_t applet_nameofs[];
#else
extern const uint16_t applet_nameofs[];
#endif

#if ENABLE_FEATURE_SUID
#define APPLET_NAME(i) (applet_names + (applet_nameofs[i] & 0x3fff))
#define APPLET_SUID(i) ((applet_nameofs[i] >> 14) & 0x3)
#else
#define APPLET_NAME(i) (applet_names + (applet_nameofs[i] & 0xffff))
#endif

#if ENABLE_FEATURE_INSTALLER
#define APPLET_INSTALL_LOC(i) ((applet_nameofs[i] >> 16) & 0x7)
#endif

#if ENABLE_FEATURE_PREFER_APPLETS
#define APPLET_IS_NOFORK(i) (applet_nameofs[i] & (1 << 19))
#define APPLET_IS_NOEXEC(i) (applet_nameofs[i] & (1 << 20))
#endif


/* Length of these names has effect on size of libbusybox
 * and "individual" binaries. Keep them short.
 */
void lbb_prepare(const char *applet, char **argv) MAIN_EXTERNALLY_VISIBLE;
#if ENABLE_BUILD_LIBBUSYBOX
#if ENABLE_FEATURE_SHARED_BUSYBOX
int lbb_main(int argc, char **argv) EXTERNALLY_VISIBLE;
#else
int lbb_main(int argc, char **argv);
#endif
#endif


#endif	/* _BB_INTERNAL_H_ */
