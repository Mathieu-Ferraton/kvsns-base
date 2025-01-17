cmake_minimum_required(VERSION 2.6.3)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -g")

add_executable(kvsns_busybox kvsns_busybox.c)
target_link_libraries(kvsns_busybox kvsns)

add_executable(kvsns_cp kvsns_cp.c)
target_link_libraries(kvsns_cp kvsns)

add_custom_target(links DEPENDS kvsns_busybox)
add_custom_command(TARGET links
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_reset
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_init
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_mkdir
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_rmdir
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_creat
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_cd
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_ln
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_link
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_rm
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_rename
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_readlink
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_getattr
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_getxattr
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_setxattr
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_listxattr
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_removexattr
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_clearxattr
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_ls
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_fsstat
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_truncate
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_mr_proper
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_dump_manifest
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_cp
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_archive
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_restore
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_release
		   COMMAND /usr/bin/ln -sf kvsns_busybox ns_state
		   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		   VERBATIM)

