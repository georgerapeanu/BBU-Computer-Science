package model;

public class Book extends Entity {

    private int pages;
    private String title;

    public Book(int pages, String title) {
        this.pages = pages;
        this.title = title;
    }

    @Override
    public String toString() {
        return "Book{" + "pages=" + pages + ", title='" + title + '\'' + ", weight=" + weight + '}';
    }
}
