/////////////////////////////////////////////////////////////////////////////
/*
This file is part of Topiary, Copyright Tom Tollenaere 2018-19.

Topiary is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Topiary is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Topiary. If not, see <https://www.gnu.org/licenses/>.
*/
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "TopiaryVariationButtonsComponent.h"

TopiaryVariationButtonsComponent::TopiaryVariationButtonsComponent()
{
	setSize(width, height);

	variationButton[0] = &button0;
	variationButton[1] = &button1;
	variationButton[2] = &button2;
	variationButton[3] = &button3;
	variationButton[4] = &button4;
	variationButton[5] = &button5;
	variationButton[6] = &button6;
	variationButton[7] = &button7;
	for (int i = 0; i < 8; i++) {
		variationButton[i]->setButtonText(String(i+1));
		variationButton[i]->setSize(buttonWidth, buttonHeight);
		variationButton[i]->setClickingTogglesState(true);
		variationButton[i]->setRadioGroupId(Topiary::VariationButtonIds::VariationButtons);
		variationButton[i]->setLookAndFeel(&topiaryLookAndFeel);
		addAndMakeVisible(*variationButton[i]);
	}
	variationButton[0]->onClick = [this] { updateToggleState(variationButton[0]); };
	variationButton[1]->onClick = [this] { updateToggleState(variationButton[1]); };
	variationButton[2]->onClick = [this] { updateToggleState(variationButton[2]); };
	variationButton[3]->onClick = [this] { updateToggleState(variationButton[3]); };
	variationButton[4]->onClick = [this] { updateToggleState(variationButton[4]); };
	variationButton[5]->onClick = [this] { updateToggleState(variationButton[5]); };
	variationButton[6]->onClick = [this] { updateToggleState(variationButton[6]); };
	variationButton[7]->onClick = [this] { updateToggleState(variationButton[7]); };
	
} // TopiaryVariationButtonsComponent()

/////////////////////////////////////////////////////////////////////////

TopiaryVariationButtonsComponent::~TopiaryVariationButtonsComponent()
{
} //~TopiaryVariationButtonsComponent
 
/////////////////////////////////////////////////////////////////////////

void TopiaryVariationButtonsComponent::resized()
{
} // resized

/////////////////////////////////////////////////////////////////////////

void TopiaryVariationButtonsComponent::updateToggleState(TextButton* button)
{   
	// Virtual method; need a version with a model to function properly!!!
	UNUSED(button)

} // updateToggleState

/////////////////////////////////////////////////////////////////////////

void TopiaryVariationButtonsComponent::paint(Graphics& g) {
	// size = 340 * 45
	int w = width; 
	int h = height; 
	int linesize = 2;
	int labeloffset = 15;
	int buttonoffsety = labeloffset+5;
	int buttonoffsetx = linesize + 5;
	int buttonseparator = 4;

	g.fillAll(TopiaryColour::background);
	//g.fillAll(Colours::antiquewhite);
	g.setColour(TopiaryColour::foreground);
	g.setFont(12.0f);
	g.drawText("Variations", 0, 0, 200, labeloffset, juce::Justification::centredLeft);
	g.drawRoundedRectangle((float) linesize, (float) labeloffset, (float) w-2*linesize-2, (float) h-labeloffset-2*linesize, (float) 4, (float) linesize);
	
	for (int i = 0; i < 8; i++) {
		variationButton[i]->setBounds(buttonoffsetx, buttonoffsety, buttonWidth, buttonHeight);
		buttonoffsetx = buttonoffsetx + buttonWidth + buttonseparator;
	}

} // paint

/////////////////////////////////////////////////////////////////////////////////////

void TopiaryVariationButtonsComponent::selectButton(int running, int selected)
{  
	jassert((selected >= 0) && (selected < 8));
	jassert((running >= 0) && (running < 8));

	// set button i (1 to 8) - don't do more; only be be called by derived object that does not have access to the buttons
	// always set to running; in case selected <> running the caller passes selected into the running variable and vice versa - so this method knows these are different (saves an if statement)
	if (running == selected)
		variationButton[running]->specialState = 0;
	else 
		variationButton[running]->specialState = Topiary::waitToApply;
	variationButton[running]->setToggleState(false, dontSendNotification); // force repaint
	variationButton[running]->setToggleState(true, dontSendNotification);  // probably called because the model changed!

} //selectButton

/////////////////////////////////////////////////////////////////////////////////////

void TopiaryVariationButtonsComponent::enableButton(int i, bool enable)
{
	variationButton[i]->setEnabled(enable);

} // enableButton

/////////////////////////////////////////////////////////////////////////////////////