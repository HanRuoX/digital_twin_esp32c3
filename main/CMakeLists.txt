
# set(COMPONENT_SRCS 
#         "websocket_task/websocket_task.c"
#     )
# set(COMPONENT_ADD_INCLUDEDIRS  "." "websocket_task" )

idf_component_register(SRCS "main.c"
                            "websocket_task/websocket_task.c"
                    INCLUDE_DIRS "."
                                 "websocket_task"
                    )