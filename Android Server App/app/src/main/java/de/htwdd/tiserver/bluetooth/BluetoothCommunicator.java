package de.htwdd.tiserver.bluetooth;

import android.bluetooth.BluetoothAdapter;
import de.htwdd.tiserver.IMachineCommunicator;

import java.util.*;

public class BluetoothCommunicator implements IMachineCommunicator {

    /**
     * Implement Interface in classes that have to Listen to changes in connected Devices
     */
    public interface ConnectedDevicesListener {
        /**
         * gets called when a Device is disconnected or connected
         * @param devices List of all Devices
         */
        void onConnectedClientsChanged(List<BluetoothClient> devices);
    }

    private Map<String, String> _rodoterMap = new HashMap<String, String>();
    private Map<String, String> _drillMap = new HashMap<String, String>();

    private BluetoothAdapter _btAdapter;
    private ConnectedDevicesListener _connectionListener;
    private List<BluetoothClient> _clients = new ArrayList<>();
    private List<Drill> _drills = new ArrayList<>();


    public BluetoothCommunicator() {
        _btAdapter = BluetoothAdapter.getDefaultAdapter();

        _rodoterMap.put("Rodoter", "98:D3:41:FD:50:E7");
        _rodoterMap.put("Flip", "98:D3:71:FD:4A:E2");
        _rodoterMap.put("Flop", "98:D3:61:FD:6F:CA");
        _rodoterMap.put("Dietrich", "98:D3:41:FD:54:C3");

        _drillMap.put("Bohrer 1", "98:D3:32:F5:B6:4F");
        _drillMap.put( "Bohrer 2", "98:D3:32:F5:B7:AD");


        // create the Client-List
        for (String name : _rodoterMap.keySet()) {
            String mac = _rodoterMap.get(name);

            BluetoothClient client = new Rodoter(mac, name, BluetoothCommunicator.this);
            _clients.add(client);
        }

        // Create the Drills-List
        for (String name : _drillMap.keySet()) {
            String mac = _drillMap.get(name);

            Drill drill = new Drill(mac, name, BluetoothCommunicator.this);
            _drills.add(drill);
            _clients.add(drill);
        }
    }

    /**
     * Try to Connect to specified Bluetooth Device
     * @return returns true, if the device was connected
     */
    public boolean connect(BluetoothClient client) {
        if (client == null)
            return false;

        return client.connect(_btAdapter);
    }

    /**
     * Disconnect the device from all BluetoothClients
     */
    public void disconnect() {
        for (BluetoothClient client : _clients) {
            client.disconnect();
        }
    }

    public void sendR(BluetoothClient client) {
        client.sendData("r");
    }

    //////////////////////////////////////////
    // Getter and Setter

    /**
     * @param connectedDevicesListener the one Listener that gets notification when a device is (dis-)connected
     */
    public void setConnectedDevicesListener(ConnectedDevicesListener connectedDevicesListener) {
        _connectionListener = connectedDevicesListener;
        _connectionListener.onConnectedClientsChanged(_clients);
    }

    /**
     * @return returns a List with all connected BluetoothClients
     */
    List<BluetoothClient> getClients() {
        return _clients;
    }

    /**
     * @return returns true, if the Device has Bluetooth and Bluetooth is enabled
     */
    public boolean isReady() {
        return (_btAdapter !=null && _btAdapter.isEnabled());
    }

    //////////////////////////////////////////
    // IMachineCommunicator Implementation

    @Override
    public void setDrillBusy(int drillId, Rodoter client) {
        if (_drills.get(drillId-1) != null)
            _drills.get(drillId-1).setBusy(client);
    }

    @Override
    public void setDrillFree(int drillId) {
        if (_drills.get(drillId-1) != null)
            _drills.get(drillId-1).setFree();
    }

    @Override
    public int getFreeDrillId() {
        for (int i = 0; i<_drills.size(); i++) {
            if (_drills.get(i) != null && _drills.get(i).isFree())
                return i+1;
        }
        return 0;
    }

    @Override
    public void connectionChanged() {
        if (_connectionListener != null)
        _connectionListener.onConnectedClientsChanged(_clients);
    }
}
