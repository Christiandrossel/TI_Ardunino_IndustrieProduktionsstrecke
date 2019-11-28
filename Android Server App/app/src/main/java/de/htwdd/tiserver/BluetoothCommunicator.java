package de.htwdd.tiserver;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

public class BluetoothCommunicator implements IMachineCommunicator {

    private static final String TAG = "BtCommunicator";
    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    private static final String[] XBEE_MAC_ADRESSES = {"98:D3:41:FD:54:C3"};

    private BluetoothAdapter btAdapter;
    private List<BluetoothClient> _clients;

    private boolean[] drillArray = { false, false, false, false } ;

    BluetoothCommunicator() {
        btAdapter = BluetoothAdapter.getDefaultAdapter();
        _clients = new ArrayList<>();
    }

    boolean isReady() {
        return (btAdapter!=null && btAdapter.isEnabled());
    }

    void connect() {
        if (btAdapter == null)
            return;

        if(_clients.size() != XBEE_MAC_ADRESSES.length) {
            _connectToAllDevices();
        } else {
            for (BluetoothClient client : _clients) {
                client.connect();
            }
        }
    }

    void disconnect() {
        for (BluetoothClient client : _clients) {
            client.disconnect();
        }
    }

    List<BluetoothClient> getClients() {
        return _clients;
    }

    //////////////////////////////////////////
    // IMachineCommunicator Implementation

    @Override
    public void setDrillBusy(int drill) {
        drillArray[drill] = false;
    }

    @Override
    public void setDrillFree(int drill) {
        drillArray[drill] = true;
    }

    @Override
    public int getFreeDrill() {
        for (int i = 0; i<drillArray.length; i++) {
            if (drillArray[i])
                return i;
        }
        return 3;
    }

    //////////////////////////////////////////
    // private helper methods

    private void _connectToAllDevices() {
        disconnect();
        _clients.clear();

        // Connect to all Rodoter
        for (int i = 0; i < XBEE_MAC_ADRESSES.length; i++) {
            BluetoothDevice device = btAdapter.getRemoteDevice(XBEE_MAC_ADRESSES[i]);
            BluetoothClient client = new BluetoothClient(device, this);
            if (client.connect())
                _clients.add(client);
        }
        btAdapter.cancelDiscovery();
    }
}
