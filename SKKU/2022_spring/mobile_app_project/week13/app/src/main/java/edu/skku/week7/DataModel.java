package edu.skku.week7;

import android.provider.ContactsContract;

public class DataModel {
    private String Title;
    private String Year;
    private String Released;
    private String Runtime;
    private String Director;
    private String Genre;
    private String imdbRating;
    private String Metascore;

    public String getTitle() {
        return Title;
    }

    public void setTitle(String title) {
        Title = title;
    }

    public String getYear() {
        return Year;
    }

    public void setYear(String year) {
        Year = year;
    }

    public String getReleased() {
        return Released;
    }

    public void setReleased(String released) {
        Released = released;
    }

    public String getRuntime() {
        return Runtime;
    }

    public void setRuntime(String runtime) {
        Runtime = runtime;
    }

    public String getDirector() {
        return Director;
    }

    public void setDirector(String director) {
        Director = director;
    }

    public String getGenre() {
        return Genre;
    }

    public void setGenre(String genre) {
        Genre = genre;
    }

    public String getImdbRating() {
        return imdbRating;
    }

    public void setImdbRating(String imdbRating) {
        this.imdbRating = imdbRating;
    }

    public String getMetascore() {
        return Metascore;
    }

    public void setMetascore(String metascore) {
        Metascore = metascore;
    }

    static class User {
        private String user;
        private String region;

        public void setUser(String user) {this.user = user; }
        public  String getUser() {return user;}
        public void setRegion(String region) { this.region = region; }
        public String getRegion() {return region; }
    }

    static class WeatherResponse {
        public DataModel.Location location;
        public DataModel.Current current;
    }

    static class Location {
        public String name;
    }

    static class Current {
        public String temperature;
        public String humidity;
        public String[] weather_descriptions;
    }

}


