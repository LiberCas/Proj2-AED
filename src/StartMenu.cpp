// ****************************************************************************************************
// ****************************************** STAR_MENU_CPP__ *****************************************
// ****************************************************************************************************

#include "StartMenu.h"
#include "Menu.h"

StartMenu::StartMenu(Controller& controller) : Menu(controller) {
    mainOptions = {
            "Passenger",
            "Staff"
    };
}