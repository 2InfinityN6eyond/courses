package com.skku.cs.pa2_unit_tester;

import android.util.Log;

import java.util.ArrayList;
import java.util.Arrays;

public class Maze {
    public int size;
    public ArrayList<ArrayList<Integer>> data = new ArrayList<>(size);

    private ArrayList<int[]> visited = new ArrayList<>(Arrays.asList(new int[] {0, 0, 0, 0}));

    private int turn_count = 0;

    private boolean hint_used = false;
    public int[] current_pos = {0, 0};

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

    void Move(int direction) {
        Log.d("move", String.valueOf(direction));
        Log.d(
                String.valueOf(data.get(current_pos[0]).get(current_pos[1])),
                String.valueOf(isMovable(direction))
        );
        if (isMovable(direction)) {
            if (direction == 1) {
                visited.add(new int[]{
                        current_pos[0],
                        current_pos[1] + 1,
                        current_pos[0],
                        current_pos[1]
                });
                current_pos[1] += 1;
            } else if (direction == 2) {
                visited.add(new int[]{
                        current_pos[0] + 1,
                        current_pos[1],
                        current_pos[0],
                        current_pos[1]
                });
                current_pos[0] += 1;
            } else if (direction == 4) {
                visited.add(new int[]{
                        current_pos[0],
                        current_pos[1] - 1,
                        current_pos[0],
                        current_pos[1]
                });
                current_pos[1] -= 1;
            } else if (direction == 8) {
                visited.add(new int[]{
                        current_pos[0] - 1,
                        current_pos[1],
                        current_pos[0],
                        current_pos[1]
                });
                current_pos[0] -= 1;
            }
        }
    }

    boolean isMovable(int direction) {
        int val = data.get(current_pos[0]).get(current_pos[1]);
        for (int i = 3; i >= 0; i--) {
            if (direction == Math.pow(2, i) * (val / Math.pow(2, i))) {
                return true;
            }
            val %= Math.pow(2, i);
        }
        return false;
    }

    void printMaze() {
        Log.d("size", String.valueOf(size));
        for (int i = 0; i < size; i++) {
            String row = "";
            for (int j = 0; j < size; j++) {
                row += String.valueOf(data.get(i).get(j));
                row += " ";
            }
            Log.d(String.valueOf(i), row);
        }
    }
}