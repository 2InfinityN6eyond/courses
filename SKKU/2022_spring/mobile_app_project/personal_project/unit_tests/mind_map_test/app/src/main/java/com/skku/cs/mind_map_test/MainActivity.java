package com.skku.cs.mind_map_test;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import me.jagar.mindmappingandroidlibrary.Listeners.OnItemClicked;
import me.jagar.mindmappingandroidlibrary.Views.ConnectionTextMessage;
import me.jagar.mindmappingandroidlibrary.Views.Item;
import me.jagar.mindmappingandroidlibrary.Views.ItemLocation;
import me.jagar.mindmappingandroidlibrary.Views.MindMappingView;

public class MainActivity extends AppCompatActivity {

    MindMappingView mindMappingView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mindMappingView = (MindMappingView)findViewById(R.id.mind_mapping_view);

        Item item = new Item(MainActivity.this, "Root", "Root Item", true);
        mindMappingView.addCentralItem(item, true);

        Item child1 = new Item(MainActivity.this, "child1", "I am child1", true);
        ConnectionTextMessage child1_message = new ConnectionTextMessage(MainActivity.this);
        child1_message.setText("id 10");
        mindMappingView.addItem(child1, item, 20, 20, ItemLocation.RIGHT, true, child1_message);


        //mindMappingView.addView(new TextView(this));

        Log.d(child1.getContent().getText().toString(), child1.getTitle().getText().toString());


        mindMappingView.setOnItemClicked(new OnItemClicked() {
            @Override
            public void OnClick(Item item) {
                item.setPressed(true);
            }
        });
    }
}