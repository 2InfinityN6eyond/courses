package com.skku.cs.pa2_unit_tester;

import android.util.Log;

import java.util.ArrayList;
import java.util.Arrays;

class State {
    public int[] curr_pos;
    public int[] prev_pos;

    public int f;
    public int g;

    State(int[] curr_pos, int[] prev_pos, int f, int g){

        this.curr_pos = new int[]{curr_pos[0], curr_pos[1]};
        this.prev_pos = new int[]{prev_pos[0], prev_pos[1]};
        this.f = f;
        this.g = g;
    }
}

public class Maze {

    public int size;
    public ArrayList<ArrayList<Integer>> data = new ArrayList<>(size);

    State curr_state;
    private int turn_count;
    private boolean hint_used;
    public boolean moved;

    Maze() {
        turn_count = 0;
        curr_state = new State(new int[]{0, 0}, new int[]{0, 0}, 0, 0);
        hint_used = false;
        moved = false;
    }

    public void setData(String data_) {
        String[] rows = data_.split("\n");

        size = rows.length - 1;

        for (int i = 1; i <= size; i++) {
            ArrayList<Integer> row = new ArrayList<>();
            String[] vals = rows[i].split(" ");
            for (int j = 0; j < size; j++) {
                row.add(Integer.valueOf(vals[j]));
            }
            data.add(row);
        }
    }

    void showHint() {
        if (!hint_used) {
            Log.d("show", "hint");

            hint_used = true;
        }
    }

    int Move(int direction) {
        if (isMovable(direction)) {
            State new_stete = getNewState(direction);

            curr_state = new_stete;
            turn_count += 1;
            moved = true;
        } else {
            moved = false;
        }
        return turn_count;
    }

    boolean isMovable(int direction) {
        int val = data.get(curr_state.curr_pos[0]).get(curr_state.curr_pos[1]);
        for (int i = 3; i >= 0; i--) {
            if (direction == Math.pow(2, i) * (val / (int)Math.pow(2, i))) {
                return false;
            }
            val %= Math.pow(2, i);
        }
        return true;
    }

    State getNewState(int direction) {
        State new_tate = curr_state;
        if (direction == 1) { // move right
            new_tate = new State(
                    new int[]{curr_state.curr_pos[0], curr_state.curr_pos[1] + 1},
                    curr_state.curr_pos,
                    curr_state.f + 1,
                    curr_state.g - 1
            );
        } else if (direction == 2) { // move down
            new_tate = new State(
                    new int[]{curr_state.curr_pos[0] + 1, curr_state.curr_pos[1]},
                    curr_state.curr_pos,
                    curr_state.f + 1,
                    curr_state.g - 1
            );
        } else if (direction == 4) { // move left
            new_tate = new State(
                    new int[]{curr_state.curr_pos[0], curr_state.curr_pos[1] - 1},
                    curr_state.curr_pos,
                    curr_state.f + 1,
                    curr_state.g + 1
            );
        } else if (direction == 8) { // move up
            new_tate = new State(
                    new int[]{curr_state.curr_pos[0] - 1, curr_state.curr_pos[1]},
                    curr_state.curr_pos,
                    curr_state.f + 1,
                    curr_state.g + 1
            );
        }
        return new_tate;
    }

}
