#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
PDU_OBJ_NAME=Pdu
# component name
PDU_OBJ_PATH=$(PROJECT_PATH)/server/$(DEVICEOPERATORS_COMPONENT_NAME)
# include and source paths - no need to change
PDU_OBJ_INCLUDE_PATH=$(PDU_OBJ_PATH)/include
PDU_OBJ_SRC_PATH=$(PDU_OBJ_PATH)/src

# used includes
PDU_INCLUDES_PATHS=$(sort	-I$(PDU_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(SOMETHING_INCLUDES_PATHS))

PDU_INCLUDES=$(sort	$(PDU_OBJ_INCLUDE_PATH)/DEV_$(PDU_OBJ_NAME).h \
									$(PDU_OBJ_PATH)/$(PDU_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(SOMETHING_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
PDU_SRC=$(PDU_OBJ_SRC_PATH)/$(PDU_OBJ_NAME).c
PDU_OUTPUT_FOLDER=$(PDU_OBJ_PATH)/bin
PDU_OBJ=$(PDU_OUTPUT_FOLDER)/$(PDU_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(PDU_OBJ): $(PDU_INCLUDES) $(PDU_SRC) $(COMPONENTNAME_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(PDU_OBJ) $(PDU_INCLUDES_PATHS) $(PDU_SRC)
