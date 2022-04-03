/*package edu.skku.cs.pa1;

import android.widget.TextView;

import java.util.ArrayList;

public class AlphabetCard extends TextView {
    String alphabet_;
    int text_color_;
    int background_color_;

    AlphabetCard()

    public void setValues(
            char alphabet,
            int text_color,
            int background_color
    ) {
        setText(String.valueOf(alphabet));
        setTextColor(text_color);
        setBackgroundColor(background_color);
    }
}

class AlphabetCardLine {
    ArrayList<AlphabetCard> cards;

    AlphabetCardLine(
            int[] alphabet_card_view_ids,
            char[] word,
            int[] tcolors,
            int[] bcolors,
            int len
    ) {
        for (int i = 0; i < len; i++) {
            cards.add(new AlphabetCard(word[i], tcolors[i], bcolors[i]));
        }
    }
}*/