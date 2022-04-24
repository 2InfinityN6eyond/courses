package com.skku.cs.pa2;

public class DataModels {

    static class UserName {
        private String username;
        private boolean success;

        public void setUsername(String username) { this.username = username; }
        public String getUserName() {return username;}

        public void setSuccess(boolean success) { this.success = success; }
        public boolean getSuccess() { return success; }

    }

    static class Map {
        private String name;
        private int size;

        public String getName() { return name; }
        public void setName(String name) { this.name = name; }

        public int getSize() { return size; }
        public void setSize(int size) { this.size = size; }
    }

    static class Maze {
        private String maze;

        public String getMaze() { return maze; }
        public void setMaze(String maze) { this.maze = maze; }
    }
}
