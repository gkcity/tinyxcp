#-------------------------------------------------------------------------------------
#
# TinyIOT
#
#-------------------------------------------------------------------------------------
ADD_SUBDIRECTORY(xcp-common)
ADD_SUBDIRECTORY(xcp-message)
ADD_SUBDIRECTORY(xcp-message-codec)
#ADD_SUBDIRECTORY(xcp-tcp)
ADD_SUBDIRECTORY(xcp-websocket)
#ADD_SUBDIRECTORY(sample_generic)
ADD_SUBDIRECTORY(sample_generic_ws)
#ADD_SUBDIRECTORY(sample_plc)
ADD_SUBDIRECTORY(sample_plc_local)
ADD_SUBDIRECTORY(sample_gateway_ws)

