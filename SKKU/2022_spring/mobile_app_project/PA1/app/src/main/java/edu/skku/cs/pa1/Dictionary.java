package edu.skku.cs.pa1;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

import androidx.annotation.NonNull;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Random;

// class representing word dictionary
class Dictionary {

    // whether file is read
    boolean is_ready;

    Random rand;
    // file stream object
    BufferedReader bufrd;

    // dictionary data object. probably array
    ArrayList<String> words;

    public Dictionary(InputStream is) {
        is_ready = false;
        words = null;
        rand = new Random();

        try {
            bufrd = new BufferedReader(new InputStreamReader(is));
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    public void readDictionary() {
        class StringArrayListHandler extends Handler {
            @Override
            public void handleMessage(@NonNull Message msg) {
                super.handleMessage(msg);
                Bundle bundle = msg.getData();
                words = bundle.getStringArrayList("words");
                is_ready = true;
            }
        }
        StringArrayListHandler handler = new StringArrayListHandler();

        class ReadThread implements Runnable {
            @Override
            public void run() {
                ArrayList<String> words_ = new ArrayList<>();
                String word = new String();

                while (true) {
                    try {
                        word = bufrd.readLine();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                    if (word == null) {
                        break;
                    }
                    words_.add(word);
                }

                Bundle bundle = new Bundle();
                Message msg = new Message();
                bundle.putStringArrayList("words", words_);
                msg.setData(bundle);
                handler.sendMessage(msg);
            }
        }
        new Thread(new ReadThread()).start();
    }

    public String sampleWord() {
        // sample one word from word distribution.
        return words.get(rand.nextInt(words.size()));
    }

    public boolean isInDictionary(String word) {
        // check if word is in dictionary
        return words.contains(word);
    }

}
