#*******************************************************************************/
#* Copyright David Gil 1998-2025                                               */
#* 								                                               */
#* davidgil@dgadv.com 			                                               */
#*******************************************************************************/

PDUOPERATOR_COMPONENT_NAME=pduOperator
PDUOPERATOR_COMPONENT_FOLDER=$(PROJECT_PATH)/server/$(PDUOPERATOR_COMPONENT_NAME)
PDUOPERATOR_COMPONENT_OUTPUT_FOLDER=$(PDUOPERATOR_COMPONENT_FOLDER)/bin

$(PDUOPERATOR_COMPONENT_OUTPUT_FOLDER):
	mkdir -p $@

#objects includes -----------------
include $(PDUOPERATOR_COMPONENT_FOLDER)/Operator.mk

PDUOPERATOR_COMPONENT_INCLUDES_PATHS= \
						$(APPXMAIN_INCLUDES_PATHS) \


PDUOPERATOR_COMPONENT_INCLUDES=	$(PDUOPERATOR_COMPONENT_FOLDER)/$(PDUOPERATOR_COMPONENT_NAME).mk \
						$(APPXMAIN_INCLUDES) \


PDUOPERATOR_COMPONENT_OBJ= \
						$(APPXMAIN_OBJ) \

