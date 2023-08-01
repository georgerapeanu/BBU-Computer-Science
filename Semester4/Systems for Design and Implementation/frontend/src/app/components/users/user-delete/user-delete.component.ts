import { Component } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { UserService } from 'src/app/services/user-service';
import { Location } from '@angular/common';

@Component({
  selector: 'app-user-delete',
  templateUrl: './user-delete.component.html',
  styleUrls: ['./user-delete.component.css']
})
export class UserDeleteComponent {
  userHandle: string = "";
  serverResponse: String|null = null;
  constructor(
    private route: ActivatedRoute,
    private userService: UserService,
    private location: Location,
    private router: Router
  ) {}

  ngOnInit(): void {
    let userHandleString: string | null = this.route.snapshot.paramMap.get('id');
    if(userHandleString == null) {
      return;
    }
    this.userHandle = userHandleString;
  }

  goBack(): void {
    this.location.back();
  }

  goToUsers(): void {
    this.router.navigate(["/users"]);
  }

  deleteUser(): void {
    this.userService.deleteUser(this.userHandle).subscribe({
      next: response => {
        this.serverResponse="Operation was succesful!";
      },
      error: error => {
        this.serverResponse="An error occured!";
      }
    });
  }
}
