import { Component } from '@angular/core';
import { LogsService } from 'src/app/services/logs-service';
import { ActivatedRoute, Router } from '@angular/router';
import { Location } from '@angular/common';

@Component({
  selector: 'app-log-delete',
  templateUrl: './log-delete.component.html',
  styleUrls: ['./log-delete.component.css']
})
export class LogDeleteComponent {
  id: number = 0;
  constructor(
    private logsService: LogsService,
    private activatedRoute: ActivatedRoute,
    private router: Router,
    private location: Location
  ) {

  }

  ngOnInit(): void {
    this.id = parseInt(this.activatedRoute.snapshot.paramMap.get("id") || "0");
  }

  submit(): void {
    this.logsService.deleteLog(this.id).subscribe({
      next: () => {this.router.navigate(['/']);},
      error: (error) => {alert(error.message);}
    });
  }

  goBack(): void {
    this.location.back();
  }
}
