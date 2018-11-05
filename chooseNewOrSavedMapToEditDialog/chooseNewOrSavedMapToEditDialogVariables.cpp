EnterFileNameDialog *chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog = NULL;
Message *chooseNewOrSavedMapToEditDialogWrongFileNameMessage = NULL;

#include "chooseNewOrSavedMapToEditDialogButtons.cpp"

void updateChooseNewOrSavedMapToEditDialogVariables()
{
	updateChooseNewOrSavedMapToEditDialogButtons();
	if (chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog)
		chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog->updatePositionAndSize();
	if (chooseNewOrSavedMapToEditDialogWrongFileNameMessage)
		chooseNewOrSavedMapToEditDialogWrongFileNameMessage->updatePositionAndSize();
}

void setChooseNewOrSavedMapToEditDialogVariables()
{
	chooseNewOrSavedMapToEditDialogSavedMapFileNameDialog = NULL;
	setChooseNewOrSavedMapToEditDialogButtons();
}
