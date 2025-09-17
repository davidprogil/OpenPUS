#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

PACKETS_COMPONENT_NAME=packets
PACKETS_COMPONENT_FOLDER=$(PROJECT_PATH)/server/$(PACKETS_COMPONENT_NAME)
PACKETS_COMPONENT_OUTPUT_FOLDER=$(PACKETS_COMPONENT_FOLDER)/bin

$(PACKETS_COMPONENT_OUTPUT_FOLDER):
	mkdir -p $@

#objects includes -----------------
include $(PACKETS_COMPONENT_FOLDER)/PacketsService1.mk

PACKETS_COMPONENT_INCLUDES_PATHS= \
						$(PACKETSSERVICE1_INCLUDES_PATHS) \


PACKETS_COMPONENT_INCLUDES=	$(PACKETS_COMPONENT_FOLDER)/$(PACKETS_COMPONENT_NAME).mk \
						$(PACKETSSERVICE1_INCLUDES) \


PACKETS_COMPONENT_OBJ= \
						$(PACKETSSERVICE1_OBJ) \

