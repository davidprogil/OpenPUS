#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

#------------------------------------------------------------------------------#
# object name
PACKETSSERVICE1_OBJ_NAME=PacketsService1
# component name
PACKETSSERVICE1_OBJ_PATH=$(PROJECT_PATH)/server/$(PACKETS_COMPONENT_NAME)
# include and source paths - no need to change
PACKETSSERVICE1_OBJ_INCLUDE_PATH=$(PACKETSSERVICE1_OBJ_PATH)/include
PACKETSSERVICE1_OBJ_SRC_PATH=$(PACKETSSERVICE1_OBJ_PATH)/src

# used includes
PACKETSSERVICE1_INCLUDES_PATHS=$(sort	-I$(PACKETSSERVICE1_OBJ_INCLUDE_PATH) \
									$(COMMON_INCLUDES_PATHS) \
									$(SOMETHING_INCLUDES_PATHS))

PACKETSSERVICE1_INCLUDES=$(sort	$(PACKETSSERVICE1_OBJ_INCLUDE_PATH)/PKT_$(PACKETSSERVICE1_OBJ_NAME).h \
									$(PACKETSSERVICE1_OBJ_PATH)/$(PACKETSSERVICE1_OBJ_NAME).mk \
									$(COMMON_INCLUDES) \
									$(SOMETHING_INCLUDES))


#------------------------------------------------------------------------------#
# no need to change anything below this line
PACKETSSERVICE1_SRC=$(PACKETSSERVICE1_OBJ_SRC_PATH)/$(PACKETSSERVICE1_OBJ_NAME).c
PACKETSSERVICE1_OUTPUT_FOLDER=$(PACKETSSERVICE1_OBJ_PATH)/bin
PACKETSSERVICE1_OBJ=$(PACKETSSERVICE1_OUTPUT_FOLDER)/$(PACKETSSERVICE1_OBJ_NAME).o

#------------------------------------------------------------------------------#
# compile object
$(PACKETSSERVICE1_OBJ): $(PACKETSSERVICE1_INCLUDES) $(PACKETSSERVICE1_SRC) $(PACKETS_COMPONENT_OUTPUT_FOLDER)
	$(CC) $(CFLAGS) -o $(PACKETSSERVICE1_OBJ) $(PACKETSSERVICE1_INCLUDES_PATHS) $(PACKETSSERVICE1_SRC)
