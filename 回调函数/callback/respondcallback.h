#ifndef RESPONDCALLBACK_H
#define RESPONDCALLBACK_H

class IButtonPressedCallback
{
public:
    virtual ~IButtonPressedCallback(){}
    virtual void onButtonPressed() = 0;
};

class RespondCallback: public IButtonPressedCallback
{
public:
    RespondCallback();
    ~RespondCallback();
private:
    virtual void onButtonPressed();
};

#endif // RESPONDCALLBACK_H
