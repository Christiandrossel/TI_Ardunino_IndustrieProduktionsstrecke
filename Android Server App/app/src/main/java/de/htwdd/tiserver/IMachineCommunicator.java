package de.htwdd.tiserver;

import de.htwdd.tiserver.bluetooth.Rodoter;

/**
 * An interface for the communication between the different Bluetooth Clients
 */
public interface IMachineCommunicator {

    /**
     * Sets the specified Drill in Busy state
     * @param drillId the Drill ID (1-2)
     * @param client The Rodoter that uses the specified Drill
     */
    void setDrillBusy(int drillId, Rodoter client);

    /**
     * Sets the specified Drill in Free state
     * @param drillId the Drill ID (1-2)
     */
    void setDrillFree(int drillId);

    /**
     * @return returns the first free Drill
     */
    int getFreeDrillId();

    /**
     * Callback for when the Connection to the Device was Changed
     */
    void connectionChanged();

    /**
     * Sets the Crane Busy with the specified Rodoter
     */
    void setCraneBusy(Rodoter rodoter);
}
