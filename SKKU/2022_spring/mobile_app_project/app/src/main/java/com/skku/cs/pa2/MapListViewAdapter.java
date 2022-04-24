package com.skku.cs.pa2;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.TextView;

import androidx.constraintlayout.widget.ConstraintLayout;

import org.w3c.dom.Text;

import java.util.ArrayList;

public class MapListViewAdapter extends BaseAdapter {

    private ArrayList<DataModels.Map> items;
    private Context mContext;
    private String server_addr;

    MapListViewAdapter(ArrayList<DataModels.Map> items, Context mContext, String server_addr) {
        this.mContext = mContext;
        this.items = items;
        this.server_addr = server_addr;
    }

    @Override
    public int getCount() {
        return items.size();
    }

    @Override
    public Object getItem(int i) {
        return items.get(i);
    }

    @Override
    public long getItemId(int i) {
        return i;
    }

    @Override
    public View getView(int i, View view, ViewGroup viewGroup) {
        if (view == null) {
            LayoutInflater layoutInflater = (LayoutInflater)mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            view = layoutInflater.inflate(R.layout.map_selection_element, viewGroup, false);
        }
        TextView name_text_view = view.findViewById(R.id.name_text_view);
        TextView size_text_view = view.findViewById(R.id.size_text_view);
        Button start_button = view.findViewById(R.id.start_button);

        name_text_view.setText(items.get(i).getName());
        size_text_view.setText(String.valueOf(items.get(i).getSize()));
        start_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.d("opening new activity...", items.get(i).getName());
                Intent intent = new Intent(mContext, MazeActivity.class);
                intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                intent.putExtra("maze_name", items.get(i).getName());
                intent.putExtra("server_addr", server_addr);
                mContext.startActivity(intent);
            }
        });

        return view;
    }
}
