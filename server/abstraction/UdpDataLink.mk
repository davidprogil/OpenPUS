#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
UDPDATALINK_OBJ_NAME=UdpDataLink
# component name
UDPDATALINK_OBJ_PATH=$(PROJECT_PATH)/server/$(ABSTRACTION_COMPONENT_NAME)
# include and source paths - no need to change
UDPDATALINK_OBJ_INCLUDE_PATH=$(UDPDATALINK_OBJ_PATH)/include
UDPDATALINK_OBJ_SRC_PATH=$(UDPDATALINK_OBJ_PATH)/src

# used includes
UDPDATALINK_INCLUDES_PATHS=$(sort	-I$(UDPDATALINK_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(LIBRARY_COMPONENT_INCLUDES_PATHS))

UDPDATALINK_INCLUDES=$(sort	$(UDPDATALINK_OBJ_INCLUDE_PATH)/ABDL_$(UDPDATALINK_OBJ_NAME).h \
									$(UDPDATALINK_OBJ_PATH)/$(UDPDATALINK_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(LIBRARY_COMPONENT_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
UDPDATALINK_SRC=$(UDPDATALINK_OBJ_SRC_PATH)/$(UDPDATALINK_OBJ_NAME).c
UDPDATALINK_OUTPUT_FOLDER=$(UDPDATALINK_OBJ_PATH)/bin
UDPDATALINK_OBJ=$(UDPDATALINK_OUTPUT_FOLDER)/$(UDPDATALINK_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(UDPDATALINK_OBJ): $(UDPDATALINK_INCLUDES) $(UDPDATALINK_SRC) $(COMPONENTNAME_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(UDPDATALINK_OBJ) $(UDPDATALINK_INCLUDES_PATHS) $(UDPDATALINK_SRC)
