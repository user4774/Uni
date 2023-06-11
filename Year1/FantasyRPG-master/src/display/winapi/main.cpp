#include "appWindow.h"

int main() {

    AppWindow app;

    if (app.init()) {
        // loads window in which game is run

        app.introWindow();
        

        while (app.isRunning()) {
            app.broadcast();
            
        }
    }



    return 0;
}
