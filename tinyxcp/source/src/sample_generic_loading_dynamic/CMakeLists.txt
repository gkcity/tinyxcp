#-----------------------------------------------------------------------------
#
# sample_generic_loading_dynamic
#
#-----------------------------------------------------------------------------

SET(SRC
        handler/OnActionInvoke.h
        handler/OnActionInvoke.c
        handler/OnPropertyGet.h
        handler/OnPropertyGet.c
        handler/OnPropertySet.h
        handler/OnPropertySet.c
        print/PrintValue.h
        print/PrintValue.c
        iid/IID.h
        Runner.h
        Runner.c
        main.c
        )

ADD_EXECUTABLE(sample_generic_loading_dynamic ${SRC})
TARGET_LINK_LIBRARIES(sample_generic_loading_dynamic
        xcpws_static
        xcp_message_codec_static
        xcp_message_static
        xcp_common_static
        ${DEPENDENCE_LIB})
