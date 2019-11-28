package de.htwdd.tiserver;

public interface IMachineCommunicator {
    void setDrillBusy(int drill);
    void setDrillFree(int drill);
    int getFreeDrill();
}
