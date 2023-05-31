import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormGroup } from '@angular/forms';
import { BehaviorSubject, Observable, combineLatest, debounceTime, distinct, distinctUntilChanged, switchMap } from 'rxjs';
import { Log } from 'src/app/models/Log';
import { LogsService } from 'src/app/services/logs-service';
import { Validators } from '@angular/forms';

@Component({
  selector: 'app-logs-overview',
  templateUrl: './logs-overview.component.html',
  styleUrls: ['./logs-overview.component.css']
})
export class LogsOverviewComponent {
  logs: Array<Log> = [];
  pageNumber: number = 0;
  user: string = "";
  severity: string = "";
  state: BehaviorSubject<{ pageNumber: number, user: string, severity: string }> = new BehaviorSubject({
    pageNumber: this.pageNumber,
    user: this.user,
    severity: this.severity
  });

  constructor(
    private logsService: LogsService,
  ) {
    this.state.asObservable().pipe(
      debounceTime(300),
      distinctUntilChanged(),
      switchMap(state => {
        return this.logsService.getLogsForPage(state.user, state.pageNumber * 4, state.severity);
      })
    ).subscribe({
      next: (logs) => { this.logs = logs; },
      error: (error) => { alert(error.message); }
    });
  }

  stateUpdate(): void {
    this.state.next({
      pageNumber: this.pageNumber,
      user: this.user,
      severity: this.severity
    });
  }

  setPageNumber(pageNumber: number): void {
    this.pageNumber = Math.max(pageNumber, 0);
    this.stateUpdate();
  }
}
