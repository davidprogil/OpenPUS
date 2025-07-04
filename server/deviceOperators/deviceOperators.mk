#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

DEVICEOPERATORS_COMPONENT_NAME=deviceOperators
DEVICEOPERATORS_COMPONENT_FOLDER=$(PROJECT_PATH)/server/$(DEVICEOPERATORS_COMPONENT_NAME)
DEVICEOPERATORS_COMPONENT_OUTPUT_FOLDER=$(DEVICEOPERATORS_COMPONENT_FOLDER)/bin

$(DEVICEOPERATORS_COMPONENT_OUTPUT_FOLDER):
	mkdir -p $@

#objects includes -----------------
include $(DEVICEOPERATORS_COMPONENT_FOLDER)/DeviceMain.mk
include $(DEVICEOPERATORS_COMPONENT_FOLDER)/Pdu.mk

DEVICEOPERATORS_COMPONENT_INCLUDES_PATHS= \
						$(DEVICEMAIN_INCLUDES_PATHS) \
						$(PDU_INCLUDES_PATHS) \


DEVICEOPERATORS_COMPONENT_INCLUDES=	$(DEVICEOPERATORS_COMPONENT_FOLDER)/$(DEVICEOPERATORS_COMPONENT_NAME).mk \
						$(DEVICEMAIN_INCLUDES) \
						$(PDU_INCLUDES) \


DEVICEOPERATORS_COMPONENT_OBJ= \
						$(DEVICEMAIN_OBJ) \
						$(PDU_OBJ) \

