void mapEditorButtonResetPress()
{ mapEditorMap->reset(); }

std::vector<TwoConditionButton> mapEditorButtons;

void setMapEditorButtons()
{
	mapEditorButtons.push_back(TwoConditionButton(	mapEditorButtonResetPress, nothing, "reset", "fonts/mapEditorButtonsFont.otf",
													sf::Color(255, 196, 64), sf::Color(0, 0, 64), sf::Color(64, 64, 128),
													0.75, 0.05, 0.15, 0.08));
}
