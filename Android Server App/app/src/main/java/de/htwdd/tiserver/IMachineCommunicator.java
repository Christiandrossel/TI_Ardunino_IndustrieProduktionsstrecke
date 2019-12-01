package de.htwdd.tiserver;

/**
 * An interface for the communication between the different Bluetooth Clients
 */
public interface IMachineCommunicator {

    /**
     * Sets the specified Drill in Busy state
     * @param drill the Drill ID (1-3)
     */
    void setDrillBusy(int drill);

    /**
     * Sets the specified Drill in Free state
     * @param drill the Drill ID (1-3)
     */
    void setDrillFree(int drill);

    /**
     * @return returns the first free Drill
     */
    int getFreeDrill();
}
