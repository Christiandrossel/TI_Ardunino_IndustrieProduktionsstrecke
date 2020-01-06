package de.htwdd.tiserver.bluetooth;

import de.htwdd.tiserver.IMachineCommunicator;

public class Rodoter extends BluetoothClient {
    private IMachineCommunicator _machineCom;

    /**
     * Creates a new Rodoter class which can communicate with the device
     *
     * @param macAddress the Mac for the Client
     * @param name the Name of the Client which is returned with getName()
     * @param machineCommunicator the MachineCommunicator for inter-machine-communication
     */
    Rodoter(String macAddress, String name, IMachineCommunicator machineCommunicator) {
        super(macAddress, name);
        _machineCom = machineCommunicator;
    }

    @Override
    void receivingThread(String input) {
        for (char c : input.toCharArray()) {
            switch (c) {
                case 'd':
                    sendData(_machineCom.getFreeDrillId() + "");
                    break;
                case '1':
                    _machineCom.setDrillBusy(1, this);
                    break;
                case '2':
                    _machineCom.setDrillBusy(2, this);
                    break;
                case 'r':
                    break;
            }
        }
    }

    @Override
    void onConnectionChanged() {
        _machineCom.connectionChanged();
    }

    public void sendR() {
        if (isConnected()) {
            sendData("r");
        }
    }
}
