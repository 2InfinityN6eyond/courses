package edu.skku.cs.pa1;

import android.content.Context;
import android.graphics.Color;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.ArrayList;

public class WordAdapter extends BaseAdapter {
    Context mContext = null;

    int tcolor1, tcolor2, tcolor3;
    int bcolor1, bcolor2, bcolor3;
    ArrayList<char[]> words;         // holds input words
    ArrayList<int[]> bcolors;   // holds background color of letters of input words
    ArrayList<int[]> tcolors;   // holds text color of letter of input wordds

    LayoutInflater mLayoutInflater = null;

    WordAdapter(
            Context context,
            int tcolor1_, int tcolor2_, int tcolor3_,
            int bcolor1_, int bcolor2_, int bcolor3_
    ) {

        words = new ArrayList<>();


        bcolors = new ArrayList<>();
        tcolors = new ArrayList<>();

        mContext = context;
        mLayoutInflater = (LayoutInflater)mContext.getSystemService(
                Context.LAYOUT_INFLATER_SERVICE);
        tcolor1 = tcolor1_;
        tcolor2 = tcolor2_;
        tcolor3 = tcolor3_;
        bcolor1 = bcolor1_;
        bcolor2 = bcolor2_;
        bcolor3 = bcolor3_;
    }

    @Override
    public int getCount() { return words.size(); }

    @Override
    public long getItemId(int position) { return position; }

    @Override
    public char[] getItem(int position) { return words.get(position); }

    @Override
    public View getView(int position, View view, ViewGroup parent) {
        if (view == null) {
            view = mLayoutInflater.inflate(R.layout.wordle_word, parent, false);
        }

        // dirty!

        TextView tv1 = (TextView)view.findViewById(R.id.textView1); // 10000013
        TextView tv2 = (TextView)view.findViewById(R.id.textView2); // 10000002
        TextView tv3 = (TextView)view.findViewById(R.id.textView3);
        TextView tv4 = (TextView)view.findViewById(R.id.textView4);
        TextView tv5 = (TextView)view.findViewById(R.id.textView5);

        // setting char for each textinputs
        tv1.setText(String.valueOf(words.get(position)[0]));
        tv2.setText(String.valueOf(words.get(position)[1]));
        tv3.setText(String.valueOf(words.get(position)[2]));
        tv4.setText(String.valueOf(words.get(position)[3]));
        tv5.setText(String.valueOf(words.get(position)[4]));

        // setting text color for each textinputs
        tv1.setTextColor(tcolors.get(position)[0]);
        tv2.setTextColor(tcolors.get(position)[1]);
        tv3.setTextColor(tcolors.get(position)[2]);
        tv4.setTextColor(tcolors.get(position)[3]);
        tv5.setTextColor(tcolors.get(position)[4]);

        // setting background image for each textinputs
        tv1.setBackgroundColor(bcolors.get(position)[0]);
        tv2.setBackgroundColor(bcolors.get(position)[1]);
        tv3.setBackgroundColor(bcolors.get(position)[2]);
        tv4.setBackgroundColor(bcolors.get(position)[3]);
        tv5.setBackgroundColor(bcolors.get(position)[4]);

        return view;
    }

    public void appendItem(String word, int[] tcolor, int[] bcolor) {
        words.add(word.toCharArray());
        for (int i = 0; i < 5; i++) {
            if        (tcolor[i] == 0) {
                tcolor[i]  = tcolor1;
            } else if (tcolor[i] == 1) {
                tcolor[i]  = tcolor2;
            } else if (tcolor[i] == 2) {
                tcolor[i]  = tcolor3;
            }
            if        (bcolor[i] == 0) {
                bcolor[i]  = bcolor1;
            } else if (bcolor[i] == 1) {
                bcolor[i]  = bcolor2;
            } else if (bcolor[i] == 2) {
                bcolor[i]  = bcolor3;
            }
        }
        tcolors.add(tcolor);
        bcolors.add(bcolor);
    }
}
