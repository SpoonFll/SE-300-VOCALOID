#include "HELPComponent.h"

HELPComponent::HELPComponent(): testButton("TEST")
{
    setSize (400, 600);

    testButton.onClick = [this] {
        if(MainWindow)
            MainWindow->broughtToFront();
        else
        {

        }
    };

    addAndMakeVisible(&testButton);
}

void HELPComponent::testButtonOnClick()
{

}

/**
 * paints the basic elements with the g graphics object
*/