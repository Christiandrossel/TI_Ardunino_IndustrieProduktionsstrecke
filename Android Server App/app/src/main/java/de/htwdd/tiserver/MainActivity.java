
package de.htwdd.tiserver;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Switch;
import android.widget.Toast;
import de.htwdd.tiserver.bluetooth.BluetoothCommunicator;

public class MainActivity extends Activity {

    BluetoothCommunicator btComm;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);

        final Button drillL  = findViewById(R.id.btnDrillL);
        final Button drillR = findViewById(R.id.btnDrillR);

        btComm = new BluetoothCommunicator();
        checkBTState();

        drillL.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                    btComm.setDrillFree(2);
            }
        });

        drillR.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                    btComm.setDrillFree(1);
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