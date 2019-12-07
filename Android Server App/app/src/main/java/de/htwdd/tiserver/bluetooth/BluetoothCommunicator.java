package de.htwdd.tiserver.bluetooth;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import de.htwdd.tiserver.IMachineCommunicator;

import java.util.ArrayList;
import java.util.List;

public class BluetoothCommunicator implements IMachineCommunicator {

    private static final String[] RODOTER_MAC_ADRESSES = {"98:D3:41:FD:54:C3", "38:DE:AD:6E:1C:E7", "98:D3:71:FD:4A:E2", "98:D3:41:FD:50:E7", "98:D3:61:FD:6F:CA"}; // Norman, Anja, Manuel, Anja, Dominic
    private static final String[] DRILL_MAC_ADRESSES = { "98:D3:32:F5:B6:4F", "98:D3:32:F5:B7:AD"}; // Anja, Dominic

    private BluetoothAdapter btAdapter;
    private List<BluetoothClient> _clients;

    private Drill[] drills = new Drill[3];

    public BluetoothCommunicator() {
        btAdapter = BluetoothAdapter.getDefaultAdapter();
        _clients = new ArrayList<>();
    }

    /**
     * @return returns true, if the Device has Bluetooth and Bluetooth is enabled
     */
    public boolean isReady() {
        return (btAdapter!=null && btAdapter.isEnabled());
    }

    /**
     * (Re)connect the device to all possible BluetoothClients
     */
    public void connect() {
        if (btAdapter == null)
            return;

        if(_clients.size() != RODOTER_MAC_ADRESSES.length) {
            _connectToAllDevices();
        } else {
            for (BluetoothClient client : _clients) {
                client.connect();
            }
        }
    }

    /**
     * Disconnect the device from all BluetoothClients
     */
    public void disconnect() {
        for (BluetoothClient client : _clients) {
            client.disconnect();
        }
    }

    /**
     * @return returns a List with all connected BluetoothClients
     */
    List<BluetoothClient> getClients() {
        return _clients;
    }

    //////////////////////////////////////////
    // IMachineCommunicator Implementation

    @Override
    public void setDrillBusy(int drillId, Rodoter client) {
        drills[drillId].setBusy(client);
    }

    @Override
    public void setDrillFree(int drillId) {
        for (Drill drill : drills) {
            if(drill != null && drill.getId() == drillId) {
                drill.setFree();
                return;
            }
        }
    }

    @Override
    public int getFreeDrillId() {
        for (int i = 1; i<drills.length; i++) {
            if (drills[i] != null && drills[i].isFree())
                return i;
        }
        return 0;
    }

    //////////////////////////////////////////
    // private helper methods

    private void _connectToAllDevices() {
        disconnect();
        _clients.clear();

        Thread connectingThread = new Thread(new Runnable() {
            @Override
            public void run() {
                // Connect to all Rodoter
                for (String xbeeMacAdress : RODOTER_MAC_ADRESSES) {
                    BluetoothDevice device = btAdapter.getRemoteDevice(xbeeMacAdress);
                    BluetoothClient client = new Rodoter(device, BluetoothCommunicator.this);
                    if (client.connect())
                        _clients.add(client);
                }
                for (int i = 1; i < 3; i++) {
                    BluetoothDevice device = btAdapter.getRemoteDevice(DRILL_MAC_ADRESSES[i-1]);
                    drills[i] = new Drill(device, BluetoothCommunicator.this, i);
                    if (drills[i].connect())
                        _clients.add(drills[i]);
                }
                btAdapter.cancelDiscovery();
            }
        });
        connectingThread.start();
    }

    public void debugR() {
        for (BluetoothClient client : _clients) {
            client.sendData("r");

        }
    }
}
