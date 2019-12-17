package de.htwdd.tiserver.ui;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;
import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;
import de.htwdd.tiserver.R;
import de.htwdd.tiserver.bluetooth.BluetoothClient;

import java.util.ArrayList;
import java.util.List;

public class ConnectedDevicesAdapter extends RecyclerView.Adapter {

    public interface ListItemClickedListener {
        void onReconnectClicked(BluetoothClient client);
        void onSendRClicked(BluetoothClient client);
    }

    public static class MyViewHolder extends RecyclerView.ViewHolder {
        // each data item is just a string in this case
        public TextView _name;
        public Button _btnConnect, _btnR;
        public MyViewHolder(View item) {
            super(item);
            _name = item.findViewById(R.id.tvName);
            _btnConnect = item.findViewById(R.id.btnConnect);
            _btnR = item.findViewById(R.id.btnSendR);
        }

        void setStatus(boolean isConnected) {
            _btnConnect.setVisibility(isConnected ? View.INVISIBLE : View.VISIBLE);
            _btnR.setVisibility(isConnected ? View.VISIBLE : View.INVISIBLE);
        }

        public void setBtnCallback(final ListItemClickedListener listener, final BluetoothClient client) {
            _btnConnect.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    listener.onReconnectClicked(client);
                }
            });
            _btnR.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    listener.onSendRClicked(client);
                }
            });
        }
    }

    private List<BluetoothClient> _dataSet = new ArrayList<>();
    private ListItemClickedListener _listener;

    public ConnectedDevicesAdapter() {

    }

    @NonNull
    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View v = LayoutInflater.from(parent.getContext()).inflate(R.layout.connected_item, parent, false);
        MyViewHolder vh = new MyViewHolder(v);
        return vh;
    }

    @Override
    public void onBindViewHolder(@NonNull RecyclerView.ViewHolder holder, int position) {
        if (holder instanceof MyViewHolder) {
            MyViewHolder viewHolder = (MyViewHolder) holder;
            viewHolder._name.setText(_dataSet.get(position).getName());
            viewHolder.setStatus(_dataSet.get(position).isConnected());
            viewHolder.setBtnCallback(_listener, _dataSet.get(position));
        }
    }

    @Override
    public int getItemCount() {
        return _dataSet.size();
    }

    public void updateData(List<BluetoothClient> clients) {
        _dataSet = clients;
    }

    public void setItemClickedListener(ListItemClickedListener listener) {
        _listener = listener;
    }
}
