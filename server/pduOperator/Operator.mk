#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
OPERATOR_OBJ_NAME=Operator
# component name
OPERATOR_OBJ_PATH=$(PROJECT_PATH)/server/$(PDUOPERATOR_COMPONENT_NAME)
# include and source paths - no need to change
OPERATOR_OBJ_INCLUDE_PATH=$(OPERATOR_OBJ_PATH)/include
OPERATOR_OBJ_SRC_PATH=$(OPERATOR_OBJ_PATH)/src

# used includes
OPERATOR_INCLUDES_PATHS=$(sort	-I$(OPERATOR_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(ABSTRACTION_COMPONENT_INCLUDES_PATHS) \
									$(SWBUS_COMPONENT_INCLUDES_PATHS))

OPERATOR_INCLUDES=$(sort	$(OPERATOR_OBJ_INCLUDE_PATH)/APPX_$(OPERATOR_OBJ_NAME).h \
									$(OPERATOR_OBJ_PATH)/$(OPERATOR_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(ABSTRACTION_COMPONENT_INCLUDES)\
									$(SWBUS_COMPONENT_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
OPERATOR_SRC=$(OPERATOR_OBJ_SRC_PATH)/$(OPERATOR_OBJ_NAME).c
OPERATOR_OUTPUT_FOLDER=$(OPERATOR_OBJ_PATH)/bin
OPERATOR_OBJ=$(OPERATOR_OUTPUT_FOLDER)/$(OPERATOR_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(OPERATOR_OBJ): $(OPERATOR_INCLUDES) $(OPERATOR_SRC) $(OPERATOR_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(OPERATOR_OBJ) $(OPERATOR_INCLUDES_PATHS) $(OPERATOR_SRC)
