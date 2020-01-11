
package de.htwdd.tiserver;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import de.htwdd.tiserver.bluetooth.BluetoothClient;
import de.htwdd.tiserver.bluetooth.BluetoothCommunicator;
import de.htwdd.tiserver.ui.ConnectedDevicesAdapter;

import java.util.List;

public class MainActivity extends Activity {

    BluetoothCommunicator btComm;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);
        final RecyclerView list = findViewById(R.id.recyclerView);
        final ConnectedDevicesAdapter recyclerAdapter = new ConnectedDevicesAdapter();
        final TextView logText = findViewById(R.id.textLog);

        list.setHasFixedSize(true);
        RecyclerView.LayoutManager layoutManager = new LinearLayoutManager(this);
        list.setLayoutManager(layoutManager);
        list.setAdapter(recyclerAdapter);
        recyclerAdapter.setItemClickedListener(new ConnectedDevicesAdapter.ListItemClickedListener() {
            @Override
            public void onReconnectClicked(BluetoothClient client) {
                btComm.connect(client);
            }

            @Override
            public void onSendRClicked(BluetoothClient client) {
                btComm.sendR(client);
            }
        });

        btComm = new BluetoothCommunicator();
        btComm.setConnectedDevicesListener(new BluetoothCommunicator.ConnectedDevicesListener() {
            @Override
            public void onConnectedClientsChanged(final List<BluetoothClient> devices) {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        int c = 0;
                        for (BluetoothClient client : devices) {
                            if (client.isConnected())
                                c++;
                        }

                        final TextView connectedDevices = findViewById(R.id.tvConnectedDevices);
                        connectedDevices.setText("Verbundene Geräte: " + c);
                        recyclerAdapter.updateData(devices);
                        recyclerAdapter.notifyDataSetChanged();
                    }
                });
            }
        });
        btComm.registerLogger(new ILogger() {
            @Override
            public void writeLog(final String msg) {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        logText.setText(logText.getText() + "\r\n" + msg);
                    }
                });
            }

            @Override
            public void writeError(final String msg) {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        logText.setText(logText.getText() +"\r\n###" +  msg);
                    }
                });
            }
        });
        checkBTState();
    }

    private void checkBTState() {
        if(!btComm.isReady()) {
            //Prompt user to turn on Bluetooth
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, 1);
        }
    }

    private void errorExit(String title, String message){
        Toast.makeText(getBaseContext(), title + " - " + message, Toast.LENGTH_LONG).show();
        finish();
    }
}