package com.skku.cs.pa2_unit_tester;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.GridView;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ArrayList<Integer> items = new ArrayList<Integer>();
        //{14. 10, 10, 9, 13, 12, 8, 9, 6, 1, 5, 5, 4, 11, 5, 5, 5, 7, 12, 3};
        //for (int i = 0; i < 10; i++) {
        //    items.add(i);
        //}
        items.add(14);
        items.add(10);
        items.add(10);
        items.add(9);
        items.add(13);

        items.add(12);
        items.add(8);
        items.add(9);
        items.add(6);
        items.add(1);

        items.add(5);
        items.add(5);
        items.add(4);
        items.add(11);
        items.add(5);

        items.add(5);
        items.add(5);
        items.add(7);
        items.add(12);
        items.add(3);

        items.add(7);
        items.add(6);
        items.add(10);
        items.add(2);
        items.add(11 + 16);


        int num_column = 2;

        GridView gridView = (GridView) findViewById(R.id.grid_view);
        gridView.setNumColumns(num_column);
        GridViewAdapter adapter = new GridViewAdapter(
                getApplicationContext(),
                items,
                num_column
        );
        gridView.setAdapter(adapter);

        adapter.notifyDataSetChanged();
    }
}