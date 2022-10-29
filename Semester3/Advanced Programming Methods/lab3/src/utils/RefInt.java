package utils;

// Wrapper for int in order to pass it by reference
public class RefInt {
    int value;

    public RefInt() {
        this.value = 0;
    }

    public RefInt(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public void increase(int delta) {
        this.value += delta;
    }
}
