namespace lab10.Models;

public class Log
{
    public int id { get; set; }
    public String severity { get; set; }
    public DateTime logDate { get; set; }
    public String user { get; set; }
    public String data { get; set; }

    public Log()
    {
        id = 0;
        severity = "";
        logDate = new DateTime();
        user = "";
        data = "";
    }
}
