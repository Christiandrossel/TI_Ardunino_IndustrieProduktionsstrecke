
package de.htwdd.tiserver;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends Activity {

    Button btnOn, btnOff;
    BluetoothCommunicator btComm;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);

        btnOn  = findViewById(R.id.button);
        btnOff = findViewById(R.id.button2);

        btComm = new BluetoothCommunicator();
        checkBTState();

        btnOn.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                for (BluetoothClient client : btComm.getClients()) {
                    client.sendData("R");
                }
            }
        });

        btnOff.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                for (BluetoothClient client : btComm.getClients()) {
                    client.sendData("L");
                }
            }
        });
    }

    @Override
    public void onResume() {
        super.onResume();
        btComm.connect();
    }

    @Override
    public void onPause() {
        super.onPause();

        btComm.disconnect();
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