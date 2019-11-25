package de.htwdd.tiserver;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

public class BluetoothCommunicator {

    private static final String TAG = "BtCommunicator";
    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    private static final String[] XBEE_MAC_ADRESSES = {"98:D3:41:FD:54:C3"};

    private BluetoothAdapter btAdapter;
    private List<BluetoothClient> _clients;

    BluetoothCommunicator() {
        btAdapter = BluetoothAdapter.getDefaultAdapter();
        _clients = new ArrayList<>();
    }

    public boolean isReady() {
        return (btAdapter!=null && btAdapter.isEnabled());
    }

    public boolean connect() {
        if (btAdapter == null)
            return false;

        if(_clients.size() != XBEE_MAC_ADRESSES.length) {
            disconnect();
            _clients.clear();

            // Connect to all Rodoter
            for (int i = 0; i < XBEE_MAC_ADRESSES.length; i++) {
                BluetoothDevice device = btAdapter.getRemoteDevice(XBEE_MAC_ADRESSES[i]);
                BluetoothClient client = new BluetoothClient(device);
                if (client.connect())
                    _clients.add(client);
            }
            btAdapter.cancelDiscovery();
        } else {
            for (BluetoothClient client : _clients) {
                client.connect();
            }
        }
        return true;
    }

    public void disconnect() {
        for (BluetoothClient client : _clients) {
            client.disconnect();
        }
    }

    public List<BluetoothClient> getClients() {
        return _clients;
    }
}
