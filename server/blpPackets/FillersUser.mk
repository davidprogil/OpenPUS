#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
BLPFILLERSUSER_OBJ_NAME=FillersUser
# component name
BLPFILLERSUSER_OBJ_PATH=$(BLPPACKETS_COMPONENT_FOLDER)
# include and source paths - no need to change
BLPFILLERSUSER_OBJ_INCLUDE_PATH=$(BLPFILLERSUSER_OBJ_PATH)/include
BLPFILLERSUSER_OBJ_SRC_PATH=$(BLPFILLERSUSER_OBJ_PATH)/src

# used includes
BLPFILLERSUSER_INCLUDES_PATHS=$(sort	-I$(BLPFILLERSUSER_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(BLPFILLERS_INCLUDES_PATHS))

BLPFILLERSUSER_INCLUDES=$(sort	$(BLPFILLERSUSER_OBJ_INCLUDE_PATH)/BLP_$(BLPFILLERSUSER_OBJ_NAME).h \
									$(BLPFILLERSUSER_OBJ_PATH)/$(BLPFILLERSUSER_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(BLPFILLERS_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
BLPFILLERSUSER_SRC=$(BLPFILLERSUSER_OBJ_SRC_PATH)/$(BLPFILLERSUSER_OBJ_NAME).c
BLPFILLERSUSER_OUTPUT_FOLDER=$(BLPFILLERSUSER_OBJ_PATH)/bin
BLPFILLERSUSER_OBJ=$(BLPFILLERSUSER_OUTPUT_FOLDER)/$(BLPFILLERSUSER_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(BLPFILLERSUSER_OBJ): $(BLPFILLERSUSER_INCLUDES) $(BLPFILLERSUSER_SRC) $(BLPPACKETS_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(BLPFILLERSUSER_OBJ) $(BLPFILLERSUSER_INCLUDES_PATHS) $(BLPFILLERSUSER_SRC)
