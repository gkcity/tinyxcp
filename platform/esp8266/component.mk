#
# Component Makefile
#
COMPONENT_ADD_INCLUDEDIRS += tinyxcp/source/src/xcp-common \
                             tinyxcp/source/src/xcp-message \
                             tinyxcp/source/src/xcp-message-codec \
                             tinyxcp/source/src/xcp-websocket \
                             tinyxcp/source/src/xcp-webcmd

COMPONENT_SRCDIRS += tinyxcp/source/src/xcp-common 			\
		     tinyxcp/source/src/xcp-message 			\
		     tinyxcp/source/src/xcp-message/iq 			\
		     tinyxcp/source/src/xcp-message/iq/basic 		\
		     tinyxcp/source/src/xcp-message/handler 		\
		     tinyxcp/source/src/xcp-message-codec 		\
		     tinyxcp/source/src/xcp-message-codec/iq 		\
		     tinyxcp/source/src/xcp-message-codec/iq/basic 	\
		     tinyxcp/source/src/xcp-message-codec/xid 		\
		     tinyxcp/source/src/xcp-websocket 			\
		     tinyxcp/source/src/xcp-websocket/client 		\
		     tinyxcp/source/src/xcp-websocket/client/handler 	\
		     tinyxcp/source/src/xcp-websocket/client/verifier 	\
		     tinyxcp/source/src/xcp-websocket/server 		\
		     tinyxcp/source/src/xcp-websocket/server/handler 	\
		     tinyxcp/source/src/xcp-websocket/code-message 	\
		     tinyxcp/source/src/xcp-websocket/code-binary 	\
		     tinyxcp/source/src/xcp-webcmd 			\
		     tinyxcp/source/src/xcp-webcmd/server 		\
		     tinyxcp/source/src/xcp-webcmd/server/handler 	\
		     tinyxcp/source/src/xcp-webcmd/client

CFLAGS += -DTINY_STATIC \
          -DESP8266 \
	  -DLWIP_SOCKET \
	  -DICACHE_FLASH \
          -Wno-multichar \
          -Wno-pointer-to-int-cast \
          -fPIC \
          -std=gnu99
