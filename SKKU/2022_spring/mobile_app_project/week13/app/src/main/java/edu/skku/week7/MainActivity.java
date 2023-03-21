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
import java.util.Arrays;

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

        String api_key = "de04f90d71d2a5e40480b3cc07523ad7";

        textView = findViewById(R.id.textView1);
        editText = findViewById(R.id.editText1);
        button = findViewById(R.id.button);
        button.setOnClickListener(view -> {

            OkHttpClient region_client = new OkHttpClient();

            HttpUrl.Builder url_builder = HttpUrl.parse("https://m6tl2034eg.execute-api.ap-northeast-2.amazonaws.com/dev/access").newBuilder();
            url_builder.addQueryParameter("name", editText.getText().toString());

            String query_url = url_builder.build().toString();

            Request req = new Request.Builder()
                    .url(query_url)
                    .build();

            region_client.newCall(req).enqueue(new Callback() {
                @Override
                public void onFailure(@NonNull Call call, @NonNull IOException e) {
                    e.printStackTrace();
                }

                @Override
                public void onResponse(@NonNull Call call, @NonNull Response response) throws IOException {
                    final String region_response = response.body().string();
                    Gson gson = new GsonBuilder().create();
                    final DataModel.User user_model = gson.fromJson(region_response, DataModel.User.class);
                    Log.d("region", user_model.getRegion());

                    OkHttpClient weather_client = new OkHttpClient();
                    HttpUrl.Builder url_builder = HttpUrl.parse("http://api.weatherstack.com/current").newBuilder();
                    url_builder.addQueryParameter("access_key", api_key);
                    url_builder.addQueryParameter("query", user_model.getRegion());

                    String query_url = url_builder.build().toString();
                    Request req = new Request.Builder().url(query_url).build();

                    weather_client.newCall(req).enqueue(new Callback() {
                        @Override
                        public void onFailure(@NonNull Call call, @NonNull IOException e) {
                            e.printStackTrace();
                        }

                        @Override
                        public void onResponse(@NonNull Call call, @NonNull Response response) throws IOException {
                            final  String weather_response = response.body().string();

                            Log.d("weather", weather_response);

                            Gson gson = new GsonBuilder().create();
                            DataModel.WeatherResponse weather_model = gson.fromJson(weather_response, DataModel.WeatherResponse.class);
                            Log.d("humidity", weather_model.current.humidity);

                            String weather_descriptions = Arrays.toString(weather_model.current.weather_descriptions);

                            MainActivity.this.runOnUiThread(new Runnable() {
                                @Override
                                public void run() {


                                    textView.setText(
                                            "weather_description : \n" + weather_descriptions +
                                            "\ntemperature : " + weather_model.current.temperature +
                                                    "\nhumidity : " + weather_model.current.humidity +
                                                    "\ncity name : " + weather_model.location.name

                                    );
                                }
                            });

                        }
                    });

                }
            });

            //OkHttpClient client = new OkHttpClient();
            //DataModel data = new DataModel();
            //data.setTitle(editText.getText().toString());
            //Gson gson = new Gson();
            //String json = gson.toJson(data, DataModel.class);
            //HttpUrl.Builder urlBuilder = HttpUrl.parse("https://06k827sss1.execute-api.us-east-2.amazonaws.com/default/jjapOmdbApi").newBuilder();
            //urlBuilder.addQueryParameter("t", editText.getText().toString());
            //Log.d("movie name", editText.getText().toString());
            //String url = urlBuilder.build().toString();
            //Request req = new Request.Builder()
            //        .url(url)
            //        .build();

            /*
            client.newCall(req).enqueue(new Callback() {
                @Override
                public void onFailure(@NonNull Call call, @NonNull IOException e) {
                    e.printStackTrace();
                }
                @Override
                public void onResponse(@NonNull Call call,
                                       @NonNull Response response) throws IOException {
                    final String myResponse = response.body().string();

                    Log.d("response", myResponse);

                    Gson gson = new GsonBuilder().create();
                    final DataModel data1 = gson.fromJson(myResponse, DataModel.class);

                    MainActivity.this.runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
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
            });*/

        });
    }
}