#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
BLPPRINTERSUSER_OBJ_NAME=PrintersUser
# component name
BLPPRINTERSUSER_OBJ_PATH=$(BLPPACKETS_COMPONENT_FOLDER)
# include and source paths - no need to change
BLPPRINTERSUSER_OBJ_INCLUDE_PATH=$(BLPPRINTERSUSER_OBJ_PATH)/include
BLPPRINTERSUSER_OBJ_SRC_PATH=$(BLPPRINTERSUSER_OBJ_PATH)/src

# used includes
BLPPRINTERSUSER_INCLUDES_PATHS=$(sort	-I$(BLPPRINTERSUSER_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(BLPPRINTERS_INCLUDES_PATHS))

BLPPRINTERSUSER_INCLUDES=$(sort	$(BLPPRINTERSUSER_OBJ_INCLUDE_PATH)/BLP_$(BLPPRINTERSUSER_OBJ_NAME).h \
									$(BLPPRINTERSUSER_OBJ_PATH)/$(BLPPRINTERSUSER_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(BLPPRINTERS_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
BLPPRINTERSUSER_SRC=$(BLPPRINTERSUSER_OBJ_SRC_PATH)/$(BLPPRINTERSUSER_OBJ_NAME).c
BLPPRINTERSUSER_OUTPUT_FOLDER=$(BLPPRINTERSUSER_OBJ_PATH)/bin
BLPPRINTERSUSER_OBJ=$(BLPPRINTERSUSER_OUTPUT_FOLDER)/$(BLPPRINTERSUSER_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(BLPPRINTERSUSER_OBJ): $(BLPPRINTERSUSER_INCLUDES) $(BLPPRINTERSUSER_SRC) $(BLPPACKETS_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(BLPPRINTERSUSER_OBJ) $(BLPPRINTERSUSER_INCLUDES_PATHS) $(BLPPRINTERSUSER_SRC)
