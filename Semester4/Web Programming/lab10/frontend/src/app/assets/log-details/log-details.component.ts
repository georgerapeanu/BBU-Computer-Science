import { Component, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { Log } from 'src/app/models/Log';
import { LogsService } from 'src/app/services/logs-service';

@Component({
  selector: 'app-log-details',
  templateUrl: './log-details.component.html',
  styleUrls: ['./log-details.component.css']
})
export class LogDetailsComponent implements OnInit {
  log: Log | null = null;

  constructor(
    private logsService: LogsService,
    private activatedRoute: ActivatedRoute
  ) {

  }

  ngOnInit(): void {
    let id = parseInt(this.activatedRoute.snapshot.paramMap.get("id") || "0");
    this.logsService.getLog(id).subscribe({
      next: (log) => { this.log = log; },
      error: (error) => { alert(error.message); }
    })
  }
}
