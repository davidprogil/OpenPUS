#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
BLPVALIDATORS_OBJ_NAME=Validators
# component name
BLPVALIDATORS_OBJ_PATH=$(BLPPACKETS_COMPONENT_FOLDER)
# include and source paths - no need to change
BLPVALIDATORS_OBJ_INCLUDE_PATH=$(BLPVALIDATORS_OBJ_PATH)/include
BLPVALIDATORS_OBJ_SRC_PATH=$(BLPVALIDATORS_OBJ_PATH)/src

# used includes
BLPVALIDATORS_INCLUDES_PATHS=$(sort	-I$(BLPVALIDATORS_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(LIBRARY_COMPONENT_INCLUDES_PATHS))

BLPVALIDATORS_INCLUDES=$(sort	$(BLPVALIDATORS_OBJ_INCLUDE_PATH)/BLP_$(BLPVALIDATORS_OBJ_NAME).h \
									$(BLPVALIDATORS_OBJ_PATH)/$(BLPVALIDATORS_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(LIBRARY_COMPONENT_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
BLPVALIDATORS_SRC=$(BLPVALIDATORS_OBJ_SRC_PATH)/$(BLPVALIDATORS_OBJ_NAME).c
BLPVALIDATORS_OUTPUT_FOLDER=$(BLPVALIDATORS_OBJ_PATH)/bin
BLPVALIDATORS_OBJ=$(BLPVALIDATORS_OUTPUT_FOLDER)/$(BLPVALIDATORS_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(BLPVALIDATORS_OBJ): $(BLPVALIDATORS_INCLUDES) $(BLPVALIDATORS_SRC) $(BLPPACKETS_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(BLPVALIDATORS_OBJ) $(BLPVALIDATORS_INCLUDES_PATHS) $(BLPVALIDATORS_SRC)
