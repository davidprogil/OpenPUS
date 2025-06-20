#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
PUSUTILS_OBJ_NAME=PusUtils
# component name
PUSUTILS_OBJ_PATH=$(PROJECT_PATH)/server/$(LIBRARY_COMPONENT_NAME)
# include and source paths - no need to change
PUSUTILS_OBJ_INCLUDE_PATH=$(PUSUTILS_OBJ_PATH)/include
PUSUTILS_OBJ_SRC_PATH=$(PUSUTILS_OBJ_PATH)/src

# used includes
PUSUTILS_INCLUDES_PATHS=$(sort	-I$(PUSUTILS_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(SOMETHING_INCLUDES_PATHS))

PUSUTILS_INCLUDES=$(sort	$(PUSUTILS_OBJ_INCLUDE_PATH)/LIB_$(PUSUTILS_OBJ_NAME).h \
									$(PUSUTILS_OBJ_PATH)/$(PUSUTILS_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(SOMETHING_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
PUSUTILS_SRC=$(PUSUTILS_OBJ_SRC_PATH)/$(PUSUTILS_OBJ_NAME).c
PUSUTILS_OUTPUT_FOLDER=$(PUSUTILS_OBJ_PATH)/bin
PUSUTILS_OBJ=$(PUSUTILS_OUTPUT_FOLDER)/$(PUSUTILS_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(PUSUTILS_OBJ): $(PUSUTILS_INCLUDES) $(PUSUTILS_SRC) $(COMPONENTNAME_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(PUSUTILS_OBJ) $(PUSUTILS_INCLUDES_PATHS) $(PUSUTILS_SRC)
