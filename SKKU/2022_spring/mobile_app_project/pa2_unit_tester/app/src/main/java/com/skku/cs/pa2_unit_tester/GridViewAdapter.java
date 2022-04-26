package com.skku.cs.pa2_unit_tester;

import android.content.Context;
import android.text.Layout;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.ArrayList;

public class GridViewAdapter extends BaseAdapter {
    Context mContext;
    LayoutInflater mLayoutInflater;

    // flattened 2D array maze.
    // [ [row1], [row2], ...] -> [row1, row2, ...]
    // encoding information to value of each element.
    // 1. wall.     4 cases.  1:right  2:bottom 4:left 8:up
    // 2. image.    3 cases.  16:goal  32:hint  64:user
    // 3. rotation. 4 cases.  128: right 256:bottom 512:left 1024:up
    ArrayList<Integer> items;

    int margin_px;
    int grid_size_px;

    int num_column;

    int user_image;
    int hint_image;
    int goal_image;
    int[] images;
    
    GridViewAdapter(Context context, ArrayList<Integer> items, int num_column) {
        mContext = context;
        this.items = items;
        this.num_column = num_column;

        int dpi = mContext.getResources().getDisplayMetrics().densityDpi;
        grid_size_px = 350 * dpi / 160;
        margin_px    = 3 * dpi / 160;

        //user_image = mContext.
        //user_image = mContext.getDrawable(R.drawable.user);
        //hint_image = mContext.getDrawable(R.drawable.hint);
        //goal_image = mContext.getDrawable(R.drawable.goal);

        images = new int[]{user_image, hint_image, goal_image};
    }

    @Override
    public int getCount() {
        return items.size();
    }

    @Override
    public Object getItem(int i) {
        return items.get(i);
    }

    @Override
    public long getItemId(int i) {
        return i;
    }

    @Override
    public View getView(int i, View view, ViewGroup parent) {
        if (view == null) {
            LayoutInflater mLayoutInflater = (LayoutInflater)mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            view = mLayoutInflater.inflate(R.layout.grid_view_item, parent, false);
        }

        int val = items.get(i);

        // initialize imageview
        ImageView imageView1 = (ImageView)view.findViewById(R.id.imageView);

        // determine rotation
        int rotation = 0;
        for (int j = 10; j > 6; j--) {
            if (val / Math.pow(2, j) == 1) {
                rotation = 12 - j;
                val %= Math.pow(2, j);
                break;
            }
        }
        rotation %= 4;

        // find image id value.
        int image_id = 0;
        for (int j = 6; j > 3; j--) {
            if (val / Math.pow(2, j) == 1) {
                image_id = images[6 - j];
                val %= Math.pow(2, j);
            }
        }
        if (image_id == 0) {
            imageView1.setImageResource(R.drawable.user);
        } else if (image_id == 1) {
            imageView1.setImageResource(R.drawable.hint);
        } else if (image_id == 1) {
            imageView1.setImageResource(R.drawable.goal);
        }
        //imageView1.setImageResource(images[image_id]);
        if (rotation > 0) {
            imageView1.setRotation(90 * rotation);
        }

        // set margin and size of imageview to draw wall
        int image_height = 0;
        int image_width = 0;
        int wall_left = 0;
        int wall_up = 0;
        int wall_down = 0;
        int wall_right = 0;
        for (int f = 3; f >= 0; f--) {
            if (val / Math.pow(2, f) == 1) {
                if (f == 0) { // right
                    wall_right = margin_px;
                } else if (f == 1) { // bottom
                    wall_down = margin_px;
                } else if (f == 2) { // left
                    wall_left = margin_px;
                } else if (f == 3) { // up
                    wall_up = margin_px;
                }
            }
        }

        Log.d(
                "cell " + String.valueOf(i),
                "val:" + String.valueOf(val) +
                " , image:" + String.valueOf(image_id) +
                        ", top:" + String.valueOf(wall_up) +
                        ", bottom:" + String.valueOf(wall_down) +
                        ", left:" + String.valueOf(wall_left) +
                        ", right:" + String.valueOf(wall_right)
                );

        image_height = grid_size_px - wall_down - wall_up;
        image_width = grid_size_px - wall_left - wall_right;

        ViewGroup.MarginLayoutParams marginLayoutParams = (ViewGroup.MarginLayoutParams) imageView1.getLayoutParams();
        marginLayoutParams.setMargins(wall_left, wall_up, wall_right, wall_down);
        imageView1.getLayoutParams().height = image_height;
        imageView1.getLayoutParams().width  = image_width;
        return view;

    }
}