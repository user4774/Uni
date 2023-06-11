#ifndef QUITMENU_H
#define QUITMENU_H

#include "menu.h"

class QuitMenu : public Menu {
    public:
        QuitMenu();
        int selectOption();
        void init();
        void refresh();
};

#endif
