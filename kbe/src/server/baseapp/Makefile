BIN  = baseapp
SRCS =						\
	archiver				\
	base					\
	baseapp					\
	baseapp_interface			\
	backup_sender				\
	forward_message_over_handler		\
	main					\
	proxy

ASMS =

MY_LIBS =		\
	server		\
	entitydef	\
	pyscript	\
	network		\
	thread
	

BUILD_TIME_FILE = main
USE_PYTHON = 1
USE_G3DMATH=1
	
ifndef USE_OPENSSL
	USE_OPENSSL = 0
endif

ifndef NO_USE_LOG4CXX
	NO_USE_LOG4CXX = 0
endif

CPPFLAGS += -DKBE_BASEAPP

#HAS_PCH = 1

ifndef KBE_ROOT
export KBE_ROOT := $(subst /kbe/src/server/$(BIN),,$(CURDIR))
endif

include $(KBE_ROOT)/kbe/src/build/common.mak

