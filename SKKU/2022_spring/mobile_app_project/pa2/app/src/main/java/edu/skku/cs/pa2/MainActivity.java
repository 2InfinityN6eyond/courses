package edu.skku.cs.pa2;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

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

public class MainActivity extends AppCompatActivity {

    String server_addr = "http://115.145.175.57:10099";
    String user_name;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        EditText name_edit_text = (EditText)findViewById(R.id.name_textedit);
        Button sign_in_button = (Button)findViewById(R.id.sign_in_button);
        sign_in_button.setOnClickListener(view -> {
            OkHttpClient client = new OkHttpClient();

            //DataModels data = new DataModels();
            DataModels.UserName data = new DataModels.UserName();

            user_name = name_edit_text.getText().toString();
            data.setUsername(user_name);

            Gson gson = new Gson();
            String json_msg = gson.toJson(data, DataModels.UserName.class);

            HttpUrl.Builder urlBuilder = HttpUrl.parse(server_addr + "/users").newBuilder();
            String url = urlBuilder.build().toString();

            Request req = new Request.Builder()
                    .url(url)
                    .post(RequestBody.create(MediaType.parse("application/json"), json_msg))
                    .build();

            client.newCall(req).enqueue(new Callback() {
                @Override
                public void onFailure(@NonNull Call call, @NonNull IOException e) {
                    e.printStackTrace();
                }

                @Override
                public void onResponse(@NonNull Call call, @NonNull Response response) throws IOException {
                    final String myResponse = response.body().string();


                    Gson gson = new GsonBuilder().create();

                    final DataModels.UserName data1 = gson.fromJson(myResponse, DataModels.UserName.class);

                    if (!data1.getSuccess()) {
                        // authentication failed
                        MainActivity.this.runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                Toast.makeText(
                                        getApplicationContext(),
                                        "Wrong User Name",
                                        Toast.LENGTH_SHORT
                                ).show();
                            }
                        });
                    } else {
                        MainActivity.this.runOnUiThread(new Runnable() {
                            @Override
                            public void run() {

                                Intent intent = new Intent(MainActivity.this, MapSelectionActivity.class);
                                intent.putExtra("server_addr", server_addr);
                                intent.putExtra("username", user_name);
                                startActivity(intent);
                            }
                        });
                    }
                }
            });
        });


    }
}