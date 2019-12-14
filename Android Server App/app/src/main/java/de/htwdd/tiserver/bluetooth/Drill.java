package de.htwdd.tiserver.bluetooth;

import android.bluetooth.BluetoothDevice;
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
        char c = input.charAt(0);
        if (c == 'r') {
            this.setFree();
        }
    }

    public boolean isFree() {
        return (_currentRodoter == null);
    }

    public void setBusy(Rodoter rodoter) {
        _currentRodoter = rodoter;
         this.sendData("b");
    }

    public void setFree() {
        if (_currentRodoter != null) {
            _currentRodoter.sendData("r");
            _currentRodoter = null;
        }
    }

    @Override
    void onConnectionChanged() {
        _machineCom.connectionChanged();
    }
}
