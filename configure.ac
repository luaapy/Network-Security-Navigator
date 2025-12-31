AC_INIT([nsn], [1.0.0], [bugs@nsnlang.org])
AC_CONFIG_SRCDIR([Nsn/nsn.c])
AC_CONFIG_HEADERS([nsnconfig.h])

# Check for programs
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_MAKE_SET

# Check for libraries
AC_CHECK_LIB([pthread], [pthread_create])
AC_CHECK_LIB([m], [sqrt])
AC_CHECK_LIB([pcap], [pcap_open_live])
AC_CHECK_LIB([ssl], [SSL_library_init])
AC_CHECK_LIB([ssh], [ssh_connect])

# Check for headers
AC_CHECK_HEADERS([sys/socket.h netinet/in.h arpa/inet.h])
AC_CHECK_HEADERS([pcap.h openssl/ssl.h libssh/libssh.h])

# Output
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
