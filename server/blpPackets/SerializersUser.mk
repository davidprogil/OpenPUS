#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
BLPSERIALIZERSUSER_OBJ_NAME=SerializersUser
# component name
BLPSERIALIZERSUSER_OBJ_PATH=$(BLPPACKETS_COMPONENT_FOLDER)
# include and source paths - no need to change
BLPSERIALIZERSUSER_OBJ_INCLUDE_PATH=$(BLPSERIALIZERSUSER_OBJ_PATH)/include
BLPSERIALIZERSUSER_OBJ_SRC_PATH=$(BLPSERIALIZERSUSER_OBJ_PATH)/src

# used includes
BLPSERIALIZERSUSER_INCLUDES_PATHS=$(sort	-I$(BLPSERIALIZERSUSER_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(BLPSERIALIZERS_INCLUDES_PATHS))

BLPSERIALIZERSUSER_INCLUDES=$(sort	$(BLPSERIALIZERSUSER_OBJ_INCLUDE_PATH)/BLP_$(BLPSERIALIZERSUSER_OBJ_NAME).h \
									$(BLPSERIALIZERSUSER_OBJ_PATH)/$(BLPSERIALIZERSUSER_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(BLPSERIALIZERS_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
BLPSERIALIZERSUSER_SRC=$(BLPSERIALIZERSUSER_OBJ_SRC_PATH)/$(BLPSERIALIZERSUSER_OBJ_NAME).c
BLPSERIALIZERSUSER_OUTPUT_FOLDER=$(BLPSERIALIZERSUSER_OBJ_PATH)/bin
BLPSERIALIZERSUSER_OBJ=$(BLPSERIALIZERSUSER_OUTPUT_FOLDER)/$(BLPSERIALIZERSUSER_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(BLPSERIALIZERSUSER_OBJ): $(BLPSERIALIZERSUSER_INCLUDES) $(BLPSERIALIZERSUSER_SRC) $(BLPPACKETS_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(BLPSERIALIZERSUSER_OBJ) $(BLPSERIALIZERSUSER_INCLUDES_PATHS) $(BLPSERIALIZERSUSER_SRC)
