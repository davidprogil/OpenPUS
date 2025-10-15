#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
BLPVALIDATORSUSER_OBJ_NAME=ValidatorsUser
# component name
BLPVALIDATORSUSER_OBJ_PATH=$(BLPPACKETS_COMPONENT_FOLDER)
# include and source paths - no need to change
BLPVALIDATORSUSER_OBJ_INCLUDE_PATH=$(BLPVALIDATORSUSER_OBJ_PATH)/include
BLPVALIDATORSUSER_OBJ_SRC_PATH=$(BLPVALIDATORSUSER_OBJ_PATH)/src

# used includes
BLPVALIDATORSUSER_INCLUDES_PATHS=$(sort	-I$(BLPVALIDATORSUSER_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(BLPVALIDATORS_INCLUDES_PATHS))

BLPVALIDATORSUSER_INCLUDES=$(sort	$(BLPVALIDATORSUSER_OBJ_INCLUDE_PATH)/BLP_$(BLPVALIDATORSUSER_OBJ_NAME).h \
									$(BLPVALIDATORSUSER_OBJ_PATH)/$(BLPVALIDATORSUSER_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(BLPVALIDATORS_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
BLPVALIDATORSUSER_SRC=$(BLPVALIDATORSUSER_OBJ_SRC_PATH)/$(BLPVALIDATORSUSER_OBJ_NAME).c
BLPVALIDATORSUSER_OUTPUT_FOLDER=$(BLPVALIDATORSUSER_OBJ_PATH)/bin
BLPVALIDATORSUSER_OBJ=$(BLPVALIDATORSUSER_OUTPUT_FOLDER)/$(BLPVALIDATORSUSER_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(BLPVALIDATORSUSER_OBJ): $(BLPVALIDATORSUSER_INCLUDES) $(BLPVALIDATORSUSER_SRC) $(BLPPACKETS_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(BLPVALIDATORSUSER_OBJ) $(BLPVALIDATORSUSER_INCLUDES_PATHS) $(BLPVALIDATORSUSER_SRC)
