package com.skku.cs.pa2_unit_tester;

import android.util.Log;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;

class State implements Comparable<State> {
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

    @Override
    public int compareTo(State state) {
        return (this.f + this.g) - (state.f + state.g);
    }
}

class StateComparator implements Comparator<State> {
    @Override
    public int compare(State state, State t1) {
        int h1 = state.f + state.g;
        int h2 = t1.f + t1.g;

        if (h1 > h2) {
            return 1;
        } else if (h1 < h2) {
            return -1;
        } else {
            return 0;
        }
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

    public State showHint() {
        if (!hint_used) {
            //hint_used = true;
            return findHint(curr_state);
        }
        return new State(new int[]{-1, -1}, new int[]{-1, -1}, 0, 0);
    }

    int Move(int direction) {
        if (isMovable(curr_state, direction)) {
            State new_stete = getNewState(curr_state, direction);

            curr_state = new_stete;
            turn_count += 1;
            moved = true;
        } else {
            moved = false;
        }
        return turn_count;
    }

    boolean isMovable(State curr_state, int direction) {
        int val = data.get(curr_state.curr_pos[0]).get(curr_state.curr_pos[1]);
        for (int i = 3; i >= 0; i--) {
            if (direction == Math.pow(2, i) * (val / (int)Math.pow(2, i))) {
                return false;
            }
            val %= Math.pow(2, i);
        }
        return true;
    }

    private boolean isVisited(ArrayList<State> visited, State node) {
        //Log.d("comparing..........",
        //        String.valueOf(node.curr_pos[0]) + "," + String.valueOf(node.curr_pos[1]));
        for (int i = 0; i < visited.size(); i++) {
            if (
                    visited.get(i).curr_pos[0] == node.curr_pos[0]
                    && visited.get(i).curr_pos[1] == node.curr_pos[1]
            ) {
                //Log.d("has boon visited", "");
                return true;
            }
        }
        //Log.d("not visited yet", "");
        return false;
    }

    public State findHint(State curr_state) {
        ArrayList<State> visited = new ArrayList<>();
        ArrayList<State> not_visited = new ArrayList<>();
        not_visited.add(new State(
                new int[]{curr_state.curr_pos[0], curr_state.curr_pos[1]},
                new int[]{curr_state.curr_pos[0], curr_state.curr_pos[1]},
                0,
                2 * (size - 1) - curr_state.prev_pos[0] - curr_state.curr_pos[1]
        ));
        while (true) {
            if (not_visited.isEmpty()) {
                break;
            }
            Collections.sort(not_visited);

            State node = not_visited.remove(0);
            visited.add(node);

            if (node.curr_pos[0] == size - 1 && node.curr_pos[1] == size - 1) {
                break;
            }
            for (int i = 0; i <= 3; i++) {
                int direction = (int) Math.pow(2, i);

                if (isMovable(node, direction)) {
                    State new_state = getNewState(node, direction);

                    if (!isVisited(visited, new_state)) {
                        not_visited.add(new_state);
                    }
                }
            }
        }

        Log.d("=================", "visited:");
        for (int i = 0; i < visited.size(); i++) {
            State n = visited.get(i);
            Log.d(
                    "(" + String.valueOf(n.curr_pos[0]) + "," + String.valueOf(n.curr_pos[1]) + ")",
                    "(" + String.valueOf(n.prev_pos[0]) + "," + String.valueOf(n.prev_pos[1]) + ")"
            );
        }

        // now path is in visited
        State curr = new State(new int[]{-1, -1}, new int[]{-1, -1}, 1, 1);


        Log.d("--------------------------------------", "-----------");
        for (int i = 0; i < visited.size(); i++) {
            State node_ = visited.get(i);
            if (
                    node_.curr_pos[0] == size - 1
                    && node_.curr_pos[1] == size - 1
            ) {
                curr = node_;
                Log.d(
                        "found goal state",
                        String.valueOf(curr.curr_pos[0]) + "," + String.valueOf(curr.curr_pos[1]));
                break;
            }
        }

        for (int i = 0; i < size * size; i++) {
            if (
                    curr.curr_pos[0] == curr_state.curr_pos[0]
                    && curr.curr_pos[1] == curr_state.curr_pos[1]
            ) {
                break;
            }

            for (int j = 0; j < visited.size(); j++) {
                State node_ = visited.get(j);
                if (
                        node_.curr_pos[0] == curr.prev_pos[0]
                        && node_.curr_pos[1] == curr.prev_pos[1]
                ) {
                    Log.d(
                            "=======",
                            "(" + String.valueOf(curr.curr_pos[0])
                            + "," + String.valueOf((curr.curr_pos[1])) + ")"
                            + "->" + "(" + String.valueOf(node_.curr_pos[0])
                                    + "," + String.valueOf((node_.curr_pos[1])) + ")"
                    );
                    curr = node_;

                    Log.d("new curr",
                            "(" + String.valueOf(curr.curr_pos[0]) + "," +
                            String.valueOf(curr.curr_pos[1]));

                    continue;
                }
            }
        }

        Log.d("target",
                String.valueOf(curr.curr_pos[0]) + "," + String.valueOf(curr.curr_pos[1]));

        return curr;

    }

    State getNewState(State curr_state, int direction) {
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
