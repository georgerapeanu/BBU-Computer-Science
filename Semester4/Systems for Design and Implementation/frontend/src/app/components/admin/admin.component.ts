import { Component } from '@angular/core';
import { AdminService } from 'src/app/services/admin.service';

@Component({
  selector: 'app-admin',
  templateUrl: './admin.component.html',
  styleUrls: ['./admin.component.css']
})
export class AdminComponent {
  constructor(
    private adminService: AdminService
  ) {}

  dropDatabase() {
    this.adminService.dropDatabase().subscribe(() => {
      alert("Database has been dropped");
    });
  }

  recreateDatabase() {
    this.adminService.recreateDatabase().subscribe(() => {
      alert("Database has been recreated");
    }); 
  }
}
