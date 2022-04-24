package com.skku.cs.pa2;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.GridView;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.io.IOException;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.HttpUrl;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
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

        client.newCall(req).enqueue(new Callback() {
            @Override
            public void onFailure(@NonNull Call call, @NonNull IOException e) {
                e.printStackTrace();
            }

            @Override
            public void onResponse(@NonNull Call call, @NonNull Response response) throws IOException {
                final String myResponse = response.body().string();
                Gson gson = new GsonBuilder().create();
                final DataModels.Maze maze_data = gson.fromJson(myResponse, DataModels.Maze.class);

                maze.setData(maze_data.getMaze());

            }
        });
    }
}