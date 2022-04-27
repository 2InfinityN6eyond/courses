package edu.skku.cs.pa2;

import android.content.Intent;
import android.os.Bundle;
import android.provider.ContactsContract;
import android.widget.ListView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.io.IOException;
import java.util.ArrayList;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.HttpUrl;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class MapSelectionActivity extends AppCompatActivity {

    private ListView listView;
    private MapListViewAdapter adapter;
    private ArrayList<DataModels.Map> items;
        //private com.skku.cs.pa2.MapListViewAdapter adapter;
    //private ArrayList<com.skku.cs.pa2.DataModels.Map> items;

    public String server_addr;
    String user_name;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_map_selection);

        Intent intent = getIntent();
        server_addr = intent.getStringExtra("server_addr");
        user_name = intent.getStringExtra("username");

        items = new ArrayList<DataModels.Map>();
        //items = new ArrayList<com.skku.cs.pa2.DataModels.Map>();
        listView = (ListView)findViewById(R.id.maze_listview);
        TextView user_name_textview = (TextView)findViewById(R.id.username_textview);
        user_name_textview.setText(user_name);

        OkHttpClient client = new OkHttpClient();
        HttpUrl.Builder urlBuilder = HttpUrl.parse(server_addr + "/maps").newBuilder();
        String url = urlBuilder.build().toString();

        Request req = new Request.Builder().url(url).build();
        client.newCall(req).enqueue(new Callback() {
            @Override
            public void onFailure(@NonNull Call call, @NonNull IOException e) {
                e.printStackTrace();
            }

            @Override
            public void onResponse(@NonNull Call call, @NonNull Response response) throws IOException {
                final String myResponse = response.body().string();

                Gson gson = new GsonBuilder().create();
                final DataModels.Map[] maps = gson.fromJson(myResponse, DataModels.Map[].class);
                //final com.skku.cs.pa2.DataModels.Map[] maps = gson.fromJson(myResponse, com.skku.cs.pa2.DataModels.Map[].class);
                for (int i = 0; i < maps.length; i++) {
                    items.add(maps[i]);
                }

                MapSelectionActivity.this.runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        adapter = new MapListViewAdapter(items, getApplicationContext(), server_addr);
                        //adapter = new com.skku.cs.pa2.MapListViewAdapter(items, getApplicationContext(), server_addr);
                        listView.setAdapter(adapter);
                    }
                });


            }
        });


    }
}