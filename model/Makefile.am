# GNU Automake config

# General compiler/linker flags
AM_CFLAGS = ${CFLAGS}
AM_FCFLAGS = ${FCFLAGS}
AM_LDFLAGS = ${LDFLAGS}

install:
	mkdir -p ${prefix}/model/i26
	cp -R ./cvms ${prefix}/model
	cp ./i26/* ${prefix}/model/i26
	chmod +x ${prefix}/model/cvms
	chmod +x ${prefix}/model/i26

