package com.skku.cs.androidpdfviewer;

import androidx.appcompat.app.AppCompatActivity;

import android.content.res.AssetManager;
import android.os.Bundle;

import com.github.barteksc.pdfviewer.PDFView;

import java.io.InputStream;

public class MainActivity extends AppCompatActivity {

    PDFView pdfView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        pdfView = (PDFView)findViewById(R.id.pdfView);
        pdfView.fromAsset("sample.pdf").load();
                //.enableSwipe(true)
                //.swipeHorizontal(true)
                //.nightMode(true)
                //.load();



        /*AssetManager assetManager = getResources().getAssets();
        InputStream is = null;

        try {
            is = assetManager.open("deep_pose.pdf");

            pdfView = (PDFView)findViewById(R.id.pdfView);
            pdfView.fromStream(is)
                    .enableSwipe(true)
                    .swipeHorizontal(true)
                    .nightMode(true)
                    .load();

        } catch (Exception e) {
            e.printStackTrace();
        }

        if (is != null) {
            try {
                is.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }*/


    }
}