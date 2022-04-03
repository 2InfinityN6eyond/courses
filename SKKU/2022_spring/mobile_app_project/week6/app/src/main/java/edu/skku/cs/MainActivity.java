package edu.skku.cs;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.lang.Math;

public class MainActivity extends AppCompatActivity {

    TextView textView1;
    MonteCarloHadler mt_handler = new MonteCarloHadler();


    class MonteCarloThread implements Runnable {
        @Override
        public void run() {
            double result = 0.0;
            int count = 0;
            int length = 10000000;
            int period = 1000000;
            double x, y;

            for (int i = 0; i < length; i += 1) {
                x = Math.random();
                y = Math.random();
                if (x * x + y * y < 1) {
                    count += 1;
                }

                if (i % period == 0 && i != 0) {
                    result = count / (double)i * 4;
                    Bundle bundle = new Bundle();
                    Message msg = new Message();
                    bundle.putDouble("pi", result);
                    bundle.putInt("finished", 0);
                    msg.setData(bundle);
                    mt_handler.sendMessage(msg);
                }

            }

            result = count / (double)length * 4;
            Bundle bundle = new Bundle();
            Message msg = new Message();
            bundle.putDouble("pi", result);
            bundle.putInt("finished", 1);
            msg.setData(bundle);
            mt_handler.sendMessage(msg);
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        MonteCarloThread mt_worker = new MonteCarloThread();

        textView1 = findViewById(R.id.textview1);

        Button button1 = findViewById(R.id.button1);
        button1.setOnClickListener(view -> {
            new Thread(mt_worker).start();
        });
    }


    class MonteCarloHadler extends Handler {
        @Override
        public void handleMessage(@NonNull Message msg) {
            super.handleMessage(msg);
            Bundle bundle = msg.getData();
            double pi = bundle.getDouble("pi");
            int finished = bundle.getInt("finished");
            String pi_msg = Double.toString(pi);
            Log.d("finished", String.valueOf(finished));
            textView1.setText(pi_msg);

            if (finished == 1) {
                Toast toast = Toast.makeText(
                        MainActivity.this,
                        "Finish Estimate",
                        Toast.LENGTH_SHORT
                );
                toast.show();
            }
        }
    }
}


