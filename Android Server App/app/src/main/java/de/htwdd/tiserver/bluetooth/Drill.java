package de.htwdd.tiserver.bluetooth;

import android.bluetooth.BluetoothDevice;
import de.htwdd.tiserver.IMachineCommunicator;

public class Drill { // extends BluetoothClient {
    private Rodoter _currentRodoter;
    private IMachineCommunicator _machineCom;
    private final int _drillId;

    /**
     * Creates a new Rodoter class which can communicate with the device
     *
     * @param device              the Bluetooth Device, created by the BluetoothCommunicator
     * @param machineCommunicator the MachineCommunicator for inter-machine-communication
     */
    Drill(BluetoothDevice device, IMachineCommunicator machineCommunicator, int drillId) {
//        super(device);
        _machineCom = machineCommunicator;
        _drillId = drillId;
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
        // this.sendData("b");
    }

    public void setFree() {
        _currentRodoter.sendData("r");
        _currentRodoter = null;
    }

    public int getId() {
        return _drillId;
    }
}
