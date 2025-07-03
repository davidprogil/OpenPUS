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
include $(DEVICEOPERATORS_COMPONENT_FOLDER)/PduOperator.mk

DEVICEOPERATORS_COMPONENT_INCLUDES_PATHS= \
						$(PDUOPERATOR_INCLUDES_PATHS) \


DEVICEOPERATORS_COMPONENT_INCLUDES=	$(DEVICEOPERATORS_COMPONENT_FOLDER)/$(DEVICEOPERATORS_COMPONENT_NAME).mk \
						$(PDUOPERATOR_INCLUDES) \


DEVICEOPERATORS_COMPONENT_OBJ= \
						$(PDUOPERATOR_OBJ) \

