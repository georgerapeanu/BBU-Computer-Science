import { Location } from '@angular/common';
import { Component, OnInit } from '@angular/core';
import { FormBuilder } from '@angular/forms';
import { LogsService } from 'src/app/services/logs-service';
import { Validators } from '@angular/forms';
import { Log } from 'src/app/models/Log';
import { ActivatedRoute } from '@angular/router';

@Component({
  selector: 'app-log-edit',
  templateUrl: './log-edit.component.html',
  styleUrls: ['./log-edit.component.css']
})
export class LogEditComponent implements OnInit {
  editForm = this.fb.group({
    id: [0, Validators.required],
    severity: ['', Validators.required],
    logDate: ['2023-10-01', [Validators.required]],
    user: ['', Validators.required],
    data: ['', Validators.required]
  });
  id: number = 0;

  constructor(
    private logsService: LogsService,
    private location: Location,
    private fb: FormBuilder,
    private activatedRoute: ActivatedRoute
  ) {

  }

  ngOnInit(): void {
    this.id = parseInt(this.activatedRoute.snapshot.paramMap.get("id") || "0");
    this.logsService.getLog(this.id).subscribe({
      next: (log) => {
        this.editForm.setValue(log);
      }
    })
  }

  submit() {
    if (this.editForm.valid) {
      let log = (this.editForm.value as Log);
      this.logsService.editLog(log).subscribe({
        next: (value) => { this.location.back(); },
        error: (error) => { alert(error.message); }
      })
    }
  }

  goBack() {
    this.location.back();
  }
}
