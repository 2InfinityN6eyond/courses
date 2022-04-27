package edu.skku.cs.pa2;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;

import java.util.ArrayList;

public class GridViewAdapter extends BaseAdapter {
    Context mContext;
    LayoutInflater mLayoutInflater;

    private int[] curr_pos;
    private int rotation;
    private int[] goal_pos;
    private int[] hint_pos;
    private boolean plot_hint;
    public ArrayList<ArrayList<Integer>> items;

    int margin_px;
    int grid_size_px;

    int num_column;

    GridViewAdapter(Context context, ArrayList<ArrayList<Integer>> items, int num_column) {
        mContext = context;
        this.items = items;
        this.num_column = num_column;

        int dpi = mContext.getResources().getDisplayMetrics().densityDpi;
        grid_size_px = 350 * dpi / 160 / num_column;
        margin_px    = 3 * dpi / 160;

        curr_pos = new int[]{0, 0};
        rotation = 0;
        goal_pos = new int[]{num_column - 1, num_column - 1};
        hint_pos = new int[]{num_column , num_column };
        plot_hint = false;
    }

    public void setCurrPos(int[] pos, int rotation) {
        curr_pos[0] = pos[0];
        curr_pos[1] = pos[1];
        this.rotation = rotation;
    }

    public void setHintPos(int[] pos) {
        hint_pos[0] = pos[0];
        hint_pos[1] = pos[1];
        plot_hint = true;

    }

    @Override
    public int getCount() {
        return num_column * num_column;
    }

    @Override
    public Object getItem(int i) {
        return items.get(i / num_column).get(i % num_column);
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

        int row_idx = i / num_column;
        int col_idx = i % num_column;

        int val = items.get(row_idx).get(col_idx);

        // initialize imageview
        ImageView iv = (ImageView)view.findViewById(R.id.imageView);

        // set image
        iv.setImageResource(R.drawable.white);
        if (row_idx == curr_pos[0] && col_idx == curr_pos[1]) { // plot user image
            Bitmap image = BitmapFactory.decodeResource(mContext.getResources(), R.drawable.user);
            Matrix matrix = new Matrix();
            matrix.preRotate(rotation * 90 + 90);
            Bitmap rotated = Bitmap.createBitmap(
                    image, 0, 0,
                    image.getWidth(),
                    image.getHeight(),
                    matrix,
                    true
            );
            iv.setImageBitmap(rotated);
        } else if (row_idx == hint_pos[0] && col_idx == hint_pos[1] && plot_hint) { // plot hint image
            iv.setImageResource(R.drawable.hint);
        } else if (row_idx == goal_pos[0] && col_idx == goal_pos[1]) {
            iv.setImageResource(R.drawable.goal);
        }

        if (hint_pos[0] == curr_pos[0] && hint_pos[1] == curr_pos[1] && plot_hint) {
            plot_hint = false;
        }

        // set margin and size of imageview to draw wall
        int image_height = 0;
        int image_width = 0;
        int wall_left = 0;
        int wall_up = 0;
        int wall_down = 0;
        int wall_right = 0;
        for (int f = 3; f >= 0; f--) {
            if (val / Math.pow(2, f) >= 1) {
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
            val %= Math.pow(2, f);
        }

        image_height = grid_size_px - wall_down - wall_up;
        image_width = grid_size_px - wall_left - wall_right;

        ViewGroup.MarginLayoutParams marginLayoutParams = (ViewGroup.MarginLayoutParams)iv.getLayoutParams();
        marginLayoutParams.setMargins(wall_left, wall_up, wall_right, wall_down);
        iv.getLayoutParams().height = image_height;
        iv.getLayoutParams().width  = image_width;
        return view;
    }
}
