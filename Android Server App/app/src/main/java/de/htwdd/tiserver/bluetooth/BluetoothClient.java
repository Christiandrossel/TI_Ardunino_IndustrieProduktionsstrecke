package de.htwdd.tiserver.bluetooth;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.util.Log;
import de.htwdd.tiserver.ILogger;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

public abstract class BluetoothClient {
    private BluetoothSocket _btSocket;
    private OutputStream _outStream;
    private InputStream _inStream;
    private Thread _readingThread;

    private String _name;
    private String _mac;
    ILogger logger;

    private class ReceivingThread implements Runnable {
        @Override
        public void run() {
            try {
                while (true) {
                    byte[] buffer = new byte[256];
                    int bytes;
                    bytes = _inStream.read(buffer);
                    String input = new String(buffer, 0, bytes);
                    if (!(input.equals("") || input.equals("\r\n"))) {
                        Log.i("BluetoothClient", "<== Recv data: " + input);
                        if(logger != null)
                            logger.writeLog(_name + " <=== '" + input + "'");
                        receivingThread(input);
                    }
                }
            } catch (IOException e) {
                onConnectionChanged();
            }
        }
    }

    /**
     * Creates a new BluetoothClient which can communicate with the device
     * @param macAddress the Mac for the Client
     * @param name the Name of the Client which is returned with getName()
     */
    BluetoothClient(String macAddress, String name) {
        _name = name;
        _mac = macAddress;
    }

    /**
     * Connecting the BluetoothClient with the device, opening output channels and listening for new Messages from the client
     * @param adapter the Bluetooth module of the android device
     * @return returns true, if the Client is connected
     */
    boolean connect(BluetoothAdapter adapter) {
        try {
            if(logger != null)
                logger.writeLog("Trying to connect to " + _name + "...");
            adapter.startDiscovery();
            BluetoothDevice btDevice = adapter.getRemoteDevice(_mac);
            UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
            _btSocket = btDevice.createRfcommSocketToServiceRecord(uuid);
            _btSocket.connect();
            _outStream = _btSocket.getOutputStream();
            _inStream = _btSocket.getInputStream();

            if(logger != null)
                logger.writeLog("=> Connected to " + _name + "!");
            _readingThread = new Thread(new ReceivingThread());
            _readingThread.start();
            onConnectionChanged();
            adapter.cancelDiscovery();

        } catch (IOException e) {
            e.printStackTrace();
            if(logger != null)
                logger.writeLog("=> Failed to connect to " + _name + "!");
            return false;
        }
        return true;
    }

    /**
     * Disconnect the Client from the device and cut off all channels and threads
     */
    void disconnect() {
        try {
            _readingThread.interrupt();
            _outStream.flush();
            _inStream.close();
            _btSocket.close();
            onConnectionChanged();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void registerLogger(ILogger logger) {
        this.logger = logger;
    }

    public String getName() {
        return _name;
    }

    public boolean isConnected() {
        return _btSocket != null && _btSocket.isConnected();
    }

    /**
     * AsyncRead Runnable, which is the Background-Task for a BluetoothClient that handles the receiving of messages
     * Overwrite in Extended methods
     * @param input the Input that was received from the BluetoothClient
     */
    void receivingThread(String input) {
    }

    /**
     * Callback for when the Device is Connected or lost connection
     * Overwrite in Extended methods
     */
    void onConnectionChanged() {
        if (_inStream == null || _outStream == null ) {
            logger.writeLog(_name + " disconnected!");
        }
    }

    /**
     * Sends a String message to the BluetoothClient from the Device
     * @param message the String, which should get send to the Client
     */
    synchronized void sendData(String message) {
        byte[] msgBuffer = message.getBytes();

        Log.i("BluetoothClient", "==> Send data: " + message);

        try {
            _outStream.write(msgBuffer);
            if(logger != null)
                logger.writeLog(_name + " ==> '" + message + "'");
        } catch (IOException e) {
            e.printStackTrace();
            onConnectionChanged();
        } catch (Exception e) {
            if(logger != null)
                logger.writeLog("Failed to send message '" + message + "' to " + _name);
        }
    }
}


