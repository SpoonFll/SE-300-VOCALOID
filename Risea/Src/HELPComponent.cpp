#include "HELPComponent.h"

HelpComponent::HelpComponent()  : testButton("test")
{
    setSize (400, 600);

    /*testButton.onClick = [this] {
        if(MainWindow)
            MainWindow->broughtToFront();
        else
        {

        }
    };*/

    addAndMakeVisible(&testButton);
}
HelpComponent::~HelpComponent() noexcept {

}

/**
 * paints the basic elements with the g graphics object
*/