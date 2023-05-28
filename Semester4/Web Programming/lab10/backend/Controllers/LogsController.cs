// for future reference https://stackoverflow.com/questions/69211933/error-405-not-allowed-on-httppost-in-asp-net-core-3-1-web-api
using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using lab10.Models;
using lab10.Repository;
using Microsoft.EntityFrameworkCore;

namespace lab10.Controllers;

public class LogsController : Controller
{
    private readonly ILogger<HomeController> _logger;
    private readonly LogsRepository _logsRepository;

    public LogsController(ILogger<HomeController> logger, LogsRepository logsRepository)
    {
        _logger = logger;
        _logsRepository = logsRepository;
    }

    [HttpGet]
    public IActionResult Index(int? id)
    {

        int start_id = Int32.Parse(Request.Query["start_id"].FirstOrDefault() ?? "0");
        string user_search = (Request.Query["user"].FirstOrDefault() ?? "");
        string severity_search = (Request.Query["severity"].FirstOrDefault() ?? "");

        if (id != null)
        {
            var log = _logsRepository.Logs.Where(e => e.id.Equals(id)).Single<Log>();
            return Json(log);
        }
        else
        {
            var logs = _logsRepository.Logs.Where(e => e.user.Contains(user_search))
            .Where(e => e.severity.Contains(severity_search))
            .Skip(start_id)
            .Take(4);
            return Json(logs);
        }
    }

    [HttpPost]
    public IActionResult Index([FromBody] Log log)
    {
        _logsRepository.Add(log);
        _logsRepository.SaveChanges();
        return Ok();
    }

    [HttpPut]
    [ActionName("Index")]
    public IActionResult UpdateIndex([FromBody] Log edit_log)
    {
        Log? log = _logsRepository.Find<Log>(edit_log.id);

        if (log == null)
        {
            return BadRequest();
        }

        log.data = edit_log.data;
        log.logDate = edit_log.logDate;
        log.severity = edit_log.severity;
        log.user = edit_log.severity;

        _logsRepository.SaveChanges();
        return Ok();
    }

    [HttpDelete]
    public IActionResult Index(int id)
    {
        Log? log = _logsRepository.Find<Log>(id);

        if (log == null)
        {
            return BadRequest();
        }
        _logsRepository.Remove<Log>(log);
        _logsRepository.SaveChanges();
        return Ok();
    }

    public IActionResult Privacy()
    {
        return View();
    }

    [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
    public IActionResult Error()
    {
        return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
    }
}
