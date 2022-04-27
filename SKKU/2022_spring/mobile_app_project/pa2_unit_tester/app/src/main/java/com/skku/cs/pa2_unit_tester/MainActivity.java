package com.skku.cs.pa2_unit_tester;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.GridView;
import android.widget.TextView;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.HttpUrl;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);



        String maze_name = "maze6";
        String server_addr = "http://115.145.175.57:10099";

        Maze maze = new Maze();
        Button up_button    = (Button)findViewById(R.id.up_button);
        Button down_button  = (Button)findViewById(R.id.down_button);
        Button left_button  = (Button)findViewById(R.id.left_button);
        Button right_button = (Button)findViewById(R.id.right_button);
        TextView turn_indicator = (TextView)findViewById(R.id.turn_indicater_textview);
        Button hint_button  = (Button)findViewById(R.id.hint_button);


        GridView gridView = (GridView)findViewById(R.id.maze_gridview);


        OkHttpClient client = new OkHttpClient();
        HttpUrl.Builder urlBuilder = HttpUrl.parse(server_addr + "/maze/map").newBuilder();
        urlBuilder.addQueryParameter("name", maze_name);
        String url = urlBuilder.build().toString();

        Log.d("url", url);

        Request req = new Request.Builder().url(url).build();

        client.newCall(req).enqueue(new Callback() {
            @Override
            public void onFailure(@NonNull Call call, @NonNull IOException e) {
                e.printStackTrace();
            }

            @Override
            public void onResponse(@NonNull Call call, @NonNull Response response) throws IOException {
                final String myResponse = response.body().string();

                Log.d("response", myResponse);

                Gson gson = new GsonBuilder().create();
                final DataModels.Maze maze_data = gson.fromJson(myResponse, DataModels.Maze.class);

                Log.d("maze_data", maze_data.getMaze());

                maze.setData(maze_data.getMaze());

                GridViewAdapter adapter = new GridViewAdapter(
                        getApplicationContext(),
                        maze.data,
                        maze.size
                );

                up_button.setOnClickListener(view -> {
                    turn_indicator.setText("Turn : " + String.valueOf(maze.Move(8)));
                    if (maze.moved) {
                        adapter.setCurrPos(maze.curr_state.curr_pos, 3);
                        adapter.notifyDataSetChanged();
                    }
                });
                down_button.setOnClickListener(view -> {
                    turn_indicator.setText("Turn : " + String.valueOf(maze.Move(2)));
                    if (maze.moved) {
                        adapter.setCurrPos(maze.curr_state.curr_pos, 1);
                        adapter.notifyDataSetChanged();
                    }
                });
                left_button.setOnClickListener(view -> {
                    turn_indicator.setText("Turn : " + String.valueOf(maze.Move(4)));
                    if (maze.moved) {
                        adapter.setCurrPos(maze.curr_state.curr_pos, 2);
                        adapter.notifyDataSetChanged();
                    }
                });
                right_button.setOnClickListener(view -> {
                    turn_indicator.setText("Turn : " + String.valueOf(maze.Move(1)));
                    if (maze.moved) {
                        adapter.setCurrPos(maze.curr_state.curr_pos, 0);
                        adapter.notifyDataSetChanged();
                    }
                });
                hint_button.setOnClickListener(view -> {
                    State target = maze.showHint();
                    Log.d("hint", String.valueOf(target.curr_pos[0] + "," + String.valueOf(target.curr_pos[1])));
                });

                MainActivity.this.runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        gridView.setNumColumns(maze.size);
                        gridView.setAdapter(adapter);

                    }
                });

            }
        });
    }
}