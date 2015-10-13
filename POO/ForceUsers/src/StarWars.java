

class ForceUser <M extends ForceUser> {
    private String name;
    private int midiChloriens;

    private M master;

    ForceUser(String name, int midiChloriens, M master) {
        this.name = name;
        this.midiChloriens = midiChloriens;
        this.master = master;
    }

    ForceUser(String name, int midiChloriens) {
        this(name, midiChloriens, null);
    }

    public int getMidiChloriens() {
        return midiChloriens;
    }

    public String getName() {
        return name;
    }

    public String saberColor() {
        return "???";
    }

    public String toString() {
        return name + ", master: " + (master == null ? "none" : master.getName()) + ", " + midiChloriens + " mc, saber: " + saberColor();
    }
}

class Jedi extends ForceUser<Jedi> {
    private String saberColor = "green";

    Jedi(String name, int midiChloriens, Jedi master, String saberColor) {
        super(name, midiChloriens, master);
        this.saberColor = saberColor;
    }

    Jedi(String name, int midiChloriens, Jedi master) {
        super(name, midiChloriens, master);
    }

    Jedi(String name, int midiChloriens, String saberColor) {
        super(name, midiChloriens);
        this.saberColor = saberColor;
    }

    Jedi(String name, int midiChloriens) {
        super(name, midiChloriens);
    }

    public String saberColor() {
        return saberColor;
    }

    public String toString() { return "Jedi " + super.toString(); }
}

class Sith extends ForceUser<Sith> {
    public String saberColor() { return "red"; }
    public String toString() { return "Sith " + super.toString(); }

    Sith(String name, int midiChloriens, Sith master) { super(name, midiChloriens, master); }
    Sith(String name, int midiChloriens) { super(name, midiChloriens); }

    public Sith corrupt(Jedi j, String sithName) {
        return new Sith(sithName, j.getMidiChloriens(), this);
    }
}


public class StarWars {
    public static void main(String... args) {
        Jedi yoda = new Jedi("Yoda", 12000000);
        Sith sidious = new Sith("Darth Sidious", 1300);
        Jedi luke = new Jedi("Luke", 2500, yoda, "blue");
        Jedi obiWan = new Jedi("Obi-Wan", 1900, yoda);
        Jedi anakin = new Jedi("Anakin", 2400, obiWan);
        Sith vader = sidious.corrupt(anakin, "Dath Vader");

        ForceUser[] users = { yoda, sidious, luke, obiWan, anakin, vader };

        for (ForceUser u : users) {
            System.out.println(u);
        }
    }
}
