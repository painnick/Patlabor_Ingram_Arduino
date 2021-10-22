class Siren {
public:
    Siren(int pinNo, bool speedMode);
    void call(unsigned long mills);
private:
    int buzzerPinNo;
    int lastFreq;
    unsigned long lastMills;
    int loopIndex; // 0 : Inc, 1 : Dec
    bool speedMode;
    int toneDelay;
};
