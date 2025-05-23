# Autoconf/automake file

bin_PROGRAMS = unittest accepttest accept_cvmsi unit_cvmsi

# General compiler/linker flags
AM_CFLAGS = ${CFLAGS} -DDYNAMIC_LIBRARY -Wall -g -std=c99 -D_LARGEFILE_SOURCE \
        -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -I../src -fPIC
AM_LDFLAGS = ${LDFLAGS} -L../src -lcvmsi -lm 
AM_FCFLAGS = ${FCFLAGS} -fPIC


# Dist sources
unittest_SOURCES = *.c *.h
accepttest_SOURCES = *.c *.h

TARGETS = $(bin_PROGRAMS)

.PHONY = run_unit run_accept

all: $(bin_PROGRAMS)

############################################
# Executables
############################################

unittest: unittest.o unittest_defs.o test_helper.o test_cvmsi_exec.o test_cvmsi_query_exec.o
	$(CC) -o $@ $^ $(AM_LDFLAGS)

run_unit: unittest
	./run_unit
	
accept_cvmsi$(EXEEXT): accept_cvmsi.o
	$(CC) -o $@ $^ $(AM_LDFLAGS)  

accepttest: accepttest.o unittest_defs.o test_helper.o test_grid_exec.o
	$(CC) -o $@ $^ $(AM_LDFLAGS)  

unit_cvmsi$(EXEEXT): unit_cvmsi.o
	$(CC) -o $@ $^ $(AM_LDFLAGS)  

run_accept: accepttest
	./run_accept

clean:
	rm -rf *.o $(bin_PROGRAMS)
	
install: all
	mkdir -p ${prefix}/test
	cp -R inputs ${prefix}/test
	cp -R ref ${prefix}/test
