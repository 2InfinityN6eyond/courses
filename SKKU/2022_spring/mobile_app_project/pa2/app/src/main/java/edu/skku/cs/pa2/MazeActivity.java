package edu.skku.cs.pa2;

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


public class MazeActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maze);

        Intent intent = getIntent();
        String maze_name = intent.getStringExtra("maze_name");
        String server_addr = intent.getStringExtra("server_addr");

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
                final DataModels.MazeData maze_data = gson.fromJson(myResponse, DataModels.MazeData.class);

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
                    adapter.setHintPos(new int[]{target.curr_pos[0], target.curr_pos[1]});
                    adapter.notifyDataSetChanged();
                });

                MazeActivity.this.runOnUiThread(new Runnable() {
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


/*
public class MazeActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maze);

        Intent intent = getIntent();
        String maze_name = intent.getStringExtra("maze_name");
        String server_addr = intent.getStringExtra("server_addr");

        com.skku.cs.pa2.Maze maze = new com.skku.cs.pa2.Maze();
        Button up_button    = (Button)findViewById(R.id.up_button);
        Button down_button  = (Button)findViewById(R.id.down_button);
        Button left_button  = (Button)findViewById(R.id.left_button);
        Button right_button = (Button)findViewById(R.id.right_button);
        Button hint_button  = (Button)findViewById(R.id.hint_button);
        GridView gridView   = (GridView)findViewById(R.id.maze_gridview);

        up_button.setOnClickListener(   view -> { maze.Move(8); });
        down_button.setOnClickListener( view -> { maze.Move(2); });
        left_button.setOnClickListener( view -> { maze.Move(4); });
        right_button.setOnClickListener(view -> { maze.Move(1); });
        hint_button.setOnClickListener( view -> { maze.showHint();      });

        OkHttpClient client = new OkHttpClient();
        HttpUrl.Builder urlBuilder = HttpUrl.parse(server_addr + "/maze/map").newBuilder();
        urlBuilder.addQueryParameter("name", maze_name);
        String url = urlBuilder.build().toString();

        Request req = new Request.Builder().url(url).build();

        Log.d("url", url);

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
                final com.skku.cs.pa2.DataModels.Maze maze_data = gson.fromJson(myResponse, com.skku.cs.pa2.DataModels.Maze.class);

                maze.setData(maze_data.getMaze());

            }
        });
    }
}

 */