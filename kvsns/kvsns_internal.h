/*
 * vim:noexpandtab:shiftwidth=8:tabstop=8:
 *
 * Copyright (C) CEA, 2016
 * Author: Philippe Deniel  philippe.deniel@cea.fr
 *
 * contributeur : Philippe DENIEL   philippe.deniel@cea.fr
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 * -------------
 */

/* kvsns_internal.h.c
 * KVSNS: headers for internal functions and macros
 */

#ifndef KVSNS_INTERNAL_H
#define KVSNS_INTERNAL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <ini_config.h>
#include <iosea/kvsns.h>
#include <iosea/extstore.h>
#include <string.h>
#include <syslog.h>

#define LogCrit(fmt, ...)   syslog(LOG_CRIT, (fmt), ## __VA_ARGS__)
#define LogMajor(fmt, ...)  syslog(LOG_WARNING, (fmt), ##__VA_ARGS__)
#define LogEvent(fmt, ...)  syslog(LOG_NOTICE, fmt, ## __VA_ARGS__)
#define LogVerb(fmt, ...)   syslog(LOG_INFO, fmt, ## __VA_ARGS__)
#define LogDebug(fmt, ...)  syslog(LOG_DEBUG, fmt, ## __VA_ARGS__)

#define RC_WRAP(__function, ...) ({\
	int __rc = __function(__VA_ARGS__);\
	syslog(LOG_DEBUG, "Call to %s rc=%d", #__function, __rc); \
	if (__rc != 0) {	\
		syslog(LOG_INFO, "Call to %s failed, rc=%d", \
			#__function, __rc); \
		return __rc; } })

#define RC_WRAP_LABEL(__rc, __label, __function, ...) ({\
	__rc = __function(__VA_ARGS__);\
	syslog(LOG_DEBUG, "Call to %s rc=%d", #__function, __rc); \
	if (__rc != 0) {       \
		syslog(LOG_INFO, "Call to %s failed, rc=%d", \
			#__function, __rc); \
		goto __label; }  })


int kvsns_next_inode(kvsns_ino_t *ino);
int kvsns_str2parentlist(kvsns_ino_t *inolist, int *size, char *str);
int kvsns_parentlist2str(kvsns_ino_t *inolist, int size, char *str);
int kvsns_create_entry(kvsns_cred_t *cred, kvsns_ino_t *parent,
		       char *name, char *lnk, mode_t mode,
		       kvsns_ino_t *new_entry, enum kvsns_type type,
		       extstore_id_t *eid,
		       int (*nof)(extstore_id_t *, unsigned int, char *));
int kvsns_get_stat(kvsns_ino_t *ino, struct stat *bufstat);
int kvsns_set_stat(kvsns_ino_t *ino, struct stat *bufstat);
int kvsns_update_stat(kvsns_ino_t *ino, int flags);
int kvsns_amend_stat(struct stat *stat, int flags);
int kvsns_delall_xattr(kvsns_cred_t *cred, kvsns_ino_t *ino);
int kvsns_get_objectid(kvsns_ino_t *ino,
		       extstore_id_t *eid);



#endif
