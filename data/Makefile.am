# GNU Automake config

# General compiler/linker flags
AM_CFLAGS = ${CFLAGS}
AM_FCFLAGS = ${FCFLAGS}
AM_LDFLAGS = ${LDFLAGS}

install:
	mkdir -p ${prefix}/data
	cp -R ./cvms ${prefix}/data
	cp -R ./i26 ${prefix}/data
	cp ./config ${prefix}/data
	chmod +x ${prefix}/data/cvms
	chmod +x ${prefix}/data/i26

