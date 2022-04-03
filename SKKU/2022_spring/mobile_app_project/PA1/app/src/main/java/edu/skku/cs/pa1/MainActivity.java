package edu.skku.cs.pa1;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Random;

public class MainActivity extends AppCompatActivity {

    InputStream is = null;
    Dictionary dictionary;
    WordleManager wordle_manager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // initialize InputStream is
        try {
            is = getApplicationContext().getAssets().open("wordle_words.txt");
        } catch(IOException e) {
            e.printStackTrace();
        }
        // declare and initialize Dictionary instance dictionary with InputStream is
        dictionary = new Dictionary(is);
        // read wordle_words.txt file in assets folder in another thread
        dictionary.readDictionary();

        EditText input_text_edit = (EditText)findViewById(R.id.input_text_edit);
        Button submit_button = (Button)findViewById(R.id.submit_button);
        ListView wordle_words_listview = (ListView)findViewById(R.id.wordle_words);
        ListView green_letters_listview = (ListView)findViewById(R.id.green_letters);
        ListView gray_letters_listview = (ListView)findViewById(R.id.gray_letters);
        ListView yellow_letters_listview = (ListView)findViewById(R.id.yellow_letters);

        wordle_manager = new WordleManager(
                getApplicationContext(),
                dictionary,
                Color.parseColor("#000000"),
                Color.parseColor("#000000"),
                Color.parseColor("#FFFFFF"),
                Color.parseColor("#99F691"),
                Color.parseColor("#FFE46F"),
                Color.parseColor("#787C7E")
        );
        wordle_words_listview.setAdapter(wordle_manager.word_adapter);
        green_letters_listview.setAdapter(wordle_manager.greens);
        yellow_letters_listview.setAdapter(wordle_manager.yellows);
        gray_letters_listview.setAdapter(wordle_manager.grays);

        submit_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                wordle_manager.tryOut(input_text_edit.getText().toString());
            }
        });

    }
}