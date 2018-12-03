List *chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog = NULL;
Message *chooseNewOrSavedMapToEditDialogWrongFileNameMessage = NULL;

#include "chooseNewOrSavedMapToEditDialogButtons.cpp"

void updateChooseNewOrSavedMapToEditDialogVariables()
{
	updateChooseNewOrSavedMapToEditDialogButtons();
	if (chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog)
		chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog->updatePositionAndSize();
	if (chooseNewOrSavedMapToEditDialogWrongFileNameMessage)
		chooseNewOrSavedMapToEditDialogWrongFileNameMessage->updatePositionAndSize();
}

void setChooseNewOrSavedMapToEditDialogVariables()
{
	chooseNewOrSavedMapToEditDialogSavedMapChooseFileDialog = NULL;
	setChooseNewOrSavedMapToEditDialogButtons();
}
