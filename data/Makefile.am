# GNU Automake config

# General compiler/linker flags
AM_CFLAGS = ${CFLAGS}
AM_FCFLAGS = ${FCFLAGS}
AM_LDFLAGS = ${LDFLAGS}

all:
if WITH_CVMSI_LARGEDATA_DIR
	echo "USING WITH_CVMSI_LARGEDATA_DIR in cvmsi"
else
	./make_data_files.py
endif

install:
if WITH_CVMSI_LARGEDATA_DIR
	if [ ! -d "${prefix}/data/i26" ]; then \
		$(MKDIR_P) ${prefix}/data; \
		$(LN_S) -f $(CVMSI_LARGEDATA_DIR) ${prefix}/data/i26; \
		echo "USING WITH_CVMSI_LARGEDATA_DIR in cvmsi"; \
	fi
	cp config ${prefix}/data
	cp -R cvms ${prefix}/data/cvms
else
	if [ ! -d "${prefix}/data/i26" ]; then \
		$(MKDIR_P) ${prefix}/data; \
		mv i26 ${prefix}/data; \
		$(LN_S) -f ${prefix}/data/i26 .; \
	fi
	cp config ${prefix}/data
	cp -R cvms ${prefix}/data/cvms
endif

clean:
	echo "clean"

