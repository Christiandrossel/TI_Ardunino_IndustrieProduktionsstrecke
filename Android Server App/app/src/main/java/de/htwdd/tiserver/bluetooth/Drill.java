package de.htwdd.tiserver.bluetooth;

import de.htwdd.tiserver.IMachineCommunicator;

public class Drill extends BluetoothClient {
    private Rodoter _currentRodoter;
    private IMachineCommunicator _machineCom;

    /**
     * Creates a new Rodoter class which can communicate with the device
     *
     * @param macAddress the Mac for the Client
     * @param name the Name of the Client which is returned with getName()
     * @param machineCommunicator the MachineCommunicator for inter-machine-communication
     */
    Drill(String macAddress, String name, IMachineCommunicator machineCommunicator) {
        super(macAddress, name);
        _machineCom = machineCommunicator;
    }

    // @Override
    void receivingThread(String input) {
        for (char c : input.toCharArray()) {
            if (c == 'r') {
                this.setFree();
            }
        }
    }

    public boolean isFree() {
        return (_currentRodoter == null);
    }

    public void setBusy(Rodoter rodoter) {
        _currentRodoter = rodoter;
        this.sendData("b");
        if (logger != null)
            logger.writeLog("\t" + _currentRodoter.getName() + " at" + this.getName());
    }

    public void setFree() {
        _currentRodoter.sendData("r");
        if (logger != null)
            logger.writeLog("\t" + _currentRodoter.getName() + " freed from " + this.getName());
        _currentRodoter = null;
    }

    @Override
    void onConnectionChanged() {
        _machineCom.connectionChanged();
    }
}
