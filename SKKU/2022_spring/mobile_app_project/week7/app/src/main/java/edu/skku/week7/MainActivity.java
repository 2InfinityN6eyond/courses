package edu.skku.week7;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.io.IOException;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.HttpUrl;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class MainActivity extends AppCompatActivity {

    Button button;
    TextView textView;
    EditText editText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        String api_key = "22f20fd3";

        textView = findViewById(R.id.textView1);
        editText = findViewById(R.id.editText1);
        button = findViewById(R.id.button);
        button.setOnClickListener(view -> {
            OkHttpClient client = new OkHttpClient();

            DataModel data = new DataModel();
            data.setTitle(editText.getText().toString());

            Gson gson = new Gson();
            String json = gson.toJson(data, DataModel.class);

            HttpUrl.Builder urlBuilder = HttpUrl.parse("http://www.omdbapi.com/").newBuilder();
            //urlBuilder.addQueryParameter("page", "2");
            urlBuilder.addQueryParameter("apikey", api_key);
            urlBuilder.addQueryParameter("t", editText.getText().toString());

            Log.d("movie name", editText.getText().toString());

            String url = urlBuilder.build().toString();


            Request req = new Request.Builder()
                    .url(url)
                    .build();

            client.newCall(req).enqueue(new Callback() {
                @Override
                public void onFailure(@NonNull Call call, @NonNull IOException e) {
                    e.printStackTrace();
                }

                @Override
                public void onResponse(@NonNull Call call,
                                       @NonNull Response response) throws IOException {
                    final String myResponse = response.body().string();

                    Gson gson = new GsonBuilder().create();
                    final DataModel data1 = gson.fromJson(myResponse, DataModel.class);

                    MainActivity.this.runOnUiThread(new Runnable() {
                        @Override
                        public void run() {

                            Log.d("response",                                     "Title : " + data1.getTitle() +
                                    "\nYear : " + data1.getYear() +
                                    "\nReleased Date : " + data1.getReleased() +
                                    "\nRuntime : " + data1.getRuntime() +
                                    "\nDirector : " + data1.getDirector() +
                                    "\nGenre : " + data1.getGenre() +
                                    "\niMDB Rates : " + data1.getImdbRating() +
                                    "\nMetascore : " + data1.getMetascore());

                            textView.setText(
                                    "Title : " + data1.getTitle() +
                                    "\nYear : " + data1.getYear() +
                                     "\nReleased Date : " + data1.getReleased() +
                                            "\nRuntime : " + data1.getRuntime() +
                                            "\nDirector : " + data1.getDirector() +
                                            "\nGenre : " + data1.getGenre() +
                                            "\niMDB Rates : " + data1.getImdbRating() +
                                            "\nMetascore : " + data1.getMetascore()

                            );
                        }
                    });
                }
            });

        });
    }
}