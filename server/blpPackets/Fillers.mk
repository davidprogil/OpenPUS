#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
BLPFILLERS_OBJ_NAME=Fillers
# component name
BLPFILLERS_OBJ_PATH=$(BLPPACKETS_COMPONENT_FOLDER)
# include and source paths - no need to change
BLPFILLERS_OBJ_INCLUDE_PATH=$(BLPFILLERS_OBJ_PATH)/include
BLPFILLERS_OBJ_SRC_PATH=$(BLPFILLERS_OBJ_PATH)/src

# used includes
BLPFILLERS_INCLUDES_PATHS=$(sort	-I$(BLPFILLERS_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(LIBRARY_COMPONENT_INCLUDES_PATHS))

BLPFILLERS_INCLUDES=$(sort	$(BLPFILLERS_OBJ_INCLUDE_PATH)/BLP_$(BLPFILLERS_OBJ_NAME).h \
									$(BLPFILLERS_OBJ_PATH)/$(BLPFILLERS_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(LIBRARY_COMPONENT_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
BLPFILLERS_SRC=$(BLPFILLERS_OBJ_SRC_PATH)/$(BLPFILLERS_OBJ_NAME).c
BLPFILLERS_OUTPUT_FOLDER=$(BLPFILLERS_OBJ_PATH)/bin
BLPFILLERS_OBJ=$(BLPFILLERS_OUTPUT_FOLDER)/$(BLPFILLERS_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(BLPFILLERS_OBJ): $(BLPFILLERS_INCLUDES) $(BLPFILLERS_SRC) $(BLPPACKETS_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(BLPFILLERS_OBJ) $(BLPFILLERS_INCLUDES_PATHS) $(BLPFILLERS_SRC)
