#include "window.h"

class AppWindow : public Window {
private:

public:
    AppWindow();
    ~AppWindow();
    void OnPaint();
    void introWindow();

    virtual void onCreate() override;
    virtual void onUpdate() override;
    virtual void onDestroy() override;

};
