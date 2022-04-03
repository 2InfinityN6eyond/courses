package edu.skku.cs.pa1;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.ArrayList;

public class LetterAdapter extends BaseAdapter {
    Context mContext;
    LayoutInflater mLayoutInflater;
    ArrayList<Character> letters;
    int tcolor, bcolor;

    LetterAdapter(Context context, int tcolor_, int bcolor_) {
        mContext = context;
        mLayoutInflater = (LayoutInflater)mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        tcolor = tcolor_;
        bcolor = bcolor_;

        letters = new ArrayList<>();
    }

    @Override
    public int getCount() {
        return letters.size();
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public Character getItem(int position) {
        return letters.get(position);
    }

    @Override
    public View getView(int position, View view, ViewGroup parent) {
        if (view == null) {
            view = mLayoutInflater.inflate(R.layout.wordle_letter, parent, false);
        }

        TextView tv = (TextView)view.findViewById(R.id.textView);
        tv.setText(String.valueOf(letters.get(position)));
        tv.setTextColor(tcolor);
        tv.setBackgroundColor(bcolor);
        return view;
    }

    public void addLetter(ArrayList<Character> letter) {
        letter.forEach((ch) -> {
            if (!letters.contains(ch)) {
                letters.add(ch);
            }
        });
    }

    public void deleteLetter(ArrayList<Character> letter) {
        letter.forEach((ch) -> {
            if (letters.contains(ch)) {
                letters.remove(ch);
            }
        });
    }
}
