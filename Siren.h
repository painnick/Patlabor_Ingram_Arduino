class Siren {
public:
    Siren(int pinNo);
    void call(unsigned long mills);
private:
    int buzzerPinNo;
    int lastFreq;
    int lastDelay;
    unsigned long lastMills;
    int loopIndex; // 0 : Inc, 1 : Dec
};
