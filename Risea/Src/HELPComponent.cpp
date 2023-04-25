#include "HELPComponent.h"

HelpComponent::HelpComponent()  : testButton("Home"), button1("Text-To-Speech"), button2("Music Synthesis")
{
    setSize (400, 600);
    //this is for opening a new window dont need
    /*testButton.onClick = [this] {
        if(MainWindow)
            MainWindow->broughtToFront();
        else
        {

        }
    };*/



    button1.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    button1.setColour(juce::TextButton::textColourOnId, juce::Colours::black);
    button1.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    addAndMakeVisible(&button1);

    button2.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    button2.setColour(juce::TextButton::textColourOnId, juce::Colours::black);
    button2.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    addAndMakeVisible(&button2);

   // addAndMakeVisible(&testButton);

    textEditor1.setMultiLine(true);
    textEditor1.setReadOnly(true);
    textEditor1.setText("Usage: Start by inputting text; Select a voice; Lastly, press the Play/Pause button");
    textEditor1.setCaretVisible(false);
    addAndMakeVisible(&textEditor1);

    textEditor2.setMultiLine(true);
    textEditor2.setReadOnly(true);
    textEditor2.setText("Usage: Select intruments, select note/tempo; press play");
    textEditor2.setCaretVisible(false);
    addAndMakeVisible(&textEditor2);


}
HelpComponent::~HelpComponent() noexcept {

}
/**
 * paints the basic elements with the g Graphics object only prints welcome for now
 * @param g
 */
void HelpComponent::paint(juce::Graphics &g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText ("Help!", getLocalBounds(), juce::Justification::centredTop, true);
}
void HelpComponent::resized()
{
   // auto testButton = getLocalBounds();
  //  auto button1 = getLocalBounds();
  // auto button2 = getLocalBounds();

    //testButton.setBounds(260,110,80,40);
    button1.setBounds(130,200,160,80);
    button2.setBounds(310,200,160,80);

    textEditor1.setBounds(130,100,160,80);
    textEditor2.setBounds(310,100,160,80);

       // button1.setBounds(testButton);//sets size
      //  button2.setBounds(button1);
       // button3.setBounds(button2);

}

/**
 * paints the basic elements with the g graphics object
*/