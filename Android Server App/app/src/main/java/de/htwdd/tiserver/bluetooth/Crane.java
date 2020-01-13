package de.htwdd.tiserver.bluetooth;

import de.htwdd.tiserver.IMachineCommunicator;

public class Crane extends BluetoothClient {

    private final IMachineCommunicator _machineCommunicator;
    private Rodoter _currentRodoter;

    /**
     * Creates a new Kran which can communicate with the device
     *
     * @param macAddress the Mac for the Client
     * @param name       the Name of the Client which is returned with getName()
     */
    Crane(String macAddress, String name, IMachineCommunicator machineCommunicator) {
        super(macAddress, name);
        _machineCommunicator = machineCommunicator;
    }

    @Override
    void receivingThread(String input) {
        for (char c : input.toCharArray()) {
            if (c == 'r') {
                setFree();
            }
        }
    }

    public void setBusy(Rodoter rodoter) {
        _currentRodoter = rodoter;
        if (logger != null)
            logger.writeLog("\t" + _currentRodoter.getName() + " at the Crane");
    }

    public void setFree() {
        if (logger != null && _currentRodoter != null) {
            logger.writeLog("\t" + _currentRodoter.getName() + " freed from Crane");
            _currentRodoter.sendR();
            _currentRodoter = null;
        }
    }
}
