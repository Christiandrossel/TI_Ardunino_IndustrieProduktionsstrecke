package de.htwdd.tiserver.bluetooth;

import android.bluetooth.BluetoothDevice;
import de.htwdd.tiserver.IMachineCommunicator;

public class Rodoter extends BluetoothClient {
    IMachineCommunicator _machineCom;

    /**
     * Creates a new Rodoter class which can communicate with the device
     *
     * @param device              the Bluetooth Device, created by the BluetoothCommunicator
     * @param machineCommunicator the MachineCommunicator for inter-machine-communication
     */
    Rodoter(BluetoothDevice device, IMachineCommunicator machineCommunicator) {
        super(device);
        _machineCom = machineCommunicator;
    }

    @Override
    void receivingThread(String input) {
        char c = input.toCharArray()[0];
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
