package edu.skku.cs.pa1;

import android.content.Context;
import android.graphics.Color;
import android.util.Log;
import android.widget.Toast;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Locale;

public class WordleManager {
    Context mContext;

    Dictionary dictionary;
    String answer;
    HashMap<Character, Integer> answer_lettr_occurances;

    WordAdapter word_adapter;

    LetterAdapter greens, yellows, grays;

    WordleManager(
            Context context,
            Dictionary dictionary_,
            int tcolor1, int tcolor2, int tcolor3,
            int bcolor1, int bcolor2, int bcolor3
    ) {
        answer       = null;
        mContext     = context;
        dictionary   = dictionary_;
        word_adapter = new WordAdapter(
                                context,
                                tcolor1, tcolor2, tcolor3,
                                bcolor1, bcolor2, bcolor3
                            );
        greens       = new LetterAdapter(context, tcolor1, bcolor1);
        yellows      = new LetterAdapter(context, tcolor2, bcolor2);
        grays        = new LetterAdapter(context, tcolor3, bcolor3);
    }

    public boolean tryOut(String word) {
        if (!dictionary.is_ready) {
            return false;
        }
        if (answer == null) {
            answer = dictionary.sampleWord().toUpperCase(Locale.ROOT);
            Log.d("answer", answer);
        }
        if (dictionary.isInDictionary((word.toLowerCase(Locale.ROOT)))) {
            handleNewInput(word);
            return true;
        } else {
            // toast message
            Toast.makeText(
                    mContext,
                    "Word '" + word + "' not in dictionary!",
                    Toast.LENGTH_SHORT
            ).show();
            return false;
        }
    }

    protected void handleNewInput(String word) {
        word = word.toUpperCase(Locale.ROOT);

        ArrayList<Character> letter1 = new ArrayList<>();
        ArrayList<Character> letter2 = new ArrayList<>();
        ArrayList<Character> letter3 = new ArrayList<>();

        char curr;
        answer_lettr_occurances = new HashMap<Character, Integer>();
        for (int i = 0; i < 5; i ++) {
            curr = answer.charAt(i);
            answer_lettr_occurances.put(
                    curr,
                    (answer_lettr_occurances.containsKey(curr) ?
                            answer_lettr_occurances.get(curr) : 0) + 1
            );
        }

        int[] bcolors = new int[5];
        int[] tcolors = new int[5];
        for (int i = 0; i < 5; i++) {
            curr = word.charAt(i);
            if (curr == answer.charAt(i)) { // correct -> green
                bcolors[i] = 0; // word_adapter interpret 0 to be "correct" color
                tcolors[i] = 0;
                answer_lettr_occurances.put(
                        curr,
                        answer_lettr_occurances.get(curr) - 1
                );
                letter1.add(new Character(curr));
            } else if (answer.indexOf(curr) < 0) { // wrong -> gray
                bcolors[i] = 2;
                tcolors[i] = 2;
                letter3.add(new Character(curr));
            } else { // potentially yellow or gray
                bcolors[i] = -1; // keep value
            }
        }
        for (int i = 0; i < 5; i ++) {
            if (bcolors[i] == -1) {
                if (answer_lettr_occurances.get(word.charAt(i)) > 0) {
                    bcolors[i] = 1;
                    tcolors[i] = 1;
                    answer_lettr_occurances.put(
                            word.charAt(i),
                            answer_lettr_occurances.get(word.charAt(i)) - 1
                    );
                    letter2.add(new Character((word.charAt(i))));
                } else {
                    bcolors[i] = 2;
                    tcolors[i] = 2;
                    letter3.add(new Character(word.charAt(i)));
                }
            }
        }

        word_adapter.appendItem(word, tcolors, bcolors);
        word_adapter.notifyDataSetChanged();

        greens.addLetter(letter1);
        grays.addLetter(letter3);
        yellows.addLetter(letter2);
        yellows.deleteLetter(greens.letters);

        greens.notifyDataSetChanged();
        grays.notifyDataSetChanged();
        yellows.notifyDataSetChanged();

    }

    public void clearGame() {
        answer = dictionary.sampleWord();
    }
}
