#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
BLPDESERIALIZERS_OBJ_NAME=Deserializers
# component name
BLPDESERIALIZERS_OBJ_PATH=$(BLPPACKETS_COMPONENT_FOLDER)
# include and source paths - no need to change
BLPDESERIALIZERS_OBJ_INCLUDE_PATH=$(BLPDESERIALIZERS_OBJ_PATH)/include
BLPDESERIALIZERS_OBJ_SRC_PATH=$(BLPDESERIALIZERS_OBJ_PATH)/src

# used includes
BLPDESERIALIZERS_INCLUDES_PATHS=$(sort	-I$(BLPDESERIALIZERS_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(LIBRARY_COMPONENT_INCLUDES_PATHS))

BLPDESERIALIZERS_INCLUDES=$(sort	$(BLPDESERIALIZERS_OBJ_INCLUDE_PATH)/BLP_$(BLPDESERIALIZERS_OBJ_NAME).h \
									$(BLPDESERIALIZERS_OBJ_PATH)/$(BLPDESERIALIZERS_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(LIBRARY_COMPONENT_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
BLPDESERIALIZERS_SRC=$(BLPDESERIALIZERS_OBJ_SRC_PATH)/$(BLPDESERIALIZERS_OBJ_NAME).c
BLPDESERIALIZERS_OUTPUT_FOLDER=$(BLPDESERIALIZERS_OBJ_PATH)/bin
BLPDESERIALIZERS_OBJ=$(BLPDESERIALIZERS_OUTPUT_FOLDER)/$(BLPDESERIALIZERS_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(BLPDESERIALIZERS_OBJ): $(BLPDESERIALIZERS_INCLUDES) $(BLPDESERIALIZERS_SRC) $(BLPPACKETS_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(BLPDESERIALIZERS_OBJ) $(BLPDESERIALIZERS_INCLUDES_PATHS) $(BLPDESERIALIZERS_SRC)
