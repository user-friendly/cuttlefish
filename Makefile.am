# 
# Root Makefile.
# 

ACLOCAL_AMFLAGS = -I m4-project

SUBDIRS = src

all: fishy
CLEANFILES = fishy

fishy:
	if [ ! -f fishy ]; then \
	    ln -s $(abs_top_builddir)/src/fishy fishy; \
    fi;
	if [ ! -d $(abs_top_builddir)/data ]; then \
		ln -s $(abs_top_srcdir)/data $(abs_top_builddir)/data; \
	fi;
