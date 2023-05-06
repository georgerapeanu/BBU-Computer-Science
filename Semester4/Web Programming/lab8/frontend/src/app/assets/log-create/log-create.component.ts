import { Component } from '@angular/core';
import { FormBuilder } from '@angular/forms';
import { LogsService } from 'src/app/services/logs-service';
import { Validators } from '@angular/forms';
import { Router } from '@angular/router';
import { Location } from '@angular/common';
import { Log } from 'src/app/models/Log';

@Component({
  selector: 'app-log-create',
  templateUrl: './log-create.component.html',
  styleUrls: ['./log-create.component.css']
})
export class LogCreateComponent {

  createForm = this.fb.group({
    severity: ['', Validators.required],
    logDate: ['2023-10-01', [Validators.required]],
    user: ['', Validators.required],
    data: ['', Validators.required]
  });

  constructor(
    private fb: FormBuilder,
    private logsService: LogsService,
    private router: Router,
    private location: Location
  ) {

  }

  submit() {
    if (this.createForm.valid) {
      let log = (this.createForm.value as Log);
      this.logsService.addLog(log).subscribe({
        next: (value) => { this.location.back(); },
        error: (error) => { alert(error.message); }
      })
    }
  }

  goBack() {
    this.location.back();
  }
}
