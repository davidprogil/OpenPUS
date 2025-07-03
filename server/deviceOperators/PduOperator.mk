#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
PDUOPERATOR_OBJ_NAME=PduOperator
# component name
PDUOPERATOR_OBJ_PATH=$(PROJECT_PATH)/server/$(DEVICEOPERATORS_COMPONENT_NAME)
# include and source paths - no need to change
PDUOPERATOR_OBJ_INCLUDE_PATH=$(PDUOPERATOR_OBJ_PATH)/include
PDUOPERATOR_OBJ_SRC_PATH=$(PDUOPERATOR_OBJ_PATH)/src

# used includes
PDUOPERATOR_INCLUDES_PATHS=$(sort	-I$(PDUOPERATOR_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(ABSTRACTION_COMPONENT_INCLUDES_PATHS) \
									$(SWBUS_COMPONENT_INCLUDES_PATHS))

PDUOPERATOR_INCLUDES=$(sort	$(PDUOPERATOR_OBJ_INCLUDE_PATH)/DEV_$(PDUOPERATOR_OBJ_NAME).h \
									$(PDUOPERATOR_OBJ_PATH)/$(PDUOPERATOR_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(ABSTRACTION_COMPONENT_INCLUDES)\
									$(SWBUS_COMPONENT_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
PDUOPERATOR_SRC=$(PDUOPERATOR_OBJ_SRC_PATH)/$(PDUOPERATOR_OBJ_NAME).c
PDUOPERATOR_OUTPUT_FOLDER=$(PDUOPERATOR_OBJ_PATH)/bin
PDUOPERATOR_OBJ=$(PDUOPERATOR_OUTPUT_FOLDER)/$(PDUOPERATOR_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(PDUOPERATOR_OBJ): $(PDUOPERATOR_INCLUDES) $(PDUOPERATOR_SRC) $(PDUOPERATOR_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(PDUOPERATOR_OBJ) $(PDUOPERATOR_INCLUDES_PATHS) $(PDUOPERATOR_SRC)
