#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
DEVICEMAIN_OBJ_NAME=DeviceMain
# component name
DEVICEMAIN_OBJ_PATH=$(PROJECT_PATH)/server/$(DEVICEOPERATORS_COMPONENT_NAME)
# include and source paths - no need to change
DEVICEMAIN_OBJ_INCLUDE_PATH=$(DEVICEMAIN_OBJ_PATH)/include
DEVICEMAIN_OBJ_SRC_PATH=$(DEVICEMAIN_OBJ_PATH)/src

# used includes
DEVICEMAIN_INCLUDES_PATHS=$(sort	-I$(DEVICEMAIN_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(ABSTRACTION_COMPONENT_INCLUDES_PATHS) \
									$(SWBUS_COMPONENT_INCLUDES_PATHS))

DEVICEMAIN_INCLUDES=$(sort	$(DEVICEMAIN_OBJ_INCLUDE_PATH)/DEV_$(DEVICEMAIN_OBJ_NAME).h \
									$(DEVICEMAIN_OBJ_PATH)/$(DEVICEMAIN_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(ABSTRACTION_COMPONENT_INCLUDES)\
									$(SWBUS_COMPONENT_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
DEVICEMAIN_SRC=$(DEVICEMAIN_OBJ_SRC_PATH)/$(DEVICEMAIN_OBJ_NAME).c
DEVICEMAIN_OUTPUT_FOLDER=$(DEVICEMAIN_OBJ_PATH)/bin
DEVICEMAIN_OBJ=$(DEVICEMAIN_OUTPUT_FOLDER)/$(DEVICEMAIN_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(DEVICEMAIN_OBJ): $(DEVICEMAIN_INCLUDES) $(DEVICEMAIN_SRC) $(DEVICEMAIN_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(DEVICEMAIN_OBJ) $(DEVICEMAIN_INCLUDES_PATHS) $(DEVICEMAIN_SRC)
