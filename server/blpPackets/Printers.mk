#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
BLPPRINTERS_OBJ_NAME=Printers
# component name
BLPPRINTERS_OBJ_PATH=$(BLPPACKETS_COMPONENT_FOLDER)
# include and source paths - no need to change
BLPPRINTERS_OBJ_INCLUDE_PATH=$(BLPPRINTERS_OBJ_PATH)/include
BLPPRINTERS_OBJ_SRC_PATH=$(BLPPRINTERS_OBJ_PATH)/src

# used includes
BLPPRINTERS_INCLUDES_PATHS=$(sort	-I$(BLPPRINTERS_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(LIBRARY_COMPONENT_INCLUDES_PATHS))

BLPPRINTERS_INCLUDES=$(sort	$(BLPPRINTERS_OBJ_INCLUDE_PATH)/BLP_$(BLPPRINTERS_OBJ_NAME).h \
									$(BLPPRINTERS_OBJ_PATH)/$(BLPPRINTERS_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(LIBRARY_COMPONENT_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
BLPPRINTERS_SRC=$(BLPPRINTERS_OBJ_SRC_PATH)/$(BLPPRINTERS_OBJ_NAME).c
BLPPRINTERS_OUTPUT_FOLDER=$(BLPPRINTERS_OBJ_PATH)/bin
BLPPRINTERS_OBJ=$(BLPPRINTERS_OUTPUT_FOLDER)/$(BLPPRINTERS_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(BLPPRINTERS_OBJ): $(BLPPRINTERS_INCLUDES) $(BLPPRINTERS_SRC) $(BLPPACKETS_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(BLPPRINTERS_OBJ) $(BLPPRINTERS_INCLUDES_PATHS) $(BLPPRINTERS_SRC)
