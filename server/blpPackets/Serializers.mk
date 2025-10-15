#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
BLPSERIALIZERS_OBJ_NAME=Serializers
# component name
BLPSERIALIZERS_OBJ_PATH=$(BLPPACKETS_COMPONENT_FOLDER)
# include and source paths - no need to change
BLPSERIALIZERS_OBJ_INCLUDE_PATH=$(BLPSERIALIZERS_OBJ_PATH)/include
BLPSERIALIZERS_OBJ_SRC_PATH=$(BLPSERIALIZERS_OBJ_PATH)/src

# used includes
BLPSERIALIZERS_INCLUDES_PATHS=$(sort	-I$(BLPSERIALIZERS_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(LIBRARY_COMPONENT_INCLUDES_PATHS))

BLPSERIALIZERS_INCLUDES=$(sort	$(BLPSERIALIZERS_OBJ_INCLUDE_PATH)/BLP_$(BLPSERIALIZERS_OBJ_NAME).h \
									$(BLPSERIALIZERS_OBJ_PATH)/$(BLPSERIALIZERS_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(LIBRARY_COMPONENT_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
BLPSERIALIZERS_SRC=$(BLPSERIALIZERS_OBJ_SRC_PATH)/$(BLPSERIALIZERS_OBJ_NAME).c
BLPSERIALIZERS_OUTPUT_FOLDER=$(BLPSERIALIZERS_OBJ_PATH)/bin
BLPSERIALIZERS_OBJ=$(BLPSERIALIZERS_OUTPUT_FOLDER)/$(BLPSERIALIZERS_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(BLPSERIALIZERS_OBJ): $(BLPSERIALIZERS_INCLUDES) $(BLPSERIALIZERS_SRC) $(BLPPACKETS_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(BLPSERIALIZERS_OBJ) $(BLPSERIALIZERS_INCLUDES_PATHS) $(BLPSERIALIZERS_SRC)
