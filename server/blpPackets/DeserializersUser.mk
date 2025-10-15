#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
BLPDESERIALIZERSUSER_OBJ_NAME=DeserializersUser
# component name
BLPDESERIALIZERSUSER_OBJ_PATH=$(BLPPACKETS_COMPONENT_FOLDER)
# include and source paths - no need to change
BLPDESERIALIZERSUSER_OBJ_INCLUDE_PATH=$(BLPDESERIALIZERSUSER_OBJ_PATH)/include
BLPDESERIALIZERSUSER_OBJ_SRC_PATH=$(BLPDESERIALIZERSUSER_OBJ_PATH)/src

# used includes
BLPDESERIALIZERSUSER_INCLUDES_PATHS=$(sort	-I$(BLPDESERIALIZERSUSER_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(BLPDESERIALIZERS_INCLUDES_PATHS))

BLPDESERIALIZERSUSER_INCLUDES=$(sort	$(BLPDESERIALIZERSUSER_OBJ_INCLUDE_PATH)/BLP_$(BLPDESERIALIZERSUSER_OBJ_NAME).h \
									$(BLPDESERIALIZERSUSER_OBJ_PATH)/$(BLPDESERIALIZERSUSER_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(BLPDESERIALIZERS_INCLUDES))

#------------------------------------------------------------------------------#
# no need to change anything below this line
BLPDESERIALIZERSUSER_SRC=$(BLPDESERIALIZERSUSER_OBJ_SRC_PATH)/$(BLPDESERIALIZERSUSER_OBJ_NAME).c
BLPDESERIALIZERSUSER_OUTPUT_FOLDER=$(BLPDESERIALIZERSUSER_OBJ_PATH)/bin
BLPDESERIALIZERSUSER_OBJ=$(BLPDESERIALIZERSUSER_OUTPUT_FOLDER)/$(BLPDESERIALIZERSUSER_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(BLPDESERIALIZERSUSER_OBJ): $(BLPDESERIALIZERSUSER_INCLUDES) $(BLPDESERIALIZERSUSER_SRC) $(BLPPACKETS_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(BLPDESERIALIZERSUSER_OBJ) $(BLPDESERIALIZERSUSER_INCLUDES_PATHS) $(BLPDESERIALIZERSUSER_SRC)
