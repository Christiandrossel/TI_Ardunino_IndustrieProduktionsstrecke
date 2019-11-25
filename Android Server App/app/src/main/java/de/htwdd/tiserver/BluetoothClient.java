package de.htwdd.tiserver;

import android.app.Application;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.util.Log;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

public class BluetoothClient {
    private BluetoothSocket _btSocket;
    private BluetoothDevice _btDevice;
    private OutputStream _outStream;
    private InputStream _inStream;
    private Thread _readingThread;
    private ClientType _type;

    public BluetoothClient(BluetoothDevice device) {
        _btDevice = device;
    }

    public boolean connect() {
        try {
            UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
            _btSocket = _btDevice.createRfcommSocketToServiceRecord(uuid);
            _btSocket.connect();
            _outStream = _btSocket.getOutputStream();
            _inStream = _btSocket.getInputStream();
            _readingThread = new Thread(new AsyncRead(_inStream));
            _readingThread.start();

        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
        return true;
    }

    public void disconnect() {
        try {
            _readingThread.interrupt();
            _outStream.flush();
            _inStream.close();
            _btSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void sendData(String message) {
        byte[] msgBuffer = message.getBytes();

        Log.i("BluetoothClient", "==> Send data: " + message);

        try {
            _outStream.write(msgBuffer);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

class AsyncRead implements Runnable {
    InputStream _stream;

    AsyncRead(InputStream stream) {
        _stream = stream;
    }

    @Override
    public void run() {
        while (true) {
            try {
                byte[] buffer = new  byte[256];
                int bytes;
                bytes = _stream.read(buffer);
                // ToDo: make buffer readable
                Log.d("BluetoothClient", buffer.toString());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
