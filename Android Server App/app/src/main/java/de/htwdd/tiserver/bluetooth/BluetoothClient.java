package de.htwdd.tiserver.bluetooth;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

abstract class BluetoothClient {
    private BluetoothSocket _btSocket;
    private BluetoothDevice _btDevice;
    private OutputStream _outStream;
    private InputStream _inStream;
    private Thread _readingThread;

    /**
     * Creates a new BluetoothClient which can communicate with the device
     * @param device the Bluetooth Device, created by the BluetoothCommunicator
     */
    BluetoothClient(BluetoothDevice device) {
        _btDevice = device;
    }

    /**
     * Connecting the BluetoothClient with the device, opening output channels and listening for new Messages from the client
     * @return returns true, if the Client is connected
     */
    boolean connect() {
        try {
            UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
            _btSocket = _btDevice.createRfcommSocketToServiceRecord(uuid);
            _btSocket.connect();

            _outStream = _btSocket.getOutputStream();
            _inStream = _btSocket.getInputStream();
            _readingThread = new Thread(new Runnable() {
                @Override
                public void run() {
                    try {
                        byte[] buffer = new  byte[256];
                        int bytes;
                        bytes = _inStream.read(buffer);
                        String input = new String(buffer, 0, bytes);
                        if(!(input.equals("") || input.equals("\r\n"))) {
                            Log.i("BluetoothClient", "<== Recv data: " + input);

                            receivingThread(input);
                        }
                    } catch (IOException e) {
                        return;
                    }
                }
            });
            _readingThread.start();

        } catch (IOException e) {
            e.printStackTrace();
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
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Sends a String message to the BluetoothClient from the Device
     * @param message the String, which should get send to the Client
     */
    void sendData(String message) {
        byte[] msgBuffer = message.getBytes();

        Log.i("BluetoothClient", "==> Send data: " + message);

        try {
            _outStream.write(msgBuffer);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * AsyncRead Runnable, which is the Background-Task for a BluetoothClient that handles the receiving of messages
     * Overwrite in Extended methods
     * @param input the Input that was received from the BluetoothClient
     */
    void receivingThread(String input) {
    }
}


